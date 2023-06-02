//gderhemi22
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>


void displayClock(bool showDate)
{

    time_t currentTime = time(NULL);
    struct tm*timeInfo=localtime(&currentTime);

    int hour=timeInfo->tm_hour;
    int minute=timeInfo->tm_min;
    int second=timeInfo->tm_sec;

    printf("Current Time: %02d:%02d:%02d\n",hour,minute,second);

    if (showDate)
    {


        int day=timeInfo->tm_mday;
        int month=timeInfo->tm_mon +1;
        int year=timeInfo->tm_year +1900;

        printf("Current Date: %02d/%02d/%02d",day,month,year);

    }
}


void setAlarm ()
{
    int alarmHour,alarmMinute;

    printf("Enter the alarm time (hour minute):");
    scanf("%d %d",&alarmHour,&alarmMinute);

    printf("Alarm set for %02d:%02d\n",alarmHour,alarmMinute);

    while (true)
    {
        time_t currentTime = time(NULL);

        struct tm*timeInfo=localtime(&currentTime);


        if (timeInfo->tm_hour==alarmHour &&timeInfo->tm_min ==alarmMinute)
        {
            printf("\nAlarm! Wake up!\n");
            break;
        }


        displayClock(false);
        sleep(1);
    }
}


void startStopwatch ()
{
    int elapsedSeconds=0;

    printf("Stopwatch started.Press any key to stop.\n");

    while (!kbhit())
    {

        displayClock(false);
        sleep(1);

        elapsedSeconds++;
    }

    printf("\nStopwatch stopped.Elapsed time:%d seconds\n",elapsedSeconds);
}


void startTimer()
{
    int duration;
    printf("Enter the duration of the timer in seconds:");
    scanf("%d",&duration);
    printf("Timer started.Press any key to stop.\n");
    while (!kbhit()&&duration>0)
    {
        displayClock(false);
        sleep(1);
        duration --;
    }
    if (duration==0)
        printf("\nTimer finished!\n");
    else
        printf("\nTimer stopped.Remaining time: %d seconds\n",duration);
}

void snoozeAlarm()
{
    int snoozeMinutes;
    printf("Enter the duration of snooze in minutes:");

    scanf("%d",&snoozeMinutes);

    printf("Alarm snoozed for %d minutes.\n",snoozeMinutes);

    time_t currentTime = time(NULL)+snoozeMinutes *60;

    struct tm*timeInfo=localtime(&currentTime);

    int alarmHour=timeInfo->tm_hour;
    int alarmMinute=timeInfo->tm_min;
    while(true)
    {
        time_t currentTime = time(NULL);
        struct tm*now=localtime(&currentTime);

        if (now->tm_hour == alarmHour && now->tm_min == alarmMinute)
        {
            printf("\nAlarm! Wake Up!\n");
            break;
        }
        displayClock(false);
    }

}
int main()
{
    int choice;
    bool showDate = true;

    while (1)
    {
        displayClock(showDate);

        printf("\nMenu Options:\n");
        printf("1. Toggle Date Display\n");
        printf("2. Set Alarm\n");
        printf("3. Start Stopwatch\n");
        printf("4. Start Timer\n");
        printf("5. Snooze Alarm\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            showDate = !showDate;
            break;
        case 2:
            setAlarm();
            break;
        case 3:
            startStopwatch();
            break;
        case 4:
            startTimer();
            break;
        case 5:
            snoozeAlarm();
            break;
        case 6:
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }

    return 0;
}

