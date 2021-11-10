#include "CTimer.h"
int strcompar(const char* str1, const char* str2) {
	for (int i = 0; str1[i] != '\0' && str2[i] != '\0'; i++) {
		if (str1[i] != str2[i])
			return 0;
	}
	return 1;
}

int main(int argc, char** argv)
{
	for (int i = 0; i < argc; i++) {
		printf("argv[%d]:%s\n", i, argv[i]);
	}
	//argc�а����������д�����ַ�����CTimer --cmd dir --times 19:00:00 ,�����argc��һ��ΪCTimer���ڶ���Ϊ--cmd �������ƣ���һ��Ϊ�������ơ�
	char* cmd;
	char** time_point;

	//_Release,_DEBUG ������ֱ���Release��Debugģʽ�±�����Ϊ1�����ڷֱ����ģʽ�ͷ���ģʽ��

#ifndef _DEBUG
	//Release
	int len = argc - 4;
	time_point = new char*[len];
	for (int i = 0; i < argc; i++) {
		if (strcompar(argv[i], "--cmd"))
			cmd = argv[i + 1];
		if (strcompar(argv[i], "--times"))
			for(int j=0;j<argc-4;j++)
				time_point[j]=argv[i+ j + 1];
	}
#endif
   
#ifdef _DEBUG
    //DEBUG
	int len = 3; 
	time_point = new char* [3];
	time_point[0] = "21:17:00";
	time_point[1] = "21:18:00";
	time_point[2] = "21:18:30";
	cmd = "dir";
#endif

	printf("cmd:%s\n", cmd);
	printf("time point: ");
	for (int i = 0; i < len; i++)
		printf("%s  ", time_point[i]);
	printf("\n");
	CTimer timer = CTimer(cmd, time_point, len);
	timer.RunTimer();
	for (int i = 0; i < len; i++)
		delete[] time_point[i];
	delete[] time_point; 
	return 0;
}
