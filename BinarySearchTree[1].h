#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "Stack.h"
#include "List.h"

#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

struct Employee {
    int id;
    int age;
    string name;

    Employee(int id = -1, int age = -1, string name = "")
        : id{ id }, age{ age }, name{ name } { }
};

class BinarySearchTree
{

public:

    struct BinaryNode
    {
        Employee element;
        BinaryNode* left;
        BinaryNode* right;

        BinaryNode(const Employee& theElement, BinaryNode* lt, BinaryNode* rt)
            : element{ theElement }, left{ lt }, right{ rt } { }

        BinaryNode(Employee&& theElement, BinaryNode* lt, BinaryNode* rt)
            : element{ std::move(theElement) }, left{ lt }, right{ rt } { }

        BinaryNode() {}
    };

    BinarySearchTree() : root{ nullptr }
    {
    }

    /**
     * Destructor for the tree
     */
    ~BinarySearchTree()
    {
        makeEmpty();
    }

    /**
     * Find the smallest item in the tree.
     * return default employee if empty
     */
    const Employee& findMin() const
    {
        return findMin(root)->element;
    }

    /**
     * Find the largest item in the tree.
     * return default employee if empty
     */
    const Employee& findMax() const
    {
        return findMax(root)->element;
    }

    /**
     * Prints employee info if id found in tree
     */
    bool find(const int id) const
    {
        return find(id, root);
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const
    {
        return (root == NULL);
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty()
    {
        makeEmpty(root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const Employee& x)
    {
        insert(x, root);
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(const int id)
    {
        remove(id, root);
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void report() const
    {
        Stack<BinaryNode*> s;
        BinaryNode* current = root;
        int level = 0;

        while (current != NULL || !s.isEmpty())
        {
            if (current != NULL)
            {
                s.push(current);
                current = current->left;
                level++;
            }
            else
            {
                current = s.top();
                s.pop();

                cout << "ID: " << current->element.id << "\nAge: " << current->element.age << "\nName: " << current->element.name;
                cout << "\nLevel: " << level << "\n\n";
                current = current->right;
            }
        }
    }

private:

    BinaryNode* root;

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(const Employee& x, BinaryNode*& t)
    {
        BinaryNode* current = root;
        BinaryNode* newNode = new BinaryNode(x,NULL,NULL);

        if (isEmpty())
        {
            newNode->left = NULL;
            newNode->right = NULL;
            root = newNode;
        }
        else
        {
            bool condition = true;

            while (condition)
            {
                if (newNode->element.id < current->element.id)
                {
                    if (current->left == NULL)
                        condition = false;
                    else
                        current = current->left;
                }
                else
                {
                    if (current->right == NULL)
                        condition = false;
                    else
                        current = current->right;
                }
            }

            // INSERTS TO THE RIGHT OF THE NODE IF THEY ARE THE SAME VALUE

            if (newNode->element.id < current->element.id)
                current->left = newNode;
            else
                current->right = newNode;
        }
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove(const int id, BinaryNode*& t)
    {
        BinaryNode* current = t;
        BinaryNode* min = root;
        BinaryNode* previous = root;

        while (current != NULL)
        {
            if (current->element.id == id)
                break;
            if (current->element.id < id)
                current = current->right;
            else
                current = current->left;
        }
        
        //Finding the Target Node
        
        if (current == NULL)
            cout << "Employee not found!\n";
        else
        {
            // Node to be deleted is a leaf
            if (current->left == NULL && current->right == NULL)
            {
                if (previous->left == current)
                    previous->left = NULL;
                else // previous->right == current
                    previous->right = NULL;
            }

            // Node to be deleted has a right child
            else if (current->left == NULL && current->right != NULL)
            {
                if (previous->left)
                    previous->left = current->right;
                else
                    previous->right = current->right;
            }

            // Node to be deleted has a left child
            else if (current->left != NULL && current->right == NULL)
            {
                if (previous->left == current)
                    previous->left = current->left;
                else
                    previous->right = current->left;
            }

            // Node to be deleted has two children
            else
            {
                min = findMin(current->right);

                if (previous->left == current)
                {
                    previous->left = min;
                    min->left = current->left;
                    min->right = current->right;
                }
                else
                {
                    previous->right = min;
                    min->left = current->left;
                    min->right = current->right;
                }
            }
            free(current);

            cout << "Employee has been deleted.\n";
        }
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode* findMin(BinaryNode* t) const
    {
        BinaryNode* current = root;
        BinaryNode* min = root;

        while (current != NULL)
        {
            if (current->element.id < min->element.id)
                min = current;
            current = current->left;
        }
        return min;
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode* findMax(BinaryNode* t) const
    {
        BinaryNode* current = root;
        BinaryNode* max = root;

        while (current != NULL)
        {
            if (current->element.id > max->element.id)
                max = current;
            current = current->right;
        }
        return max;
    }


    /**
     * id is item to search for.
     * t is the node that roots the subtree.
     */
    bool find(const int id, BinaryNode* t) const
    {
        while (t != NULL)
        {
            if (t->element.id == id)
            {
                cout << "ID: " << t->element.id << "\nAge: " << t->element.age << "\nName: " << t->element.name;
                return true;
            }

            if (t->element.id < id)
                t = t->right;
            else
                t = t->left;

            if (t == NULL)
                break;
        }
        cout << "Employee not found!\n";
        return false;
    }

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty(BinaryNode*& t)
    {
        if (t != NULL)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            free(t);
            t = NULL;
        }
        else
            return;
    }
};

#endif
