/*************************************************************************
	> File Name: Graph.h
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2018年01月03日 星期三 11时40分42秒
 ************************************************************************/

#ifndef _GRAPH_H
#define _GRAPH_H
const int DefaultVertices = 30;  //默认最大顶点数
enum bool{false, true};
template<class T, class E>
class Graph
{
protected:
    int maxVertices;  //图中最大顶点数
    int numEdges;     //当前边数
    int numVertices   //当前顶点数
    virtual int getVertexPos(T vertex)  //给出顶点vertex在图中的位置
public:
    const E maxWeight;               //代表无穷大
    Graph(int sz = DefaultVertices); //构造函数
    ~Graph();
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
    int NumberOfEdges                //返回当前边数
    {
        return numEdges;
    }
    virtual T getValue(int i) = 0;       //取顶点i的值,不合理返回
    virtual E getWeight(int v1, int v2);      //取边(v1, v2)上的权值
    virtual int getFirstNeighbor(int v);      //取顶点v第一个邻接顶点
    virtual int getNextNeighbor(int v, int w);//取邻接顶点W的下一个邻接顶点
    virtual bool insertVertex(const T& vertex);//插入一个顶点vertex
    virtual bool insertEdge(int v1, int v2, E cost); //插入边(v1, v2),权值为cost
    virtual bool removeVertex(int v);       //删去顶点v和所有与相关联边
    virtual bool removeEdge(int v1, int v2); //在图中删去边(v1, v2)
};

template<class T, class E>
struct Edge             //边节点的定义
{
    int dest;           //边的另一顶点位置
    E cost;             //边上的权值
    Edge<T, E> *link;   //下一条边链指针
    Edge(){}            //构造函数
    Edge(int num, E weight) : dest(num), cost(weight), link(NULL) //构造函数
    {}
    bool operator!= (Edge<T, E>& R)const          //判边不等否
    {
        return (dest != R.desk) ? true : false;
    }
};

template<class T, class E>
struct vertex                     //顶点的定义
{
    T data;                       //顶点的名字
    Edge<T, E> *adj;              //边链表的头指针
};

template<class T, class E>
class Graphlnk : public Graph<T, E>      //图的类定义
{
    friend istream& operator >>(istream& in, Graphlnk<T, E>& G); //输入
    friend ostream& operator <<(ostream& out, Graphlnk<T, E>& G); //输出
public:
    Graphlnk(int sz = DefaultVertices);  //构造函数
    ~Graphlnk();                         //析构函数
    T getValue(int i)                    //取位置为i的顶点中的值
    {
        return (i >= 0 && i < numVertices) ? NodeTable[i].data : 0;
    }
    E getWeight(int v1, int v2);
    bool insertVertex(const T& vertex);  //在图中插入一个顶点vertex
    bool removeVertex(int v);            //在图中删除一个顶点v
    bool insertEdge(int v1, int v2, E cost); //在图中插入一条边(v1, v2)
    bool removeEdge(int v1, int v2);         //在途中删除一条边(v1, v2)
    int getFirstNeighbor(int v);             //取顶点v的第一个邻接顶点
    int getNextNeighbor(int v, int w);       //取v的邻接顶点w的下一个邻接顶点
private:
    Vertex<T, E> *NodeTable;                 //顶点表(各边链表的头节点)
    int getVertexPos(const T vertex)         //给出顶点vertex在图中的位置
    {
        for(int i = 0; i < numVertices; i++)
        {
            if(NodeTable[i].data == Vertex)
                return i;
        }
        return -1;
    }
}

template<class T, class E>
Graphlnk<T, E>::Graphlnk(int sz)  //构造函数: 构造一个空的邻接表
{
    maxVertices = sz;
    numVertices = 0;
    numEdges = 0;
    NodeTable = new Vertex<T, E>[maxVertices];  //创建顶点表数组
    if(NodeTable == NULL)
    {
        cerr << "存储分配错!" << endl;
        exit(1);
    }
    for(int i = 0; i < maxVerticesl; i++)
    {
        NodeTable[i].adj = NULL;
    }
};

template<class T, class E>
Graphlnk<T, E>::~Graphlnk()       //析构函数: 删除一个邻接表
{
    for(int i = 0l i < numVertices)     //删除各边链表中的结点
    {
        Edge<T, E> *p = NodeTable[i].adj; //找到其对应边链表的首结点
        while(p != NULL)                  //不断地删除第一个结点
        {
            NodeTable[i].adj = p -> link;
            delete p;
            p = NodeTable[i].adj;
        }
    }
    delete []NodeTable;           //删除顶点表数组
};

