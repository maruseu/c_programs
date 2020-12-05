#include <sys/utsname.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if defined(CLOCK_BOOTTIME)
	#define UPTIME_FLAG CLOCK_BOOTTIME
#elif defined(CLOCK_UPTIME)
	#define UPTIME_FLAG CLOCK_UPTIME
#else
	#define UPTIME_FLAG CLOCK_MONOTONIC
#endif

char* getValue(char *buff, char initChar, char endChar){
	int indexInit = 0;
	while(!(buff[indexInit - 1]==initChar) )
		indexInit++;
	int indexEnd = indexInit+1;
	while(buff[indexEnd]!=endChar)
		indexEnd++;
	memcpy(buff, &buff[indexInit],indexEnd - indexInit);
	buff[indexEnd - indexInit]='\0';
	return buff;
}

int main(){
	struct utsname utsvar;
	uname(&utsvar);

	struct timespec uptime;
	clock_gettime(UPTIME_FLAG, &uptime);

	uid_t id = geteuid();
	struct passwd *pwd = getpwuid(id);
	
	char ascii_0[]=" "; char ascii_1[]=" "; 
	char ascii_2[]=" "; char ascii_3[]=" "; 
	char ascii_4[]=" "; char ascii_5[]=" "; 
	char ascii_6[]=" "; char ascii_7[]=" ";

	printf("%s[36m%s[0m@[36m%s\n", ascii_0, pwd->pw_name, utsvar.nodename);
	printf("%s[0m____________________\n", ascii_1);
	{	
		FILE *fp;
		fp = fopen("/etc/os-release", "r");
		if (fp != NULL){
			char buff[63];
			for(int i = 0; i < 20 ; i++){
				fgets(buff, 63, (FILE*)fp);
				if(strstr(buff,"PRETTY_NAME")){
					printf("%s[36mos     [0m%s\n", ascii_2, getValue(buff,'"','"'));
					break;
				}
			}	
		fclose(fp);
		} else {
			printf("%s\n", ascii_2);
		}
	}

	printf("%s[36mshell [0m %s\n", ascii_3, getenv("SHELL"));
	printf("%s[36mhost  [0m %s\n", ascii_4, utsvar.machine);
	printf("%s[36mkernel[0m %s\n", ascii_5, utsvar.release);
	printf("%s[36muptime[0m %dd %dh %dm\n", ascii_6, (int)(uptime.tv_sec/3600 / 24), (int)(uptime.tv_sec/3600 % 24), (int)(uptime.tv_sec % 3600 / 60));

	{	
		FILE *fp;
		fp = fopen("/proc/meminfo", "r");
		if (fp != NULL){
			char buff[63];
			int avail = -1;
			int total = -1;
			for(int i = 0; (avail == -1 || total == -1) && i < 20 ; i++){
				fgets(buff, 63, (FILE*)fp);
				if(strstr(buff,"MemTotal")){
					total = strtol(getValue(buff,':','k'),NULL, 10);
				}
				if(strstr(buff,"MemAvailable")){
					avail = strtol(getValue(buff,':','k'),NULL, 10);
				}
			}	
			printf("%s[36mmemory [0m%dM / %dM\n", ascii_7, (total - avail) / 1024, total / 1024);
			fclose(fp);
		}else {
			printf("\n");
		}
	}
//	printf("\n");
//	for(int i = 0; i < 8; ++i) 
//		printf("[4%dm   ", i);
//	printf("\n");
//	for(int i = 0; i < 8; ++i) 
//		printf("[10%dm   ", i);
	printf("[0m\n");

	return 0;
}
