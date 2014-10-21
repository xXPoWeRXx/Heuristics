/*
 * FibonacciTree.h
 *
 *  Created on: Oct 16, 2014
 *      Author: alex
 */

#ifndef FIBONACCITREE_H_
#define FIBONACCITREE_H_

#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

struct node

{

    int saving;
    int route;
    int degree;
    node* parent;
    node* child;
    node* left;
    node* right;
    char mark;
    char C;

};


class FibonacciHeap
{

    private:
        int nH;
        node *H;

    public:
        node* InitializeHeap();
        void Fibonnaci_link(node*, node*, node*);
        node *Create_node(int, int);
        node *Insert(node *, node *);
        node *Union(node *, node *);
        node *Extract_Min(node *);
        void Consolidate(node *);
        int Display(node *);
        node *Find(node *, int);
        int Decrease_key(node *, int, int);
        int Delete_key(node *,int);
        void Cut(node *, node *, node *);
        void Cascase_cut(node *, node *);
        FibonacciHeap()
        {
            H = InitializeHeap();
        }

};

#endif /* FIBONACCITREE_H_ */
