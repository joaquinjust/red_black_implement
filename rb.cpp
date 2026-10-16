#include<bits/stdc++.h>
using namespace::std;
 
enum Color { RED, BLACK };
 
template<typename data_type>
struct RedBlackTree {
 
    struct TreeNode {
        data_type data;
        Color color;
        TreeNode* left;
        TreeNode* right;
        TreeNode* parent;
 
        TreeNode(data_type data = data_type(), Color color = BLACK,
                    TreeNode* left = nullptr,
                    TreeNode* right = nullptr,
                    TreeNode* parent = nullptr) :
                    data(data), color(color), left(left), right(right), parent(parent) {}
    };
 
    TreeNode* root;
    TreeNode* nil;
 
    RedBlackTree() {
        nil = new TreeNode();
        nil -> color = BLACK;
        nil -> left = nil;
        nil -> right = nil;
        nil -> parent = nil;
        root = nil;
    }
 
    ~RedBlackTree() {
        destroy(root);
        delete nil;
    }
 
    void destroy(TreeNode* u) {
        if (u == nil) return;
        destroy(u -> left);
        destroy(u -> right);
        delete u;
    }
 
    int h(TreeNode* u) {
        if (u == nil) return -1;
        return 1 + max(h(u -> left), h(u -> right));
    }
 
    TreeNode* find(data_type key) {
        TreeNode* current = root;
        while (current != nil) {
            if (current -> data == key) {
                return current;
            }
            if (current -> data > key) {
                current = current -> left;
            }
            else {
                current = current -> right;
            }
        }
        return nil;
    }
 
    bool search(data_type key) {
        return find(key) != nil;
    }
 
    TreeNode* min_element(TreeNode* u) {
        if (u == nil) return nil;
        TreeNode* current = u;
        while (current -> left != nil) {
            current = current -> left;
        }
        return current;
    }
 
    TreeNode* max_element(TreeNode* u) {
        if (u == nil) return nil;
        TreeNode* current = u;
        while (current -> right != nil) {
            current = current -> right;
        }
        return current;
    }
 
    TreeNode* min_element() {
        return min_element(root);
    }
 
    TreeNode* max_element() {
        return max_element(root);
    }
 
    TreeNode* successor(TreeNode* x) {
        if (x -> right != nil) {
            return min_element(x -> right);
        }
        TreeNode* y = x -> parent;
        while (y != nil and y -> right == x) {
            x = y;
            y = y -> parent;
        }
        return y;
    }
 
    TreeNode* predecessor(TreeNode* x) {
        if (x -> left != nil) {
            return max_element(x -> left);
        }
        TreeNode* y = x -> parent;
        while (y != nil and y -> left == x) {
            x = y;
            y = y -> parent;
        }
        return y;
    }
 
    void rotate_left(TreeNode* x) {
        TreeNode* y = x -> right;
        x -> right = y -> left;
        if (y -> left != nil) {
            y -> left -> parent = x;
        }
        y -> parent = x -> parent;
        if (x -> parent == nil) {
            root = y;
        }
        else if (x == x -> parent -> left) {
            x -> parent -> left = y;
        }
        else {
            x -> parent -> right = y;
        }
        y -> left = x;
        x -> parent = y;
    }
 
    void rotate_right(TreeNode* x) {
        TreeNode* y = x -> left;
        x -> left = y -> right;
        if (y -> right != nil) {
            y -> right -> parent = x;
        }
        y -> parent = x -> parent;
        if (x -> parent == nil) {
            root = y;
        }
        else if (x == x -> parent -> right) {
            x -> parent -> right = y;
        }
        else {
            x -> parent -> left = y;
        }
        y -> right = x;
        x -> parent = y;
    }
 
    void insert_fixup(TreeNode* z) {
        while (z -> parent -> color == RED) {
            if (z -> parent == z -> parent -> parent -> left) {
                TreeNode* t = z -> parent -> parent -> right;
                if (t -> color == RED) {
                    z -> parent -> color = BLACK;
                    t -> color = BLACK;
                    z -> parent -> parent -> color = RED;
                    z = z -> parent -> parent;
                }
                else {
                    if (z == z -> parent -> right) {
                        z = z -> parent;
                        rotate_left(z);
                    }
                    z -> parent -> color = BLACK;
                    z -> parent -> parent -> color = RED;
                    rotate_right(z -> parent -> parent);
                }
            }
            else {
                TreeNode* t = z -> parent -> parent -> left;
                if (t -> color == RED) {
                    z -> parent -> color = BLACK;
                    t -> color = BLACK;
                    z -> parent -> parent -> color = RED;
                    z = z -> parent -> parent;
                }
                else {
                    if (z == z -> parent -> left) {
                        z = z -> parent;
                        rotate_right(z);
                    }
                    z -> parent -> color = BLACK;
                    z -> parent -> parent -> color = RED;
                    rotate_left(z -> parent -> parent);
                }
            }
        }
        root -> color = BLACK;
    }
 
