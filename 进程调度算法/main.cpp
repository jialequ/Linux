#include "pcb.h"
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
		else
		{
			if (choose == 1)
			{
				//�����ȷ����㷨
				vector<Pcb> pcb;
				int n = 0;
				FCFS(pcb, n);
			}
			else if (choose == 2)
			{
				//����ҵ�����㷨
				vector<Pcb> pcb;
				int n = 0;
				SJF(pcb, n);
			}
			else if (choose == 3)
			{
				//ʱ��Ƭ��ת�㷨
				vector<Pcb> pcb;
				int n = 0;
				int q = 0;
				cout << "������ʱ��Ƭ��С: ";
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