#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999


class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
    void print();
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************


//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	int ** matrix ; //adjacency matrix to store the graph
	
	char *color;
	int *parent;
	int *dist;

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source); //will run bfs in the graph
	void printBridges();
	Queue q;
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	matrix = 0 ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
	parent =0;
	dist=0;
	color=0;



}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;

	//allocate space for the matrix
    matrix = new int*[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0;j<nVertices;j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }

}

void Graph::addEdge(int u, int v)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    if(matrix[u][v]==0){
        matrix[u][v] = 1;
        nEdges++;
        if(!directed) matrix[v][u] = 1;
    }


}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    if(matrix[u][v]==1){
        matrix[u][v]=0;
        nEdges--;
        if(!directed){
            matrix[v][u]=0;
        }
    }
    return;

}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) {
        printf("vertex not in graph\n");
        return false;
    }
    if(matrix[u][v]==1) return true;
    else return false;
}

int Graph::getDegree(int u)
{
    //returns the degree of vertex u
    if(u<0 || u>=nVertices ) {
        printf("vertex not in graph\n");
        return 0;
    }
    int outdeg=0,indeg=0;
    for(int i=0;i<nVertices;i++){
        if(matrix[u][i]==1){
            outdeg++;
        }
    }
    if(!directed)
        return outdeg;
    else{
        for(int i=0;i<nVertices;i++){
            if(matrix[i][u]==1){
                indeg++;
            }
        }
        return outdeg+indeg;
    }
}

void Graph::printAdjVertices(int u)
{
    //prints all adjacent vertices of a vertex u
    if(u<0 || u>=nVertices ) {
        printf("vertex not in graph\n");
        return ;
    }
    for(int i=0;i<nVertices;i ++){
        if(matrix[u][i]==1){
            printf("%d ",i);
        }
    }
    printf("\n");
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) {
        printf("vertex not in graph\n");
        return false;
    }
    for(int i=0;i< nVertices; i++){
        if(matrix[u][i]==1 && matrix[v][i]==1){
            return true;
        }
    }
    return false;

}

void Graph::bfs(int source)
{
    
    dist = new int [nVertices];
    parent = new int [nVertices];
    color = new char[nVertices];
    for(int i=0;i<nVertices;i++){
        color[i]= 'w';
        parent[i]=-1;
        dist[i]= INFINITY;
    }
  
    color[source]='g';
    q.enqueue(source);
    dist[source]=0;
    while(!q.empty()){
        int u = q.dequeue();
        //printf("%d  ",u);
        for(int v=0;v<nVertices;v++){
            if(matrix[u][v]==1){
                if(color[v]=='w'){
                    color[v]='g';
                    dist[v]=dist[u]+1;
                    parent[v]=u;
                    q.enqueue(v);
                }
            }
        }
        color[u]='b';
    }
    printf("\n");

}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v using bfs
    
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) {
        printf("vertex not in graph\n");
        return false;
    }
    bfs(u);
    return dist[v];
    //return INFINITY ;
}


void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices;j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
    }

    
}
void Graph::printBridges()
{
	for(int i=0;i<nVertices;i++){
		for(int j=0;j<nVertices;j++){
			if(matrix[i][j]==1 && i>=j){
				removeEdge(i,j);
				bfs(i);
				//printf("%d %d\n",i,j);
				for(int k=0;k<nVertices;k++){
					if(color[k]=='w'){
						printf("%d %d\n",i,j);
					}
				}
			}
		}
		//printf("\n");
	}
}
Graph::~Graph()
{
    //write your destructor here
    if(parent)delete[]parent;
    if(color)delete[]color;
    if(dist)delete[]dist;
    delete[]matrix;
}


//**********************Graph class ends here******************************


//******main function to test code*************************
int main(void)
{
    int n;
    Graph g;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("1. Add edge. 2.Remove Edge 3.Is Edge?\n");
        printf("4. Get Degree. 5. Print Graph  6.Print Adjacent Vertices\n7.Has common Adjacent? 8.Get Distance \n");
        printf("10.exit\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
	    printf("Enter vertices \n");
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
        }
        else if(ch==2)
        {
            int u, v;
	    printf("Enter vertices \n");
            scanf("%d%d", &u, &v);
            g.removeEdge(u, v);

        }
        else if(ch==3)
        {
            int u, v;
	    printf("Enter vertices \n");
            scanf("%d%d", &u, &v);
            printf("\n%d\n",g.isEdge(u, v));
        }
        else if(ch==4)
        {
            int u;
	    printf("Enter vertex \n");
            scanf("%d", &u);
            printf("\n%d\n",g.getDegree(u));

        }
        else if(ch==5)
        {
            g.printGraph();
        }
        else if(ch==6)
        {
            int u;
            printf("Enter vertices \n");
            scanf("%d", &u);
            g.printAdjVertices(u);
            printf("\n");
        }
        else if(ch==7)
        {
            int u, v;
            printf("Enter vertices \n");
            scanf("%d%d", &u, &v);
            printf("\n%d\n",g.hasCommonAdjacent(u, v));

        }
        else if(ch==8)
        {
            int u, v;
            printf("Enter vertices \n");
            scanf("%d%d", &u, &v);
            printf("\n%d\n",g.getDist(u, v));
        }
        else if(ch==10)
        {
            break;
        }
    }

}
