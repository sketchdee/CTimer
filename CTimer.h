#pragma once
#include <iostream>
#include "stdlib.h"
#include "string.h"
#include<ctime>
#ifdef _UNIX
#include "unistd.h"
#endif
#ifndef _UNIX
#ifdef linux
#include "unistd.h"
#endif
#endif

#ifdef _WINDOWS
#include "windows.h"
#define sleep Sleep
#endif

class CTimer {
public:
	CTimer(char*cmd,char** time_point, int time_point_len);
	void SetTimePoint(char** timep, int len) { this->time_point = timep; this->timme_point_len = len; }
	void SetCmd(char* cmd) { this->cmd = cmd; }
	void RunTimer();
	bool ExecCmd();

	static void PrintNowTime();
	static void PrintTime(time_t o_time);
	static time_t StrToDatetime(char* str);
	static time_t* ToDatime(char** time_point, int len);
	static char** AddDate(char** time_point, int num);
	static char* AddDate(char* time_point, time_t date);

private:
	char** time_point;
	int timme_point_len;
	char* cmd;
};





// TODO: 在此处引用程序需要的其他标头;。