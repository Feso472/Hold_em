#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "main.h"

int n=4,r=1,mo=10,bl=0,pot=0,pl[4][3]={0},pl_f[4][6],pu[5],win[4]={1,1,1,1},fold[4]={0},chip[4],bet[4]={0},kbsignal[2];
char suit[4]={3,4,5,6};
char num[16]={0xef,0xbc,0x91,0x00,0xef,0xbc,0x92,0x00,0xef,0xbc,0x93,0x00,0xef,0xbc,0x94,0x00};


int main()
{
    CONSOLE_CURSOR_INFO cursor;    //用于隐去光标
	cursor.bVisible = FALSE;
	cursor.dwSize = sizeof(cursor);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cursor);    //https://blog.csdn.net/ZouHuiDong/article/details/89816918

    system("mode con cols=100 lines=40");    //初始化窗口大小
    system("chcp 65001");    //设定控制台编码为UTF-8
    start();    //进入开始函数
    return 0;
}


