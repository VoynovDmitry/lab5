#include <iostream>	

using namespace std;

bool bracket(char* str)
{
	int size = strlen(str);
	struct stack {
		char bracket;
		stack* next;
	};
	stack* head = NULL;
	stack* current;
	bool test = true;
	for (int i = 0; (i < size) && (test != false); i++)
	{
		switch (str[i])
		{
		case '(':
			current = new stack;
			current->bracket = '(';
			current->next = head;
			head = current;
			break;
		case '[':
			current = new stack;
			current->bracket = '[';
			current->next = head;
			head = current;
			break;
		case '{':
			current = new stack;
			current->bracket = '{';
			current->next = head;
			head = current;
			break;
		case ')':
			if (head != NULL && head->bracket == '(')
			{
				head = head->next;
				break;
			}
			else
			{
				test = false;
				break;
			}
		case ']':
			if (head != NULL && head->bracket == '[')
			{
				head = head->next;
				break;
			}
			else
			{
				test = false;
				break;
			}
		case '}':
			if (head != NULL && head->bracket == '{')
			{
				head = head->next;
				break;
			}
			else
			{
				test = false;
				break;
			}
		}
	}
	if (test == false || head != NULL) return false;
	else return true;
}

int main()
{
	char string[100];
	cin >> string;
	cout << bracket(string) << endl;
	return 0;
}