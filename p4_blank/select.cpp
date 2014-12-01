#include "catalog.h"
#include "query.h"
#include "index.h"

/*
 * Selects records from the specified relation.
 *
 * Returns:
 * 	OK on success
 * 	an error code otherwise
 */
Status Operators::Select(const string & result,      // name of the output relation
	                 const int projCnt,          // number of attributes in the projection
		         const attrInfo projNames[], // the list of projection attributes
		         const attrInfo *attr,       // attribute used inthe selection predicate 
		         const Operator op,         // predicate operation
		         const void *attrValue)     // literal value in the predicate
{
	//check if there is an index for the selection predicate: attr
	//Get attribute info
	Status status;
	AttrDesc attrdesc;
	string rName = attr->relName;
	string attrName = attr->attrName;
	status = getInfo(rName, attrName, attrdesc);
	if(status != OK)
		return status;

	int reclen = 0;
	string result;
	if(attrdesc.indexed && op == EQ)
		IndexSelect(result, projCnt, projNames, &attrdesc, op, attrValue, reclen);
	else
		ScanSelect(result, projCnt, projNames, &attrdesc, op, attrValue, reclen);

	return OK;
}

