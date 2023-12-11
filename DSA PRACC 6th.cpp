/*#PROVIDED BY mr.SHLOK
6.To implement In-order TBT and to perform In-order, and Pre-order traversals.*/
#include <iostream>
#include <cstdlib>

using namespace std;

struct nod // node declaration
{
    int info;
    struct nod *l;
    struct nod *r;
} *r;

class BST
{
public:
    void insert(nod *, nod *);
    void preorder(nod *);
    void inorder(nod *);
    void postorder(nod *);
    void show(nod *, int);

    BST()
    {
        r = NULL;
    }
};

void BST::insert(nod *tree, nod *newnode)
{
    if (r == NULL)
    {
        r = new nod;
        r->info = newnode->info;
        r->l = NULL;
        r->r = NULL;
        cout << "Root Node is Added" << endl;
        return;
    }

    if (tree->info == newnode->info)
    {
        cout << "Element already in the tree" << endl;
        return;
    }

    if (tree->info > newnode->info)
    {
        if (tree->l != NULL)
        {
            insert(tree->l, newnode);
        }
        else
        {
            tree->l = newnode;
            (tree->l)->l = NULL;
            (tree->l)->r = NULL;
            cout << "Node Added To Left" << endl;
            return;
        }
    }
    else
    {
        if (tree->r != NULL)
        {
            insert(tree->r, newnode);
        }
        else
        {
            tree->r = newnode;
            (tree->r)->l = NULL;
            (tree->r)->r = NULL;
            cout << "Node Added To Right" << endl;
            return;
        }
    }
}

void BST::preorder(nod *ptr)
{
    if (r == NULL)
    {
        cout << "Tree is empty" << endl;
        return;
    }

    if (ptr != NULL)
    {
        cout << ptr->info << " ";
        preorder(ptr->l);
        preorder(ptr->r);
    }
}

void BST::inorder(nod *ptr)
{
    if (r == NULL)
    {
        cout << "Tree is empty" << endl;
        return;
    }

    if (ptr != NULL)
    {
        inorder(ptr->l);
        cout << ptr->info << " ";
        inorder(ptr->r);
    }
}

void BST::postorder(nod *ptr)
{
    if (r == NULL)
    {
        cout << "Tree is empty" << endl;
        return;
    }

    if (ptr != NULL)
    {
        postorder(ptr->l);
        postorder(ptr->r);
        cout << ptr->info << " ";
    }
}

void BST::show(nod *ptr, int level)
{
    int i;

    if (ptr != NULL)
    {
        show(ptr->r, level + 1);
        cout << endl;

        if (ptr == r)
            cout << "Root->: ";
        else
        {
            for (i = 0; i < level; i++)
                cout << " ";
        }

        cout << ptr->info;
        show(ptr->l, level + 1);
    }
}

int main()
{
    int c, n, item;
    BST bst;
    nod *t;

    while (1)
    {
        cout << "1.Insert Element" << endl;
        cout << "2.Inorder Traversal" << endl;
        cout << "3.Preorder Traversal" << endl;
        cout << "4.Postorder Traversal" << endl;
        cout << "5.Display the tree" << endl;
        cout << "6.Quit" << endl;
        cout << "Enter your choice: ";
        cin >> c;

        switch (c)
        {
        case 1:
            t = new nod;
            cout << "Enter the number to be inserted: ";
            cin >> t->info;
            bst.insert(r, t);
            break;
        case 2:
            cout << "Inorder Traversal of BST:" << endl;
            bst.inorder(r);
            cout << endl;
            break;
        case 3:
            cout << "Preorder Traversal of BST:" << endl;
            bst.preorder(r);
            cout << endl;
            break;
        case 4:
            cout << "Postorder Traversal of BST:" << endl;
            bst.postorder(r);
            cout << endl;
            break;
        case 5:
            cout << "Display BST:" << endl;
            bst.show(r, 1);
            cout << endl;
            break;
        case 6:
            exit(1);
        default:
            cout << "Wrong choice" << endl;
        }
    }
}
