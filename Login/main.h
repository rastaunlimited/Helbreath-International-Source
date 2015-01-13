#ifndef _MAIN_H
#define _MAIN_H
#include "..\\Shared\\common.h"

void 	 SafeCopy(char *c1, char *c2, DWORD lenght = 0);
MMRESULT _StartTimer(DWORD dwTime);
void   	 _StopTimer(MMRESULT timerid);
BOOL   	 IsSame(char *c1, char *c2);
BYTE	 bGetOffsetValue(char * cp, DWORD offset);
WORD	 wGetOffsetValue(char * cp, DWORD offset);
DWORD	 dwGetOffsetValue(char * cp, DWORD offset);
uint64 ullGetOffsetValue(char * cp, DWORD offset);
void 	 PutOffsetValue(char * cp, DWORD offset, BYTE size, uint64 value);
void	 PutLogFileList(char * cStr, char *FileName = NULL);
void	 PutLogList(char * cMsg, BYTE MsgLvl = NULL, BOOL PutOnFile = NULL, char *FileName = NULL);
void	 MakeGoodName(char *dest, char *source);
void	 Delay(DWORD nTimeMs);

#endif