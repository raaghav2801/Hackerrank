#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{

   protected:
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};
class LRUCache: Cache {
 public:
  LRUCache(int l) {
    cp = l;
    tail = NULL;
    head = NULL;
    mp = {};
  }
  virtual void set(int k, int v) {
    auto it = mp.find(k);
    if (it == mp.end()) {
      Node *node = new Node(k, v);
      if (cp == 0) {
        node->next = head;
        head->prev = node;
        head = node;
        Node *tmp = tail;
        mp.erase(tmp->key);
        tail = tail->prev;
        delete tmp;
      } else {
        cp--;
        if (head == NULL) {
          head = node;
          tail = node;
        } else {
          node->next = head;
          head->prev = node;
          head = node;
        }
      }
      mp[k] = node;
    } else {
      Node *tmp = it->second;
      if (tmp != head) {
        if (tmp == tail) {
          tail = tmp->prev;
          tmp->prev->next = NULL;
          tmp->prev = NULL;
          tmp->next = head;
          head->prev = tmp;
          head = tmp;
        } else {
          tmp->prev->next = tmp->next;
          tmp->next->prev = tmp->prev;
          tmp->prev = NULL;
          tmp->next = head;
          head->prev = tmp;
          head = tmp;
        }
      }
      head->value = v;
    }
  }
  virtual int get(int k) {
    auto it = mp.find(k);
    if (it != mp.end()) {
      return it->second->value;
    }
    return -1;
  }
};
int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      }
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}
