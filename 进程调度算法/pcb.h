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
	float arr_time;//����ʱ��
	float ser_time;//����ʱ��
	float fin_time;//���ʱ��
	float tur_time;//��תʱ��
	float b_tur_time;//��Ȩ��תʱ��
	float run_time = 0;//����ʱ��
	bool flag_run = false;//ִ�б�־
	bool flag_push = false;//��ӱ�־
}Pcb;

void Input(vector<Pcb>& pcb, int &n)
{
	cout << "�������������: ";
	cin >> n;
	cout << endl;
	pcb.resize(n);
	for (int i = 0; i < n; ++i)
	{
		cout << "���������" << i + 1 << "�Ľ�����, ����ʱ��, ����ʱ��: ";
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
	printf("ƽ����תʱ�� : %6.2f\n", avg_tur_sum);
	printf("ƽ����Ȩ��תʱ�� : %6.2f\n", avg_b_tur_sum);
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

//�����ȷ���
void FCFS(vector<Pcb>& pcb, int &n)
{
	Input(pcb, n);
	Time_BubbleSort(pcb, n);

	float tur_sum = 0.0;
	float b_tur_sum = 0.0;
	//��һ������������
	pcb[0].fin_time = pcb[0].ser_time;
	pcb[0].flag_run = true;
	pcb[0].tur_time = pcb[0].fin_time - pcb[0].arr_time;
	pcb[0].b_tur_time = pcb[0].tur_time / pcb[0].ser_time;
	tur_sum += pcb[0].tur_time;
	b_tur_sum += pcb[0].b_tur_time;
	//�������ÿһ����
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

//����ҵ����
void SJF(vector<Pcb>& pcb, int n)
{
	Input(pcb, n);
	//�Ȱ��յ���ʱ������
	Time_BubbleSort(pcb, n);	

	float Time = 0;
	bool flag_have = false;
	float tur_sum = 0.0;
	float b_tur_sum = 0.0;

	//��һ������һ��������
	pcb[0].fin_time = pcb[0].ser_time;
	pcb[0].flag_run = true;
	pcb[0].tur_time = pcb[0].fin_time - pcb[0].arr_time;
	pcb[0].b_tur_time = pcb[0].tur_time / pcb[0].ser_time;
	Time = pcb[0].fin_time;
	tur_sum += pcb[0].tur_time;
	b_tur_sum += pcb[0].b_tur_time;

	for (int i = 0; i < n - 1; ++i)
	{
		//�ҳ���ǰ�����л�û�����еĵ�һ��pcb
		int Min_ser = 0;
		for (int index = 1; index < n; ++index)
		{
			if (!pcb[index].flag_run)
			{
				Min_ser = index;
				break;
			}
		}
		//�ҵ�֮��, �ӵ�ǰ�ڵ㿪ʼ������, �ж���û�е���ʱ��С��Time��
		//�� : ���ҳ�����ʱ����С��
		//û��: ��ǰ���̾��ǵ���ʱ����С��, ֱ��������, Min_ser���ñ�
		for (int j = 1; j < n; ++j)
		{
			if ((pcb[j].arr_time < Time) && (!pcb[j].flag_run))
			{
				flag_have = true;
				if (pcb[j].ser_time < pcb[Min_ser].ser_time)
					Min_ser = j;
			}
		}

		//�������ʱ��û��С��Time��,���з���ʱ����һ����
		if (!flag_have)
			Min_ser = i;

		//���㵱ǰ���̵ĸ���ʱ��
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
	//����
	Input(pcb, n);
	//�Ȱ�����ʱ������
	Time_BubbleSort(pcb, n);
	//��һ��һ��������

	queue<Pcb> pq;
	//�Ƚ�pcb[0]push��ȥ
	pcb[0].flag_push = true;
	pq.push(pcb[0]);

	float Time = 0;//���������ʱ��
	float q = 2;
	bool flag_all = false;//�Ƿ�ȫ�����
	while (!pq.empty())
	{
		--q;
		++Time;
		//����н��̵���, ���
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

		//��������ʱ��+1
		++pq.front().run_time;
		//�����������
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
			//û��������
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
	//�������ÿһ����
	for (int i = 1; i < n; ++i)
	{
		pcb[i].tur_time = pcb[i].fin_time - pcb[i].arr_time;
		tur_sum += pcb[i].tur_time;
		pcb[i].b_tur_time = pcb[i].tur_time / pcb[i].ser_time;
		b_tur_sum += pcb[i].b_tur_time;
	}

	Output(pcb, n, tur_sum, b_tur_sum);
}