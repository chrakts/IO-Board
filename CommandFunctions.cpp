/*
 * CommandFunctions.cpp
 *
 * Created: 26.04.2017 14:54:45
 *  Author: a16007
 */
#include "External.h"
#include "CommandFunctions.h"
#include "ComReceiver.h"
#include "CRC_Calc.h"

void jobGotCRCError(Communication *output, char function,char address,char job, void * pMem)
{
	output->sendAnswer(fehler_text[CRC_ERROR],quelle_KNET,function,address,job,false);
}

void jobGetInputStatus(Communication *output, char function,char address,char job, void * pMem)
{
uint8_t status;
  if(  getInputStatus( (uint8_t) address-48,&status ) == true  )
    output->sendAnswerInt(quelle_KNET,function,address,job,status,true);
  else
    output->sendPureAnswer(quelle_KNET,function,address,job,false);
}

void jobSetOutputStatus(Communication *output, char function,char address,char job, void * pMem)
{
  uint8_t *wert =  (uint8_t *)pMem ;
  if(  setOutputStatus( (uint8_t) address-48,wert[0] ) == true  )
    output->sendPureAnswer(quelle_KNET,function,address,job,true);
  else
    output->sendPureAnswer(quelle_KNET,function,address,job,false);
}

void jobSetSecurityKey(Communication *output, char function,char address,char job, void * pMem)
{
uint8_t ret = true;
	if (strcmp((char *)pMem,"Phe6%!kdf?+2aQ")==0)
	{
		SecurityLevel = PRODUCTION;
	}
	else if(strcmp((char *)pMem,"D=&27ane%24dez")==0)
	{
		SecurityLevel = DEVELOPMENT;
	}
	else
	{
		SecurityLevel = CUSTOMER;
		ret = false;
	}
	output->sendAnswerInt(quelle_KNET,function,address,job,SecurityLevel,ret);
}

void jobGetSecurityKey(Communication *output, char function,char address,char job, void * pMem)
{
	output->sendAnswerInt(quelle_KNET,function,address,job,SecurityLevel,true);
}


void jobGetCompilationDate(Communication *output, char function,char address,char job, void * pMem)
{
char temp[20];
	strcpy(temp,Compilation_Date);
	output->sendAnswer(temp,quelle_KNET,function,address,job,true);
}

void jobGetCompilationTime(Communication *output, char function,char address,char job, void * pMem)
{
char temp[20];
	strcpy(temp,Compilation_Time);
	output->sendAnswer(temp,quelle_KNET,function,address,job,true);
}

void jobGetFreeMemory(Communication *output, char function,char address,char job, void * pMem)
{
extern int __heap_start, *__brkval;
int v;

	uint16_t mem = (uint16_t) &v - (__brkval == 0 ? (uint16_t) &__heap_start : (uint16_t) __brkval);
	output->sendAnswerInt(quelle_KNET,function,address,job,mem,true);
}




