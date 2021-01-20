//
//
//  Dijkstras Algorithm
//
//  Created by Saurabh Savara on 10/15/20.
//  Copyright © 2020 Saurabh Savara. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <vector>
#include <stdio.h>
#define MAX_N 1000

using namespace std;
void swap(int *x, int *y); // implement swap for MinHeap
int vertices;  // Store number of vertices of the input  graph
int edges;  // Store number of edges of the input graph
vector<vector <pair<int,double> > >graph(MAX_N); // Graph to store vertices amd weights
  
class BinaryMinHeap
{
    //MinHeap Declaration, Array to store the heap and track size and current heap size
public:
    int *heap_array;
    int size;
    int heap_size;


//Declare functions to be initialized
    BinaryMinHeap(int size);
    void HEAPIFY(int );
    int HEAP_EXTRACT_MIN();
    void push(int k);
    bool isEmpty();

    //Set Parent and Child node "formula"
    int parent(int i)
    {
        return (i-1)/2;

    }
    int left_child(int i)
    {
        return (2*i + 1);

    }
    int right_child(int i)
    {
        return (2*i + 2);

    }
    //Return the minimum in the heap
    int getMin()
    {
        return heap_array[0];

    }

};


//Default constructor defination
BinaryMinHeap::BinaryMinHeap(int size)
{
    heap_size = 0;
    size = size;
    heap_array = new int[size];
}

//Check if the heap is empty
bool BinaryMinHeap::isEmpty()
{
    if(heap_size==0)
        return true;
    else
        return false;

}
//Push item into heap
void BinaryMinHeap::push(int k)
{
    if (heap_size == size)
    {
        return;
    }
    heap_size++;
    int i = heap_size - 1;
    heap_array[i] = k;
    while (i != 0 && heap_array[parent(i)] > heap_array[i])
    {
       swap(&heap_array[i], &heap_array[parent(i)]);
       i = parent(i);
    }
}
//Extract mininum value from the heap
int BinaryMinHeap::HEAP_EXTRACT_MIN()
{
    if (heap_size <= 0)
        return -1;
    if (heap_size == 1)
    {
        heap_size--;
        return heap_array[0];
    }

    // Store the minimum value, and remove it from heap
    int root = heap_array[0];
    heap_array[0] = heap_array[heap_size-1];
    heap_size--;
    //Heapify the heap to restore heap properties
    HEAPIFY(0);

    return root;
}
//Heapify to set heap to  follow all heap laws
void BinaryMinHeap::HEAPIFY(int i)
{
    int smallest = i;
    int left = left_child(i);
    int right = right_child(i);

    if (left < heap_size && heap_array[left] < heap_array[i])
        smallest = left;

    if (right < heap_size && heap_array[right] < heap_array[smallest])
        smallest = right;

    if (smallest != i)
    {
        swap(&heap_array[i], &heap_array[smallest]);
        HEAPIFY(smallest);
    }
}
//Given two values swap  old value with new
void swap(int *old, int *newval)
{
    int temp = *old;
    *old = *newval;
    *newval= temp;
}
//Print the path of the shortest path
void printPath(int path[], int j)
{

    // Base Case : If j is source
    if (path[j]== -1)
        return;

    printPath(path, path[j]);

    printf("%d ", j);
}

//Print all components of the solution, vertex 1 will always have a distance of 0 so we dont need to show that, redundant information
void printSolution(int path[],vector<double>distance)
{
    int src=1;
    for (int i = 1; i <=vertices; i++)
    {
        printf("Vertex: %d", i);
        cout<<endl;
        cout<<"Shortest Distance: "<<distance[i];
        cout<<endl;
        printf("Shortest Path: %d ",src);
        printPath(path, i);
        cout<<endl;
    }
}
//Fiding the shortest path
vector<double>ShortestPath(vector<vector<pair <int,double> > >graph,int source)
{
    vector<double> distance;
    //set distnace to infinity, in this case assume infinity as 9999999
    for(int i=0;i<=vertices;i++)
    {
        distance.push_back(9999999);
    }
    int path[vertices+1];
    path[source]=-1;
    //initialize our min heap with number of vertices
    BinaryMinHeap heap(vertices);
    distance[1]=0;

    //build minheap
    for(int i=0;i<vertices;i++)
    {
        heap.push(i);
    }
    //Run Shortest path algorithm
    while(heap.isEmpty()!=true)
    {
        //Get minimum value from the minheap
        int temp=heap.HEAP_EXTRACT_MIN();
        for(size_t i=0;i<graph[temp].size();i++)
        {
            //get the end vertex and weight
            int temp2=graph[temp][i].first;
            double w=graph[temp][i].second;

            //relax the nodes
            if(distance[temp2]>(distance[temp]+w))
            {
                path[temp2]=temp;
                distance[temp2]=distance[temp]+w;
                heap.push(temp2);

            }

        }
    }
    printSolution(path,distance);
    return distance;
}

//Driver method
int main(int argc, const char * argv[]) {

        int count=1;
        cin>>vertices;
        cin>>edges;
        string s;
        int i ,j;
        double k;
        //read in graph
        cin.ignore();
        do{
            cin>>i;
            cin>>j;
            cin>>k;
            //Push edges into a graph, since undirected we push the edge and weight from each vertice of a pair
            graph[i].push_back(make_pair(j, k));
            graph[j].push_back(make_pair(i, k));
            count++;
        }while(edges>count);
        cin>>i;
        cin>>j;
        cin>>k;
        graph[i].push_back(make_pair(j, k));
        graph[j].push_back(make_pair(i, k));
        //Push last edge into a forward graph and reverse graph

   ShortestPath(graph, 1);
    return 0;
}