    void insert(data_type value) {
        TreeNode* z = new TreeNode(value, RED, nil, nil, nil);
        TreeNode* y = nil;
        TreeNode* x = root;
        while (x != nil) {
            y = x;
            if (z -> data < x -> data) {
                x = x -> left;
            }
            else {
                x = x -> right;
            }
        }
        z -> parent = y;
        if (y == nil) {
            root = z;
        }
        else if (z -> data < y -> data) {
            y -> left = z;
        }
        else {
            y -> right = z;
        }
        insert_fixup(z);
    }
 
    void transplant(TreeNode* u, TreeNode* v) {
        if (u -> parent == nil) {
            root = v;
        }
        else if (u == u -> parent -> left) {
            u -> parent -> left = v;
        }
        else {
            u -> parent -> right = v;
        }
        v -> parent = u -> parent;
    }
 
    void erase_fixup(TreeNode* x) {
        while (x != root and x -> color == BLACK) {
            if (x == x -> parent -> left) {
                TreeNode* w = x -> parent -> right;
                if (w -> color == RED) {
                    w -> color = BLACK;
                    x -> parent -> color = RED;
                    rotate_left(x -> parent);
                    w = x -> parent -> right;
                }
                if (w -> left -> color == BLACK and w -> right -> color == BLACK) {
                    w -> color = RED;
                    x = x -> parent;
                }
                else {
                    if (w -> right -> color == BLACK) {
                        w -> left -> color = BLACK;
                        w -> color = RED;
                        rotate_right(w);
                        w = x -> parent -> right;
                    }
                    w -> color = x -> parent -> color;
                    x -> parent -> color = BLACK;
                    w -> right -> color = BLACK;
                    rotate_left(x -> parent);
                    x = root;
                }
            }
            else {
                TreeNode* w = x -> parent -> left;
                if (w -> color == RED) {
                    w -> color = BLACK;
                    x -> parent -> color = RED;
                    rotate_right(x -> parent);
                    w = x -> parent -> left;
                }
                if (w -> right -> color == BLACK and w -> left -> color == BLACK) {
                    w -> color = RED;
                    x = x -> parent;
                }
                else {
                    if (w -> left -> color == BLACK) {
                        w -> right -> color = BLACK;
                        w -> color = RED;
                        rotate_left(w);
                        w = x -> parent -> left;
                    }
                    w -> color = x -> parent -> color;
                    x -> parent -> color = BLACK;
                    w -> left -> color = BLACK;
                    rotate_right(x -> parent);
                    x = root;
                }
            }
        }
        x -> color = BLACK;
    }
 
    void erase(TreeNode* z) {
        TreeNode* y = z;
        Color original_color = y -> color;
        TreeNode* x;
        if (z -> left == nil) {
            x = z -> right;
            transplant(z, z -> right);
        }
        else if (z -> right == nil) {
            x = z -> left;
            transplant(z, z -> left);
        }
        else {
            y = min_element(z -> right);
            original_color = y -> color;
            x = y -> right;
            if (y -> parent == z) {
                x -> parent = y;
            }
            else {
                transplant(y, y -> right);
                y -> right = z -> right;
                y -> right -> parent = y;
            }
            transplant(z, y);
            y -> left = z -> left;
            y -> left -> parent = y;
            y -> color = z -> color;
        }
        delete z;
        if (original_color == BLACK) {
            erase_fixup(x);
        }
    }
 
    void erase(data_type key) {
        TreeNode* z = find(key);
        if (z == nil) return;
        erase(z);
    }
 
