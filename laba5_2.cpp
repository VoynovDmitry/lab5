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

int main()
{
	
	return 0;
}