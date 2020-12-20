//This is a node class for the 8 puzzle problem.
//It contains an array of 3x3 matrix, pointers to one parent node //and up to 4 children nodes
//Date: 2-13-2016
//Ni. Y. Lu
#include <iostream>
#include "Point.hpp"
#include <queue>
#include <cmath>
#ifndef _NODECLASS_HEADERFILE
#define _NODECLASS_HEADERFILE

class Node
{
public:
    int a[3][3];    //represents the 8 puzzle, 0 for empty title
    Node* parent;   //pointer to parent node
    //Node* child[4];    //pointer to child nodes, up to 4
    Point<int> p[9]; //array of points to store locations; its index gives int value at the location
    int g;  //to record  cost to this node from starting node
    int h;  //cost from this node to goal node
    int f; //total cost

    void SetElement(int i, int j, int value)   //setter function setting value to coordinate (i,j) of the 3x3 matrix

    {
        a[i][j]=value;
    }
    void copy_elements_to(Node& another_node)   //copy elements of this to another node and set this to be another_node's parent
    {
        for (int i=0;i<3;i++)
            for (int j=0;j<3;j++)
        {
            another_node.a[i][j]=a[i][j];   //copy element-wise
        }
        another_node.parent = this;
    }
    void IndexAllElements() // index all elements of 3x3 matrix of current node
    {
        for (int i=0;i<3;i++)
        {
           for (int j = 0; j<3;j++)
            p[a[i][j]] = Point<int>(i,j);   //store the location of each value
        }
    }
    Point<int> GetLocation(int m)    //get the location of a value in 3x3 matrix of the current node
    {
        return p[m];
    }
    friend bool operator ==(const Node& node1, const Node& node2)   //compare if two nodes are identical
    {
        for (int i=0;i<3;i++)
            for (int j=0;j<3;j++)
        {
            if (node1.a[i][j]!=node2.a[i][j]) return false;
        }
        return true;
    }
    friend bool operator !=(const Node& node1, const Node& node2)   //compare if two nodes are different
    {
        return not (node1 == node2);
    }
    friend bool operator <(Node& node1, Node& node2 )   //to compare two matrices
    {
        for (int i=0;i<3;i++)
            for (int j=0;j<3;j++)
        {
            if (node1.a[i][j]<node2.a[i][j]) return true;
        }
        return false;
    }
    int cost_misplaced(const Node& another_node)  //cost function from the current node to another
    {
        int cost=0;
        for (int i=0;i<3;i++)
        {
            for (int j = 0; j<3; j++)
                cost += a[i][j]!=another_node.a[i][j];
        }
        return cost;
    }
    int cost_manhattan(const Node& another_node)    //cost from current node to another node using manhattan distance
    {
        int cost=0;
        for (int i=0;i<3;i++)
        {
            for (int j = 0; j<3; j++)
                {
                    const Point<int>& pos=another_node.p[a[i][j]];
                    cost=cost+std::abs(i-pos.X()) + std::abs(j-pos.Y());
                }
        }
        return cost;
    }
    std::set<Node*> expand () //function to expand the current node, giving its children
    {
        std::set<Node*> neighbors;  //set to contain all neighbors of current node
        IndexAllElements();
        Point<int> p0=GetLocation(0);
        if (p0.Y()<2) //if empty tile is not at the right end wall, move it to the right
        {
            Node* move_right=new Node;
            copy_elements_to(*move_right);
            move_right->a[p0.X()][p0.Y()]=a[p0.X()][p0.Y()+1];  //move the empty tile to the right
            move_right->a[p0.X()][p0.Y()+1]=a[p0.X()][p0.Y()];  //swap the right tile with the empty tile
            move_right->g=g+1;  //every move swap one tile and empty tile, add 1 to cost so far
            neighbors.insert(move_right);
        }
        if (p0.X()<2) //if empty tile is not at the bottom, move it down
        {
            Node* move_down=new Node;
            copy_elements_to(*move_down);
            move_down->a[p0.X()][p0.Y()]=a[p0.X()+1][p0.Y()];   //move the empty tile down
            move_down->a[p0.X()+1][p0.Y()]=a[p0.X()][p0.Y()];   //swap the left tile with the empty tile
            move_down->g=g+1;  //every move swap one tile and empty tile, add 1 to cost so far
            neighbors.insert(move_down);
        }
        if (p0.Y()>0) //if empty tile is not at the left end wall, move it to the left
        {
            Node* move_left=new Node;
            copy_elements_to(*move_left);
            move_left->a[p0.X()][p0.Y()]=a[p0.X()][p0.Y()-1];   //move the empty tile to the left
            move_left->a[p0.X()][p0.Y()-1]=a[p0.X()][p0.Y()];   //swap the tile below with the empty tile
            move_left->g=g+1;  //every move swap one tile and empty tile, add 1 to cost so far
            neighbors.insert(move_left);
        }
        if (p0.X()>0) //if empty tile is not at the top, move it up
        {
            Node* move_up=new Node;
            copy_elements_to(*move_up);
            move_up->a[p0.X()][p0.Y()]=a[p0.X()-1][p0.Y()];   //move the empty tile up
            move_up->a[p0.X()-1][p0.Y()]=a[p0.X()][p0.Y()];   //swap the tile above with the empty tile
            move_up->g=g+1;  //every move swap one tile and empty tile, add 1 to cost so far
            neighbors.insert(move_up);
        }
        return neighbors;
    }
    friend std::ostream& operator << (std::ostream& os, const Node& node)
{ // Print the node and its g value

    for (int i=0;i<3;i++)
    {
        for (int j=0;j<3;j++)
        {
            os << node.a[i][j] << " ";
        }
        os<<std::endl;
    }
    os<<"g = " << node.g<<std::endl;
	return os;
}
};

















#endif // NODECLASS_HEADERFILE_
