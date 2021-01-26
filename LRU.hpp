
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
public:
    LRUCache_(int capacity) {
        cap = capacity;
    }

    int get(int key) {
        int ret = -1;
        auto it = table.find(key);
        if (it != table.end()) {
            ret = it->second->second;
            touch(key);
        }
        return ret;
    }

    void put(int key, int value) {
        auto it = table.find(key);
        if (it != table.end()) {
            it->second->second = value;
            touch(key);
        }
        else {
            lru.push_front({ key, value });
            table[key] = lru.begin();
            if (lru.size() > cap) {
                int del = lru.back().first;
                table.erase(table.find(del));
                lru.pop_back();
            }
        }
    }
public:
    list<pair<int, int>> lru;
    unordered_map<int, list<pair<int, int>>::iterator> table;
    int cap;

    void touch(int key) {
        auto it = table.find(key);
        int val = it->second->second;
        lru.erase(it->second);
        lru.push_front({ key, val });
        table[key] = lru.begin();
    }
};
