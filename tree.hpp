#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;
template <class T> struct TreapNode;
template <class T> struct TreapNode {
  T key;
  TreapNode<T> *left, *right;
  int priority;
  TreapNode(T key = 0, TreapNode<T> *left = NULL, TreapNode<T> *right = NULL,
            int priority = rand()) {
    this->key = key;
    this->left = left;
    this->right = right;
    this->priority = priority;
  }
  ~TreapNode() {
    if (left != NULL)
      delete left;
    if (right != NULL)
      delete right;
  }
  static void print(TreapNode<T> *root) {
    if (root == nullptr)
      return;
    print(root->left);
    cout << root->key << " ";
    print(root->right);
  }
};
template <class T> class Treap;
template <class T> class Treap {
private:
  TreapNode<T> *root;
  int _height;

public:
  Treap() {
    root = nullptr;
    _height = 0;
  }
  ~Treap() { delete root; }
  static void merge(TreapNode<T> *&t, TreapNode<T> *l, TreapNode<T> *r) {
    if (l == NULL) {
      t = r;
    } else if (r == NULL) {
      t = l;
    } else if (l->priority > r->priority) {
      merge(l->right, l->right, r);
      t = l;
    } else {
      merge(r->left, l, r->left);
      t = r;
    }
    return;
  }
  static void split(TreapNode<T> *t, TreapNode<T> *&l, TreapNode<T> *&r, T x0) {
    l = r = NULL;
    if (t == NULL)
      return;
    if (t->key <= x0) {
      if (t->right)
        split(t->right, t->right, r, x0);
      l = t;
    } else {
      if (t->left)
        split(t->left, l, t->left, x0);
      r = t;
    }
    return;
  }
  void split(TreapNode<T> *&l, TreapNode<T> *&r, T x0) {
    split(root, l, r, x0);
  }
  void insert(TreapNode<T> *n) {
    if (root == nullptr) {
      root = n;
      return;
    }
    split(n->left, n->right, n->key);
    TreapNode<T> *l = n->left, *r = n->right;
    n->left = n->right = NULL;
    merge(n, n, r);
    merge(root, l, n);
    l = r = NULL;
    return;
  }
  static void erase(TreapNode<T> *&t, T x) {
    if (t == NULL)
      return;
    if (t->key == x) {
      TreapNode<T> *l = t->left, *r = t->right;
      t->left = t->right = nullptr;
      delete t;
      merge(t, l, r);
    } else
      erase((t->key < x) ? t->right : t->left, x);
    return;
  }
  void erase(T x) { erase(root, x); }
  static int calc_height(TreapNode<T> *c) {
    if (c == NULL || c->priority < 0)
      return 0;
    int m1 = calc_height(c->right);
    int m2 = calc_height(c->left);
    int res = (m1 > m2) ? m1 : m2;
    return (res + 1);
  }
  int height() {
    if (_height > 0)
      return _height;
    return calc_height(root);
  }
  static void del(TreapNode<T> *c) {
    if (c == NULL)
      return;
    del(c->left);
    del(c->right);
    delete c;
    delete &c;
    return;
  }
  bool find(T key) {
    TreapNode<T> *cur = this->root;
    while (cur != nullptr) {
      if (cur->key < key)
        cur = cur->left;
      else if (cur->key == key)
        return true;
      else
        cur = cur->right;
    }
  }
  friend class Tree;
};
// Интерфейс
class Container {
public:
  // Виртуальные методы, будут реализованы далее
  virtual void insert(int value) = 0;
  virtual bool exists(int value) = 0;
  virtual void remove(int value) = 0;
  // Это потом заменим на перегруженный оператор <<
  virtual void print() = 0;

  // Виртуальный деструктор
  virtual ~Container();
};
Container::~Container() {}
class Tree : public Container {
private:
  Treap<int> m_tree;

public:
  virtual void insert(int value) { m_tree.insert(new TreapNode<int>(value)); }
  virtual bool exists(int value) { return m_tree.find(value); }
  virtual void remove(int value) { m_tree.erase(value); }
  virtual void print() { TreapNode<int>::print(m_tree.root); }
  int height() { return m_tree.height(); }
};
