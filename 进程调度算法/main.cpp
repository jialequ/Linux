#include "pcb.h"
void menu()
{
	cout << "************进程调度算法**********" << endl;
	cout << "*********1. 先来先服务算法********" << endl;
	cout << "*********2. 短作业优先算法********" << endl;
	cout << "*********3. 时间片轮转算法********" << endl;
	cout << "**************0. 退出************" << endl;
	cout << "请选择算法:";
}

void start()
{
	int choose;
	while (1)
	{
		menu();
		cin >> choose;
		if (choose == 0)
		{
			break;
		}
		else
		{
			if (choose == 1)
			{
				//先来先服务算法
				vector<Pcb> pcb;
				int n = 0;
				FCFS(pcb, n);
			}
			else if (choose == 2)
			{
				//短作业优先算法
				vector<Pcb> pcb;
				int n = 0;
				SJF(pcb, n);
			}
			else if (choose == 3)
			{
				//时间片轮转算法
				vector<Pcb> pcb;
				int n = 0;
				int q = 0;
				cout << "请输入时间片大小: ";
				cin >> q;
				RR(pcb, n);
			}
		}
	}
}

int main()
{
	start();
	system("pause");
	return 0;
}