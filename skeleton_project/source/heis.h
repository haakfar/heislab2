#pragma once


void setDownList(int etasje, int status); //setter status på gitt etasje
void setUpList(int etasje, int status);
void setCabList(int etasje, int status);

int getDownList(int etasje); //returnerer status på gitt etasje
int getUpList(int etasje); 
int getCabList(int etasje);
