#include "heis.h"


int downList[4] = {0,0,0,0};
int upList[4] = {0,0,0,0};
int cabList[4] = {0,0,0,0};

void setDownList(int etasje, int status) //setter status på gitt etasje
{
  downList[etasje] = status;
};
void setUpList(int etasje, int status)
{
   upList[etasje] = status;
};
void setCabList(int etasje, int status)
{
   cabList[etasje] = status;
};

int getDownList(int etasje) //returnerer status på gitt etasje
{
   return downList[etasje];
};
int getUpList(int etasje)
{
   return upList[etasje];
};
int getCabList(int etasje)
{
   return cabList[etasje];
};