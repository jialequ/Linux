#include "pcb.h"
const int NUM = 100;
void menu()
{
	cout << "************���̵����㷨**********" << endl;
	cout << "*********1. �����ȷ����㷨********" << endl;
	cout << "*********2. ����ҵ�����㷨********" << endl;
	cout << "*********3. ʱ��Ƭ��ת�㷨********" << endl;
	cout << "**************0. �˳�************" << endl;
	cout << "��ѡ���㷨:";
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
		else if (choose == 1)
		{
			//�����ȷ����㷨
			vector<Pcb> pcb(NUM);
			int n = 0;
			FCFS(pcb, n);
		}
		else if (choose == 2)
		{
			//����ҵ�����㷨
			vector<Pcb> pcb(NUM);
			int n = 0;
			SJF(pcb, n);
		}
	}
}

int main()
{
	start();
	system("pause");
	return 0;
}