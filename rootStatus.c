#include <unistd.h>
#include <X11/Xlib.h>
#include <time.h>
#include <stdio.h>
#define bs 64
char buffer[bs];
Display *dpy;
struct tm *times;
time_t rawtime;
const char *getWeekdayName(int);

int main(void){
	FILE* pFTemp;
	int temp;
	if((dpy=XOpenDisplay(NULL)))
		do {
			XFlush(dpy);
			sleep(1);

			pFTemp = fopen("/sys/class/hwmon/hwmon0/temp1_input", "r");
			fscanf(pFTemp,"%d",&temp);

			time(&rawtime);
			times=localtime(&rawtime);

			snprintf(buffer,bs * sizeof(char),"%.1f °C | %s %02d/%02d %02d:%02d",
					temp/1000.0f,
					getWeekdayName(times->tm_wday),
					times->tm_mday,times->tm_mon+1,
					times->tm_hour,times->tm_min);
		} while(XStoreName(dpy, DefaultRootWindow(dpy),buffer));
	else printf("Couldnt open display\n");

	return 0;
}




const char *getWeekdayName(int wday){
	switch(wday){
		case 0: return "Sun";
		case 1: return "Mon";
		case 2: return "Tue";
		case 3: return "Wed";
		case 4: return "Thu";
		case 5: return "Fri";
		case 6: return "Sat";
	} return "Err";
}
