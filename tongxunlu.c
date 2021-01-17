#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
FILE* fp;
typedef struct link {
	struct link* previous;
	char name[11];
	char num[12];
	char e_mail[20];
	char note[60];
	struct link* next;
}m;
struct link* head = NULL, * last, * current;
void menu();
void all();
void save();
void out();
m*rank();
m* search();
char* f_gets(char* st, int n) {
	char* ret_val;
	char* find;

	ret_val = fgets(st, n, fp);
	if (ret_val)
	{
		find = strchr(st, '\n');//查找换行符
		if (find)//如果地址不是null
			*find = '\0';//在此处放置一个空字符
		else//输入超限时吃掉屏幕上的字符

			while (getchar() != '\n')
				continue;// 处理剩余输入行
	}
	return ret_val;
}
char* s_gets(char* st, int n) {
	char* ret_val;
	char* find;

	ret_val = fgets(st, n, stdin);
	if (ret_val)
	{
		find = strchr(st, '\n');//查找换行符
		if (find)//如果地址不是null
			*find = '\0';//在此处放置一个空字符
		else

			while (getchar() != '\n')
				continue;// 处理剩余输入行
	}
	return ret_val;
}
void input() {

	char m[11], n[12], p[20], q[60];//这是输入功能，可以随时加入
	fp = fopen("file.txt", "a");
	printf("请输入姓名：\n");
	if (fp)while (s_gets(m, 11) != NULL && m[0] != '\0') {
		printf("手机号：\n");
		s_gets(n, 12);
		printf("电子邮箱：\n");
		s_gets(p, 20);
		printf("备注：\n");
		s_gets(q, 60);
		if (head == NULL)
		{
			head = (struct link*)malloc(sizeof(struct link));
			current = head;
		} 
		else
		{
			current->next = (struct link*)malloc(sizeof(struct link));
			current->next->previous = current;//将前一个的指针指向
			current = current->next;
		}
		strcpy(current->name, m);
		strcpy(current->num, n);
		strcpy(current->e_mail, p); strcpy(current->note, q);
		//fprintf(fp, "%s\n%s\n%s\n%s\n", current->name, current->num, current->e_mail, current->note);
		last = current;
		current->next = NULL;//将下一个置为空指针
		printf("请输入姓名：\n");
	}//姓名 手机号 qq e-mail 备注 性别 	

	fclose(fp);

}
struct link* pre, * cur;
struct link* search_d_c() {//关键字查找
	if (head == NULL)
	{
		printf("通讯录内无数据！\n");
		menu();
	}
	printf("请输入要查找的内容\n");
	char in[20];
	cur = head;
	pre = head;
	s_gets(in, 20);
	m *temp[20];
	int nn = 0;
	for (; ; cur = cur->next)
	{
		if (strcmp(in, cur->name) == 0 || strcmp(in, cur->num) == 0 || strcmp(in, cur->e_mail) == 0)
		{
			temp[nn] =cur ; nn++;
			printf("查找成功！\n%d： 姓名 : %s\n电话 : %s\ne-mail: %s\n备注 : %s\n",nn, cur->name, cur->num, cur->e_mail, cur->note);
			if(cur->next==NULL&&nn==1)return cur; 
			else 
			{
				char a;
				printf("请输入要修改或者删除的编号\n");
				a = getch();
				return temp[a - '0'-1];
			}
			

				
		}
		else {
			if (cur->next == NULL) { printf("查找失败！\n"); break; }
		}
		pre = cur;
	}
	return NULL;
	//return cur;
}
void correct() {//修改人员信息,能否继续修改？？修改后是否能放入文件？？
	int n;
	//printf("请输入姓名或号码qq或e-mail：\n");
	struct link* cur = search_d_c();
	if (cur == NULL)
	{
		system("cls");
		menu();
	}
	char in[60];
	printf("请输入要修改的内容：1.姓名2.号码3.e-mail4.备注others返回主菜单\n");
	n = getch();
	
	switch (n - '0') {
	case 2:printf("请输入修改后的值\n"); s_gets(in, 12); strcpy(cur->num, in); break;
	case 1:printf("请输入修改后的值\n"); s_gets(in, 11); strcpy(cur->name, in); break;
	case 3:printf("请输入修改后的值\n"); s_gets(in, 20); strcpy(cur->e_mail, in); break;
	case 4:printf("请输入修改后的值\n"); s_gets(in, 60); strcpy(cur->note, in); break;
	default:break;
	}
	system("cls");
	//printf("修改成功！\n");
}
void del() {
	struct link* cur = search_d_c();
	if(cur!=NULL)
	{
		if (cur == head)
		{
			head = head->next;
		}
		else
			pre->next = cur->next;
		free(cur);printf("从通讯录中删除成功！\n");
	}
	else 
	{
		printf("查找失败，要删除的用户不存在！\n");
	}
	
}
void read() {
	//FILE* fp;
	fp = fopen("file.txt", "r");
	char nam[20] = { 0 };
	if (fp)for (; ; current->next = NULL)
	{
		if (f_gets(nam, 20) == NULL)break;
		if (nam[0] == '\0')break;//使用strcpy方便结束
		if (head == NULL)
		{
			head = (struct link*)malloc(sizeof(struct link));
			current = head;
		}
		else
		{
			current->next = (struct link*)malloc(sizeof(struct link));// 分配空间
			current = current->next;
		}
		strcpy(current->name, nam);
		f_gets(current->num, 20); f_gets(current->e_mail, 20); f_gets(current->note, 60);
	}
	fclose(fp);
}
int main()
{
	//FILE*fp;
	current = head;
	menu();
}
void menu() {
flag:
	printf("******通讯录************\n");
	printf("***1.输入功能***********\n");
	printf("***2.查询功能***********\n");//可以创造一个按关键字查询的应用
	printf("***3.排序输出功能*******\n");
	printf("***4.修改功能***********\n");
	printf("***5.删除功能***********\n");
	printf("***6.从文件中读取数据***\n");
	printf("***7.保存退出***********\n");
	printf("***8.删除全部数据*******\n");
	printf("**请输入需要实现的功能：*\n");
	int n;
	n = getch();


	switch (n - '0')
	{
	case 1:system("cls"); input();
		system("cls");
		printf("输入成功,返回主菜单！\n");
		goto flag;
		break;
	case 2:system("cls"); search(); system("pause"); system("cls"); goto flag;
		break;
	case 3:system("cls"); out(); system("pause"); system("cls"); goto flag;
		break;
	case 4:system("cls"); correct(); goto flag;
		break;
	case 5:system("cls"); del(); system("pause"); system("cls"); goto flag;
		break;
	case 6:system("cls"); read(); printf("读取完成！\n"); goto flag;
	case 7:save();
	case 8:all(); system("cls"); printf("所有数据已被删除！\n"); goto flag;
	default:
		system("cls");
		printf("请重新输入\n");
		goto flag;
	}
}
void out() {
	int amount=0;
	if (head == NULL)
	{
		printf("通信录内没有数据！\n");
		menu();
	}
	m* t = rank(); 
	if (t)for (; ; t = t->next)
	{
		
		printf("%d.姓名:%s\n电话:%s\n电子邮箱:%s\n备注：%s\n",amount+1, t->name, t->num, t->e_mail, t->note);
		amount++;
		if (t->next == NULL) { 
			
			break; }
	}
}
m* rank()//按姓名排序
{
	m* las=head;
	if(head)for (int a = 0; a < 200; a++) {
		int circle = 0;
		for (m* i = head; i->next != NULL && i != NULL; )
		{
			
				if (strcmp(i->name, i->next->name) > 0)
				{
					circle++;
					if (i != head) {
						las->next = i->next;
						i->next = i->next->next;
						las->next->next = i;
						las = las->next;
					}
					else
					{
						head =head->next;
						i->next = i->next->next;
						head->next = i;
						las = head;

					}
				}

			
			else {
				las = i; i = i->next;
				if (i->next == NULL)break;
			}

		}
		if (circle == 0)break;
	}
	return head;
}
struct link* search() {
	if (head == NULL)
	{
		printf("通讯录内无数据！\n");
		menu();
	}
	printf("请输入要查找的内容\n");
	//while (getchar() != '\n');
	char in[20];
	cur = head;
	pre = head;
	s_gets(in, 20);
	int nn = 0;
	for (; cur!=NULL; cur = cur->next)
	{
		if (strcmp(in, cur->name) == 0 || strcmp(in, cur->num) == 0 || strcmp(in, cur->e_mail) == 0)
		{
			
			nn++;
			printf("查找成功！\n%d： 姓名 : %s\n电话 : %s\ne-mail: %s\n备注 : %s\n", nn,cur->name, cur->num, cur->e_mail, cur->note);
			if (cur->next == NULL)break;
		}
		else 
		{
			if (cur->next == NULL&&nn==0) { printf("查找失败！\n"); break; }
		}
		pre = cur;
	}
	return NULL;
	//return cur;
}
void save()

{
	FILE* fp;
	fp = fopen("file.txt", "w");
	for (m* i = head;i!=NULL ; i=i->next)
	{
		if(i)fprintf(fp, "%s\n%s\n%s\n%s\n", i->name, i->num, i->e_mail, i->note);
	}
	fclose(fp);
	exit(0);
}
void all()
{
	m*p;
	for (m* i = head;i!=NULL;)
	{
		p = i->next;
		if (i == head) { head = NULL; }
		else free(i);
		i = p;
	}
}
