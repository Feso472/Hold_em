#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "main.h"

void init()
{
    int i,j,tmp,li[52];
    for(i=0;i<52;i++)
        li[i]=i;
    srand(time(NULL));
    for(i=0;i<52;i++)
    {
        j=rand()%52;
        tmp=li[i];
        li[i]=li[j];
        li[j]=tmp;
    }
    tmp=0;
    for(i=0;i<n;i++)
        for(j=1;j<3;j++,tmp++)
            pl[i][j]=li[tmp];
    for(i=0;i<5;i++,tmp++)
        pu[i]=li[tmp];
    for(i=0;i<n;i++,tmp++)
            pl[i][0]=li[tmp];
    for(i=0;i<n;i++)
    {
        win[i]=1;
        fold[i]=0;
    }
}

void state()
{
    int i=3,j;
    cls(3);
    SetPos(74,i);
    printf("     【ROUND %d】",r);
    SetPos(74,i+=4);
    printf("POT: %d",pot);
    SetPos(74,i+=4);
    printf("MINIMUM BET: %d",bl);
    SetPos(74,i+=4);
    printf("BET: ");
    SetPos(76,i+=2);
    printf("You     : %d",bet[0]);
    for(j=1;j<n;j++)
    {
        SetPos(76,i+=2);
        printf("Player %d: %d",j,bet[j]);
    }
    SetPos(74,i+=4);
    printf("CHIP: ");
    SetPos(76,i+=2);
    printf("You     : %d",chip[0]);
    for(j=1;j<n;j++)
    {
        SetPos(76,i+=2);
        printf("Player %d: %d",j,chip[j]);
    }
}

void match(int card)
{
    int va,p[5],ak,st,flush,flag[4],i,j,k,t1,t2,t3;
    for(i=0;i<n;i++)
    {
        pl[i][0]=0;
        for(t1=0;t1<card;t1++)
            for(t2=t1+1;t2<card+1;t2++)
                for(t3=t2+1;t3<card+2;t3++)
                {
                    k=0,ak=0,st=0,flush=0,flag[0]=-1,flag[1]=-1;
                    for(j=0;j<2;j++)
                        p[j]=pl[i][j+1];
                    p[2]=pu[t1],p[3]=pu[t2],p[4]=pu[t3];

                    bubble_sort(p,5);
                    for(j=0;j<4;j++)
                    {
                        if(p[j]%13-p[j+1]%13==0)
                            ak++;
                        else
                        {
                            flag[k]=j;
                            k++;
                            if(p[j]%13-p[j+1]%13==1)
                                st++;
                        }
                        if(p[j]/13==p[j+1]/13)
                            flush++;
                    }

                    if(flush==4 && st==4)
                        va=8;
                    else if(ak==3 && k==1)
                        if(flag[0]==0||flag[0]==3)
                            va=7;
                        else
                            va=6;
                    else if(flush==4)
                        va=5;
                    else if(st==4)
                        va=4;
                    else if(ak==2 && k==2)
                        if((flag[0]==2&&flag[1]==3)||(flag[0]==0&&flag[1]==3)||(flag[0]==0&&flag[1]==1))
                            va=3;
                        else
                            va=2;
                    else if(ak==1)
                        va=1;
                    else
                        va=0;
                    if(va>pl[i][0] || va==pl[i][0]&&p[0]>pl[i][1])
                    {
                        pl[i][0]=va;
                        pl_f[i][0]=va;
                        for(j=1;j<6;j++)
                            pl_f[i][j]=p[j-1];
                    }
                }
    }
}

void winner()
{
    int i,j,max,tmp;
    for(j=0;j<6;j++)
    {
        max=-1;
        for(i=0;i<n;i++)
            if(max<pl[i][j]%13)
                if(win[i])
                    if(!fold[i])
                        max=pl[i][j]%13;
        for(i=0;i<n;i++)
            if(pl[i][j]%13!=max)
                win[i]=0;
    }

}

