#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "main.h"

void start()
{
    int x=44,y=23,flag=0;
    system("cls");
    ui('t',26,7);
    ui('m',40,21);
    SetPos(x,y);
    printf("%c",16);
    while(1)
    {
        if(getkb())
        {
            if(kbIs(KEY_UP))
                if(y==23)
                    y+=4,flag+=2;
                else
                    y-=2,flag--;
            if(kbIs(KEY_DOWN))
                if(y==27)
                    y-=4,flag-=2;
                else
                    y+=2,flag++;
            if(kbIs(KEY_ENTER) || kbIs('z'))
            {
                if(flag==0)
                    return content();
                if(flag==1)
                    return setting();
                if(flag==2)
                    system("cls"),exit(0);
            }
            printf("\b ");
            SetPos(x,y);
            printf("%c",16);
        }

    }
}

void content()
{
    int i,j,tmp,plb[4],flag;
    for(i=0;i<n;i++)
        chip[i]=1000;
    while(1)
    {
        system("cls");
        SetPos(0,10);
        for(i=0;i<70;i++)
            printf("═");
        SetPos(0,35);
        for(i=0;i<70;i++)
            printf("═");
        for(i=0;i<40;i++)
        {
            SetPos(70,i);
            if(i==35 || i==10)
                printf("╣");
            else
                printf("║");
        }
        SetPos(66,33);
        printf("╔ ═ ╣");
        SetPos(66,34);
        printf("║ %s",num);
        SetPos(66,35);
        printf("╩");
        for(i=1;i<n-1;i++)
        {
            for(j=0;j<10;j++)
            {
                SetPos(69/(n-1)*i,j);
                printf("║");
            }
            SetPos(69/(n-1)*i,10);
            printf("╩");
            SetPos(69/(n-1)*i-4,8);
            printf("╔ ═ ╣");
            SetPos(69/(n-1)*i-4,9);
            printf("║ %s",num+(i*4));
            SetPos(69/(n-1)*i-4,10);
            printf("╩");
        }
        SetPos(66,8);
        printf("╔ ═ ╣");
        SetPos(66,9);
        printf("║ %s",num+(i*4));
        SetPos(66,10);
        printf("╩");
        state();
        init();
        ui('s',10,16);
        Sleep(300);
        SetPos(4,37);
        printf("Press ant key to select the dealer button.    ▼");
        while(!getkb());
        cls(0);
        cls(1);
        Sleep(500);
        //庄家
        poker(pl[0][0],30,31,0);
        j=0,tmp=pl[0][0],flag=0;
        Sleep(800);
        for(i=1;i<n;i++)
        {
            poker(pl[i][0],69/(n-1)*(i-1)+69/(n-1)/2-4,0,1);
            if(pl[i][0]%13>tmp%13)
                tmp=pl[i][0];
            Sleep(800);
        }
        for(i=0,j=0;i<n;i++)
            if(pl[i][0]%13==tmp%13)
            {
                plb[j++]=i;
                flag++;
            }
        SetPos(4,37);
        if(flag>1)
        {
            plb[0]=plb[rand()%flag]+1;
            if(plb[0]==1)
                printf("After a drastic rock-paper-scissors game, you are the dealer\n    button this round.    ▼");
            else
                printf("After a drastic rock-paper-scissors game, player %d is the dealer\n    button this round.    ▼",plb[0]);
        }
        else
        {
            plb[0]=plb[0]+1;
            if(plb[0]==1)
                printf("You are the dealer button this round.    ▼");
            else
                printf("Player %d is the dealer button this round.   ▼",plb[0]);
        }
        if(plb[0]==1)
            SetPos(68,34);
        else if(plb[0]==n)
            SetPos(68,9);
        else
            SetPos(69/(n-1)*(plb[0]-1)-2,9);
        switch(plb[0])
        {
        case 1:
            printf("①");
            break;
        case 2:
            printf("②");
            break;
        case 3:
            printf("③");
            break;
        case 4:
            printf("④");
            break;
        }
        while(!getkb());
        cls(1);
        Sleep(500);
        //盲注
        mo=10;
        ui('b',12,17);
        SetPos(4,37);
        if(plb[0]==n)
        {
            printf("You need to post the blind.    ▼");
            while(!getkb());
            cls(1);
            SetPos(19,36);
            printf("▲");
            SetPos(4,37);
            printf("You will bet Ф%d as blind.",mo);
            SetPos(19,38);
            printf("▼");
            while(1)
            {
                if(getkb())
                {
                    if(kbIs(KEY_UP))
                    {
                        if(mo==90)
                            mo=10;
                        else
                            mo+=10;
                    }
                    if(kbIs(KEY_DOWN))
                    {
                        if(mo==10)
                            mo=90;
                        else
                            mo-=10;
                    }
                    if(kbIs(KEY_ENTER) || kbIs('z'))
                    {
                        bl=mo;
                        pot+=bl;
                        chip[0]-=bl;
                        bet[0]+=bl;
                        state();
                        break;
                    }
                    SetPos(19,37);
                    printf("%d",mo);
                }
            }
            cls(1);
            SetPos(4,37);
            printf("You bets Ф%d as blind.    ▼",bl);
            while(!getkb());
        }
        else
        {
            printf("Player %d is posting the blind",plb[0]+1);
            Sleep(500);
            printf(".");
            Sleep(500);
            printf(".");
            Sleep(500);
            printf(".");
            Sleep(500);
            tmp=rand()%18;
            if(tmp==17)
                bl=10;
            else if(tmp>=6)
                bl=(tmp%4+2)*10;
            else
                bl=(tmp+1)*10;
            pot+=bl;
            chip[plb[0]]-=bl;
            bet[plb[0]]+=bl;
            state();
            cls(1);
            SetPos(4,37);
            printf("Player %d bets Ф%d as blind.    ▼",plb[0]+1,bl);
            while(!getkb());
        }
        //发牌
        cls(0),cls(1);
        ui('d',15,17);
        Sleep(500);
        poker(pl[0][1],27,31,0);
        poker(pl[0][2],33,31,0);
        Sleep(500);
        for(i=1;i<n;i++)
        {
            poker(-1,69/(n-1)*(i-1)+69/(n-1)/2-7,0,1);
            poker(-1,69/(n-1)*(i-1)+69/(n-1)/2-1,0,1);
            Sleep(500);
        }
        //preflop
        cls(0),cls(1);
        ui('p',1,17);
        Sleep(1500);
        cls(0);
        Sleep(500);
        for(i=0;i<n;i++)
        {
            pl[i][0]=0;
            if(pl[i][1]%13==pl[i][2]%13)
                pl[i][0]++;
            if(pl[i][1]/13==pl[i][2]/13)
                pl[i][0]++;
        }
        for(i=plb[0]+2;i%n!=(plb[0]+1)%n;i++)
        {
            if(i%n==1)
            {
                if(!fold[0])
                    option();
            }
            else
                if(!fold[(i-1)%n])
                    ai((i-1)%n);
        }
        //flop
        cls(0),cls(1);
        ui('f',15,17);
        Sleep(1500);
        cls(0);
        Sleep(500);
        for(i=0;i<3;i++)
        {
            poker(pu[i],8+12*i,18,1);
            Sleep(500);
        }
        match(1);
        for(i=plb[0]+1;i%n!=(plb[0]+1)%n || i==plb[0]+1;i++)
        {
            if(i%n==1)
            {
                if(!fold[0])
                    option();
            }
            else
                if(!fold[(i-1)%n])
                    ai((i-1)%n);
        }
        //turn
        cls(0),cls(1);
        ui('u',15,17);
        Sleep(1500);
        cls(0);
        poker(pu[0],8,18,1);
        poker(pu[1],20,18,1);
        poker(pu[2],32,18,1);
        Sleep(500);
        poker(pu[3],44,18,1);
        Sleep(500);
        match(2);
        for(i=plb[0]+1;i%n!=(plb[0]+1)%n || i==plb[0]+1;i++)
        {
            if(i%n==1)
            {
                if(!fold[0])
                    option();
            }
            else
                if(!fold[(i-1)%n])
                    ai((i-1)%n);
        }
        //river
        cls(0),cls(1);
        ui('r',10,16);
        Sleep(1500);
        cls(0);
        poker(pu[0],8,18,1);
        poker(pu[1],20,18,1);
        poker(pu[2],32,18,1);
        poker(pu[3],44,18,1);
        Sleep(500);
        poker(pu[4],56,18,1);
        Sleep(500);
        match(3);
        for(i=plb[0]+1;i%n!=(plb[0]+1)%n || i==plb[0]+1;i++)
        {
            if(i%n==1)
            {
                if(!fold[0])
                    option();
            }
            else
                if(!fold[(i-1)%n])
                    ai((i-1)%n);
        }
        //showdown
        cls(0),cls(1);
        ui('h',10,16);
        Sleep(1500);
        cls(0);
        poker(pu[0],8,18,1);
        poker(pu[1],20,18,1);
        poker(pu[2],32,18,1);
        poker(pu[3],44,18,1);
        poker(pu[4],56,18,1);
        Sleep(500);
        for(i=1;i<n;i++)
        {
            poker(pl[i][1],69/(n-1)*(i-1)+69/(n-1)/2-7,0,1);
            poker(pl[i][2],69/(n-1)*(i-1)+69/(n-1)/2-1,0,1);
            Sleep(500);
        }
        winner();
        cls(1);
        SetPos(4,37);
        for(i=0;i<n;i++)
            if(win[i]==1)
            {
                switch(pl[i][0])
                {
                case 0:
                    printf("High Card! ");
                    break;
                case 1:
                    printf("One Pair! ");
                    break;
                case 2:
                    printf("Two Pairs! ");
                    break;
                case 3:
                    printf("Three of a Kind! ");
                    break;
                case 4:
                    printf("Straight! ");
                    break;
                case 5:
                    printf("Flush! ");
                    break;
                case 6:
                    printf("Fullhouse! ");
                    break;
                case 7:
                    printf("Four of a Kind! ");
                    break;
                case 8:
                    if(pl[i][1]%13==12)
                        printf("Royal Flush! ");
                    else
                        printf("Straight Flush! ");
                    break;
                }
            }
        tmp=0;
        for(i=0;i<n;i++)
            if(win[i]==1)
            {
                if(i==0)
                    printf("You and ");
                else
                    printf("Player %d and ",i+1);
                tmp++;
            }
        printf("\b\b\b\bwin this round and get the bonus.    ▼");
        //bonus
        for(i=0;i<n;i++)
            if(win[i]==1)
                chip[i]+=pot/tmp;
        pot=0;
        bl=0;
        for(i=0;i<n;i++)
            bet[i]=0;
        state();
        while(!getkb());
        //replay
        i=43,j=37,flag=0;
        cls(1);
        SetPos(4,37);
        printf("Do you wanna play one more round?        Yes       No");
        SetPos(i,j);
        printf("%c",16);
        while(1)
        {
            if(getkb())
            {
                if(kbIs(KEY_LEFT)||kbIs(KEY_UP))
                    if(i==43)
                        i+=10,flag++;
                    else
                        i-=10,flag--;
                if(kbIs(KEY_RIGHT)||kbIs(KEY_DOWN))
                    if(i==53)
                        i-=10,flag--;
                    else
                        i+=10,flag++;
                if(kbIs(KEY_ENTER) || kbIs('z'))
                {
                    if(flag==0)
                    {
                        r++;
                        break;
                    }
                    if(flag==1)
                        start();
                }
                printf("\b ");
                SetPos(i,j);
                printf("%c",16);
            }
        }
    }
}

