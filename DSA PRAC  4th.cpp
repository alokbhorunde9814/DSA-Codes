/*#PROVIDED BY mr.SHLOK
4.  To construct an Expression Tree from postfix and prefix expression. Perform recursive and non- recursive
in-order, pre-order and post-order traversals.*/
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct Node {
    char value;
    Node* left;
    Node* right;

    Node(char val) : value(val), left(nullptr), right(nullptr) {}
};

Node* constructExpressionTreePostfix(const string& postfix) {
    stack<Node*> st;
    for (char symbol : postfix) {
        if (isalnum(symbol)) {
            st.push(new Node(symbol));
        } else {
            Node* node = new Node(symbol);
            node->right = st.top();
            st.pop();
            node->left = st.top();
            st.pop();
            st.push(node);
        }
    }
    return st.top();
}

Node* constructExpressionTreePrefix(const string& prefix) {
    stack<Node*> st;
    for (int i = prefix.size() - 1; i >= 0; --i) {
        char symbol = prefix[i];
        if (isalnum(symbol)) {
            st.push(new Node(symbol));
        } else {
            Node* node = new Node(symbol);
            node->left = st.top();
            st.pop();
            node->right = st.top();
            st.pop();
            st.push(node);
        }
    }
    return st.top();
}

void recursiveInorderTraversal(Node* root) {
    if (root) {
        recursiveInorderTraversal(root->left);
        cout << root->value << " ";
        recursiveInorderTraversal(root->right);
    }
}

void recursivePreorderTraversal(Node* root) {
    if (root) {
        cout << root->value << " ";
        recursivePreorderTraversal(root->left);
        recursivePreorderTraversal(root->right);
    }
}

void recursivePostorderTraversal(Node* root) {
    if (root) {
        recursivePostorderTraversal(root->left);
        recursivePostorderTraversal(root->right);
        cout << root->value << " ";
    }
}

void nonRecursiveInorderTraversal(Node* root) {
    stack<Node*> st;
    Node* current = root;

    while (current || !st.empty()) {
        while (current) {
            st.push(current);
            current = current->left;
        }

        current = st.top();
        st.pop();

        cout << current->value << " ";

        current = current->right;
    }
}

void nonRecursivePreorderTraversal(Node* root) {
    stack<Node*> st;
    st.push(root);

    while (!st.empty()) {
        Node* current = st.top();
        st.pop();

        if (current) {
            cout << current->value << " ";
            st.push(current->right);
            st.push(current->left);
        }
    }
}

void nonRecursivePostorderTraversal(Node* root) {
    stack<Node*> st;
    vector<char> result;

    st.push(root);

    while (!st.empty()) {
        Node* current = st.top();
        st.pop();

        if (current) {
            result.push_back(current->value);
            st.push(current->left);
            st.push(current->right);
        }
    }

    for (int i = result.size() - 1; i >= 0; --i) {
        cout << result[i] << " ";
    }
}

int main() {
    string postfix, prefix;
    cout << "Enter a postfix expression: ";
    cin >> postfix;

    Node* rootPostfix = constructExpressionTreePostfix(postfix);

    cout << "Enter a prefix expression: ";
    cin >> prefix;

    Node* rootPrefix = constructExpressionTreePrefix(prefix);

    cout << "\nRecursive In-order Traversal: ";
    recursiveInorderTraversal(rootPostfix);
    cout << endl;

    cout << "\nRecursive Pre-order Traversal: ";
    recursivePreorderTraversal(rootPostfix);
    cout << endl;

    cout << "\nRecursive Post-order Traversal: ";
    recursivePostorderTraversal(rootPostfix);
    cout << endl;

    cout << "\nNon-Recursive In-order Traversal: ";
    nonRecursiveInorderTraversal(rootPostfix);
    cout << endl;

    cout << "\nNon-Recursive Pre-order Traversal: ";
    nonRecursivePreorderTraversal(rootPostfix);
    cout << endl;

    cout << "\nNon-Recursive Post-order Traversal: ";
    nonRecursivePostorderTraversal(rootPostfix);
    cout << endl;

    return 0;
}
