#include "catalog.h"
#include "query.h"
#include "index.h"

/*
 * Inserts a record into the specified relation
 *
 * Returns:
 * 	OK on success
 * 	an error code otherwise
 */

Status Updates::Insert(const string& relation,      // Name of the relation
                       const int attrCnt,           // Number of attributes specified in INSERT statement
                       const attrInfo attrList[])   // Value of attributes specified in INSERT statement
{
    /* Your solution goes here */

    //Get the attrLen for each element in attrList[]
    //And reorder all the elements into the new array: attrInfo insertAttrList[]
    int attrNum;
    int totalSizeinBytes = 0;
    AttrDesc *attrs = new AttrDesc[attrCnt];
    attrCat->getRelInfo(relation, attrNum, attrs);
    attrInfo *insertAttrList = new attrInfo[attrCnt];
    for(int i = 0; i < attrCnt; i++)
    {
    	char attrName[MAXNAME];
    	strcpy(attrName, attrs[i].attrName);
    	for(int j = 0; j < attrCnt; j++)
    	{
    		if(strcmp(attrName, attrList[j]) == 0)
    		{
    			insertAttrList[i] = attrList[j];
    			insertAttrList[i].attrLen = attrs[i].attrLen;
    			totalSizeinBytes += attrs[i].attrLen;
    			break;
    		}
    	}
    }

    

    return OK;
}