void ai(int npc)
{
    cls(1);
    SetPos(4,37);
    printf("Player %d is making decision",npc+1);
    Sleep(500);
    printf(".");
    Sleep(500);
    printf(".");
    Sleep(500);
    printf(".");
    Sleep(500);
    cls(1);
    SetPos(4,37);
    if((bl/10-pl[npc][0]>7 || (bl/10-pl[npc][0]>4 && pl[npc][1]%13+pl[npc][2]%13<8) || chip[npc]<bl))
    {
        fold[npc]=1;
        printf("Player %d chooses to fold.    ▼",npc+1);
        if(npc+1==n)
            SetPos(68,9);
        else
            SetPos(69/(n-1)*npc-2,9);
        printf("Ｆ");
        while(!getkb());
    }
    else if((bl/10-pl[npc][0]<2 || (bl/10-pl[npc][0]<5 && pl[npc][1]%13+pl[npc][2]%13>16)) && chip[npc]>bl && pl[npc][0]>0 && bl!=90)
    {
        printf("Player %d chooses to raise.    ▼",npc+1);
        while(!getkb());
        if(bl+pl[npc][0]/2*10>chip[npc])
            bl=chip[npc];
        else if(bl+pl[npc][0]*10>90)
            bl=90;
        else if(pl[npc][0]/2==0)
            bl+=10;
        else
            bl+=pl[npc][0]/2*10;
        pot+=bl;
        chip[npc]-=bl;
        bet[npc]+=bl;
        state();
        cls(1);
        SetPos(4,37);
        printf("Player %d bets Ф%d as raise.    ▼",npc+1,bl);
        while(!getkb());
    }
    else
    {
        printf("Player %d chooses to call.    ▼",npc+1);
        while(!getkb());
        pot+=bl;
        chip[npc]-=bl;
        bet[npc]+=bl;
        state();
        cls(1);
        SetPos(4,37);
        printf("Player %d bets Ф%d as call.    ▼",npc+1,bl);
        while(!getkb());
    }
}

void option()
{
    int x=9,y=37,flag=0,mo=bl+10;
    cls(1);
    SetPos(x+3,y);
    printf("CALL                 RAISE                FOLD");
    SetPos(x,y);
    printf("%c",16);
    while(1)
    {
        if(getkb())
        {
            if(kbIs(KEY_LEFT)||kbIs(KEY_UP))
                if(x==7)
                    x+=42,flag+=2;
                else
                    x-=21,flag--;
            if(kbIs(KEY_RIGHT)||kbIs(KEY_DOWN))
                if(x==52)
                    x-=42,flag-=2;
                else
                    x+=21,flag++;
            if(kbIs(KEY_ENTER) || kbIs('z'))
            {
                if(flag ==0)
                {
                    if(chip[0]>=bl)
                    {
                        pot+=bl;
                        chip[0]-=bl;
                        bet[0]+=bl;
                        state();
                        cls(1);
                        SetPos(4,37);
                        printf("You bets Ф%d as call.    ▼",bl);
                        while(!getkb());
                        break;
                    }
                    else
                    {
                        cls(1);
                        SetPos(4,37);
                        printf("Your chips are not enough.    ▼");
                        while(!getkb());
                        return option();
                    }
                }
                if(flag==1)
                {
                    if(bl==90)
                    {
                        cls(1);
                        SetPos(4,37);
                        printf("Minimum bet has been too much!    ▼");
                        while(!getkb());
                        return option();
                    }
                    else
                    {
                        cls(1);
                        SetPos(19,36);
                        printf("▲");
                        SetPos(4,37);
                        printf("You will bet Ф%d as raise.",mo);
                        SetPos(19,38);
                        printf("▼");
                        while(1)
                        {
                            if(getkb())
                            {
                                if(kbIs(KEY_UP))
                                {
                                    if(mo==90)
                                        mo=bl+10;
                                    else
                                        mo+=10;
                                }
                                if(kbIs(KEY_DOWN))
                                {
                                    if(mo==bl+10)
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
                                if(kbIs(KEY_ESC))
                                    return option();
                                SetPos(19,37);
                                printf("%d",mo);
                            }
                        }
                        cls(1);
                        SetPos(4,37);
                        printf("You bets Ф%d as raise.    ▼",bl);
                        while(!getkb());
                        break;
                    }
                }
                if(flag==2)
                {
                    fold[0]=1;
                    cls(1);
                    SetPos(4,37);
                    printf("You folded. You are bystander now.    ▼");
                    SetPos(68,34);
                    printf("Ｆ");
                    while(!getkb());
                    break;
                }
            }
            printf("\b ");
            SetPos(x,y);
            printf("%c",16);
        }

    }
}