template<class T, class E>
int Graphlnk<T, E>::getFirstNeighbor(int v)   //给出顶点位置为v的第一个邻接顶点的位置，如果找不到，则函数返回-1
{
    if(v != -1)                 //顶点v存在
    {
        Edge<T, E> *p = NodeTable[v].adj;  //对应边链表第一个边结点
        if(p != NULL)                      //存在，返回第一个邻接顶点
            return p->dest;
    }
    return -1;                             //第一个邻接顶点不存在
};

template<class T, class E>
int Graphlnk<T, E>::getNextNeighbor(int v, int w)   //给出顶点v的邻接顶点w的下一个邻接顶点的位置，若没有下一个邻接顶点，则函数返回-1
{
    if(v != -1)   //顶点v存在
    {
        Edge<T, E> *p = NodeTable[v].adj;           //对应边链表第一个边结点
        while(p != NULL && p->dest != w)            //寻找邻接顶点w
        {
            p = p->link;
        }
        if(p != NULL && p->link != NULL)
        {
            return p->link->desk;                   //返回下一个邻接顶点
        }
    }
    return -1;                                      //下一个邻接顶点不存在
};

template<class T, class E>
E Graphlnk<T, E>::getWeight(int v1, int v2)         //函数返回边(v1, v2)上的权值，若该边不在图中，则函数返回权值0
{
    if(v1 != -1 && v2 != -1)
    {
        Edge<T, E> *p = NodeTable[v1].adj;          //v1的第一条关联的边
        while(p != NULL && p->dest != v2)           //寻找邻接顶点v2
        {
            p = p->link;
        }
        if(p != NULL)                               //找到此边，返回权值
            return p->cost;
    }
    return 0;                                       //边(v1, v2)不存在
};

template<class T, class E>
bool Graphlnk::insertVertex(const T& vertex)   //在图的顶点表中插入一个新顶点vertex。若插入成功,函数返回true,否则返回false
{
    if(numVertices == maxVertices)                  //顶点表满，不能插入
        return false;
    NodeTable[numVertices].data = vertex;           //插入在表的最后
    numVertices++;
    return true;
};
mZ
bool Graphlnk<T, E>::removeVertex(int v)            //在图中删除一个指定顶点v,v是顶点号。若删除成功，函数返回true,否则返回false
{
    if(numVertices == 1 || v < 0 || v >= numVertices) //表空或顶点号超出范围
        return false;
    Edge<T, E> *p, *s, *t;
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
        numEdges--;                                 //与顶点v相关联的边数减1
    }
    numVertices--;                                  //图的顶点个数减1/
    Node[v].data = NodeTable[numVertices].data;     //填补
    p = NodeTable[v].adj = NodeTable[numVertices].adj;
    while(p != NULL)
    {
        s = NodeTable[p->dest].adj;
        while(s != NULL)
        {
            if(s->dest == numVertices)
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

template<class T, class E>
bool Graphlnk<T, E>::insertEdge(int v1, int v2, E weight) //在带权图中插入一条边(v1, v2),若此边存在或参数不合理，函数返回false,否则返回true。对于非带权图，最后一个参数weight不要。算法中相应语句也不要。
{
    if(v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices)
    {
        Edge<T, E> *q, *p = NodeTable[v1].adj;            //v1对应的边链表头指针
        while(p != NULL && p->dest != v2)                 //寻找邻接顶点v2
        {
            p = p->link;
        }
        if(p != NULL)
            return false;
        p = new Edge<T, E>;                 //否则，创建新结点
        q = new Edge<T, E>;
        p->dest = v2;
        p->cost = weight;
        p->link = NodeTable[v1].adj         //链入v1边链表
        NodeTable[v1].adj = p;
        q->dest = v1;
        q->cost = weight;
        q->link = NodeTable[v2].adj;        //链入v2边链表
        NodeTable[v2].adj = q;
        numEdges++;
        return true;
    }
    return 0;
}

template<class T, class E>
bool Graphlnk<T, E>::removeEdge(int v1, int v2)         //在图中删除一条边(v1, v2)
{
    if(v1 != -1 && v2 != -1)
    {
        Edge<T, E> *p = NodeTable[v1].adj, *q = NULL, *s = p;
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

#endif
