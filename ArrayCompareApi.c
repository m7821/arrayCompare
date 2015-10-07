#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int meetArrayNum;
  int *meetArray;
} ARRAY_COMPARE_RESULT;

void
recordArrayCompareResult (
  int                   dataStrNum,
  ARRAY_COMPARE_RESULT  *compareResult
  )
{
  ARRAY_COMPARE_RESULT  compareResultTmp = {0};
  int                   index = 0;

  if (compareResult->meetArrayNum == 0) {
    compareResult->meetArrayNum = 1;
    compareResult->meetArray    = calloc (1, sizeof (int));
    compareResult->meetArray[0] = dataStrNum;
  } else {
    compareResultTmp.meetArrayNum = compareResult->meetArrayNum + 1;
    compareResultTmp.meetArray    = calloc (compareResultTmp.meetArrayNum, sizeof (int));
      
    for (index = 0; index < compareResult->meetArrayNum; index++)
      compareResultTmp.meetArray[index] = compareResult->meetArray[index];

    compareResultTmp.meetArray[index] = dataStrNum;

    free (compareResult->meetArray);
    compareResult->meetArrayNum = compareResultTmp.meetArrayNum;
    compareResult->meetArray    = compareResultTmp.meetArray;
  }
}

_Bool
arrayCompare (
  char                  *inputStr,
  char                  **dataBaseStr,
  int                   dataBaseStrNum, 
  ARRAY_COMPARE_RESULT  *compareResult
  )
{
  int inputStrlen = strlen (inputStr);
  int dataBaseStrlen;
  int index = 0;

  for (index = 0; index < dataBaseStrNum; index++) {
    
    dataBaseStrlen = strlen (dataBaseStr[index]);

    if (inputStrlen <= dataBaseStrlen)
      continue;
    
    if (!strncasecmp (inputStr, dataBaseStr[index], dataBaseStrlen))
      recordArrayCompareResult (index, compareResult);
  }

  
}

_Bool
arrayCompareApi (
  char                  *inputStr, 
  char                  **dataBaseStr, 
  int                   dataBaseStrNum, 
  ARRAY_COMPARE_RESULT  *compareResult
  )
{
  int inputStrlen = strlen (inputStr);
  int index = 0;

  for (index = 0; index < inputStrlen; index++) {
    arrayCompare (&inputStr[index], dataBaseStr, dataBaseStrNum, compareResult);
  }

  if (compareResult->meetArrayNum != 0)
    return 1;
  else
    return 0;
}

void main (int argc, char **argv) 
{
  ARRAY_COMPARE_RESULT  compareResult = {0};
  int   index;
  _Bool gotAResult = 0;

  gotAResult = arrayCompareApi ("asdfgcaryyyypeneqasdqwerfcairqwerg", argv, argc, &compareResult);

  for (index = 0; index < compareResult.meetArrayNum; index++)
    printf ("%d ", compareResult.meetArray[index]);

  if (compareResult.meetArray)
    free (compareResult.meetArray);
}

