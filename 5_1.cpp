#include <iostream>

using namespace std;

char opening[3] = {'(', '{', '['};
char closing[3] = {')', '}', ']'};

bool solve (char in[], int lenIn)
{
	char stack[10000];
	int top = 0;
	if ((in[0] == '}')||(in[0] == ')')||(in[0] == ']')) return false;
	stack[top] = in[0];
	for (int i=1;i<lenIn;i++)
	{
		bool inClosing = false;
		for (int j=0;j<3;j++)
    		if (in[i] == closing[j])
	    		if (stack[top] == opening[j])
				{
					inClosing = true;
		    		top--;
				}
			    else
				    return false;
		if (!inClosing)
			stack[++top] = in[i];
	}
	if (top==-1) return true;
	else return false;
}
		

int main()
{
	char a[1000];
	cin >> a;
	cout << solve(a, strlen(a));
	system("pause");
	return 0;
}