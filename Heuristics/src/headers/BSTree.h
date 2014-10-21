/*
 * BSTree.h
 *
 *  Created on: Oct 16, 2014
 *      Author: alex
 */

#ifndef BSTREE_H_
#define BSTREE_H_


#include <iostream>
#include <cstdlib>
using namespace std;

class BinarySearchTree
{
    public:
        BinarySearchTree()
        {
           root = NULL;
        }
        struct tree_node
        {
           tree_node* left;
           tree_node* right;
           int route;
           int saving;
        };
        bool isEmpty() const { return root==NULL; }
        void print_inorder();
        void inorder(tree_node*);
        void print_preorder();
        void preorder(tree_node*);
        void print_postorder();
        void postorder(tree_node*);
        void insert(int, int);
        void remove(int);
        BinarySearchTree::tree_node* getRoot();
    private:
        tree_node* root;
};

#endif /* BSTREE_H_ */
