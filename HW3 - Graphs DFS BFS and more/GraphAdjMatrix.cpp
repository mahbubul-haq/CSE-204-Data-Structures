#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 0;
#define GREY 1;

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


//******************Graph class starts here**************************
class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    int ** matrix ; //adjacency matrix to store the graph
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
    void dfs();
};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    matrix = 0 ;
    directed = dir ; //set direction of the graph
    //define other variables to be initialized
    dist=0;
    color=0;
    parent=0;
    distime=0;
    finishtime=0;
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
    dist=new int[nVertices];
    color=new int[nVertices];
    parent=new int[nVertices];
    distime=new int[nVertices];

    for(int i=0;i<nVertices;i++){
        dist[i]=NULL_VALUE;
        color[i]=WHITE;
        parent[i]=NULL_VALUE;
        distime[i]=INFINITY;
    }

    finishtime=NULL_VALUE;

}

void Graph::addEdge(int u, int v)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = 1;
    if(!directed) matrix[v][u] = 1;

}

void Graph::removeEdge(int u, int v)
{
    //write this function

    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v]=0;
    if(!directed) matrix[v][u]=0;

}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false

    if(matrix[u][v]) return true;
    if(directed&matrix[v][u]==1) return true;
    return false;

}

int Graph::getDegree(int u)
{
    //returns the degree of vertex u
    int degree=0;
    if(!directed){

        for(int i=0;i<this->nVertices;i++){
            if(matrix[u][i]==1) degree++;
        }
        return degree;
    }

    else{
        for(int i=0;i<this->nVertices;i++){
            for(int j=0;j<this->nVertices;j++){
                if(matrix[i][j]==1&&(i==u||j==u)){
                    degree++;
                }
            }
        }
        return degree;
    }

}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices

    if(u>nVertices||v>nVertices||v<0||u<0) return false;
    
    for(int i=0;i<this->nVertices;i++){
        if(matrix[u][i]==1&&matrix[v][i]==1) return true;
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
    int layer=-1;


    while( !q.empty() )
    {
        //complete this part

        int x=q.dequeue();
        for(int i=0;i<nVertices;i++){

            if(color[i]==0&&matrix[x][i]==1){
                parent[i]=x;
                color[i]=GREY;
                q.enqueue(i);
                dist[i]=dist[x]+1;
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

        for(j=0;j<nVertices;j++){
            if(color[j]==0&&matrix[i][j]==1){
                
                starttime++;
                distime[j]=starttime;
                
                parent[j]=i;
                color[j]=GREY;
                top++;
                stk[top]=j;
                none=true;
                printf("%d ",j);
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
    return (dist[v]-dist[u]);

    return INFINITY ;
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

Graph::~Graph()
{
    //write your destructor here

    if(matrix) {
        for (int i = 0; i < nVertices; i++) {
            if (matrix[i])
                delete[]matrix[i];
        }
        delete[]*matrix;
    }
    matrix=0;
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
        printf("\n10. getDist\n");
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