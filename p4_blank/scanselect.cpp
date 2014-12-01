#include "catalog.h"
#include "query.h"
#include "index.h"

/* 
 * A simple scan select using a heap file scan
 */

Status Operators::ScanSelect(const string& result,       // Name of the output relation
                             const int projCnt,          // Number of attributes in the projection
                             const AttrDesc projNames[], // Projection list (as AttrDesc)
                             const AttrDesc* attrDesc,   // Attribute in the selection predicate
                             const Operator op,          // Predicate operator
                             const void* attrValue,      // Pointer to the literal value in the predicate
                             const int reclen)           // Length of a tuple in the result relation
{
  cout << "Algorithm: File Scan" << endl;
  
  /* Your solution goes here */
  
  Status status;
  //Open the output heapfile
  HeapFile output(result, status);
  if(status != OK)
  	return status;

  Record record;
  record.length = 0;

  //Open the relation file scan
  string rName = attrDesc->relName;
  HeapFileScan relFile(rName, status);
  if(status != OK)
  	return status;
  char* filter = attrValue;
  int offset = attrDesc->attrOffset;
  Datatype type = attrDesc->attrType;
  int length = attrDesc->attrLen;
  status = startScan();


  return OK;
}
