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
	cout << "Max矩阵: " << endl;
	for (int i = 0; i < PcbNum; ++i)
	{
		cout << "p[" << i << "]: " ;
		for (int j = 0; j < Resource; ++j)
		{
			cout << Max[i][j] << "    ";
		}
		cout << endl;
	}
	cout << "Allocation矩阵: " << endl;
	for (int i = 0; i < PcbNum; ++i)
	{
		cout << "p[" << i << "]: " ;
		for (int j = 0; j < Resource; ++j)
		{
			cout << Allocation[i][j] << "    ";
		}
		cout << endl;
	}
	cout << "Need矩阵: " << endl;
	for (int i = 0; i < PcbNum; ++i)
	{
		cout << "p[" << i << "]: ";
		for (int j = 0; j < Resource; ++j)
		{
			cout << Need[i][j] << "    ";
		}
		cout << endl;
	}
	cout << "Available矩阵: " << endl;
	for (int i = 0; i < Resource; ++i)
	{
		cout << Available[i] << "    ";
	}
	cout << endl;
	cout << endl;
}

//初始化
void Init()
{
	cout << "请输入进程数目: ";
	cin >> PcbNum;
	cout << "请输入资源个数: ";
	cin >> Resource;

	//输入Allocation矩阵
	cout << "输入Allocation矩阵: " << endl;
	for (int i = 0; i < PcbNum; ++i)
	{
		cout << "p[" << i << "]: " ;
		for (int j = 0; j < Resource; ++j)
		{
			cin >> Allocation[i][j];
		}
	}
	//输入Need矩阵
	cout << "输入Need矩阵: " << endl;
	for (int i = 0; i < PcbNum; ++i)
	{
		cout << "p[" << i << "]: " ;
		for (int j = 0; j < Resource; ++j)
		{
			cin >> Need[i][j];
		}
	}
	//输入系统剩余资源数
	cout << "输入Available矩阵:" << endl;
	for (int i = 0; i < Resource; ++i)
	{
		cin >> Available[i];
	}
	//求出Max矩阵
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
//安全性检测
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
			//如果有一个进程的Need < Work
			Finish[i] = 1;
			for (int k = 0; k < Resource; ++k)
			{
				Work[k] = Work[k] + Allocation[i][k];
			}
			Safe_orde.push_back(i);
			//下一次还是从第一个开始找
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
		cout << endl << "!!!当前状态安全,存在安全序列!!!" << endl;
		cout << "安全序列为: ";
		for (size_t i = 0; i < Safe_orde.size(); ++i)
			cout << "p[" << Safe_orde[i] << "]  ";
		cout << endl;
	}
	else
		cout << endl << "!!!当前状态不安全,不存在安全序列!!!" << endl;
}

//银行家算法
void Bank()
{
	int PcbId;
	cout << "输入发起请求的进程下标: ";
	cin >> PcbId;
	cout << "输入请求向量: ";
	for (int i = 0; i < Resource; ++i)
	{
		cin >> Request[i];
	}
	
	for (int i = 0; i < Resource; ++i)
	{
		if (Request[i] > Need[PcbId][i])
		{
			cout << "请求的资源大于需求最大值!!!" << endl;
			return;
		}
		if (Request[i] > Available[i])
		{
			cout << "请求的资源大于系统可分配的资源!!!" << endl;
			return;
		}
	}

	//试分配
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
		cout << "系统不能分配资源!!!" << endl;
}
void menu()
{
	cout << "*******************************" << endl;
	cout << "***********1. 初始化***********" << endl;
	cout << "***********2. 安全性算法*******" << endl;
	cout << "***********3. 银行家算法*******" << endl;
	cout << "***********0. 退出*************" << endl;
	cout << "*******************************" << endl;
}

void Start()
{
	int Choose;
	while (1)
	{
		menu();
		cout << "请输入选择: ";
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
