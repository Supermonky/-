#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<math.h>
#include <cmath>
#define MAX 2000 //�ŵ���Χ 
#define N 1000 //������Ŀ 
using namespace std;

int list[MAX];  //���������������� 
int visit[MAX]; //������� 
int location;//��ʼ��ͷλ��  
int closedistant; //���������ŵ��뵱ǰ��ͷ���ڴŵ�����̾��� 

//���ŵ���С�������� 
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

//�ȵ��ȷ����㷨
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
	printf("\n����FCFS�㷨���Ѱ������Ϊ��\n");
	for (i = 0; i < N - 1; i++) {
		printf("%d->", list[i]);
	}
	printf("���н������к��ͷ���е��ܴŵ���Ϊ��%d\n\n", move);
	printf("ƽ��Ѱ��ʱ��Ϊ��%.2lf\n\n", move * 0.001);
	printf("\n-------------------------------------------------------\n\n");


}

//���������ͷ��ʼλ�úͷ������� 
void CreateList()
{
	int j;
	int i;
	location = rand() % MAX + 1;//���������ʼ��ͷλ�� 
	printf("��ǰ��ͷλ�ã�%d\n\n", location);
	printf("������ʵĴŵ������У�\n");
	for (i = 0; i < N; i++) {           //�����������ŵ������� 
		list[i] = rand() % MAX + 1;
		printf("%d ", list[i]);
	}
	printf("\n\n");
}

//���Ѱ�������㷨
void SSTF()
{
	int i;
	int j;
	int k;//��¼����Ĵŵ��� 
	int loca;
	int move;
	int shortest;  //��¼��̵ľ��� 
	int after[MAX];
	memset(visit, 1, sizeof(visit));
	move = 0;
	loca = location;
	for (i = 0; i < N; i++) {
		shortest = MAX;
		for (j = 0; j < N; j++) {//�и����ŵ����� 
			if (visit[j]) {
				if (fabs(loca - list[j]) < shortest) {
					shortest = fabs(loca - list[j]);
					k = j;
				}
			}
		}
		move = move + shortest;  //��¼�ƶ��ľ��� 
		loca = list[k];  //���ٵ�ǰ��ͷ����λ�� 
		visit[k] = 0;  //����ѷ��� 
		after[i] = list[k];  //��¼·�� 
	}
	printf("\n����SSTF�㷨���Ѱ������Ϊ��\n");
	for (i = 0; i < N - 1; i++) {
		printf("%d->", after[i]);
	}
	printf("%d\n\n", after[i]);
	printf("���н������к��ͷ���е��ܴŵ���Ϊ��%d\n\n", move);
	printf("ƽ��Ѱ��ʱ��Ϊ��%.2lf\n\n", move * 0.001);
	printf("\n-------------------------------------------------------\n\n");
}

//ѭ��ɨ���㷨
void CSCAN()
{
	int i;
	int j;
	int move;
	int loca;
	int after[MAX];
	i = 0;
	loca = location;
	for (i = 0; i < N; i++) {      //�ҵ���ͷ�������е�λ�� 
		if (list[i] >= loca) {
			break;
		}
	}
	move = 0;
	for (j = 0; j < N; i++, j++) {
		if (i == N) {         //�γ�ͷβ���� 
			i = 0;
		}
		move = move + fabs(list[i] - loca);  //��¼�ƶ��ľ��� 
		loca = list[i];    //��¼��ǰ��ͷ����λ�� 
		after[j] = list[i];  //��¼·�� 
	}
	printf("\n���㷨�涨��ͷ���������ƶ�\n\n");
	printf("����CSCAN�㷨���Ѱ������Ϊ��\n");
	for (i = 0; i < N - 1; i++) {
		printf("%d->", after[i]);
	}
	printf("%d\n\n", after[i]);
	printf("���н������к��ͷ���е��ܴŵ���Ϊ��%d\n\n", move);
	printf("ƽ��Ѱ��ʱ��Ϊ��%.2lf\n\n", move * 0.001);
	printf("\n-------------------------------------------------------\n\n");
}

//ɨ���㷨
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
	for (i = 0; i < N; i++) {   //�ҵ���ǰ��ͷ����λ�� 
		if (list[i] >= loca) {
			break;
		}
	}
	j = i - 1;
	k = 0;
	move = 0;
	while (i < N) {//���������� 
		move = move + fabs(list[i] - loca);//��¼�ƶ��ľ��� 
		loca = list[i]; //��¼��ǰ��ͷλ�� 
		after[k++] = list[i];//��¼·�� 
		i++;
	}
	while (j >= 0) {//���������� `
		move = move + fabs(list[j] - loca);//��¼�ƶ��ľ���
		loca = list[j]; //��¼��ǰ��ͷλ�� 
		after[k++] = list[j];//��¼·�� 
		j--;
	}
	printf("\n���㷨�涨��ͷ��ʼ����Ϊ�Եʹŵ���ߴŵ�\n\n");
	printf("����SCAN�㷨���Ѱ������Ϊ��\n");
	for (i = 0; i < N - 1; i++) {
		printf("%d->", after[i]);
	}
	printf("%d\n\n", after[i]);
	printf("���н������к��ͷ���е��ܴŵ���Ϊ��%d\n\n", move);
	printf("ƽ��Ѱ��ʱ��Ϊ��%.2lf\n\n", move * 0.001);
	printf("\n-------------------------------------------------------\n\n");
}

void Start()
{
	
	printf("��ѡ��\n1��FCFS���ȵ��ȷ����㷨��\n2��SSTF�����Ѱ�������㷨��\n3��SCAN��ɨ���㷨��\n");
	printf("4��CSCAN��ѭ��ɨ���㷨��\n5�����²���һ���µ�����\n6������\n\n");
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