/*
 * CommandFunctions.h
 *
 * Created: 26.04.2017 14:55:18
 *  Author: a16007
 */


#ifndef COMMANDFUNCTIONS_H_
#define COMMANDFUNCTIONS_H_

#include "IO-Board.h"

void jobGotCRCError(Communication *output, char function,char address,char job, void * pMem);
void jobGetInputStatus(Communication *output, char function,char address,char job, void * pMem);
void jobSetOutputStatus(Communication *output, char function,char address,char job, void * pMem);
void jobGetCompilationDate(Communication *output, char function,char address,char job, void * pMem);
void jobGetCompilationTime(Communication *output, char function,char address,char job, void * pMem);
void jobSetSecurityKey(Communication *output, char function,char address,char job, void * pMem);
void jobGetSecurityKey(Communication *output, char function,char address,char job, void * pMem);
void jobGetFreeMemory(Communication *output, char function,char address,char job, void * pMem);

#endif /* COMMANDFUNCTIONS_H_ */
