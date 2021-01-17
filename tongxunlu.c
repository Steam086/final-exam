#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
FILE* fp;
void menu(void);
void out(void);
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
struct link {
	struct link* previous;
	char name[11];
	char num[12];
	//char qq[12];
	//int gender;//1表示男，0女
	char e_mail[20];
	char note[60];//备注
	struct link* next;
};
struct link* head = NULL, * last, * current;
void input() {
	
	char m[11], n[12], p[20], q[60];//这是输入功能，可以随时加入
	//while (getchar() != '\n');
	fp = fopen("D:/file.txt", "a");
	printf("请输入姓名：\n");
	if(fp)while (s_gets(m, 11) != NULL && m[0] != '\0') {
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
		}//头指针  
		else
		{
			current->next = (struct link*)malloc(sizeof(struct link));
			current->next->previous = current;//将前一个的指针指向
			current = current->next;
		}
		strcpy(current->name, m);
		strcpy(current->num, n);//strcpy(current->qq,o);
		strcpy(current->e_mail, p); strcpy(current->note, q);
		fprintf(fp, "%s\n%s\n%s\n%s\n", current->name, current->num, current->e_mail, current->note);
		//printf("请输入性别，1.男，2.女\n");
		//scanf("%d",&current->gender);
		//while(getchar()!='\n');
		last = current;
		current->next = NULL;//将下一个置为空指针
		printf("请输入姓名：\n");
		//保存在文件中
		//可以新建一个函数来保存在文件中
		//每次添加成功后都保存在文件中	//current->qq,
	}//姓名 手机号 qq e-mail 备注 性别 	

	//fclose(fp);

}




struct link* pre, * cur;
struct link* search() {//关键字查找
	//最后的查找失败
	printf("请输入要查找的内容\n");
	//while (getchar() != '\n');
	char in[20];//可用宏定义随时修改
	cur = head;
	s_gets(in, 20);//只有精准输入才能实现,可以考虑一下部分查找，比如查找 某个姓
	for (; ; cur = cur->next)
	{
		if (strcmp(in, cur->name) == 0 || strcmp(in, cur->num) == 0 || strcmp(in, cur->e_mail) == 0)
		{
			printf("查找成功！\n 姓名：%s\n 电话：%s\ne-mail:%s\n备注：%s\n", cur->name, cur->num, cur->e_mail, cur->note);
			if(pre==NULL)
				return cur; break;
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
	struct link* cur = search();
	if (cur == NULL)
	{
		menu();
	}
	char in[60];
	printf("请输入要修改的内容：1.姓名2.号码3.e-mail4.备注others返回主菜单\n");
	//scanf("%d", &n);
	n=getch();
	printf("请输入修改后的值\n");
	//getchar();//吃掉回车
	switch (n-'0') {
	case 2:s_gets(in, 12); strcpy(cur->num, in); break;
	case 1:s_gets(in, 11); strcpy(cur->name, in); break;
	case 3:s_gets(in, 20); strcpy(cur->e_mail, in); break;
	case 4:s_gets(in, 60); strcpy(cur->note, in); break;
	default:menu(); break;
	}
}

		

void del(){
	//getchar();
	struct link* cur = search();
	if (cur == NULL)
	{
		printf("查找失败，要删除的用户不存在！\n");
	}
	else
	{
		if (cur == head)
		{
		head = head->next;
		}
		else 
		pre->next = cur->next;
		free(cur);	
	}
	printf("从通讯录中删除成功！\n");
	menu();//转到menu
}//没问题



void read(){//读取函数
	//读取时如果为空，那么会囤囤囤
	fp = fopen("D:/file.txt", "r");
	char nam[20] = { 0 };
	if (fp)for ( ; ; current->next = NULL)
			{
				if (f_gets(nam,20)==NULL)break;
				if (nam[0] == '\0')break;//使用strcpy方便结束
				if (nam[0] == '\0')break;//使用strcpy方便结束
				if (head == NULL)
				{
					head= (struct link*)malloc(sizeof(struct link));
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


//菜单函数
void menu(){
flag:
	printf("******通讯录**********\n");
	printf("***1.输入功能*********\n");
	printf("***2.查询功能*********\n");//可以创造一个按关键字查询的应用
	printf("***3.排序输出功能*****\n");
	printf("***4.修改功能*********\n");
	printf("***5.删除功能*********\n");
	printf("***6.从文件中读取数据**\n");
	printf("**请输入需要实现的功能：*\n");
	int n;
	n=getch();
	

	switch (n-'0')
	{
	case 1:system("cls"); input(); 
		system("cls");
		printf("输入成功,返回主菜单！\n");
		goto flag;
		break;
	case 2:system("cls"); search(); system("pause"); goto flag;
		break;
	case 3:system("cls"); out(); system("pause"); system("cls"); goto flag;
		break;
	case 4:system("cls"); correct(); goto flag;
		break;
	case 5:system("cls"); del(); system("pause"); system("cls"); goto flag;
		break;
	case 6:system("cls"); read(); printf("读取完成！\n"); goto flag;
	default:
		system("cls");
		printf("请重新输入\n");
		goto flag;
	}
}


//输出函数
void out(){
	struct link* t = head;
	
	if(t)for (; ; t = t->next)
	{
		printf("姓名:%s\n电话:%s\n电子邮箱:%s\n备注：%s\n", t->name, t->num, t->e_mail, t->note);
		if (t->next == NULL)break;
	}
}