void setting()
{
    system("cls");
    int i,j,x=7,y=4,flag=0;
    SetPos(2,1);
    printf("╔");
    for(i=0;i<46;i++)
        if(i==15)
            printf("╦ ");
        else
            printf("══");
    printf(" ╗\n");
    for(i=0;i<36;i++)
    {
        printf("  │");
        for(j=0;j<46;j++)
            if(j==15)
                printf("│　");
            else
                printf("  ");
        printf("│\n");
    }
    printf("  ╚");
    for(i=0;i<46;i++)
        if(i==15)
                printf("╩ ");
        else
            printf("══");
    printf(" ╝");
    SetPos(10,4);
    printf("Number of players");
    SetPos(10,8);
    printf("Help");
    SetPos(10,12);
    printf("Back");
    text(flag);
    SetPos(x,y);
    printf("%c",16);

    while(1)
    {
        if(getkb())
        {
            printf("\b ");
            if(kbIs(KEY_UP))
            {
                if(y==4)
                    y+=8,flag+=2;
                else
                    y-=4,flag--;
                text(flag);
            }
            if(kbIs(KEY_DOWN))
            {
                if(y==12)
                    y-=8,flag-=2;
                else
                    y+=4,flag++;
                text(flag);
            }
            if(kbIs(KEY_ENTER) || kbIs('z'))
            {
                if(flag==0)
                    return player_n();
                if(flag==2)
                    return start();
            }
            if(kbIs(KEY_ESC))
                return start();
            SetPos(x,y);
            printf("%c",16);
        }
    }
}
