/*************************************************************************
	> File Name: Graph.cpp
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2018年01月05日 星期五 12时00分40秒
 ************************************************************************/

#include"Graph.h"

ostream& operator<<(ostream& out, Weight& t)
{
   	out << t.distance << " " << t.timecost << " " << t.cost;
   	return out;
}

Graphlnk::Graphlnk(const char* path, int sz)  //构造函数: 构造一个空的邻接表
{
	this->path = path;
    this->maxVertices = sz;
    this->numVertices = 0;
    this->numEdges = 0;
    NodeTable = new Vertex[this->maxVertices];  //创建顶点表数组
    nodeArr = new GraphNode[this->maxVertices];
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
    delete []nodeArr;
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
    if(this->numVertices == this->maxVertices || getVertexPos(vertex) < this->numVertices)                  //顶点表满，不能插入
        return false;
    NodeTable[this->numVertices].data = vertex;           //插入在表的最后
    this->numVertices++;
    writefile();
    Reset();
    readfile();
    return true;
};

bool Graphlnk::removeVertex(int v)            //在图中删除一个指定顶点v,v是顶点号。若删除成功，函数返回true,否则返回false
{
    if(this->numVertices == 1 || v < 0 || v >= this->numVertices) //表空或顶点号超出范围
        return false;
    Edge *p, *s;
    int i, k;
    char buff[256];
    strcpy(buff, path);
    strcat(buff, NodeTable[v].data.c_str());
    remove(buff);                                   //删除城市所在文件
    while(NodeTable[v].adj != NULL)                 //删除第v个边链表中所有结点
    {
        p = NodeTable[v].adj;                       
        NodeTable[v].adj = p->link;                 //清除顶点v的边链表结点
        delete p;
    }
    for(int i = 0; i < this->numVertices; ++i)
    {
    	if(i == v)
    		continue;
    	Edge *p = NodeTable[i].adj, *q = NULL, *s = p;
        while(p != NULL && p->dest != v)       //v1对应边链表中找被删边
        {
            q = p;
            p = p->link;
        }
        if(p != NULL)                           //找到被删边结点
        {
            if(p == s)                       //该结点是边链表首结点
            {
                NodeTable[i].adj = p->link;
            }
            else                             //不是重新链接
            {
                q->link = p->link;
            }
            delete p;
        }
    }

    NodeTable[v].data = NodeTable[this->numVertices].data;     //填补
    p = NodeTable[v].adj = NodeTable[this->numVertices].adj;
    writefile();
    Reset();
    this->numVertices--;                                  //图的顶点个数减1/
    readfile();
    return true;
}

bool Graphlnk::removeVertex(string& place)
{
	return removeVertex(getVertexPos(place));
}

bool Graphlnk::insertEdge(int v1, int v2, const string& place, Weight& weight) //在带权图中插入一条边(v1, v2),若此边存在或参数不合理，函数返回false,否则返回true。对于非带权图，最后一个参数weight不要。算法中相应语句也不要。
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
    return false;
}
bool Graphlnk::insertEdge(string& c1, string& c2, Weight& weight)
{
	return insertEdge(getVertexPos(c1), getVertexPos(c2), c2, weight);
}
/*
bool Graphlnk::insertEdge(string& p1, string& p2, const char* place, Weight weight)
{
	return insertEdge(getVertexPos(),);
}
*/	
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
        /*
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
        */

        return true;
    }
    return false;                            //没有找到结点
}

bool Graphlnk::removeEdge(string& c1, string& c2)
{
	return removeEdge(getVertexPos(c1), getVertexPos(c2));
}

bool Graphlnk::Reset()
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
}

