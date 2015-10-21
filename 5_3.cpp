#include <iostream>

using namespace std;

char stackOut[1000], stackTemp[1000]; // ������ �����: ��������, � ������� �������� �������� ������, � ���������, � ������� ������������ ��������
int topOut, topTemp; // ������������� �������� ������

void initstacks()
{
	topOut = -1;
	topTemp = -1;
}

void pushFTTO() // ������� ����������� �������� �� ���������� ����� � �������� + ���������� � ����� �������
{
	stackOut[++topOut] = stackTemp[topTemp--];
	stackOut[++topOut] = ',';
}

int priority(char op) // ������� ���������� ��������
{
	if ((op == '*')||(op == '/'))
		return 2;
	if (op == '-')
		return 1;
	if (op == '+')
		return 0;
	else
		return -1;
}

double solve(char in[], int lenIn)
{
	initstacks();
	int pos=0;
	for (  ;pos<lenIn;pos++) // ���� �� ������� ������
	{
		if (isdigit(in[pos])) // ���� ����������� �����, �� ���������� ��� � �������� ����
		{
			stackOut[++topOut] = in[pos];
			if (!isdigit(in[pos+1]))
				stackOut[++topOut] = ',';
		}
		else
			if ((in[pos] == '(')||(in[pos] == ')')) 
			{
				if (in[pos] == '(') // ����������� ������ ������ ���������� �� ��������� ����
					stackTemp[++topTemp] = in[pos];
				else
				{
					while (stackTemp[topTemp] != '(') // ���� ������ �����������, �� ����� �� ���������� ����� ��� �������� �� ����������� ������. ���� ����������� ������ �������
						pushFTTO();
					topTemp--;
				}
			}
			else
			{
				if (topTemp == -1) // ���� ��������� ���� ������, �� ������ ���������� ������ � ����
					stackTemp[++topTemp] = in[pos];
				else
				if (priority(in[pos]) <= priority(stackTemp[topTemp])) // ���� ��������� ������� �������� �� ������ ���������� �������� �� �������� ���������� �����,
				{
					pushFTTO();                                                 // �� �������� �� �������� ����� � �������� ����,
					while (priority(in[pos]) <= priority(stackTemp[topTemp]))   // ��� �� ����� ��� �������� �� ���������� �����, ��������� ������� �� ������ �������,
					    pushFTTO();
					stackTemp[++topTemp] = in[pos];                             // � ������� ����� �� ���������
				}
				else 
					stackTemp[++topTemp] = in[pos];                    // ���� ��������� ������� �������� ������ ���������� �������� ������ ���������� �����, �� ������ ����� �� � ���� ����
			}


	}
	while (topTemp>-1)   // ���������� ��� ���������� �������� �� ���������� ����� � ��������
		pushFTTO();
	stackOut[++topOut] = '\0';

	                                           // ������� � �������� �������� ������� ��������, ������ ������� �����

	double a[1000] = {0};
	int i=0, numOfNumbers=0; // i - ��������� �� ��������� � ������ � �������� �������� �������
	while (i<topOut)
	{
		double num = 0;
		if (isdigit(stackOut[i]))  // ���� ���� �����, ���������� �� ��� �����
        {
			while (isdigit(stackOut[i]))
			    num = num*10.0 + (double)(stackOut[i++] - '0');   
		    a[numOfNumbers++] = num;
			i++;               // � ����� ��������� while i ��������� �� ������� ����� �����, ������� ����������� �� 1
		}
		else 
			if (!isdigit(stackOut[i]))  // ���� ����������� ��������, �� ��������� �� � ���� ��������� ������ �� �������
			{
    			switch (stackOut[i]) {
	    		case '+': 
					{
						a[numOfNumbers-2]+=a[numOfNumbers-1];
						numOfNumbers--;
					}
		 	    	break;
		    	case '-': 
					{
						a[numOfNumbers-2]-=a[numOfNumbers-1];
						numOfNumbers--;
					}
		    	 	break;
		        case '*': 
					{
						a[numOfNumbers-2]*=a[numOfNumbers-1];
						numOfNumbers--;
					}
	    			break;
			    case '/': 
					{
						a[numOfNumbers-2]/=a[numOfNumbers-1];
						numOfNumbers--;
					}
    				break;
				}
				i+=2;   // i ��������� �� ��������, ��������� ������� - �������, ������� ����������� �� 2
			}
	}
	return a[0];   // ������������ ���������� �������� � ���� ���������
}

int main()
{

	return 0;
}