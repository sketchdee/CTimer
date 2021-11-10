#include "CTimer.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
//Summary :For code safety, you need to pass in the lines number of passed into the string array
//Parameters:
//        cmd: Type char*，the command whitch will be executed every times.
//        time_point: Type char**,the time list whitch is CTimer run time point.
//        time_point_len: Type int,the lenth of the string array.
//Return : Constructor.
// 
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
CTimer::CTimer(char* cmd, char** time_point,int time_point_len) {
	this->cmd = cmd;
	this->time_point = time_point;
	this->timme_point_len = time_point_len;
}


bool CTimer::ExecCmd() {
	try {
		system(this->cmd);
	}
	catch (std::exception e) {
		printf(e.what());
	}
	return false;
}

void CTimer::RunTimer() {
	int len = this->timme_point_len;
	char** Datetime_point = 0;
	time_t* time_arry = 0;
	time_t nowtime = 0;
	time_t interval = 0;
	time_t date = 0;
	char* day_str =NULL;
	bool flage = true;
	long long sleep_time = -1;
	while (flage) {
		Datetime_point = AddDate(this->time_point, len);
		time_arry = ToDatime(Datetime_point, len);
		for (int i = 0; i < len; i++)
			delete[] Datetime_point[i];//
		delete[] Datetime_point;
		time(&nowtime);
		interval = -1;
		for (int i = 0; i < len; i++) {
			//PrintTime(time_arry[i]);
			interval = time_arry[i] - nowtime;
			if (interval > 0) {
				sleep_time = interval;
				break;
			}
		}
		delete[] time_arry;
		if (sleep_time == -1) {
			time_t date = nowtime + 86400;
			day_str = AddDate(this->time_point[0], date);
			time_t next_day_time = StrToDatetime(day_str);
			delete day_str;//fix double free
			sleep_time = next_day_time - nowtime;
		}
		if (sleep_time == -1)
			break;
		PrintNowTime();
		printf(" CTimer goes to  sleep for %lld second, and will weak up at ", sleep_time);
		PrintTime(nowtime + sleep_time);
		#ifdef _WINDOWS
		sleep(sleep_time*1000);
		#endif
		#ifndef _WINDOWS
		sleep(sleep_time);
		#endif
		PrintNowTime();
		printf(" CTimer is weak up, execute command: %s\n",this->cmd);
		ExecCmd();
		sleep_time = -1;	
	}
}

void CTimer::PrintNowTime() {
	time_t nowtime;
	time(&nowtime);
	struct tm* timep;
	timep = localtime(&nowtime);
	//从1900开始计年，月份从0开始计到11,%02d为%d不满两位时用零补齐。
	printf("%d年%d月%d日 %02d:%02d:%02d\n", timep->tm_year + 1900, timep->tm_mon + 1, timep->tm_mday, timep->tm_hour, timep->tm_min, timep->tm_sec);
}

void CTimer::PrintTime(time_t o_time) {
	struct tm* timep;
	timep = localtime(&o_time);
	printf("%d年%d月%d日 %02d:%02d:%02d\n", timep->tm_year + 1900, timep->tm_mon + 1, timep->tm_mday, timep->tm_hour, timep->tm_min, timep->tm_sec);
}


//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
//Summary :定义tm结构体，对结构体内的变量进行赋值，包括年月日、时分秒的赋值,
//         年：由于tm结构体存储的是从1900年开始的时间，所以tm_year为int临时变量减去1900,
//         月：由于tm结构体的月份存储范围为0-11，所以tm_mon为int临时变量减去1,
//         时：非夏令时，用tm_isdst=0;
//         maketime(tm*) 函数可将tm结构体转换为time_t类型，longlong类型，为1900年到目标时间的秒数;
//         sscanf(char* _Buffer,const char* _Format,...)函数可通过格式化字符串对相应的值进行扫描，从而实现字符串转数字。
//Parameters:
//        cmd: Type char*，the command whitch will be executed every times.
//        time_point: Type char**,the time list whitch is CTimer run time point.
//        time_point_len: Type int,the lenth of the string array.
//Return : Constructor.
// 
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
time_t CTimer::StrToDatetime(char* str)
{
	char* cha = str;
	tm tm_;																			
	int year, month, day, hour, minute, second;										
	sscanf(cha, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);	
	tm_.tm_year = year - 1900;														
	tm_.tm_mon = month - 1;															
	tm_.tm_mday = day;																
	tm_.tm_hour = hour;																
	tm_.tm_min = minute;															
	tm_.tm_sec = second;															
	tm_.tm_isdst = 0;																
	time_t t_ = mktime(&tm_);														
	return t_;																		 
}

time_t* CTimer::ToDatime(char** time_point, int len) {
	time_t* re_val = new time_t[len];
	for (int i = 0; i < len; i++) {
		re_val[i] = StrToDatetime(time_point[i]);
	}
	return re_val;
}

char** CTimer::AddDate(char** time_point, int len) {
	char** re_val = new char* [len];
	time_t nowtime;
	time(&nowtime);
	struct tm* timep = localtime(&nowtime);
	//如果将时间点存为结构体，	其中的时分秒分别存为数字，可以简化计算。
	for (int i = 0; i < len; i++) {
		re_val[i] = new char[20];
		sprintf(re_val[i], "%d-%d-%d %s", timep->tm_year + 1900, timep->tm_mon + 1, timep->tm_mday,time_point[i]);
	}
	return re_val;
}

char* CTimer::AddDate(char* time_point, time_t date) {
	char* re_val = new char[20];
	struct tm* timep = localtime(&date);
	sprintf(re_val, "%d-%d-%d %s", timep->tm_year + 1900, timep->tm_mon + 1, timep->tm_mday,time_point);
	return re_val;
}
/**
* edit by sketchdee 2021.7.6 9:08
* TODO:time point can be saved in number rather than charactor array.
* If in linux/unix system, modify CTimer.h (#include "unistd.h"),modify CTimer.cpp(sleep(sleep_time))
*         the sleep funciton in linux has different argument and in defferent head file.
* linux don't hava these enhance function named "function_s",if want to use it ,you would better search document to confirm it.
**/