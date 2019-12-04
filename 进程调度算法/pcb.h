#pragma once
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct Pcb
{
	char name;
	float arr_time;//到达时间
	float ser_time;//服务时间
	float fin_time;//完成时间
	float tur_time;//周转时间
	float b_tur_time;//带权周转时间
	float run_time = 0;//运行时间
	bool flag_run = false;//执行标志
	bool flag_push = false;//入队标志
}Pcb;

void Input(vector<Pcb>& pcb, int &n)
{
	cout << "请输入进程数量: ";
	cin >> n;
	cout << endl;
	pcb.resize(n);
	for (int i = 0; i < n; ++i)
	{
		cout << "请输入进程" << i + 1 << "的进程名, 到达时间, 服务时间: ";
		cin >> pcb[i].name >> pcb[i].arr_time >> pcb[i].ser_time;
	}
}

void Output(vector<Pcb>& pcb, int n, float tur_sum, float b_tur_sum)
{
	float avg_tur_sum = tur_sum / n;
	float avg_b_tur_sum = b_tur_sum / n;

	cout << endl;
	cout << "id|   arr  |   ser  |   fin  |   tur  |  b_tur |" << endl;
	for (int i = 0; i < n; ++i)
	{
		printf("%c | %6.2f | %6.2f | %6.2f | %6.2f | %6.2f | \n", pcb[i].name, pcb[i].arr_time, pcb[i].ser_time, pcb[i].fin_time, pcb[i].tur_time, pcb[i].b_tur_time);
	}
	cout << endl;
	printf("平均周转时间 : %6.2f\n", avg_tur_sum);
	printf("平均带权周转时间 : %6.2f\n", avg_b_tur_sum);
	cout << endl;
}

void Swap(Pcb& a, Pcb& b)
{
	swap(a.name, b.name);
	swap(a.arr_time, b.arr_time);
	swap(a.ser_time, b.ser_time);
}

void Time_BubbleSort(vector<Pcb>& pcb, int n)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 1; j < n - i; ++j)
		{
			if (pcb[j].arr_time < pcb[j - 1].arr_time)
			{
				Swap(pcb[j], pcb[j - 1]);
			}
		}
	}
}

//先来先服务
void FCFS(vector<Pcb>& pcb, int &n)
{
	Input(pcb, n);
	Time_BubbleSort(pcb, n);

	float tur_sum = 0.0;
	float b_tur_sum = 0.0;
	//第一个进程先运行
	pcb[0].fin_time = pcb[0].ser_time;
	pcb[0].flag_run = true;
	pcb[0].tur_time = pcb[0].fin_time - pcb[0].arr_time;
	pcb[0].b_tur_time = pcb[0].tur_time / pcb[0].ser_time;
	tur_sum += pcb[0].tur_time;
	b_tur_sum += pcb[0].b_tur_time;
	//计算后面每一个的
	for (int i = 1; i < n; ++i)
	{
		pcb[i].fin_time = pcb[i].ser_time + pcb[i - 1].fin_time;
		pcb[i].tur_time = pcb[i].fin_time - pcb[i].arr_time;
		tur_sum += pcb[i].tur_time;
		pcb[i].b_tur_time = pcb[i].tur_time / pcb[i].ser_time;
		b_tur_sum += pcb[i].b_tur_time;
	}

	Output(pcb, n, tur_sum, b_tur_sum);
}

