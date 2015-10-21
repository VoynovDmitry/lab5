#include <iostream>

using namespace std;

char stackOut[1000], stackTemp[1000]; // —оздаю стеки: основной, в котором хранитс€ польска€ запись, и временный, в который закидываютс€ операции
int topOut, topTemp; // »нициализаци€ верхушек стеков

void initstacks()
{
	topOut = -1;
	topTemp = -1;
}

void pushFTTO() // ‘ункци€ перемещени€ операции из временного стека в основной + добавление в конце зап€той
{
	stackOut[++topOut] = stackTemp[topTemp--];
	stackOut[++topOut] = ',';
}

int priority(char op) // ¬озврат приоритета операции
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
	for (  ;pos<lenIn;pos++) // »дем по входной строке
	{
		if (isdigit(in[pos])) // ≈сли встретилось число, то записываем его в основной стек
		{
			stackOut[++topOut] = in[pos];
			if (!isdigit(in[pos+1]))
				stackOut[++topOut] = ',';
		}
		else
			if ((in[pos] == '(')||(in[pos] == ')')) 
			{
				if (in[pos] == '(') // ќткрывающую скобку просто закидываем во временный стек
					stackTemp[++topTemp] = in[pos];
				else
				{
					while (stackTemp[topTemp] != '(') // ≈сли скобка закрывающа€, то пушим из временного стека все операции до открывающей скобки. —аму открывающую скобку достаем
						pushFTTO();
					topTemp--;
				}
			}
			else
			{
				if (topTemp == -1) // ≈сли временный стек пустой, то просто закидываем символ в него
					stackTemp[++topTemp] = in[pos];
				else
				if (priority(in[pos]) <= priority(stackTemp[topTemp])) // ≈сли приоритет входной операции не больше приоритета операции на верхушке временного стека,
				{
					pushFTTO();                                                 // то операцию из верхушки пушим в основной стек,
					while (priority(in[pos]) <= priority(stackTemp[topTemp]))   // так же пушим все операции из временного стека, приоритет которых не меньше входной,
					    pushFTTO();
					stackTemp[++topTemp] = in[pos];                             // а входную пушим во временный
				}
				else 
					stackTemp[++topTemp] = in[pos];                    // ≈сли приоритет входной операции больше приоритета операции сверху временного стека, то просто пушим ее в этот стек
			}


	}
	while (topTemp>-1)   // ƒопушиваем все оставшиес€ операции из временного стека в основной
		pushFTTO();
	stackOut[++topOut] = '\0';

	                                           // ѕеревод в обратную польскую систему закончен, теперь считаем ответ

	double a[1000] = {0};
	int i=0, numOfNumbers=0; // i - указатель на положение в строке с обратной польской записью
	while (i<topOut)
	{
		double num = 0;
		if (isdigit(stackOut[i]))  // ѕока идут цифры, составл€ем из них число
        {
			while (isdigit(stackOut[i]))
			    num = num*10.0 + (double)(stackOut[i++] - '0');   
		    a[numOfNumbers++] = num;
			i++;               // ¬ конце оператора while i указывает на зап€тую после числа, поэтому увеличиваем на 1
		}
		else 
			if (!isdigit(stackOut[i]))  // ≈сли встретилась операци€, то примен€ем ее к двум последним числам из массива
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
				i+=2;   // i указывает на операцию, следующий элемент - зап€та€, поэтому увеличиваем на 2
			}
	}
	return a[0];   // ≈динственное оставшеес€ значение и есть результат
}

int main()
{

	return 0;
}