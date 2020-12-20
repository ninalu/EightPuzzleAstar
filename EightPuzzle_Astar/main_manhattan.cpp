#include <iostream>
#include <queue>    //for priority_queue
#include <set>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>       /* sqrt */
#include "NodeClass.hpp"

using namespace std;

Node goal_node;     //global variable because need it in the following classes
struct Compare_Node_Cost
{
    bool operator ()(Node* node1, Node* node2)
    {
      node1->f = node1->g + node1->cost_misplaced( goal_node);
      node2->f = node2->g + node2->cost_misplaced( goal_node);
      return node1->f > node2->f;
    }
};
struct Compare_Node_Cost_Manhattan
{
    bool operator ()(Node* node1, Node* node2)
    {
      node1->f = std::max(node1->g + node1->cost_manhattan( goal_node), node1->parent->f);
      node2->f = std::max(node2->g + node2->cost_manhattan( goal_node), node2->parent->f);
      return node1->f > node2->f;
    }
};
struct Compare_Nodepointer
{
    bool operator ()(Node* node1, Node* node2)
    {
      return *node1< *node2;  //using operator < defined in node class as a global function
    }
};

void Astar(Node & starting_node)
{
    clock_t t;
    //priority_queue<Node*, vector<Node*>, Compare_Node_Cost> open_list_queue;
    priority_queue<Node*, vector<Node*>, Compare_Node_Cost_Manhattan> open_list_queue;
    typedef set <Node*, Compare_Nodepointer> OrderedNodeSet;    //rename
    OrderedNodeSet open_list_set; //order elements in open list uniquely
    //list closed_list;
    OrderedNodeSet closed_list_set;   //order elements in closed list uniquely
        t = clock();
    open_list_queue.push(&starting_node);
    open_list_set.insert(&starting_node);
    Node* current = open_list_queue.top();
    int count_node_expanded=0;
    while (current and *current !=goal_node)    //while we have not reached our goal
    {
        closed_list_set.insert(current);    //put current node in closed_list
        open_list_queue.pop();
        open_list_set.erase(current);
        set<Node*> neighbors=current->expand(); //save all neighbors of current node into the set neighbors
        count_node_expanded += neighbors.size();
//        cout<<"current node:"<<*current
//            << ", num of neighbors " << neighbors.size()
//            <<", cost g = " << current->g
//            << ", total f = " << current->f
//            << ", open list size " << open_list_set.size()
//            << ", closed list size " << closed_list_set.size()
//            << std::endl;
        //for each neighbor
        for (set<Node*>::iterator it=neighbors.begin();it!=neighbors.end();it++)
        {
            //cout<<"neighbor node:"<<**it;
            OrderedNodeSet::iterator closed_iter = closed_list_set.find(*it);
            OrderedNodeSet::iterator open_iter = open_list_set.find(*it);
            if (closed_iter!=closed_list_set.end()   //looking to see if this neighbor is already in closed list
                                                        //return an iterator if found, else return an end iterator of closed list
                and ((*it)->g)<(*closed_iter)->g)   //if our current value g of this neighbor is lower
                //if true, move this this neighbor from the closed list into open list
                {
                    //int old_g = (*closed_iter)->g;
                    Node* ptr = *closed_iter; // save the pointer value before we remove closed_iter
                    closed_list_set.erase(closed_iter);
                    open_list_queue.push(ptr);   //add to open list priority queue
                    open_list_set.insert(ptr);   //add to open list set
                    //update the neighbor with a new, lower g value
                    ptr->g=(*it)->g;
                    //change the neighbor parent to our current node
                    ptr->parent=current;
                    //another way to do this is to romove closed_iter from closed list and add (*it) into open list
                    //closed_list_set.erase(closed_iter);   //remove
                    //open_list_queue.push(*it); //add

//                    cout<<"neighbor node moved from closed to open, g = " << ptr->g
//                        << ", old g " << old_g
//                        << ", open list size " << open_list_set.size()
//                        << ", closed list size " << closed_list_set.size()
//                        << "\n"<<**it;
                    delete *it;
                }
            else if(open_iter !=open_list_set.end()   //looking to see if this neighbor is already in open list
                                                        //return an iterator if found, else return an end iterator of open list
                and ((*it)->g)<(*open_iter)->g)   //if our current value g of this neighbor is lower
                //if true, move this this neighbor from the closed list into open list
                {
                   // int old_g = (*open_iter)->g;
                    Node* ptr = *open_iter; // save the pointer value before we remove closed_iter
                    //update the neighbor with a new, lower g value
                    ptr->g=(*it)->g;
                    //change the neighbor parent to our current node
                    ptr->parent=current;

//                    cout<<"neighbor node g updated, g = " << ptr->g
//                        << ", old_g " << old_g
//                        << ", open list size " << open_list_set.size()
//                        << ", closed list size " << closed_list_set.size()
//                        << "\n"<<**it;
                    delete *it;
                }

            //if this neighbor is in neither the open list nor closed list
            else if (closed_iter==closed_list_set.end()and open_iter==open_list_set.end())
            {
                // add this neighbor in  the open list
                open_list_set.insert(*it);
                open_list_queue.push(*it);
//                cout<<"neighbor inserted into open, g updated, g = " << (*it)->g
//                    << ", open list size " << open_list_set.size()
//                    << ", closed list size " << closed_list_set.size()
//                    << "\n "<<**it;
                //update this neighbor g value, already did when expand the node
            }
            else // already in either open or closed list
            {
//                cout << "Already has node in open list " << (open_iter!=open_list_set.end())
//                     << " or in closed list " << (closed_iter !=closed_list_set.end())
//                     << ", open list size " << open_list_set.size()
//                     << ", closed list size " << closed_list_set.size()
//                     << "\n" << **it
//                     ;
                delete *it;

            }
                // add this neighbor in  the open list
                //update this neighbor g value
        }//end of neighbor loop

        current = open_list_queue.top();// get a new current node, preparing for next iteration
    }//end of while loop
    //check if we have reached our goal
    if (*current==goal_node)
    {
        int seq_length = current->g;
        //going backward to print out solution
        cout<<"Here is the optimal solution in reverse order: "<<endl;

        for (; *current!=starting_node;current=current->parent)
        {
            cout<<*current << endl;
        }
        cout<<starting_node<<endl;
        t = clock() - t;
        cout<<"It took me "<<t<<" ticks ("<<((float)t)/CLOCKS_PER_SEC<<" seconds)."
            <<"The number of nodes expanded is "<<count_node_expanded
            <<", and the length of the optimal sequence is "<<seq_length<<"."<<endl;
    }
}

