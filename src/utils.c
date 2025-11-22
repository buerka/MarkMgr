#include <stdio.h>

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen()
{
    printf("按回车继续...");
    getchar();
}

void flushInput()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