void Graphlnk::dijkstra(int src, int mode)
{  

    //初始化顶点信息  
    for(int i = 0; i < numVertices; ++i){  
        nodeArr[i].known = false;  
        nodeArr[i].dist = INFINITY;  
        nodeArr[i].path = 0;  
    }  
    //重要的一步，开启算法的关键一步  
    nodeArr[src].dist = 0;  
  
    for(; ;){  
        //找到unknown的dist最小的顶点   
        int v = 0;  
        int max = INFINITY;  
        for(int i = 0; i < numVertices; ++i){  
            if(!nodeArr[i].known && (max > nodeArr[i].dist)){  
                max = nodeArr[i].dist;  
                v = i;  
            }  
        }  
  
        //没有找到满足条件的顶点,退出算法  
        if(max == INFINITY)  
            break;  
  
        nodeArr[v].known = true;  
        //更新与v相邻所有顶点w的dist,path 
        if(mode == 1)
        { 
		    Edge* p = NodeTable[v].adj;
		    for(Edge* p = NodeTable[v].adj; p != NULL; p = p->link)
		    {  
		        if(!nodeArr[p->dest].known)
		        {  
		            if(nodeArr[v].dist + p->weight.distance < nodeArr[p->dest].dist){  
		                nodeArr[p->dest].dist = nodeArr[v].dist + p->weight.distance;  
		                nodeArr[p->dest].path = v;  
		            }  
		        }
		    }
		}
		else if(mode == 2)
		{
			Edge* p = NodeTable[v].adj;
		    for(Edge* p = NodeTable[v].adj; p != NULL; p = p->link)
		    {  
		        if(!nodeArr[p->dest].known)
		        {  
		            if(nodeArr[v].dist + p->step < nodeArr[p->dest].dist){  
		                nodeArr[p->dest].dist = nodeArr[v].dist + p->step;  
		                nodeArr[p->dest].path = v;  
		            }  
		        }
		    }
		}
		else if(mode == 1)
        { 
		    Edge* p = NodeTable[v].adj;
		    for(Edge* p = NodeTable[v].adj; p != NULL; p = p->link)
		    {  
		        if(!nodeArr[p->dest].known)
		        {  
		            if(nodeArr[v].dist + p->weight.timecost < nodeArr[p->dest].dist){  
		                nodeArr[p->dest].dist = nodeArr[v].dist + p->weight.timecost;  
		                nodeArr[p->dest].path = v;  
		            }  
		        }
		    }
		}
	 
    }  
}  

void Graphlnk::dijkstra(string& c, int mode)
{
	return dijkstra(getVertexPos(c), mode);
}
/*
void Graphlnk::printShorestPath()  
{  
    cout << "顶点\t" << "known\t" << "dist\t" << "path" << endl;  
    for(int i = 0; i < numVertices; ++i){  
        if(nodeArr[i].known)  
            cout << NodeTable[i].data << "\t" << nodeArr[i].known << "\t" << nodeArr[i].dist << "\t" << nodeArr[i].path << endl;  
    }   
}
*/
void Graphlnk::printShorestPath(string& start, string& end)
{
	int Spos = getVertexPos(start);
	int Epos = getVertexPos(end);
	if(Spos != -1 && Epos != -1)
	{
		vector<int> stack(10);
		int i;
		stack[0] = Epos;
		for(i = 1; ; ++i)
		{
			stack[i] = nodeArr[stack[i - 1]].path;
			if(stack[i] == Spos)
			{
				break;
			}
		}
		for( ; i >= 0; --i)
		{
			cout << NodeTable[stack[i]].data << " -> ";
		}
		cout << "结束" << endl;
	} 
}

bool Graphlnk::readfile()        //初始化读文件
{
	this->numVertices = 0;
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

bool Graphlnk::writefile()
{
	char buff[256];
	strcpy(buff, path);
    int len = strlen(path);
    string place;
    Weight weight;
    for(int i = 0; i < this->numVertices; ++i)
    {
    	strcpy(buff + len, NodeTable[i].data.c_str());
    	FILE* fp = fopen(buff, "w");
    	if(fp == NULL)
    		return false;
    	Edge *p = NodeTable[i].adj;
    	while(p != NULL)
    	{
    		place = p->Place;
    		weight = p->weight;
    		fprintf(fp,"%s %d %lf %lf\n", place.c_str(), weight.distance, weight.timecost, weight.cost);
    		p = p->link;
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