int main()
{

    Node starting_node[4];
//hard-code starting node, easy case
    starting_node[0].a[0][0]=1;
    starting_node[0].a[0][1]=3;
    starting_node[0].a[0][2]=4;
    starting_node[0].a[1][0]=8;
    starting_node[0].a[1][1]=6;
    starting_node[0].a[1][2]=2;
    starting_node[0].a[2][0]=7;
    starting_node[0].a[2][1]=0;
    starting_node[0].a[2][2]=5;
    starting_node[0].g=0;
    starting_node[0].parent=NULL;

    //hard-code starting node, medium case
    starting_node[1].a[0][0]=2;
    starting_node[1].a[0][1]=8;
    starting_node[1].a[0][2]=1;
    starting_node[1].a[1][0]=0;
    starting_node[1].a[1][1]=4;
    starting_node[1].a[1][2]=3;
    starting_node[1].a[2][0]=7;
    starting_node[1].a[2][1]=6;
    starting_node[1].a[2][2]=5;
    starting_node[1].g=0;
    starting_node[1].parent=NULL;

    //hard-code starting node, hard case
    starting_node[2].a[0][0]=2;
    starting_node[2].a[0][1]=8;
    starting_node[2].a[0][2]=1;
    starting_node[2].a[1][0]=4;
    starting_node[2].a[1][1]=6;
    starting_node[2].a[1][2]=3;
    starting_node[2].a[2][0]=0;
    starting_node[2].a[2][1]=7;
    starting_node[2].a[2][2]=5;
    starting_node[2].g=0;
    starting_node[2].parent=NULL;

    // Worst start node
    starting_node[3].a[0][0]=5;
    starting_node[3].a[0][1]=6;
    starting_node[3].a[0][2]=7;
    starting_node[3].a[1][0]=4;
    starting_node[3].a[1][1]=0;
    starting_node[3].a[1][2]=8;
    starting_node[3].a[2][0]=3;
    starting_node[3].a[2][1]=2;
    starting_node[3].a[2][2]=1;
    starting_node[3].g=0;
    starting_node[3].parent=NULL;
    //starting_node.f=starting_node.cost_misplaced(goal_node);

    //hard-code goal node
    goal_node.a[0][0]=1;
    goal_node.a[0][1]=2;
    goal_node.a[0][2]=3;
    goal_node.a[1][0]=8;
    goal_node.a[1][1]=0;
    goal_node.a[1][2]=4;
    goal_node.a[2][0]=7;
    goal_node.a[2][1]=6;
    goal_node.a[2][2]=5;
    std::string case_names[4];
    case_names[0] = "Easy case";
    case_names[1] = "Medium case";
    case_names[2] = "Hard case";
    case_names[3] = "Worst case";
    cout << "Hello! This is the eight puzzle problem using A* search" << endl;
    for (int i=0; i<3; i++)
    {
        starting_node[i].f=starting_node[i].cost_manhattan(goal_node);
        cout << case_names[i] << endl;
        Astar(starting_node[i]);
    }
    return 0;
}
