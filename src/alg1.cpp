#include "tstack.h"
#include <iostream>
using namespace std;

int transform(char input)
{
	switch (input)
	{
	case '(': return 0;
	case ')': return 1;
	case '+': return 2;
	case '-': return 2;
	case '*': return 3;
	case '/': return 3;
	default: return -1;
	}
}

string infx2pstfx(string inf)
{
	TStack<char> stack1;
	string temp = " ";
	for (int i = 0; i < inf.size(); i++)
	{
		char ch = inf[i];
		int a = transform(ch);

		if (a == -1)
			temp.append(string(1, ch));
		else
			if (stack1.isEmpty() || a == 0 || a > transform(stack1.get()))
				stack1.push(ch);
			else
			{
				if (ch == ')')
					while (true)
					{
						char sym = stack1.get();
						stack1.pop();
						if (sym != '(')
							temp.append(string(1, sym));
						else
							break;
					}
				else
				{
					while (!stack1.isEmpty())
					{
						char lastStackEl = stack1.get();
						stack1.pop();
						if (transform(lastStackEl) >= a)
							temp.append(string(1, lastStackEl));
					}
					stack1.push(ch);
				}
			}
	}
	while (!stack1.isEmpty())
	{
		char Stack = stack1.get();
		stack1.pop();
		temp.append(string(1, Stack));
	}
	return temp;
}

int ex_transform(int r1, int r2, char pst)
{
	switch (pst)
	{
	case '+': return r1 + r2;
	case '-': return r1 - r2;
	case '*': return r1 * r2;
	case '/': return r1 / r2;
	default: return -1;
	}
}

int eval(string pst)
{
	TStack<int> stack2;
	for (int i = 0; i < pst.size(); i++)
	{
		char ch = pst[i];
		int b = transform(ch);

		if (b == -1)
			stack2.push(ch - 48);
		else
		{
			int  r1 = stack2.get();
			stack2.pop();

			int r2 = stack2.get();
			stack2.pop();

			int res = ex_transform(r2, r1, ch);
			stack2.push(res);
		}

	}
	return stack2.get();
}
