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
	float arr_time;
	float ser_time;
	float fin_time;
	float tur_time;
	float b_tur_time;
}Pcb;

void Input(vector<Pcb>& pcb, int &n)
{
	cout << "请输入进程数量: ";
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cout << "请输入进程" << i + 1 << "的进程名, 到达时间, 服务时间: ";
		cin >> pcb[i].name >> pcb[i].arr_time >> pcb[i].ser_time;
	}
}

void Swap(Pcb& a, Pcb& b)
{
	swap(a.name, b.name);
	swap(a.arr_time, b.arr_time);
	swap(a.ser_time, b.ser_time);
}

void FCFS_BubbleSort(vector<Pcb>& pcb, int n)
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


void SJF_BubbleSort(vector<Pcb>& pcb, int n)
{
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = 2; j < n - i; ++j)
		{
			if (pcb[j].ser_time < pcb[j - 1].ser_time)
			{
				Swap(pcb[j], pcb[j - 1]);
			}
		}
	}
}

void Cal(vector<Pcb>& pcb, int &n)
{
	pcb[0].fin_time = pcb[0].ser_time;

	for (int i = 1; i < n; ++i)
	{
		pcb[i].fin_time = pcb[i].ser_time + pcb[i - 1].fin_time;
	}

	float tur_sum = 0.0;
	for (int i = 0; i < n; ++i)
	{
		pcb[i].tur_time = pcb[i].fin_time - pcb[i].arr_time;
		tur_sum += pcb[i].tur_time;
	}

	float b_tur_sum = 0.0;
	for (int i = 0; i < n; ++i)
	{
		pcb[i].b_tur_time = pcb[i].tur_time / pcb[i].ser_time;
		b_tur_sum += pcb[i].b_tur_time;
	}

	float avg_tur_sum = tur_sum / n;
	float avg_b_tur_sum = b_tur_sum / n;
	cout << endl;
	cout << "id|   arr  |   ser  |   fin  |   tur  |  b_tur |" << endl;
	for (int i = 0; i < n; ++i)
	{
		printf("%c | %6.2f | %6.2f | %6.2f | %6.2f | %6.2f | \n", pcb[i].name, pcb[i].arr_time, pcb[i].ser_time, pcb[i].fin_time, pcb[i].tur_time, pcb[i].b_tur_time);
	}
	cout << endl;
	cout << "平均周转时间 : " << avg_tur_sum << endl;
	cout << "平均带权周转时间 : " << avg_b_tur_sum << endl;
}