#include <sys/utsname.h>
#include <sys/types.h>
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
	struct passwd *pwd;
	struct timespec uptime;
	
	uname(&utsvar);

	char ascii_0[]="                  "; char ascii_1[]="                  "; 
	char ascii_2[]="                  "; char ascii_3[]="                  "; 
	char ascii_4[]="                  "; char ascii_5[]="                  "; 
	char ascii_6[]="                  "; char ascii_7[]="                  ";
	system("(echo -e '0;1;0;0;110;110;;;;;.face\n4;\n3;' | /usr/lib/w3m/w3mimgdisplay) &> /dev/null &");

	//char ascii_0[]="[31m       /\\         ";
	//char ascii_1[]="[31m      /  \\        ";
	//char ascii_2[]="[31m     /\\   \\       ";
	//char ascii_3[]="[31m    /  '   \\      ";
	//char ascii_4[]="[31m   /   ,,   \\     ";
	//char ascii_5[]="[31m  /   |  | -_\\    ";
	//char ascii_6[]="[31m /_-''    ''-_\\   ";
	//char ascii_7[]="                  ";

	pwd = getpwuid(geteuid());

	clock_gettime(UPTIME_FLAG, &uptime);
	printf("%s[31m%s[0m@[31m%s\n", ascii_0, pwd->pw_name, utsvar.nodename);
	printf("%s[0m____________________\n", ascii_1);
	{	
		FILE *fp;
		fp = fopen("/etc/os-release", "r");
		char buff[63];
		for(int i = 0; i < 20 ; i++){
			fgets(buff, 63, (FILE*)fp);
			if(strstr(buff,"PRETTY_NAME")){
				printf("%s[31mos     [0m%s\n", ascii_2, getValue(buff,'"','"'));
				break;
			}
		}	
		fclose(fp);
	}

	printf("%s[31mshell [0m %s\n", ascii_3, getenv("SHELL"));
	printf("%s[31mhost  [0m %s\n", ascii_4, utsvar.machine);
	printf("%s[31mkernel[0m %s\n", ascii_5, utsvar.release);
	printf("%s[31muptime[0m %dd %dh %dm\n", ascii_6, (int)(uptime.tv_sec/3600 / 24), (int)(uptime.tv_sec/3600 % 24), (int)(uptime.tv_sec % 3600 / 60));

	{	
		FILE *fp;
		fp = fopen("/proc/meminfo", "r");
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
		printf("%s[31mmemory [0m%dM / %dM\n", ascii_7, (total - avail) / 1024, total / 1024);
		fclose(fp);
	}

	printf("\n[40m   [41m   [42m   [43m   [44m   [45m   [46m   [47m   [0m\n");
	printf("[1;100m   [101m   [102m   [103m   [104m   [105m   [106m   [107m   [0m\n");
	printf("\n");

	return 0;
}
