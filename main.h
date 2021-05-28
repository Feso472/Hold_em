//出于使用习惯的奇怪宏定义
#define TRUE 1
#define FALSE 0
#define bool int
//按键编码的宏定义
#define KEY_UP 0xffffff48
#define KEY_DOWN 0xffffff50
#define KEY_LEFT 0xffffff4b
#define KEY_RIGHT 0xffffff4d
#define KEY_DELETE 0xffffff53
#define KEY_ENTER 0x0000000d
#define KEY_BACKSPACE 0x00000008
#define KEY_SPACE 0x00000020
#define KEY_ESC 0x0000001b
#define KEY_PAGEUP 0xffffff49
#define KEY_PAGEDOWN 0xffffff51
#define KEY_TAB 0x00000009

void start();    //绘制开始界面
void content();    //游戏内容，包含大量的窗口绘制
void setting();    //绘制设置界面
void player_n();    //玩家人数选框
void ui(char n,int x,int y);    //在坐标(x,y)绘制各种图标
void init();    //初始化游戏
void state();    //打印游戏状态
void match(int card);    //比较牌型
void winner();    //决定胜利玩家
void ai(int npc);    //npc的决策函数
void option();    //玩家选项函数
void bubble_sort(int arr[], int len);    //冒泡排序
void SetPos(int x, int y);    //移动光标
bool getkb();    //获取键盘输入，来自SDDF
bool kbIs(int tch);    //判断键盘输入，来自SDDF

extern int n,r,mo,bl,pot,pl[4][3],pl_f[4][6],pu[5],win[4],fold[4],chip[4],bet[4],kbsignal[2];
extern char suit[4];
extern char num[16];
