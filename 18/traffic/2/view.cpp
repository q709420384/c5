/*************************************************************************
> File Name: view.cpp
> Author:Sanjingye 
> Mail: 
> Created Time: 2018年01月05日 星期五 09时12分35秒
************************************************************************/

#include"view.h"


char getch()
{
	char c;
	system("stty -echo");
	system("stty -icanon");
	c=getchar();
	system("stty icanon");
	system("stty echo");
	return c;
}
char* s_gets(char* st,int n)
{
    char* ret_val;
    int i=0;
    ret_val=fgets(st,n,stdin);
    if(ret_val)
    {
        while(st[i]!='\n'&&st[i]!='\0')
        i++;
        if(st[i]=='\n')
        st[i]='\0';
        else
        while(getchar()!='\n')
        continue;
    }
    return ret_val;
}
bool CheckPassword()
{
	cout << "请输入密码:" << endl;
    char passwd[20], ch;
    int i = 0;
    while(i<20&&(ch=getch(),ch!='\n'))
    {
        if(ch==127)
        {
            if(i>0)
            {
                i--;
                printf("\b \b");
            }
            else
            putchar(7);
        }
        else
        {
            passwd[i++]=ch;
            putchar('*');
        }
    }
    passwd[i]='\0';
    puts("");
    if(strcmp(passwd, "lijiahao") == 0)
        return true;
    return false;
}
void Register(Graphlnk &G)   //登陆
{
    char chose[10];
    while(1)
    {
        system("clear");
        printf("\033[32m\t\t\t\t1. 管理员登陆\n");
        printf("\t\t\t\t2. 普通登陆\n");
        printf("\t\t\t\t3. 结束\n\033[0m");
        printf("请选择登陆方式:\n");
        s_gets(chose, 10);
        if(strcmp("1", chose) == 0)
        {
            if(CheckPassword())
            {
                RootView(G);
            }
            else
            {
                cerr << "密码输入错误" << endl;
                sleep(2);
            }
        }
        else if(strcmp("2", chose) == 0)
        	VisitorsView(G);
        else if(strcmp("3", chose) == 0)
        	break;
    }

}
int RootView(Graphlnk &G)
{
    char chose[10];
    while(1)
    {
		system("clear");
		G.print();
		printf("\033[35m\t\t\t\t1. 增加城市\n");
		printf("\t\t\t\t2. 删除城市\n");
		printf("\t\t\t\t3. 增加路线\n");
		printf("\t\t\t\t4. 删除路线\n");
		printf("\t\t\t\t5. 退出\n\033[0m");
		cout << "请选择:" << endl;
		s_gets(chose, 10);
		if(strcmp(chose, "1") == 0)
		{
			string place;
			cout << "请输入要添加的城市:" << endl;
			cin >> place;
			if(G.insertVertex(place))
			{
		        cout << "添加成功" << endl;
		    }
		    else
		    {
		        cout << "添加失败" << endl;
		    }
		    sleep(2);
		}
		else if(strcmp(chose,"2") == 0)
		{

		    string place;
		    cout << "请输入要删除城市的名称:" << endl;
		    cin >> place;
		    if(G.removeVertex(place))
		    {
		        cout << "删除成功" << endl;
		    }
		    else
		    {
		        cout << "删除失败" << endl;
		    }
		    sleep(2);

		}
		else if(strcmp(chose,"3") == 0)
		{
			string c1, c2;
			Weight weight;
			cout << "起始城市:" << endl;
			cin >> c1;
			cout << "到达城市:" << endl;
			cin >> c2;
			cout << "请依次输入 距离 时间 花费" << endl;
			scanf("%d %lf %lf", &weight.distance, &weight.timecost, &weight.cost);
			if(G.insertEdge(c1, c2, weight))
			{
				G.writefile();
				cout << "添加路线成功" << endl;
			}
			else
			{
				cout << "添加路线失败" << endl;
			}
			sleep(2);
		}
		else if(strcmp(chose,"4") == 0)
		{
			string c1, c2;
			cout << "起始城市:" << endl;
			cin >> c1;
			cout << "到达城市:" << endl;
			cin >> c2;
			if(G.removeEdge(c1, c2))
			{
				G.writefile();
				cout << "删除路线成功" << endl;
			}
			else
			{
				cout << "删除路线失败" << endl;
			}
			sleep(2);
		}
		else if(strcmp(chose,"5") == 0)
		    break;
	}
}
int VisitorsView(Graphlnk &G)
{
	char chose[10];
	while(1)
	{
		system("clear");
		G.print();
		printf("\033[34m\t\t\t\t1. 距离最短优先\n");
		printf("\t\t\t\t2. 中转最少优先\n");
		printf("\t\t\t\t3. 时间最少优先\n");
		printf("\t\t\t\t4. 花费最少优先\n");
		printf("\t\t\t\t5. 退出\n\033[0m");
		cout << "请选择:" << endl;
		s_gets(chose, 10);
		if(strcmp(chose, "1") == 0)
		{
			string c1, c2;
			cout << "起始城市" << endl;
			cin >> c1;
			cout << "到达地点" << endl;
			cin >> c2;
			G.dijkstra(c1, 1);
			G.printShorestPath(c1, c2);
			getchar();
			getchar();
		}
		else if(strcmp(chose, "2") == 0)
		{
			string c1, c2;
			cout << "起始城市" << endl;
			cin >> c1;
			cout << "到达地点" << endl;
			cin >> c2;
			G.dijkstra(c1, 2);
			G.printShorestPath(c1, c2);
			getchar();
			getchar();
		}
		else if(strcmp(chose, "3") == 0)
		{
			string c1, c2;
			cout << "起始城市" << endl;
			cin >> c1;
			cout << "到达地点" << endl;
			cin >> c2;
			G.dijkstra(c1, 3);
			G.printShorestPath(c1, c2);
			getchar();
			getchar();
		}
		else if(strcmp(chose, "4") == 0)
			;
		else if(strcmp(chose, "5") == 0)
			break;
	}
}
