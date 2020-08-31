#include <iostream>
#include <vector>
using namespace std;

#define Pcb_num  10
#define Res_num  10

int Allocation[Pcb_num][Res_num];
int Need[Pcb_num][Res_num];
int Max[Pcb_num][Res_num];
int Available[Res_num];
int Finish[Pcb_num] = {0};
int Work[Res_num];
int Request[Res_num];
vector<int> Safe_orde;
int PcbNum = 0;
int Resource = 0;
bool Safe_flag_try = false;

void Display()
{
	cout << "Max����: " << endl;
	for (int i = 0; i < PcbNum; ++i)
	{
		cout << "p[" << i << "]: " ;
		for (int j = 0; j < Resource; ++j)
		{
			cout << Max[i][j] << "    ";
		}
		cout << endl;
	}
	cout << "Allocation����: " << endl;
	for (int i = 0; i < PcbNum; ++i)
	{
		cout << "p[" << i << "]: " ;
		for (int j = 0; j < Resource; ++j)
		{
			cout << Allocation[i][j] << "    ";
		}
		cout << endl;
	}
	cout << "Need����: " << endl;
	for (int i = 0; i < PcbNum; ++i)
	{
		cout << "p[" << i << "]: ";
		for (int j = 0; j < Resource; ++j)
		{
			cout << Need[i][j] << "    ";
		}
		cout << endl;
	}
	cout << "Available����: " << endl;
	for (int i = 0; i < Resource; ++i)
	{
		cout << Available[i] << "    ";
	}
	cout << endl;
	cout << endl;
}

//��ʼ��
void Init()
{
	cout << "�����������Ŀ: ";
	cin >> PcbNum;
	cout << "��������Դ����: ";
	cin >> Resource;

	//����Allocation����
	cout << "����Allocation����: " << endl;
	for (int i = 0; i < PcbNum; ++i)
	{
		cout << "p[" << i << "]: " ;
		for (int j = 0; j < Resource; ++j)
		{
			cin >> Allocation[i][j];
		}
	}
	//����Need����
	cout << "����Need����: " << endl;
	for (int i = 0; i < PcbNum; ++i)
	{
		cout << "p[" << i << "]: " ;
		for (int j = 0; j < Resource; ++j)
		{
			cin >> Need[i][j];
		}
	}
	//����ϵͳʣ����Դ��
	cout << "����Available����:" << endl;
	for (int i = 0; i < Resource; ++i)
	{
		cin >> Available[i];
	}
	//���Max����
	for (int i = 0; i < PcbNum; ++i)
	{
		for (int j = 0; j < Resource; ++j)
		{
			Max[i][j] = Need[i][j] + Allocation[i][j];
		}
	}
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	Display();
}
//��ȫ�Լ��
void Safe()
{
	for (int i = 0; i < Resource; ++i)
	{
		Work[i] = Available[i];
	}
	bool flag = false;
	bool Safe_flag = true;
	Safe_flag_try = false;
	for (int i = 0; i < PcbNum; ++i)
	{
		if (Finish[i] == 1)
		{
			continue;
		}
		for (int j = 0; j < Resource; ++j)
		{
			if (Work[j] >= Need[i][j])
			{
				flag = true;
			}
			else
			{
				flag = false;
				break;
			}
		}
		if (flag)
		{
			//�����һ�����̵�Need < Work
			Finish[i] = 1;
			for (int k = 0; k < Resource; ++k)
			{
				Work[k] = Work[k] + Allocation[i][k];
			}
			Safe_orde.push_back(i);
			//��һ�λ��Ǵӵ�һ����ʼ��
			i = -1;
		}
	}
	for (int i = 0; i < Resource; ++i)
	{
		if (Finish[i] == 0)
			Safe_flag = false;
	}

	if (Safe_flag)
	{
		Safe_flag_try = true;
		cout << endl << "!!!��ǰ״̬��ȫ,���ڰ�ȫ����!!!" << endl;
		cout << "��ȫ����Ϊ: ";
		for (size_t i = 0; i < Safe_orde.size(); ++i)
			cout << "p[" << Safe_orde[i] << "]  ";
		cout << endl;
	}
	else
		cout << endl << "!!!��ǰ״̬����ȫ,�����ڰ�ȫ����!!!" << endl;
}

//���м��㷨
void Bank()
{
	int PcbId;
	cout << "���뷢������Ľ����±�: ";
	cin >> PcbId;
	cout << "������������: ";
	for (int i = 0; i < Resource; ++i)
	{
		cin >> Request[i];
	}
	
	for (int i = 0; i < Resource; ++i)
	{
		if (Request[i] > Need[PcbId][i])
		{
			cout << "�������Դ�����������ֵ!!!" << endl;
			return;
		}
		if (Request[i] > Available[i])
		{
			cout << "�������Դ����ϵͳ�ɷ������Դ!!!" << endl;
			return;
		}
	}

	//�Է���
	//TryAlloc(PcbId);
	for (int i = 0; i < Resource; ++i)
	{
		Need[PcbId][i] = Need[PcbId][i] - Request[i];
		Allocation[PcbId][i] = Allocation[PcbId][i] + Request[i];
		Available[i] = Available[i] - Request[i];
	}
	for (int i = 0; i < PcbNum; ++i)
	{
		Finish[i] = 0;
	}
	Safe_orde.clear();
	Safe();
	if (!Safe_flag_try)
		cout << "ϵͳ���ܷ�����Դ!!!" << endl;
}
void menu()
{
	cout << "*******************************" << endl;
	cout << "***********1. ��ʼ��***********" << endl;
	cout << "***********2. ��ȫ���㷨*******" << endl;
	cout << "***********3. ���м��㷨*******" << endl;
	cout << "***********0. �˳�*************" << endl;
	cout << "*******************************" << endl;
}

void Start()
{
	int Choose;
	while (1)
	{
		menu();
		cout << "������ѡ��: ";
		cin >> Choose;
		if (Choose == 1)
		{
			Init();
		}
		else if (Choose == 2)
		{
			Safe();
		}
		else if (Choose == 3)
		{
			Bank();
		}
		else if (Choose == 0)
		{
			break;
		}
	}
}

int main()
{
	Start();
	system("pause");
	return 0;
}
