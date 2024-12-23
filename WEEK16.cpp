#include <iostream>
using namespace std;


struct Node {
    int x;
    int height;  
    Node* L;
    Node* R;
    Node(int a){
         x = a;
         height=1;
         L=NULL;
         R=NULL;
    }
};


int height(Node* node) {
    return node ? node->height : 0;
}


int getBalance(Node* node) {
    return node ? height(node->L) - height(node->R) : 0;
}


void updateHeight(Node* node) {
    if (node) {
        node->height = 1 + (height(node->L) > height(node->R) ? height(node->L) : height(node->R));
    }
}

Node* xoay_phai(Node* y) {
    Node* x = y->L;
    Node* T = x->R;

    x->R = y;
    y->L = T;

    updateHeight(y);
    updateHeight(x);

    return x;
}


Node* xoay_trai(Node* x) {
    Node* y = x->R;
    Node* T = y->L;

    y->L = x;
    x->R = T;

    updateHeight(x);
    updateHeight(y);

    return y;
}


Node* can_bang(Node* node) {
    updateHeight(node);

    int y = getBalance(node);

 
    if (y > 1 && getBalance(node->L) >= 0) {
        return xoay_phai(node);
    }

    if (y > 1 && getBalance(node->L) < 0) {
        node->L = xoay_trai(node->L);
        return xoay_phai(node);
    }
 
    if (y < -1 && getBalance(node->R) <= 0) {
        return xoay_trai(node);
    }

    if (y < -1 && getBalance(node->R) > 0) {
        node->R = xoay_phai(node->R);
        return xoay_trai(node);
    }

    return node; 
}


Node* insert(Node* root, int x) {
    if (!root) {
        return new Node(x);
    }

    if (x < root->x) {
        root->L = insert(root->L, x);
    } else if (x > root->x) {
        root->R = insert(root->R, x);
    } else {
        return root;
    }

    return can_bang(root);
}


void inOrder(Node* root) {
    if (root) {
        inOrder(root->L);
        cout << root->x << " ";
        inOrder(root->R);
    }
}


int main() {
    Node* root = NULL;

    int n;
    cout << "Nhap so luong phan tu: ";
    cin >> n;

    cout << "Nhap cac phan tu: ";
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        root = insert(root, x);
    }

    cout << "Cay AVL theo thu tu LNR: ";
    inOrder(root);
    cout << endl;

    return 0;
}
