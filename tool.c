#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "main.h"

bool getkb()    //SDDF
{
	if (_kbhit()) {
		kbsignal[0] = _getch();
		if (kbsignal[0] == 0xe0 || kbsignal[0] == 0) {
			kbsignal[1] = _getch();
		}
		else {
			kbsignal[1] = 0;
		}
		return TRUE;
	}
	return FALSE;
}

bool kbIs(int tch)  //SDDF
{
	if (tch & 0xffffff00) {
		if (kbsignal[1] == (tch & 0xff)) {
			return TRUE;
		}
	}
	else {
		if (tch >= 'a' && tch <= 'z')tch -= ('a' - 'A');
		if (kbsignal[0] == tch) {
			return TRUE;
		}
		if (tch >= 'A' && tch <= 'Z' && kbsignal[0] == tch + ('a' - 'A')) {
			return TRUE;
		}
	}
	return FALSE;
}

void bubble_sort(int arr[], int len)    //https://www.runoob.com/cprogramming/c-sort-algorithm.html (changed)
{
    int i, j, temp;
    for (i = 0; i < len - 1; i++)
        for (j = 0; j < len - 1 - i; j++)
            if (arr[j]%13 < arr[j + 1]%13)
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

void player_n()
{
    SetPos(34,16);
    printf("┌────────────────────────────────┐\n");
    SetPos(34,17);
    printf("│                            ▲  │\n");
    SetPos(34,18);
    printf("│  按方向键上/下以更改人数： %s  │\n",num+(n*4-4));
    SetPos(34,19);
    printf("│                            ▼  │\n");
    SetPos(34,20);
    printf("└────────────────────────────────┘\n");
    while(1)
    {

        if(getkb())
        {
            if(kbIs(KEY_UP))
            {
                if(n==4)
                    n=1;
                else
                    n++;
            }
            if(kbIs(KEY_DOWN))
            {
                if(n==1)
                    n=4;
                else
                    n--;
            }
            if(kbIs(KEY_ENTER) || kbIs(KEY_ESC) || kbIs('z'))
                return setting();
            SetPos(63,18);
            printf("%s",num+(n*4-4));
        }
    }

}

void text(int a)
{
    int i,j;
    for(i=4;i<38;i+=2)
    {
        SetPos(40,i);
        for(j=0;j<50;j++)
            printf(" ");
    }
    if(a==0)
    {
        SetPos(40,4);
        printf("从游戏性来考虑相当微妙的选项");
        SetPos(40,6);
        printf("按照老师的要求姑且是放在这里了");
        SetPos(40,8);
        printf("按下可以设置游戏的人数");
        SetPos(40,10);
        printf("不过仅限于1-4人");
    }
    if(a==1)
    {
        SetPos(40,4);
        printf("大体上是德州扑克的规则\n");
        SetPos(40,6);
        printf("即通过手牌和公共牌组成总数为「五张」一组牌");
        SetPos(40,8);
        printf("并根据牌型大小决出本轮的胜负");
        SetPos(40,10);
        printf("乍一看像是个只看运气的游戏");
        SetPos(40,12);
        printf("但核心部分实际在于每次翻牌时的下注");
        SetPos(40,14);
        printf("牌型优势时");
        SetPos(40,16);
        printf("通过加注（raise）提高接下来的底注（minimum bet）");
        SetPos(40,18);
        printf("以获取更大的单局收益");
        SetPos(40,20);
        printf("反之则适当跟注（call）,必要时盖牌（fold）");
        SetPos(40,22);
        printf("将自己的损失控制在最小");
        SetPos(40,24);
        printf("顺带一提");
        SetPos(40,26);
        printf("所谓「大体上是」");
        SetPos(40,28);
        printf("指的是由于种种原因");
        SetPos(40,30);
        printf("只能通过手牌的两张加上公共牌中任选的三张");
        SetPos(40,32);
        printf("组成你的最终牌型");
        SetPos(40,34);
        printf("这点请务必要多注意");
    }
    if(a==2)
    {
        SetPos(40,4);
        printf("按下回到主菜单");
        SetPos(40,6);
        printf("玩的开心");
    }
}

void poker(int a,int x,int y,int flag)
{
    char num[4]={'J','Q','K','A'};
    SetPos(x,y);
    printf("╭ ───── ╮\n");
    SetPos(x,y+1);
    if(a==-1)
        printf("│       │\n");
    else if(a%13<9)
        printf("│ %c%-2d   │\n",suit[a/13],a%13+2);
    else
        printf("│ %c%-2c   │\n",suit[a/13],num[a%13-9]);
    SetPos(x,y+2);
    printf("│       │\n");
    SetPos(x,y+3);
    printf("│       │\n");
    if(flag==1)
    {
        SetPos(x,y+4);
        printf("│       │\n");
        SetPos(x,y+5);
        if(a==-1)
            printf("│       │\n");
        else if(a%13<9)
            printf("│    %2d%c│\n",a%13+2,suit[a/13]);
        else
            printf("│    %2c%c│\n",num[a%13-9],suit[a/13]);
        SetPos(x,y+6);
        printf("╰ ───── ╯\n");
    }
}

void ui(char n,int x,int y)
{
    int i;
    SetPos(x, y++);
    if(n=='t')
    {
        printf("  ___ ___        .__       .__/\\             \n");
        SetPos(x, y++);
        printf(" /   |   \\  ____ |  |    __| _)/___   _____  \n");
        SetPos(x, y++);
        printf("/    ~    \\/  _ \\|  |   / __ |/ __ \\ /     \\ \n");
        SetPos(x, y++);
        printf("\\    Y    (  <_> )  |__/ /_/ \\  ___/|  Y Y  \\\n");
        SetPos(x, y++);
        printf(" \\___|_  / \\____/|____/\\____ |\\___  >__|_|  /\n");
        SetPos(x, y++);
        printf("       \\/                   \\/    \\/      \\/ \n");
    }
    if(n=='m')
    {
        printf("╔══════════════╗\n");
        SetPos(x, y++);
        printf("│              │\n");
        SetPos(x, y++);
        printf("│     Start    │\n");
        SetPos(x, y++);
        printf("│              │\n");
        SetPos(x, y++);
        printf("│     Setting  │\n");
        SetPos(x, y++);
        printf("│              │\n");
        SetPos(x, y++);
        printf("│     Exit     │\n");
        SetPos(x, y++);
        printf("│              │\n");
        SetPos(x, y++);
        printf("╚══════════════╝\n");
    }
    if(n=='s')
    {
        printf("ROUND %d",r);
        SetPos(x, y++);
        printf("  _________________________ _____________________\n");
        SetPos(x, y++);
        printf(" /   _____/\\__    ___/  _  \\\\______   \\__    ___/\n");
        SetPos(x, y++);
        printf(" \\_____  \\   |    | /  /_\\  \\|       _/ |    |   \n");
        SetPos(x, y++);
        printf(" /        \\  |    |/    |    \\    |   \\ |    |   \n");
        SetPos(x, y++);
        printf("/_______  /  |____|\\____|__  /____|_  / |____|   \n");
        SetPos(x, y++);
        printf("        \\/                 \\/       \\/           \n");
    }
    if(n=='b')
    {
        printf("__________.____    .___ _______  ________   \n");
        SetPos(x, y++);
        printf("\\______   \\    |   |   |\\      \\ \\______ \\  \n");
        SetPos(x, y++);
        printf(" |    |  _/    |   |   |/   |   \\ |    |  \\ \n");
        SetPos(x, y++);
        printf(" |    |   \\    |___|   /    |    \\|    `   \\\n");
        SetPos(x, y++);
        printf(" |______  /_______ \\___\\____|__  /_______  /\n");
        SetPos(x, y++);
        printf("        \\/        \\/           \\/        \\/ \n");
    }
    if(n=='d')
    {
        printf("________  ___________   _____  .____     \n");
        SetPos(x, y++);
        printf("\\______ \\ \\_   _____/  /  _  \\ |    |    \n");
        SetPos(x, y++);
        printf(" |    |  \\ |    __)_  /  /_\\  \\|    |    \n");
        SetPos(x, y++);
        printf(" |    `   \\|        \\/    |    \\    |___ \n");
        SetPos(x, y++);
        printf("/_______  /_______  /\\____|__  /_______ \\\n");
        SetPos(x, y++);
        printf("        \\/        \\/         \\/        \\/\n");
    }
    if(n=='p')
    {
        printf("_________________________________________.____    ________ _________ \n");
        SetPos(x, y++);
        printf("\\______  \\______   \\_   _____/\\_   _____/|    |   \\_____  \\\\______  \\\n");
        SetPos(x, y++);
        printf(" |     __/|       _/|    __)_  |    __)  |    |    /   |   \\|     __/\n");
        SetPos(x, y++);
        printf(" |    |   |    |   \\|        \\ |     \\   |    |___/    |    \\   |    \n");
        SetPos(x, y++);
        printf(" |____|   |____|_  /_______  / \\___  /   |_______ \\_______  /___|    \n");
        SetPos(x, y++);
        printf("                 \\/        \\/      \\/            \\/       \\/         \n");
    }
    if(n=='f')
    {
        printf("___________.____    ________ __________ \n");
        SetPos(x, y++);
        printf("\\_   _____/|    |   \\_____  \\\\______   \\\n");
        SetPos(x, y++);
        printf(" |    __)  |    |    /   |   \\|     ___/\n");
        SetPos(x, y++);
        printf(" |     \\   |    |___/    |    \\    |    \n");
        SetPos(x, y++);
        printf(" \\___  /   |_______ \\_______  /____|    \n");
        SetPos(x, y++);
        printf("     \\/            \\/       \\/          \n");
    }
    if(n=='u')
    {
        printf("_______________ _____________  _______   \n");
        SetPos(x, y++);
        printf("\\__    ___/    |   \\______   \\ \\      \\  \n");
        SetPos(x, y++);
        printf("  |    |  |    |   /|       _/ /   |   \\ \n");
        SetPos(x, y++);
        printf("  |    |  |    |  / |    |   \\/    |    \\\n");
        SetPos(x, y++);
        printf("  |____|  |______/  |____|_  /\\____|__  /\n");
        SetPos(x, y++);
        printf("                           \\/         \\/ \n");
    }
    if(n=='r')
    {
        printf("__________._______   _________________________ \n");
        SetPos(x, y++);
        printf("\\______   \\   \\   \\ /   /\\_   _____/\\______   \\\n");
        SetPos(x, y++);
        printf(" |       _/   |\\   Y   /  |    __)_  |       _/\n");
        SetPos(x, y++);
        printf(" |    |   \\   | \\     /   |        \\ |    |   \\\n");
        SetPos(x, y++);
        printf(" |____|_  /___|  \\___/   /_______  / |____|_  /\n");
        SetPos(x, y++);
        printf("        \\/                       \\/         \\/ \n");
    }
    if(n=='h')
    {
        printf("  _________ ___ ___ ________  __      __        \n");
        SetPos(x, y++);
        printf(" /   _____//   |   \\\\_____  \\/  \\    /  \\       \n");
        SetPos(x, y++);
        printf(" \\_____  \\/    ~    \\/   |   \\   \\/\\/   /       \n");
        SetPos(x, y++);
        printf(" /        \\    Y    /    |    \\        /        \n");
        SetPos(x, y++);
        printf("/_______  /\\___|_  /\\_______  /\\__/\\  /         \n");
        SetPos(x, y++);
        printf("        \\/       \\/         \\/      \\/          \n");
        SetPos(x, y++);
        printf("       ________   ________  __      _________   \n");
        SetPos(x, y++);
        printf("       \\______ \\  \\_____  \\/  \\    /  \\      \\  \n");
        SetPos(x, y++);
        printf("        |    |  \\  /   |   \\   \\/\\/   /   |   \\ \n");
        SetPos(x, y++);
        printf("        |    `   \\/    |    \\        /    |    \\\n");
        SetPos(x, y++);
        printf("       /_______  /\\_______  /\\__/\\  /\\____|__  /\n");
        SetPos(x, y++);
        printf("               \\/         \\/      \\/         \\/ \n");
    }
}

void cls(int a)
{
    int i,j;
    if(a==0)
    {
        for(i=11;i<=30;i++)
        {
            SetPos(0,i);
            if(i>32)
                for(j=0;j<66;j++)
                    printf(" ");
            else
                for(j=0;j<70;j++)
                    printf(" ");
        }

    }
    if(a==1)
    {
        SetPos(0,36);
        for(i=0;i<68;i++)
                printf(" ");
        SetPos(0,37);
        for(i=0;i<68;i++)
                printf(" ");
        SetPos(0,38);
        for(i=0;i<68;i++)
                printf(" ");
    }
    if(a==2)
    {
        for(i=30;i<=34;i++)
        {
            SetPos(0,i);
            if(i>32)
                for(j=0;j<66;j++)
                    printf(" ");
            else
                for(j=0;j<69;j++)
                    printf(" ");
        }
    }
    if(a==3)
    {
        for(i=0;i<40;i++)
        {
            SetPos(72,i);
            for(j=0;j<28;j++)
                printf(" ");
        }
    }
}

void SetPos(int x, int y)   //https://www.pianshen.com/article/5107919485/
{
       COORD point = { x, y };//光标要设置的位置x,y
       HANDLE HOutput = GetStdHandle(STD_OUTPUT_HANDLE);//使用GetStdHandle(STD_OUTPUT_HANDLE)来获取标准输出的句柄
       SetConsoleCursorPosition(HOutput, point);//设置光标位置
}
