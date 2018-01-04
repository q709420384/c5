/*************************************************************************
	> File Name: Graph.h
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2018年01月03日 星期三 11时40分42秒
 ************************************************************************/

#ifndef _GRAPH_H
#define _GRAPH_H

#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<iostream>
#include<string.h>
#include<string>
using std::ostream;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::cin;

const int DefaultVertices = 30;  //默认最大顶点数

struct Weight
{

	int distance;       //距离
    double timecost;    //时间花费
    double cost;        //钱数
    Weight(int dis = 0, double ti = 0, double co = 0) : distance(dis), timecost(ti), cost(co)
    {}
    Weight(const Weight &t)
    {
    	distance = t.distance;
    	timecost = t.timecost;
    	cost = t.cost;
    }
    Weight& operator=(Weight t)
    {
    	distance = t.distance;
    	timecost = t.timecost;
    	cost = t.cost;
    	return *this;
    }
    void getvalue(int dis, double ti, double co)
    {
    	distance = dis;
    	timecost = ti;
    	cost = co;
    }
    friend ostream& operator<<(ostream& out, Weight &t);
};

ostream& operator<<(ostream& out, Weight& t)
{
   	out << t.distance << " " << t.timecost << " " << t.cost;
   	return out;
}

class Graph
{
protected:
    int maxVertices;  //图中最大顶点数
    int numEdges;     //当前边数
    int numVertices;  //当前顶点数
    virtual int getVertexPos(const string vertex) = 0; //给出顶点vertex在图中的位置
public:
    const int maxWeight = 9999;               //代表无穷大
    Graph() //构造函数
    {
    	maxVertices = DefaultVertices;
    	numEdges = 0;
    	numVertices = 0;
    }
    virtual ~Graph()
    {}
    bool GraphEmpty()const           //判断图否
    {
        if(numEdges == 0)
            return true;
        else
            return false;
    }
    bool GraphFull()const            //判图满否
    {
        if(numVertices == maxVertices || numEdges == maxVertices * (maxVertices - 1) / 2)
            return true;
        else
            return false;
    }
    int NumberOfVertices()           //返回当前顶点数
    {
        return numVertices;
    }
    int NumberOfEdges()              //返回当前边数
    {
        return numEdges;
    }
    virtual string getValue(int i) = 0;       //取顶点i的值,不合理返回
    virtual Weight getWeight(int v1, int v2) = 0 ;      //取边(v1, v2)上的权值
    virtual int getFirstNeighbor(int v) = 0 ;      //取顶点v第一个邻接顶点
    virtual int getNextNeighbor(int v, int w) = 0 ;//取邻接顶点W的下一个邻接顶点
    virtual bool insertVertex(const string& vertex) = 0 ;//插入一个顶点vertex
    virtual bool insertEdge(int v1, int v2, const char* place, Weight weight) = 0 ; //插入边(v1, v2),权值为cost
    virtual bool removeVertex(int v) = 0 ;       //删去顶点v和所有与相关联边
    virtual bool removeEdge(int v1, int v2) = 0 ; //在图中删去边(v1, v2)
};


struct Edge             //边节点的定义
{
    int dest;           //边的另一顶点位置
    string Place;         //地点名称
    Weight weight;
    Edge* link;   //下一条边链指针
    Edge(){}            //构造函数
    Edge(int num, const char* place, Weight &t) : dest(num), Place(place), weight(t), link(NULL) //构造函数
    {}
    bool operator!= (Edge& R)const          //判边不等否
    {
        return (dest != R.dest) ? true : false;
    }
};

struct Vertex                     //顶点的定义
{
    string data;                  //顶点的名字
    Edge* adj;              //边链表的头指针
};

