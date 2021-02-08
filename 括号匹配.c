//2021/2/7
#include<stdio.h>
typedef struct Stack {
	char sth[100];
	int ma[100];
	char* top;
	int* to;
}m;
m l;
int mark[100];
int main()
{
	char a[100];
	l.top = l.sth;
	l.to = l.ma;
	scanf("%s", a);
	for (int i = 0; a[i]!='\0'; i++)
	{
		*l.top = a[i];
		*l.to = i + 1;
		if (*(l.top - 1) == '(' && *l.top == ')')//能匹配就出栈
		{
			mark[*(l.to-1)] = *l.to;
			l.to--, l.top--;	
		}

		else
		{
			l.top++;
			l.to++;
		}
	}
	for (int i = 0; a[i]!='\0'; i++)
	{ 
		if (mark[i] != 0)printf("%d %d\n", i, mark[i]);
	}
}