    int verify(TreeNode* u, const data_type* lo, const data_type* hi) {
        if (u == nil) return 1;
        if (lo != nullptr and !(*lo < u -> data)) return -1;
        if (hi != nullptr and !(u -> data < *hi)) return -1;
        if (u -> color == RED and (u -> left -> color == RED or u -> right -> color == RED)) return -1;
        if (u -> left != nil and u -> left -> parent != u) return -1;
        if (u -> right != nil and u -> right -> parent != u) return -1;
        int a = verify(u -> left, lo, &(u -> data));
        if (a == -1) return -1;
        int b = verify(u -> right, &(u -> data), hi);
        if (b == -1) return -1;
        if (a != b) return -1;
        if (u -> color == BLACK) return a + 1;
        return a;
    }
 
    bool verify() {
        if (nil -> color != BLACK) return false;
        if (root -> color != BLACK) return false;
        if (root != nil and root -> parent != nil) return false;
        return verify(root, nullptr, nullptr) != -1;
    }
 
    void print_color(TreeNode* u) {
        if (u -> color == RED) cout << "R";
        else cout << "N";
    }
 
    void print_inorder() {
        print_subtree_inorder(root);
        cout << endl;
    }
 
    void print_subtree_inorder(TreeNode* u) {
        if (u == nil) return;
        print_subtree_inorder(u -> left);
        cout << u -> data << " ";
        print_subtree_inorder(u -> right);
    }
 
    void print_preorder() {
        print_subtree_preorder(root);
        cout << endl;
    }
 
    void print_subtree_preorder(TreeNode* u) {
        if (u == nil) return;
        cout << u -> data;
        print_color(u);
        cout << " ";
        print_subtree_preorder(u -> left);
        print_subtree_preorder(u -> right);
    }
 
    void print_postorder() {
        print_subtree_postorder(root);
        cout << endl;
    }
 
    void print_subtree_postorder(TreeNode* u) {
        if (u == nil) return;
        print_subtree_postorder(u -> left);
        print_subtree_postorder(u -> right);
        cout << u -> data << " ";
    }
};
 
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int q;
    cin >> q;
    RedBlackTree<int> T;
    while (q--) {
        string op;
        cin >> op;
        if (op == "insert") {
            int x;
            cin >> x;
            T.insert(x);
            cout << "insertado " << x << " | altura = " << T.h(T.root) << ", raiz = " << T.root -> data;
            T.print_color(T.root);
            cout << '\n';
        }
        else if (op == "erase") {
            int x;
            cin >> x;
            if (!T.search(x)) {
                cout << x << " no esta en el arbol\n";
            }
            else {
                T.erase(x);
                cout << "eliminado " << x << " | altura = " << T.h(T.root);
                if (T.root != T.nil) cout << ", raiz = " << T.root -> data;
                cout << '\n';
            }
        }
        else if (op == "search") {
            int x;
            cin >> x;
            if (T.search(x)) cout << x << " esta\n";
            else cout << x << " no esta\n";
        }
        else if (op == "min") {
            if (T.root == T.nil) cout << "arbol vacio\n";
            else cout << "min = " << T.min_element() -> data << '\n';
        }
        else if (op == "max") {
            if (T.root == T.nil) cout << "arbol vacio\n";
            else cout << "max = " << T.max_element() -> data << '\n';
        }
        else if (op == "succ") {
            int x;
            cin >> x;
            auto u = T.find(x);
            if (u == T.nil) {
                cout << x << " no esta en el arbol\n";
            }
            else {
                auto s = T.successor(u);
                if (s == T.nil) cout << "no hay sucesor de " << x << '\n';
                else cout << "sucesor de " << x << " = " << s -> data << '\n';
            }
        }
        else if (op == "pred") {
            int x;
            cin >> x;
            auto u = T.find(x);
            if (u == T.nil) {
                cout << x << " no esta en el arbol\n";
            }
            else {
                auto p = T.predecessor(u);
                if (p == T.nil) cout << "no hay predecesor de " << x << '\n';
                else cout << "predecesor de " << x << " = " << p -> data << '\n';
            }
        }
        else if (op == "height") {
            cout << "altura = " << T.h(T.root) << '\n';
        }
        else if (op == "inorder") {
            T.print_inorder();
        }
        else if (op == "preorder") {
            T.print_preorder();
        }
        else if (op == "postorder") {
            T.print_postorder();
        }
        else if (op == "verify") {
            if (T.verify()) cout << "Red-Black valido\n";
            else cout << "Red-Black INVALIDO\n";
        }
        else {
            cout << "comando desconocido: " << op << '\n';
        }
    }
    return 0;
}