//短作业优先
void SJF(vector<Pcb>& pcb, int n)
{
	Input(pcb, n);
	//先按照到达时间排序
	Time_BubbleSort(pcb, n);	

	float Time = 0;
	bool flag_have = false;
	float tur_sum = 0.0;
	float b_tur_sum = 0.0;

	//第一个进程一定先运行
	pcb[0].fin_time = pcb[0].ser_time;
	pcb[0].flag_run = true;
	pcb[0].tur_time = pcb[0].fin_time - pcb[0].arr_time;
	pcb[0].b_tur_time = pcb[0].tur_time / pcb[0].ser_time;
	Time = pcb[0].fin_time;
	tur_sum += pcb[0].tur_time;
	b_tur_sum += pcb[0].b_tur_time;

	for (int i = 0; i < n - 1; ++i)
	{
		//找出当前数组中还没有运行的第一个pcb
		int Min_ser = 0;
		for (int index = 1; index < n; ++index)
		{
			if (!pcb[index].flag_run)
			{
				Min_ser = index;
				break;
			}
		}
		//找到之后, 从当前节点开始向后访问, 判断有没有到达时间小于Time的
		//有 : 再找出服务时间最小的
		//没有: 当前进程就是到达时间最小的, 直接运行它, Min_ser不用变
		for (int j = 1; j < n; ++j)
		{
			if ((pcb[j].arr_time < Time) && (!pcb[j].flag_run))
			{
				flag_have = true;
				if (pcb[j].ser_time < pcb[Min_ser].ser_time)
					Min_ser = j;
			}
		}

		//如果到达时间没有小于Time的,运行服务时间下一个的
		if (!flag_have)
			Min_ser = i;

		//计算当前进程的各个时间
		pcb[Min_ser].fin_time = Time + pcb[Min_ser].ser_time;
		pcb[Min_ser].tur_time = pcb[Min_ser].fin_time - pcb[Min_ser].arr_time;
		pcb[Min_ser].b_tur_time = pcb[Min_ser].tur_time / pcb[Min_ser].ser_time;
		pcb[Min_ser].flag_run = true;
		Time = pcb[Min_ser].fin_time;
		
		tur_sum += pcb[Min_ser].tur_time;
		b_tur_sum += pcb[Min_ser].b_tur_time;
	}

	Output(pcb, n, tur_sum, b_tur_sum);
}

void RR(vector<Pcb>& pcb, int n)
{
	//输入
	Input(pcb, n);
	//先按到达时间排序
	Time_BubbleSort(pcb, n);
	//第一个一定先运行

	queue<Pcb> pq;
	//先将pcb[0]push进去
	pcb[0].flag_push = true;
	pq.push(pcb[0]);

	float Time = 0;//程序的运行时间
	float q = 2;
	bool flag_all = false;//是否全部入队
	while (!pq.empty())
	{
		--q;
		++Time;
		//如果有进程到达, 入队
		if (!flag_all)
		{
			for (int i = 1; i < n; ++i)
			{
				if ((pcb[i].arr_time == Time) && (!pcb[i].flag_push))
				{
					pcb[i].flag_push = true;
					pq.push(pcb[i]);
					break;
				}
				if (pq.size() == n)
					flag_all = true;
			}
		}

		//自身的完成时间+1
		++pq.front().run_time;
		//如果运行完了
		if (pq.front().run_time == pq.front().ser_time)
		{
			pq.front().fin_time = Time;
			for (int i = 0; i < n; ++i)
			{
				if (pcb[i].name == pq.front().name)
				{
					pcb[i] = pq.front();
					break;
				}
			}
			pq.pop();
			q = 2;
		}
		else
		{
			//没有运行完
			if (!pq.empty() && pq.size() > 1)
			{
				if (q == 0)
				{
					q = 2;
					pq.push(pq.front());
					pq.pop();
				}
			}
		}
	}

	pcb[0].tur_time = pcb[0].fin_time - pcb[0].arr_time;
	pcb[0].b_tur_time = pcb[0].tur_time / pcb[0].ser_time;
	float tur_sum = pcb[0].tur_time;
	float b_tur_sum = pcb[0].b_tur_time;
	//计算后面每一个的
	for (int i = 1; i < n; ++i)
	{
		pcb[i].tur_time = pcb[i].fin_time - pcb[i].arr_time;
		tur_sum += pcb[i].tur_time;
		pcb[i].b_tur_time = pcb[i].tur_time / pcb[i].ser_time;
		b_tur_sum += pcb[i].b_tur_time;
	}

	Output(pcb, n, tur_sum, b_tur_sum);
}