class Graphlnk : public Graph     //图的类定义
{
    //friend std::istream& operator >>(std::istream& in, Graphlnk<T, E>& G); //输入
    //friend std::ostream& operator <<(std::ostream& out, Graphlnk<T, E>& G); //输出
public:
    Graphlnk(int sz = DefaultVertices);  //构造函数
    ~Graphlnk();                         //析构函数
    string getValue(int i)                    //取位置为i的顶点中的值
    {
        return (i >= 0 && i < this->numVertices) ? NodeTable[i].data : "null";
    }
    Weight getWeight(int v1, int v2);
    bool insertVertex(const string& vertex);  //在图中插入一个顶点vertex
    bool removeVertex(int v);            //在图中删除一个顶点v
    bool insertEdge(int v1, int v2, const char* place, Weight weight); //在图中插入一条边(v1, v2)
    bool removeEdge(int v1, int v2);         //在途中删除一条边(v1, v2)
    int getFirstNeighbor(int v);             //取顶点v的第一个邻接顶点
    int getNextNeighbor(int v, int w);       //取v的邻接顶点w的下一个邻接顶点
    bool init(const char* path);              //初始化
    void print();                            //打印
private:
    Vertex *NodeTable;                 //顶点表(各边链表的头节点)
    int getVertexPos(const string vertex)         //给出顶点vertex在图中的位置
    {
        for(int i = 0; i < this->numVertices; i++)
        {
            if(NodeTable[i].data == vertex)
                return i;
        }
        return -1;
    }
};

Graphlnk::Graphlnk(int sz)  //构造函数: 构造一个空的邻接表
{
    this->maxVertices = sz;
    this->numVertices = 0;
    this->numEdges = 0;
    NodeTable = new Vertex[this->maxVertices];  //创建顶点表数组
    if(NodeTable == NULL)
    {
        cerr << "存储分配错!" << endl;
        exit(1);
    }
    for(int i = 0; i < this->maxVertices; i++)
    {
        NodeTable[i].adj = NULL;
    }
}

Graphlnk::~Graphlnk()       //析构函数: 删除一个邻接表
{
    for(int i = 0; i < this->numVertices; ++i)     //删除各边链表中的结点
    {
        Edge* p = NodeTable[i].adj; //找到其对应边链表的首结点
        while(p != NULL)                  //不断地删除第一个结点
        {
            NodeTable[i].adj = p -> link;
            delete p;
            p = NodeTable[i].adj;
        }
    }
    delete []NodeTable;           //删除顶点表数组
}

int Graphlnk::getFirstNeighbor(int v)   //给出顶点位置为v的第一个邻接顶点的位置，如果找不到，则函数返回-1
{
    if(v != -1)                 //顶点v存在
    {
        Edge *p = NodeTable[v].adj;  //对应边链表第一个边结点
        if(p != NULL)                      //存在，返回第一个邻接顶点
            return p->dest;
    }
    return -1;                             //第一个邻接顶点不存在
}

int Graphlnk::getNextNeighbor(int v, int w)   //给出顶点v的邻接顶点w的下一个邻接顶点的位置，若没有下一个邻接顶点，则函数返回-1
{
    if(v != -1)   //顶点v存在
    {
        Edge *p = NodeTable[v].adj;           //对应边链表第一个边结点
        while(p != NULL && p->dest != w)            //寻找邻接顶点w
        {
            p = p->link;
        }
        if(p != NULL && p->link != NULL)
        {
            return p->link->dest;                   //返回下一个邻接顶点
        }
    }
    return -1;                                      //下一个邻接顶点不存在
};

Weight Graphlnk::getWeight(int v1, int v2)       //函数返回边(v1, v2)上的权值，若该边不在图中，则函数返回权值0
{
    if(v1 != -1 && v2 != -1)
    {
        Edge *p = NodeTable[v1].adj;          //v1的第一条关联的边
        while(p != NULL && p->dest != v2)           //寻找邻接顶点v2
        {
            p = p->link;
        }
        if(p != NULL)                               //找到此边，返回权值
            return p->weight;
    }
    return 0;                                       //边(v1, v2)不存在
};

bool Graphlnk::insertVertex(const string& vertex)   //在图的顶点表中插入一个新顶点vertex。若插入成功,函数返回true,否则返回false
{
    if(this->numVertices == this->maxVertices)                  //顶点表满，不能插入
        return false;
    NodeTable[this->numVertices].data = vertex;           //插入在表的最后
    this->numVertices++;
    return true;
};

