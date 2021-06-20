#include <unistd.h>
#include <X11/Xlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define GETBS(BUFFER) sizeof(BUFFER)/sizeof(BUFFER[0])

const char* weekday[]={"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
char bat_buf[8];
char temp_buf[16];
char date_buf[32];
char mus_buf[128];

char buffer[256];

Display *dpy;

pthread_t bat_trd;
pthread_t temp_trd;
pthread_t date_trd;
pthread_t mus_trd;

const char *getWeekdayName(int wday);

void * upd_bat();
void * upd_date();
void * upd_temp();
void * upd_mus();

int updateRoot(){
	snprintf(buffer,GETBS(buffer),"%s  %s   %s   %s  ",
		mus_buf, temp_buf, bat_buf, date_buf);
	if(XStoreName(dpy, DefaultRootWindow(dpy),buffer)){
		XFlush(dpy);
		printf("flushed!\n");
		return 1;
	} else
		return 0;
}

int main(void){
	bat_buf[0]='\0';
	temp_buf[0]='\0';
	date_buf[0]='\0';
	mus_buf[0]='\0';

	pthread_create(&bat_trd, NULL, upd_bat, NULL);
	pthread_create(&date_trd, NULL, upd_date, NULL);
	pthread_create(&temp_trd, NULL, upd_temp, NULL);
	pthread_create(&mus_trd, NULL, upd_mus, NULL);

	if((dpy = XOpenDisplay(NULL)))
		while(updateRoot()) sleep(1);
	else {
		printf("Couldnt open display\n");
		return 1;
	}

	return 0;
}

void * upd_bat(){
	int batCap;
	char batStatus[16];
	FILE *pFBat;
	FILE *pFBatStatus;

	while(1){
		pFBat = fopen("/sys/class/power_supply/BAT0/capacity", "r");
		if (pFBat){
			fscanf(pFBat,"%d",&batCap);

			pFBatStatus = fopen("/sys/class/power_supply/BAT0/status", "r");
			if (pFBatStatus) {
				fscanf(pFBatStatus,"%15s",batStatus);
				if(!strcmp("Discharging",batStatus))
					snprintf(bat_buf,GETBS(bat_buf),"%d ⇣", batCap);
				else
					snprintf(bat_buf,GETBS(bat_buf),"%d ⚡", batCap);
				
				fclose(pFBatStatus);
			}
			fclose(pFBat);
		} else snprintf(bat_buf,GETBS(bat_buf),"");
		printf("Bat..");
		fflush(stdout);
		sleep(1);
	}
}

void * upd_temp(){
	int temp;
	FILE *pFTemp;

	while(1){
		pFTemp = fopen("/sys/class/hwmon/hwmon1/temp1_input", "r");
		if(pFTemp){
			fscanf(pFTemp,"%d",&temp);
			snprintf(temp_buf,GETBS(temp_buf),"%.1f C", temp/1000.0f);

			fclose(pFTemp);
		}
		printf("temp..");
		fflush(stdout);
		sleep(1);
	}
}

#define GETMUS(CMD) \
		memset(music,'\0',sizeof(music) * sizeof(music[0])); \
		pFmpc = popen(CMD, "r"); \
		if(pFmpc){ \
			fread(music, sizeof(char),GETBS(music),pFmpc); \
			{ \
				int i=0; \
				while(music[i]!='\0') i++; \
				if(music[i-1]=='\n') music[i-1]='\0'; \
			} \
			if(!strcmp("",music) || !strcmp("\n",music)) \
				snprintf(mus_buf,GETBS(mus_buf),""); \
			else snprintf(mus_buf,GETBS(mus_buf),"「 ♪  %s  」",music); \
			fclose(pFmpc); \
		} \
		printf("mus.."); \
		updateRoot(); \

void * upd_mus(){
	FILE *pFmpc;
	char music[128 - 8];
	GETMUS("/bin/mpc current");
	while(1){
		GETMUS("/bin/mpc current --wait");
	}
}

void * upd_date(){
	struct tm *times;
	time_t rawtime;

	while(1){
		time(&rawtime);
		times=localtime(&rawtime);

		snprintf(date_buf,GETBS(date_buf),"%s %02d:%02d",
				weekday[times->tm_wday],
				times->tm_hour,times->tm_min);
		printf("date..");
		fflush(stdout);
		sleep(61 - times->tm_sec);
	}
}
