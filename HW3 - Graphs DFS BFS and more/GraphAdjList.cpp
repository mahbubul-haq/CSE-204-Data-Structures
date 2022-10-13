#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 0
#define GREY 1
#define BLACK 3

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

//****************Dynamic ArrayList class based************************
class ArrayList
{
    int * list;
    int length ;
    int listMaxSize ;
    int listInitSize ;
public:
    ArrayList() ;
    ~ArrayList() ;
    int searchItem(int item) ;
    void insertItem(int item) ;
    void removeItem(int item) ;
    void removeItemAt(int item);
    int getItem(int position) ;
    int getLength();
    bool empty();
    void printList();
} ;


ArrayList::ArrayList()
{
    listInitSize = 2 ;
    listMaxSize = listInitSize ;
    list = new int[listMaxSize] ;
    length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
    int * tempList ;
    if (length == listMaxSize)
    {
        //allocate new memory space for tempList
        listMaxSize = 2 * listMaxSize ;
        tempList = new int[listMaxSize] ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
    };

    list[length] = newitem ; //store new item
    length++ ;
}

int ArrayList::searchItem(int item)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if( list[i] == item ) return i;
    }
    return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
    if ( position < 0 || position >= length ) return ; //nothing to remove
    list[position] = list[length-1] ;
    length-- ;
}


void ArrayList::removeItem(int item)
{
    int position;
    position = searchItem(item) ;
    if ( position == NULL_VALUE ) return ; //nothing to remove
    removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
    if(position < 0 || position >= length) return NULL_VALUE ;
    return list[position] ;
}

int ArrayList::getLength()
{
    return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    ArrayList  * adjList ;
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation
    int * color;
    int *dist;
    int *parent;
    int *distime;
    int finishtime;

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source); //will run bfs in the graph
    void dfs(); //will run dfs in the graph
};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    adjList = 0 ;
    directed = dir ; //set direction of the graph
    //define other variables to be initialized
    color=0;
    parent=0;
    dist=0;
    distime=0;
    finishtime=0;
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;
    if(adjList!=0) delete[] adjList ; //delete previous list
    adjList = new ArrayList[nVertices] ;
    dist=new int[nVertices];
    color=new int[nVertices];
    parent=new int[nVertices];
    distime=new int[nVertices];

    for(int i=0;i<nVertices;i++) {
        dist[i] = NULL_VALUE;
        color[i] = WHITE;
        parent[i] = NULL_VALUE; distime[i]=INFINITY;

    }
    finishtime=NULL_VALUE;
}

void Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges++ ;
    adjList[u].insertItem(v) ;
    if(!directed) adjList[v].insertItem(u) ;
}

void Graph::removeEdge(int u, int v)
{
    //write this function

    if(u<0||v<0||u>=nVertices||v>=nVertices) return;
    this->nEdges--;
    adjList[u].removeItem(v);
    if(!directed) adjList[v].removeItem(u);
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false

    if(u<0||v<0||u>=nVertices||v>=nVertices) return false;

    bool edge=false;

    for(int i=0;i<adjList[u].getLength();i++){
        if(adjList[u].getItem(i)==v) {
            edge=true;
            break;
        }
    }
    if(directed){
        for(int i=0;i<adjList[v].getLength();i++){
            if(adjList[v].getItem(i)==u){
                edge=true;
                break;
            }
        }
    }

    return edge;

}

int Graph::getDegree(int u)
{
    //returns the degree of vertex u

    if(!directed) return adjList[u].getLength();

    int numOfDegree=0;

    for(int i=0;i<nVertices;i++){
        for(int j=0;j<adjList[i].getLength();j++){
            if(i==u||j==u) numOfDegree++;
        }
    }

    return numOfDegree;

}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices

    for(int i=0;i<adjList[u].getLength();i++){
        int ver=adjList[u].getItem(i);
        for(int j=0;j<adjList[v].getLength();j++){
            if(ver==adjList[v].getItem(j)){
                return true;
            }
        }
    }

    return false;

}

void Graph::bfs(int source)
{
    //complete this function
    //initialize BFS variables


    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }
    Queue q ;
    color[source] = GREY;
    dist[source] = 0 ;
    q.enqueue(source) ;

    while( !q.empty() )
    {
        //complete this part

        int x=q.dequeue();
        for(int j=0;j<adjList[x].getLength();j++){
            int y=adjList[x].getItem(j);
            if(color[y]==0){

                color[y]=GREY;
                parent[y]=x;
                dist[y]=dist[x]+1;
                q.enqueue(y);

            }
        }

    }
}

void Graph::dfs()
{
    //write this function

    int stk[nVertices];
    int top=0;

    int starting_node=0;
    finishtime=INFINITY;

    for(int i=0;i<nVertices;i++){
        color[i]=WHITE;
        parent[i]=NULL_VALUE;
        distime[i]=INFINITY;
    }
    color[starting_node]=GREY;
    stk[top]=starting_node;
    printf("0 ");

    distime[starting_node]=0;
    bool none =false;
    int starttime=0;

    while(top>=0){
        int i,j;
        i=stk[top];
        none=false;

        for(j=0;j<adjList[i].getLength();j++){
            int xx=adjList[i].getItem(j);
            if(color[xx]==0){
                starttime++;
                distime[xx]=starttime;
             
                parent[xx]=i;
                color[xx]=GREY;
                top++;
                stk[top]=xx;
                none=true;
                printf("%d ",xx);
                break;

            }
        }
        if(none==false){
            top--;
        }

    }

    
    printf("\nFinished time: %d",starttime);

    printf("\n");

}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance

    bfs(u);
    return dist[v];
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    //write your destructor here

    if(adjList) delete [] adjList;
    adjList=0;

    if(color) delete []color;
    if(dist) delete[]dist;
    if(distime) delete [] distime;
    if(parent) delete [] parent;
    color=0; dist=0; distime=0; parent=0;

}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n;
    Graph g;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("10. getDist\n");
        printf("1. Add edge. 3.dfs, 4. bfs, 7. isEdge, 8.getDegree \n");
        printf("2.removeEdge. 9. hasCommonAdj 5. Print Graph  6. Exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
        }
        else if(ch==2)
        {
            printf("Enter the two vertices: ");
            int u,v;
            scanf("%d %d",&u,&v);
            g.removeEdge(u,v);
        }
        else if(ch==3)
        {
            g.dfs();
        }
        else if(ch==5)
        {
            g.printGraph();
        }
        else if(ch==6)
        {
            break;
        }
        else if(ch==4){
            printf("Enter source: ");
            int source;
            scanf("%d",&source);
            g.bfs(source);
        }
        else if(ch==7){
            printf("Enter the two vertices: ");
            int u,v;
            scanf("%d %d",&u,&v);

            printf("u--v: ");
            if(g.isEdge(u,v))printf("true");
            else printf("false");
        }
        else if(ch==8){
            printf("Enter vertex: ");
            int u;
            scanf("%d",&u);
            printf("Degree of u: %d",g.getDegree(u));
        }
        else if(ch==9){
            printf("Enter the two vertices: ");
            int u,v;
            scanf("%d %d",&u,&v);
            if(g.hasCommonAdjacent(u,v)) printf("true");
            else printf("false");

        }
        else if(ch==10){
            printf("Enter the two vertices: ");
            int u,v;
            scanf("%d %d",&u,&v);

            printf("Dist: %d",g.getDist(u,v));
        }
    }
}
