#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<math.h>
#include <cmath>
#define MAX 2000 //磁道范围 
#define N 1000 //序列数目 
using namespace std;

int list[MAX];  //存放随机产生的序列 
int visit[MAX]; //标记数组 
int location;//初始磁头位置  
int closedistant; //保存其他磁道与当前磁头所在磁道的最短距离 

//按磁道从小到大排序 
void sort()
{
	int i;
	int j;
	int t;
	for (i = 0; i < N - 1; i++) {
		for (j = i + 1; j < N; j++) {
			if (list[j] < list[i]) {
				t = list[i];
				list[i] = list[j];
				list[j] = t;
			}
		}
	}
}

//先到先服务算法
void FCFS()
{
	int i;
	int move=0;
	int loca;
	i = 0;
	loca = location;
	for (i = 0;i < N - 1; i++)
	{
		move += abs(loca - list[i]);
		loca = list[i];
	}
	printf("\n采用FCFS算法后的寻道序列为：\n");
	for (i = 0; i < N - 1; i++) {
		printf("%d->", list[i]);
	}
	printf("所有进程运行后磁头运行的总磁道数为：%d\n\n", move);
	printf("平均寻道时间为：%.2lf\n\n", move * 0.001);
	printf("\n-------------------------------------------------------\n\n");


}

//随机产生磁头初始位置和访问序列 
void CreateList()
{
	int j;
	int i;
	location = rand() % MAX + 1;//随机产生初始磁头位置 
	printf("当前磁头位置：%d\n\n", location);
	printf("请求访问的磁道号序列：\n");
	for (i = 0; i < N; i++) {           //随机产生请求磁道号序列 
		list[i] = rand() % MAX + 1;
		printf("%d ", list[i]);
	}
	printf("\n\n");
}

//最短寻道优先算法
void SSTF()
{
	int i;
	int j;
	int k;//记录最近的磁道号 
	int loca;
	int move;
	int shortest;  //记录最短的距离 
	int after[MAX];
	memset(visit, 1, sizeof(visit));
	move = 0;
	loca = location;
	for (i = 0; i < N; i++) {
		shortest = MAX;
		for (j = 0; j < N; j++) {//有更近磁道更新 
			if (visit[j]) {
				if (fabs(loca - list[j]) < shortest) {
					shortest = fabs(loca - list[j]);
					k = j;
				}
			}
		}
		move = move + shortest;  //记录移动的距离 
		loca = list[k];  //跟踪当前磁头所在位置 
		visit[k] = 0;  //标记已访问 
		after[i] = list[k];  //记录路径 
	}
	printf("\n采用SSTF算法后的寻道序列为：\n");
	for (i = 0; i < N - 1; i++) {
		printf("%d->", after[i]);
	}
	printf("%d\n\n", after[i]);
	printf("所有进程运行后磁头运行的总磁道数为：%d\n\n", move);
	printf("平均寻道时间为：%.2lf\n\n", move * 0.001);
	printf("\n-------------------------------------------------------\n\n");
}

//循环扫描算法
void CSCAN()
{
	int i;
	int j;
	int move;
	int loca;
	int after[MAX];
	i = 0;
	loca = location;
	for (i = 0; i < N; i++) {      //找到磁头在序列中的位置 
		if (list[i] >= loca) {
			break;
		}
	}
	move = 0;
	for (j = 0; j < N; i++, j++) {
		if (i == N) {         //形成头尾相连 
			i = 0;
		}
		move = move + fabs(list[i] - loca);  //记录移动的距离 
		loca = list[i];    //记录当前磁头所在位置 
		after[j] = list[i];  //记录路径 
	}
	printf("\n本算法规定磁头自里向外移动\n\n");
	printf("采用CSCAN算法后的寻道序列为：\n");
	for (i = 0; i < N - 1; i++) {
		printf("%d->", after[i]);
	}
	printf("%d\n\n", after[i]);
	printf("所有进程运行后磁头运行的总磁道数为：%d\n\n", move);
	printf("平均寻道时间为：%.2lf\n\n", move * 0.001);
	printf("\n-------------------------------------------------------\n\n");
}

//扫描算法
void SCAN()
{
	int i;
	int j;
	int k;
	int move;
	int loca;
	int after[MAX];
	loca = location;
	i = 0;
	for (i = 0; i < N; i++) {   //找到当前磁头所在位置 
		if (list[i] >= loca) {
			break;
		}
	}
	j = i - 1;
	k = 0;
	move = 0;
	while (i < N) {//先自里向外 
		move = move + fabs(list[i] - loca);//记录移动的距离 
		loca = list[i]; //记录当前磁头位置 
		after[k++] = list[i];//记录路径 
		i++;
	}
	while (j >= 0) {//后自外向里 `
		move = move + fabs(list[j] - loca);//记录移动的距离
		loca = list[j]; //记录当前磁头位置 
		after[k++] = list[j];//记录路径 
		j--;
	}
	printf("\n本算法规定磁头初始方向为自低磁道向高磁道\n\n");
	printf("采用SCAN算法后的寻道序列为：\n");
	for (i = 0; i < N - 1; i++) {
		printf("%d->", after[i]);
	}
	printf("%d\n\n", after[i]);
	printf("所有进程运行后磁头运行的总磁道数为：%d\n\n", move);
	printf("平均寻道时间为：%.2lf\n\n", move * 0.001);
	printf("\n-------------------------------------------------------\n\n");
}

void Start()
{
	
	printf("请选择：\n1、FCFS（先到先服务算法）\n2、SSTF（最短寻道优先算法）\n3、SCAN（扫描算法）\n");
	printf("4、CSCAN（循环扫描算法）\n5、重新产生一组新的序列\n6、结束\n\n");
	char c;
	while (c = getchar(), c != '5') {
		switch (c) {
		case '1':FCFS(); break;
		case '2':sort();  SSTF(); break;
		case '3':sort(); SCAN(); break;
		case '4':sort(); CSCAN(); break;
		case '5':CreateList(); break;
		default:break;
		}
	}
}

int main()
{
	srand((unsigned)time(NULL));
	CreateList();
	Start();
	return 0;
}