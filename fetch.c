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
	
	//char ascii_0[]="                  "; char ascii_1[]="                  "; 
	//char ascii_2[]="                  "; char ascii_3[]="                  "; 
	//char ascii_4[]="                  "; char ascii_5[]="                  "; 
	//char ascii_6[]="                  "; char ascii_7[]="                  ";
	//system("(echo -e '0;1;0;0;110;110;;;;;.face\n4;\n3;' | /usr/lib/w3m/w3mimgdisplay) &> /dev/null &");

	//char ascii_0[]="[31m       /\\         ";
	//char ascii_1[]="[31m      /  \\        ";
	//char ascii_2[]="[31m     /\\   \\       ";
	//char ascii_3[]="[31m    /  '   \\      ";
	//char ascii_4[]="[31m   /   ,,   \\     ";
	//char ascii_5[]="[31m  /   |  | -_\\    ";
	//char ascii_6[]="[31m /_-''    ''-_\\   ";
	//char ascii_7[]="                  ";

	char ascii_0[]="[0m[38;5;219m[48;5;212m▃[0m[38;5;212m[48;5;219mQ[0m[38;5;219m[48;5;212mZ[0m[38;5;219m[48;5;212m_[0m[38;5;211m[48;5;219m{[0m[38;5;230m[48;5;182m▂[0m[38;5;181m[48;5;224m▀[0m[38;5;224m[48;5;230m▃[0m[38;5;224m[48;5;230m▆[0m[38;5;224m[48;5;181m▔[0m[38;5;224m[48;5;181m▘[0m[38;5;182m[48;5;224m▕[0m[38;5;212m[48;5;219my[0m[38;5;219m[48;5;212mz[0m[38;5;219m[48;5;212m)[0m[38;5;219m[48;5;212m▃[0m[38;5;218m[48;5;219m▁[0m ";
	char ascii_1[]="[0m[38;5;183m[48;5;219m▀[0m[38;5;218m[48;5;219m\\[0m[38;5;212m[48;5;218m◆[0m[38;5;224m[48;5;181m▆[0m[38;5;174m[48;5;224m▂[0m[38;5;181m[48;5;224m▃[0m[38;5;181m[48;5;230m▼[0m[38;5;230m[48;5;181m▅[0m[38;5;181m[48;5;230m`[0m[38;5;182m[48;5;230m'[0m[38;5;181m[48;5;230m▀[0m[38;5;223m[48;5;181m▂[0m[38;5;230m[48;5;181m▂[0m[38;5;224m[48;5;219m▍[0m[38;5;218m[48;5;219mr[0m[38;5;212m[48;5;219m%[0m[38;5;212m[48;5;219m%[0m ";
	char ascii_2[]="[0m[38;5;219m[48;5;183m▃[0m[38;5;219m[48;5;189m\\[0m[38;5;189m[48;5;219m*[0m[38;5;217m[48;5;219m▔[0m[38;5;230m[48;5;187m▅[0m[38;5;230m[48;5;230m [0m[38;5;230m[48;5;230m [0m[38;5;230m[48;5;230m [0m[38;5;230m[48;5;230m [0m[38;5;230m[48;5;230m [0m[38;5;230m[48;5;230m [0m[38;5;230m[48;5;230m [0m[38;5;230m[48;5;182m▊[0m[38;5;219m[48;5;219m'[0m[38;5;219m[48;5;219m [0m[38;5;219m[48;5;219m [0m[38;5;219m[48;5;219m [0m ";
	char ascii_3[]="[0m[38;5;189m[48;5;219m\\[0m[38;5;183m[48;5;219m▃[0m[38;5;183m[48;5;189m▅[0m[38;5;187m[48;5;230m▘[0m[38;5;230m[48;5;230m [0m[38;5;230m[48;5;230m [0m[38;5;230m[48;5;230m [0m[38;5;230m[48;5;230m [0m[38;5;152m[48;5;230m▁[0m[38;5;230m[48;5;230m [0m[38;5;230m[48;5;230m [0m[38;5;181m[48;5;230m▍[0m[38;5;230m[48;5;230m [0m[38;5;223m[48;5;219m▋[0m[38;5;219m[48;5;189m▞[0m[38;5;219m[48;5;219m [0m[38;5;219m[48;5;219m [0m ";
	char ascii_4[]="[0m[38;5;255m[48;5;219m▃[0m[38;5;189m[48;5;219m▞[0m[38;5;181m[48;5;230m][0m[38;5;230m[48;5;230m [0m[38;5;230m[48;5;230m [0m[38;5;230m[48;5;230m [0m[38;5;230m[48;5;230m [0m[38;5;249m[48;5;230m▗[0m[38;5;110m[48;5;152m4[0m[38;5;231m[48;5;230m▂[0m[38;5;230m[48;5;231m▀[0m[38;5;110m[48;5;255m5[0m[38;5;230m[48;5;230m [0m[38;5;230m[48;5;230m [0m[38;5;252m[48;5;183m▃[0m[38;5;219m[48;5;183m▗[0m[38;5;183m[48;5;219m▅[0m ";
	char ascii_5[]="[0m[38;5;231m[48;5;231m [0m[38;5;255m[48;5;231m`[0m[38;5;181m[48;5;230m▕[0m[38;5;181m[48;5;230m▍[0m[38;5;230m[48;5;230m [0m[38;5;181m[48;5;230m▂[0m[38;5;230m[48;5;230m [0m[38;5;230m[48;5;167m▆[0m[38;5;231m[48;5;230m▝[0m[38;5;231m[48;5;231m [0m[38;5;231m[48;5;231m [0m[38;5;252m[48;5;231m▞[0m[38;5;230m[48;5;230m [0m[38;5;224m[48;5;230m◆[0m[38;5;224m[48;5;231m▖[0m[38;5;231m[48;5;231m [0m[38;5;231m[48;5;219m▅[0m ";
	char ascii_6[]="[0m[38;5;183m[48;5;231m●[0m[38;5;183m[48;5;231m▆[0m[38;5;183m[48;5;231m▅[0m[38;5;230m[48;5;183m▀[0m[38;5;176m[48;5;181m▆[0m[38;5;176m[48;5;176m [0m[38;5;176m[48;5;176m [0m[38;5;176m[48;5;181m▅[0m[38;5;176m[48;5;230m▆[0m[38;5;183m[48;5;231mz[0m[38;5;231m[48;5;238m▎[0m[38;5;238m[48;5;230m▅[0m[38;5;238m[48;5;230m▎[0m[38;5;187m[48;5;230mc[0m[38;5;231m[48;5;230m▅[0m[38;5;231m[48;5;231m [0m[38;5;255m[48;5;231m▝[0m ";
	char ascii_7[]="[0m[38;5;231m[48;5;231m [0m[38;5;231m[48;5;231m [0m[38;5;231m[48;5;231m [0m[38;5;231m[48;5;183m▆[0m[38;5;176m[48;5;183m▃[0m[38;5;176m[48;5;183m▃[0m[38;5;183m[48;5;176mz[0m[38;5;176m[48;5;183m▀[0m[38;5;176m[48;5;182m▀[0m[38;5;183m[48;5;244m▀[0m[38;5;16m[48;5;236m▖[0m[38;5;235m[48;5;238m▼[0m[38;5;230m[48;5;223m▞[0m[38;5;181m[48;5;230m▖[0m[38;5;230m[48;5;230m [0m[38;5;231m[48;5;230m▝[0m[38;5;231m[48;5;231m [0m ";

	printf("%s[31m%s[0m@[31m%s\n", ascii_0, pwd->pw_name, utsvar.nodename);
	printf("%s[0m____________________\n", ascii_1);
	{	
		FILE *fp;
		fp = fopen("/etc/os-release", "r");
		if (fp != NULL){
			char buff[63];
			for(int i = 0; i < 20 ; i++){
				fgets(buff, 63, (FILE*)fp);
				if(strstr(buff,"PRETTY_NAME")){
					printf("%s[31mos     [0m%s\n", ascii_2, getValue(buff,'"','"'));
					break;
				}
			}	
		fclose(fp);
		} else {
			printf("%s\n", ascii_2);
		}
	}

	printf("%s[31mshell [0m %s\n", ascii_3, getenv("SHELL"));
	printf("%s[31mhost  [0m %s\n", ascii_4, utsvar.machine);
	printf("%s[31mkernel[0m %s\n", ascii_5, utsvar.release);
	printf("%s[31muptime[0m %dd %dh %dm\n", ascii_6, (int)(uptime.tv_sec/3600 / 24), (int)(uptime.tv_sec/3600 % 24), (int)(uptime.tv_sec % 3600 / 60));

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
			printf("%s[31mmemory [0m%dM / %dM\n", ascii_7, (total - avail) / 1024, total / 1024);
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
