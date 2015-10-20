#include <iostream>

using namespace std;

char max(char a, char b)
{
	if (a > b) return a;
	else return b;
}

char min(char a, char b)
{
	if (a < b) return a;
	else return b;
}

char maxmin(char *str)
{
	int size = strlen(str);
	struct stack {
		char ch;
		stack *next;
	};
	stack *head = NULL;
	stack *current;
	for (int i = 0; i < size; i++)
	{
		if (str[i] == 'n'|| str[i] == 'x' || isdigit(str[i]) )
		{
			current = new stack;
			current->ch = str[i];
			current->next = head;
			head = current;
		}
		if (str[i] == ')')
		{
			if (head->next->next->ch == 'n')
			{
				head->next->next->ch = min(head->ch, head->next->ch);
				head = head->next->next;
			}
			else 
			{
				head->next->next->ch = max(head->ch, head->next->ch);
				head = head->next->next;
			}
		}
	}
	return head->ch;
}

void assert(char test[], char ans)
{
	if (maxmin(test) == ans) cout << "OK" << endl;
	else cout << "FAIL" << endl;
}

int main()
{
	assert("max(4,min(max(1,3),min(8,5)))", '4');
	assert("max(1,7)", '7');
	assert("min(max(min(2,5),max(3,4)),min(max(8,min(9,9)),8))", '4');
	assert("max(1,min(2,max(3,min(4,max(5,min(6,max(7,min(8,9))))))))", '2');

	
	
	return 0;
}