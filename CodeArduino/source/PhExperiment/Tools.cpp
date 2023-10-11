#include "Tools.h"

float GetAvgRange(float arr[], int arrSize)
{
  SortArray(arr, arrSize);

  float average = 0.0;
  int cutoffpoint = (int)(arrSize/4);
  for(int i=cutoffpoint; i<arrSize-cutoffpoint; i++)
  {
    average += arr[i];
  }

  return RoundResult((average/(arrSize-2*cutoffpoint)));
}

void SortArray(float arr[], int arrSize)
{
  int i, j;
  for(i=0; i<arrSize; i++)
    for(j=0; j<arrSize-i-1; j++)
      if(arr[j] > arr[j+1])
        Swap(&arr[j], &arr[j+1]);         
}

void Swap(float* xp, float* yp)
{
  float temp = *xp;
  *xp = *yp;
  *yp = temp;
}

float RoundResult(float i)
{
  return ((long)(i*1000.0))/1000.0;
}

void PrintArray(float arr[])
{
  for(int i=0; i<10; i++)
  {
    Serial.print(arr[i]);
    Serial.print(";");
  }
  Serial.println();
}
