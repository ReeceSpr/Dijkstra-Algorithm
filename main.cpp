#include <cstdlib>
#include <iostream>
#include <fstream>
#include <locale>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

/* Implement the Graph class  */
struct Node {
    char key;
    int distance;
    Node *next;
};

struct GraphNode{
    char key;
    Node *listpointer;
};

void AddNodetoFront(Node*& listpointer, char newkey, int newdistance){
    Node *temp;
    temp = new Node;
    temp->key = newkey;
    temp->distance=newdistance;
    temp->next = listpointer;
    listpointer = temp;
}

void PrintLLnodes(Node*& listpointer){
    Node *temp;
    temp = listpointer;
    while(temp!=NULL){
        printf("to node %c dist: %d \n", temp->key, temp->distance);
        temp=temp->next;
    }
}

int cost(Node*& listpointer, char goal){
    Node *temp;
    temp = listpointer;
    while(temp!=NULL){
        if (temp->key==goal){
            return temp->distance;
        } else {
            temp = temp->next;
        }
    }
}

bool contains(vector<char> v, char goal){
    for (int i = 0; i < v.size(); ++i) {
        if(v.at(i)==goal){
            return true;
        }
    }
    return false;
}


int numberOfPaths(Node*& listpointer){
    Node *temp;
    temp = listpointer;
    int i=0;
    while(temp!=NULL){
        i++;
        temp=temp->next;
    }
    return i;
}



class Graph{
private:
    vector<GraphNode> adjlist;
public:
    Graph(){NUMOFNODE = 0;};
    ~Graph(){};
    int NUMOFNODE;
    void AddNewGraphNode(char newgraphnode);
    void AddNewEdgeBetweenGraphNodes(char A, char B, int distance);
    void PrintAllGraphNodesWithCosts();
    void Dijkstra();
    int findNodeIndex(char nodeName);
    GraphNode findNode(char nodeName);
};

void Graph::AddNewGraphNode(char newgraphnode){
    GraphNode temp;
    temp.key=newgraphnode;
    temp.listpointer=NULL;//important
    adjlist.push_back(temp);
    NUMOFNODE++;
}

void Graph::AddNewEdgeBetweenGraphNodes(char A, char B, int distance){
    //find which node A is
    int a;
    for (a=0;adjlist.size();a++){
        if (A==adjlist[a].key) break;
    }
    AddNodetoFront(adjlist[a].listpointer, B, distance);
}

void Graph::PrintAllGraphNodesWithCosts(){
    for (int a=0;a<adjlist.size();a++){
        printf("From Node %c: \n", adjlist[a].key);
        PrintLLnodes(adjlist[a].listpointer);
    }
}

int Graph::findNodeIndex(char nodeName) {
    for (int a=0;a<adjlist.size();a++){
       if(nodeName == adjlist[a].key){
           return a;
       }
    }
}

GraphNode Graph::findNode(char nodeName) {
    for (int a=0;a<adjlist.size();a++){
        if(nodeName == adjlist[a].key){
            return adjlist[a];
        }
    }
}

