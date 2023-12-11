/*5.   Implement binary search tree and Perform following operations:
a) Insert,
b) delete,
c) search
d) display tree (traversal)
e) display — depth of tree
f) display - mirror image
) create a copy
f) Display all parent nodes with their child nodes
g) display tree level wise
h) display leaf nodes.
(Note: Insertion, Deletion, Search and Traversal are compulsory, from rest of operations, perform Any
three*/
#include<iostream>
#include<stdio.h>
using namespace std;

struct treeNode {
    int data;
    treeNode* left;
    treeNode* right;
};

treeNode* FindMin(treeNode* node) {
    if (node == NULL) {
        return NULL;
    }
    if (node->left)
        return FindMin(node->left);
    else
        return node;
}

treeNode* FindMax(treeNode* node) {
    if (node == NULL) {
        return NULL;
    }
    if (node->right)
        return FindMax(node->right);
    else
        return node;
}

treeNode* Insert(treeNode* node, int data) {
    if (node == NULL) {
        treeNode* temp;
        temp = new treeNode;
        temp->data = data;
        temp->left = temp->right = NULL;
        return temp;
    }
    if (data > (node->data)) {
        node->right = Insert(node->right, data);
    }
    else if (data < (node->data)) {
        node->left = Insert(node->left, data);
    }
    return node;
}

treeNode* Delete(treeNode* node, int data) {
    treeNode* temp;
    if (node == NULL) {
        cout << "Element not found";
    }
    else if (data < node->data) {
        node->left = Delete(node->left, data);
    }
    else if (data > node->data) {
        node->right = Delete(node->right, data);
    }
    else {
        if (node->right && node->left) {
            temp = FindMin(node->right);
            node->data = temp->data;
            node->right = Delete(node->right, temp->data);
        }
        else {
            temp = node;
            if (node->left == NULL)
                node = node->right;
            else if (node->right == NULL)
                node = node->left;
            free(temp);
        }
    }
    return node;
}

treeNode* Find(treeNode* node, int data) {
    if (node == NULL) {
        return NULL;
    }
    if (data > node->data) {
        return Find(node->right, data);
    }
    else if (data < node->data) {
        return Find(node->left, data);
    }
    else {
        return node;
    }
}

void Inorder(treeNode* node) {
    if (node == NULL) {
        return;
    }
    Inorder(node->left);
    cout << node->data << " ";
    Inorder(node->right);
}

void Preorder(treeNode* node) {
    if (node == NULL) {
        return;
    }
    cout << node->data << " ";
    Preorder(node->left);
    Preorder(node->right);
}

void Postorder(treeNode* node) {
    if (node == NULL) {
        return;
    }
    Postorder(node->left);
    Postorder(node->right);
    cout << node->data << " ";
}

int main() {
    treeNode* root = NULL;
    int ch;
    while (1) {
        cout << "\n1.Insert\n2.Delete\n3.Inorder\n4.Preorder\n5.Postorder\n6.FindMin\n7.FindMax\n8.Search\n9.Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;
        switch (ch) {
            case 1:
                cout << "\nEnter the element to be inserted: ";
                cin >> ch;
                root = Insert(root, ch);
                cout << "\nElements in BST are: ";
                Inorder(root);
                break;
            case 2:
                cout << "\nEnter the element to be deleted: ";
                cin >> ch;
                root = Delete(root, ch);
                cout << "\nAfter deletion, elements in BST are: ";
                Inorder(root);
                break;
            case 3:
                cout << "Inorder traversal is: ";
                Inorder(root);
                break;
            case 4:
                cout << "Preorder traversal is: ";
                Preorder(root);
                break;
            case 5:
                cout << "Postorder traversal is: ";
                Postorder(root);
                break;
            case 6:
                treeNode* temp;
                temp = FindMin(root);
                cout << "\nMinimum element is: " << temp->data;
                break;
            case 7:
                temp = FindMax(root);
                cout << "\nMaximum element is: " << temp->data;
                break;
            case 8:
                cout << "\nEnter the element to be searched: ";
                cin >> ch;
                temp = Find(root, ch);
                if (temp == NULL) {
                    cout << "Element not found";
                }
                else {
                    return NULL;
                }
        }
    }
}