bool Graphlnk::removeVertex(int v)            //在图中删除一个指定顶点v,v是顶点号。若删除成功，函数返回true,否则返回false
{
    if(this->numVertices == 1 || v < 0 || v >= this->numVertices) //表空或顶点号超出范围
        return false;
    Edge *p, *s, *t;
    int i, k;
    while(NodeTable[v].adj != NULL)                 //删除第v个边链表中所有结点
    {
        p = NodeTable[v].adj;                       //取邻接顶点k
        k = p->dest;
        s = NodeTable[v].adj;                       //找对称存放的边结点
        t = NULL;
        while(s != NULL && s->dest != v)
        {
            t = s;
            s = s->link;
        }
        if(s != NULL)
        {
            if(t == NULL)
            {
                NodeTable[k].adj = s->link;
            }
            else
                t->link = s->link;
            delete s;
        }
        NodeTable[v].adj = p->link;                 //清除顶点v的边链表结点
        delete p;
        this->numEdges--;                                 //与顶点v相关联的边数减1
    }
    this->numVertices--;                                  //图的顶点个数减1/
    NodeTable[v].data = NodeTable[this->numVertices].data;     //填补
    p = NodeTable[v].adj = NodeTable[this->numVertices].adj;
    while(p != NULL)
    {
        s = NodeTable[p->dest].adj;
        while(s != NULL)
        {
            if(s->dest == this->numVertices)
            {
                s->dest = v;
                break;
            }
            else
                s = s->link;
        }
    }
    return true;
}

bool Graphlnk::insertEdge(int v1, int v2, const char* place, Weight weight) //在带权图中插入一条边(v1, v2),若此边存在或参数不合理，函数返回false,否则返回true。对于非带权图，最后一个参数weight不要。算法中相应语句也不要。
{
    if(v1 >= 0 && v1 < this->numVertices && v2 >= 0 && v2 < this->numVertices)
    {
        Edge *p = NodeTable[v1].adj;            //v1对应的边链表头指针
        while(p != NULL && p->dest != v2)                 //寻找邻接顶点v2
        {
            p = p->link;
        }
        if(p != NULL)
            return false;
        p = new Edge;                 //否则，创建新结点
        p->dest = v2;
        p->Place = place;
        p->weight = weight;
        p->link = NodeTable[v1].adj;         //链入v1边链表
        NodeTable[v1].adj = p;
        this->numEdges++;
        return true;
    }
    return 0;
}

bool Graphlnk::removeEdge(int v1, int v2)         //在图中删除一条边(v1, v2)
{
    if(v1 != -1 && v2 != -1)
    {
        Edge *p = NodeTable[v1].adj, *q = NULL, *s = p;
        while(p != NULL && p->dest != v2)       //v1对应边链表中找被删边
        {
            q = p;
            p = p->link;
        }
        if(p != NULL)                           //找到被删边结点
        {
            if(p == s)                       //该结点是边链表首结点
            {
                NodeTable[v1].adj = p->link;
            }
            else                             //不是重新链接
            {
                q->link = p->link;
            }
            delete p;
        }
        else
            return false;
        p = NodeTable[v2].adj;
        q = NULL; s = p;                     //v2对应边链表中删除
        while(p->dest != v1)                 //寻找被删边结点
        {
            q = p;
            p = p->link;
        }
        if(p == s)                           //该结点是边链表首结点
            NodeTable[v2].adj = p->link;
        else                                 //不是重新链接
            q->link = p->link;
        delete p;
        return true;
    }
    return false;                            //没有找到结点
}

bool Graphlnk::init(const char* path)
{
	DIR* dir;
	struct dirent* ptr;
	dir = opendir(path);
	if(dir == NULL)
	{
		return false;
	}
    while ((ptr = readdir(dir)) != NULL)
    {
		if(ptr->d_name[0] == '.')
			continue;
		NodeTable[this->numVertices++].data = ptr->d_name;
    }
    closedir(dir);
    char buff[256], place[256];
    strcpy(buff, path);
    int len = strlen(path), dis;
    double time, cost;
    Weight weight;
    for(int i = 0; i < this->numVertices; ++i)
    {
    	strcpy(buff + len, NodeTable[i].data.c_str());
    	FILE* fp = fopen(buff, "r");
    	
    	while(fscanf(fp,"%s %d %lf %lf", place, &dis, &time, &cost) != EOF)
    	{
			Weight weight(dis, time, cost);
			this->insertEdge(i, getVertexPos(place), place, weight);
    	}
    	fclose(fp);
    }
    return true;
}

void Graphlnk::print()
{
	for(int i = 0; i < this->numVertices; ++i)
	{
		cout << NodeTable[i].data << ":" <<endl;
		Edge* p = NodeTable[i].adj;
		while(p != NULL)
		{
			cout << p-> dest << " " << p->Place << " " ;
			cout << p->weight << endl;
			p = p->link;
		}
	}
}
#endif