void Graph::Dijkstra() {
 /*   int d[adjlist.size()];
    char s[adjlist.size()];
    for (int a=0; a<adjlist.size(); a++){
        d[a]= 1000;
        s[a]='t';
    }
    
    int currentindex = findNodeIndex('A');

    cout<<adjlist.size();
    d[currentindex]=0;
    s[currentindex]='p';

    int d_current = 0;
    char current = 'A';

    int smallest=1000;
    int smallestIndex=0;

    bool endOfAlgorithm = false;

    int x;
    int y;

    int i=0;

    int minCost;

    while(!endOfAlgorithm){
        endOfAlgorithm=true;
        for(i=0; i!=adjlist.size(); i++){
            if(s[i] == 't'){
                //Operation
                endOfAlgorithm=false;
                x = d[currentindex] + cost(adjlist[i].listpointer, current);
                y = d[i];
                minCost = min(x,y);
                d[i] = minCost;
                cout<<" "<<d[i];
                int c = adjlist.size();
                d[i] = min(x,y );
                cout<<(x);
            }
            /*if(smallest>d[i]){
                smallest=d[i];
                smallestIndex = i;
            }
        }
        d_current=smallestIndex;
        current = adjlist[d_current].key;
        s[d_current] = 'p';
    }
    for(int i:s){
        cout<<i;
    }


    

*/
    vector<int> distances;
    vector<char> states;
    int i = 0;
    for(i=0;i<NUMOFNODE; i++){
        distances.push_back(1000);
        states.push_back('t');
    }

    int currentIndex = findNodeIndex('A');

    distances.at(currentIndex) = 0;
    states.at(currentIndex) = 'p';

    GraphNode currentNode = findNode('A');
    Node *currentNodePaths = currentNode.listpointer;

    int smallest=1000;

    while(contains(states, 't')){
        while(currentNodePaths != NULL){
            //Do Werid Calc
            int v=findNodeIndex(currentNodePaths->key);
            if(states[v]=='t'){
                distances[v]=min(distances[v], distances[currentIndex] + cost(currentNode.listpointer, currentNodePaths->key));
                currentNodePaths = currentNodePaths->next;
            } else {
                currentNodePaths = currentNodePaths->next;
            }
        }
    //Change current with smallest distances, set new current states to p
        for (i = 0; i < adjlist.size(); ++i) {
            if(states[i]!='p') {
                if (smallest != min(smallest, distances[i])) {
                    smallest = distances[i];
                    currentIndex = i;
                }
            }
        }
        currentNode = adjlist[currentIndex];
        currentNodePaths = currentNode.listpointer;

        states[currentIndex] = 'p';
        smallest = 1000;

    }
    for(char character='B'; character<'A'+NUMOFNODE; character++){
        cout<<"From A to "<<character<<":"<<distances[findNodeIndex(character)]<<endl;
        findNodeIndex(character);
    }


}



/* declare a new Graph */
Graph *graph = new Graph();

int main( int argc, char** argv ){//get filename from arguments
    //read an input text file
    string expression;
    ifstream input_file;
    if(argc!=2) {cout<< "Type a file name. " << endl << argv[1] << endl; exit(0);}
    input_file.open(argv[1]);
    if(!input_file.is_open()) {cout << "Could not read file: " << endl << argv[1] << endl; exit(0);}
    string token;
    while(!input_file.eof()){
        getline(input_file,expression);
        stringstream line(expression);
        if(input_file.eof()) break;
        if(expression[0] =='#') continue;//jump line, this is a line of comments
        char node_name;
        if(expression[0] =='N' && expression[1]=='o') {//read a Node name, single character
            getline(line, token,' ');
            getline(line, token,' ');
            node_name=(token.c_str())[0];
            //cout << "Node " << node_name << endl;//Comment this out on the final version
            /* Insert nodes into the graph */
                graph->AddNewGraphNode(node_name);
            /* */
        }
        else{
            char nodefrom;
            getline(line, token,' ');
            nodefrom=(token.c_str())[0];
            //cout << "From " << nodefrom;//Comment this out on the final version
            char nodeto;
            getline(line, token,' ');
            nodeto=(token.c_str())[0];
            //cout << " to " << nodeto; //Comment this out on the final version
            int cost;
            getline(line, token,' ');
            //cost = stoi(token);//only works with option -std=c++11
            cost = atoi(token.c_str());//use this one if your compiler is not C++11
            //cout << " costs " << cost << endl;//Comment this out on the final version
            /* Insert these edges into the graph */
            graph->AddNewEdgeBetweenGraphNodes(nodefrom, nodeto, cost);
            /*  */
        }
    }
    /* After loading the graph from the text file in the while loop above, run your implementation of Dijkstra here*/
    /* Dijkstra can be implemented either as a function or as a method of the class Graph


    /* call Dijkstra  */


    // Print answer in the required format
    graph->Dijkstra();

}
