
#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

class LRUCache {
private:
    struct DLinkedNode {
        int key, value;
        DLinkedNode* next;
        DLinkedNode* prev;
        DLinkedNode() : key(0), value(0), prev(nullptr), next(nullptr) {}
        DLinkedNode(int _key, int _val) : key(_key), value(_val), next(nullptr), prev(nullptr) {}
    };

    unordered_map<int, DLinkedNode*> cache;
    DLinkedNode* head;
    DLinkedNode* tail;
    int size;
    int capacity;

public:
    LRUCache(int _capacity) : capacity(_capacity), size(0) {
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (!cache.count(key)) {
            return -1;
        }
        DLinkedNode* node = cache[key];
        moveToHead(node);
        return node->value;
    }

    void put(int key, int value) {
        if (!cache.count(key)) {
            DLinkedNode* node = new DLinkedNode(key, value);
            cache[key] = node;
            addToHead(node);
            ++size;
            if (size > capacity) {
                DLinkedNode* removed = removeTail();
                cache.erase(removed->key);
                delete removed;
                --size;
            }
        }
        else {
            DLinkedNode* node = cache[key];
            node->value = value;
            moveToHead(node);
        }
    }

    void addToHead(DLinkedNode* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }

    void removeNode(DLinkedNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void moveToHead(DLinkedNode* node) {
        removeNode(node);
        addToHead(node);
    }

    DLinkedNode* removeTail() {
        DLinkedNode* node = tail->prev;
        removeNode(node);
        return node;
    }
};

class LRUCache_ {
private:
    struct Node {
        int key, val;
        Node* prev;
        Node* next;
        Node() : key(0), val(0), prev(nullptr), next(nullptr) {}
        Node(int _key, int _val) : key(_key), val(_val), prev(nullptr), next(nullptr) {}
    };

    unordered_map<int, Node*> cache;
    Node* head;
    Node* tail;
    int size;
    int cap;

public:
    LRUCache_(int _cap) : cap(_cap), size(0) {
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (!cache.count(key)) return -1;
        auto node = cache[key];
        moveToHead(node);
        return node->val;
    }

    void put(int key, int val) {
        if (!cache.count(key)) {
            auto node = new Node(key, val);
            cache[key] = node;
            addToHead(node);
            ++size;
            if (size > cap) {
                auto removed = removeTail();
                cache.erase(removed->key);
                delete removed;
                --size;
            }
        }
        else {
            auto node = cache[key];
            node->val = val;
            moveToHead(node);
        }
    }

    void removeNode(Node* node) {
        node->next->prev = node->prev;
        node->prev->next = node->next;
    }

    void addToHead(Node* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }

    void moveToHead(Node* node) {
        removeNode(node);
        addToHead(node);
    }

    Node* removeTail() {
        auto node = tail->prev;
        removeNode(node);
        return node;
    }
};

class LRUCache__ {
private:
    list<pair<int, int>> lru;
    unordered_map<int, list<pair<int, int>>::iterator> cache;
    int cap;

    void touch(int key) {
        auto it = cache.find(key);
        int val = it->second->second;
        lru.erase(it->second);
        lru.push_front({ key, val });
        cache[key] = lru.begin();
    }
public:
    LRUCache__(int _cap) : cap(_cap) {}

    int get(int key) {
        int ret = -1;
        auto it = cache.find(key);
        if (it != cache.end()) {
            ret = it->second->second;
            touch(key);
        }
        return ret;
    }

    void put(int key, int value) {
        auto it = cache.find(key);
        if (it != cache.end()) {
            it->second->second = value;
            touch(key);
        }
        else {
            lru.push_front({ key, value });
            cache[key] = lru.begin();
            if (lru.size() > cap) {
                int del = lru.back().first;
                cache.erase(cache.find(del));
                lru.pop_back();
            }
        }
    }
};

class LRUCache___ {
private:
    list<pair<int, int>> lru;
    unordered_map<int, list<pair<int, int>>::iterator> cache;
    int size;
    int cap;

    void update(int key) {
        auto it = cache[key];
        auto val = it->second;
        lru.erase(it);
        lru.push_front({ key, val });
        cache[key] = lru.begin();
    }

public:
    LRUCache___(int _cap) : cap(_cap), size(0) {}
    
    int get(int key) {
        if (!cache.count(key)) return -1;
        auto it = cache[key];
        int ret = it->second;
        update(key);
        return ret;
    }

    void put(int key, int val) {
        if (!cache.count(key)) {
            lru.push_front({ key, val });
            cache[key] = lru.begin();
            ++size;
            if (size > cap) {
                cache.erase(lru.back().first);
                lru.pop_back();
                --size;
            }
        }
        else {
            auto it = cache[key];
            it->second = val;
            update(key);
        }
    }
};