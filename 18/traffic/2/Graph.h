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
#include <sys/stat.h>
#include<dirent.h>
#include<iostream>
#include<string.h>
#include<string>
#include<vector>
using std::ostream;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::cin;
using std::vector;

#define INFINITY 1000000  //将INFINITY定义为无穷大的值  

const int DefaultVertices = 30;  //默认最大顶点数

struct GraphNode{  
    bool known;//当前顶点距离起点的距离是否确定  
    int dist;//当前顶点到起点的最短距离  
    int path;//当前顶点距离起点的最短路径的前一个顶点  
};  
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
    virtual bool insertEdge(int v1, int v2, const string& place, Weight& weight) = 0 ; //插入边(v1, v2),权值为cost
    virtual bool removeVertex(int v) = 0 ;       //删去顶点v和所有与相关联边
    virtual bool removeEdge(int v1, int v2) = 0 ; //在图中删去边(v1, v2)
};


struct Edge             //边节点的定义
{
    int dest;           //边的另一顶点位置
    string Place;         //地点名称
    const int step = 1;
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
    Graphlnk(const char* path = "./city/", int sz = DefaultVertices);  //构造函数
    ~Graphlnk();                         //析构函数
    string getValue(int i)                    //取位置为i的顶点中的值
    {
        return (i >= 0 && i < this->numVertices) ? NodeTable[i].data : "null";
    }
    Weight getWeight(int v1, int v2);
    bool insertVertex(const string& vertex);  //在图中插入一个顶点vertex
    bool removeVertex(int v);            //在图中删除一个顶点v
    bool removeVertex(string& place);
    bool insertEdge(int v1, int v2, const string& place, Weight& weight); //在图中插入一条边(v1, v2)
    bool insertEdge(string& c1, string& c2, Weight& weight);
    bool removeEdge(int v1, int v2);         //在途中删除一条边(v1, v2)
    bool removeEdge(string& c1, string& c2);
    int getFirstNeighbor(int v);             //取顶点v的第一个邻接顶点
    int getNextNeighbor(int v, int w);       //取v的邻接顶点w的下一个邻接顶点
    bool readfile();              //初始化
    bool writefile();         //写入文件
    void print();                            //打印
    void dijkstra(int src, int mode);
    void dijkstra(string& c1, int mode);
    void printShorestPath(string& start, string& end);
private:
    Vertex *NodeTable;                 //顶点表(各边链表的头节点)
    const char* path;
    GraphNode* nodeArr;         //保存每个顶点信息的数组
    int getVertexPos(const string vertex)         //给出顶点vertex在图中的位置
    {
        for(int i = 0; i < this->numVertices; i++)
        {
            if(NodeTable[i].data == vertex)
                return i;
        }
        return -1;
    }
    bool Reset();
};

#endif
