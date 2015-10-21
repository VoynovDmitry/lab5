#include <iostream>

using namespace std;

char opening[3] = {'(', '{', '['};
char closing[3] = {')', '}', ']'};

bool solve (char in[], int lenIn)
{
	char stack[10000];  // Инициализация стека
	int top = 0;
	if ((in[0] == '}')||(in[0] == ')')||(in[0] == ']')) return false; 
	stack[top] = in[0];          // Если первая скобка закрывающая - противоречие, в противном случае пушим скобку в стек
	for (int i=1;i<lenIn;i++)
	{
		bool inClosing = false;  
		for (int j=0;j<3;j++)
    		if (in[i] == closing[j])                // Если входящая скобка закрывающая, то
	    		if (stack[top] == opening[j])   // если скобка сверху стека есть соответствующая открывающая, то
				{        
                                      top--;             // достаем эту скобку из стека       
		                      inClosing = true;   // Указывает на то, что входящая скобка была закрывающей
				}
			    else
				    return false;  // Если же скобка сверху стека оказалась несоответствующей открывающей, то противоречие
		if (!inClosing) 
			stack[++top] = in[i]; // Если скобка открывающая, то пушим ее в стек
	}
	if (top==-1) return true;  // Если в конце стек оказался пустым, то последовательность правильная, 
	else return false;        // в противном случае нет
}

void assert(char* str, int length, bool test)
{
	if (solve(str, length) == test) cout << "OK" << endl;
	else cout << "FAIL" << endl;
}
		
int main()
{
	assert("(([])({}))", 10, true);
	assert(")))", 3, false);
	assert("()()())}}}{{}", 13, false);
	assert("(((()()", 7, false);
	assert("[(){}{{}}]((({{}})))", 20, true);

	return 0;
}