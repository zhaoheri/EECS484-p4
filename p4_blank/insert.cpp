#include "catalog.h"
#include "query.h"
#include "index.h"
#include <string.h>
#include <iostream>
#include <stdlib.h>

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

    //For error check: go to piazza @1009
    
    //Get the attrLen for each element in attrList[]
    //And re-order all the elements into the new array: attrInfo insertAttrList[]
    Status status;
    Record record;
    int attrNum;
    record.length = 0;
    AttrDesc *attrs = new AttrDesc[attrCnt];
    status = attrCat->getRelInfo(relation, attrNum, attrs);
    if(status != OK) 
        return status;
    if(attrNum != attrCnt)
    {
        //error
    }

    attrInfo *insertAttrList = new attrInfo[attrCnt];
    for(int i = 0; i < attrCnt; i++)
    { 
    	char attrName[MAXNAME];
    	strcpy(attrName, attrs[i].attrName);
    	for(int j = 0; j < attrCnt; j++)
    	{
    		if(strcmp(attrName, attrList[j].attrName) == 0)
    		{
    			insertAttrList[i] = attrList[j];
    			insertAttrList[i].attrLen = attrs[i].attrLen;
    			record.length += attrs[i].attrLen;
    			break;
    		}
    	}
    }

    //Allocate mem for a record and copy it in void *data
    record.data = malloc(record.length);
    void *temp = record.data;
    for(int i = 0; i < attrNum; i++)
    {
        // cout << *(int *)insertAttrList[i].attrValue << endl;
        temp = attrs[i].attrOffset;
        memcpy(temp, insertAttrList[i].attrValue, insertAttrList[i].attrLen);
    }

    //Insert the record in the heapfile
    Status returnStatus;
    HeapFile heapfile(relation, returnStatus);
    if(returnStatus != OK)
        return returnStatus;
    RID rid;
    status = heapfile.insertRecord(record, rid);
    if(status != OK)
        return status;
    
    //Delete memory
    delete attrs;
    delete insertAttrList;
    free(record.data);

    return OK;
}
