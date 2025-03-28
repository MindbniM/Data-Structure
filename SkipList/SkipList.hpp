#pragma once
#include <vector>
template<typename T>
struct skiplist_node
{
    T _val;
    std::vector<skiplist_node*> _next; 
    skiplist_node(int val,size_t size):_val(val),_next(size)
    {}

};
template<typename T>
class Skiplist {
public:
    Skiplist(int maxLevel=32,double p=0.5):_maxLevel(maxLevel),_p(p) {
        _head=new skiplist_node<T>(0,1);
    }
    ~Skiplist() {
        skiplist_node<T>* node = _head->_next[0];
        while (node != nullptr)
        {
            skiplist_node<T>* next = node->_next[0];
            delete node;
            node = next;
        }
        delete _head;
    }
    
    std::pair<std::vector<skiplist_node<T>*>,skiplist_node<T>*> GetPrev(int val)
    {
        std::vector<skiplist_node<T>*> prev(_head->_next.size());
        int i=_head->_next.size()-1;
        skiplist_node<T>* p=_head;
        while(i>=0)
        {
            if(p->_next[i]==nullptr||p->_next[i]->_val>=val)
            {
                prev[i]=p;
                i--;
            }
            else p=p->_next[i];
        }
        if(p->_next[0]==nullptr||p->_next[0]->_val!=val)
            return {prev,nullptr};
        else return {prev,prev[0]->_next[0]};
    }
    bool search(T target) {
        auto [prev,flag]=GetPrev(target);
        return flag!=nullptr;
    }
    
    void add(T num) {
        auto it=GetPrev(num);
        std::vector<skiplist_node<T>*> prev = it.first;
        int level=RandLevel();
        skiplist_node<T>* node=new skiplist_node<T>(num,level);
        if(level>_head->_next.size())
        {
            _head->_next.resize(level);
            prev.resize(level);
        }
        for(int i=0;i<level;i++)
        {
            if (prev[i] == nullptr) prev[i] = _head;
            skiplist_node<T>* next =prev[i]->_next[i];
            prev[i]->_next[i]=node;
            node->_next[i]=next;
        }
    }
    
    bool erase(T num) {
        auto it=GetPrev(num);
        std::vector<skiplist_node<T>*> prev = it.first;
        skiplist_node<T>* node = it.second;
        if(!node) return false;
        for(int i=0;i<node->_next.size(); i++)
        {
            prev[i]->_next[i]=node->_next[i];
        }
        delete node;
        return true;
    }
    int RandLevel()
    {
        int level=1;
        while(rand()<RAND_MAX*_p&&level<=_maxLevel)
        {
            level++;
        }
        return level;
    }
    skiplist_node<T>* _head;
    int _maxLevel;
    double _p;
};