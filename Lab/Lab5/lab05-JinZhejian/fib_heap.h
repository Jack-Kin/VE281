#ifndef FIB_HEAP_H
#define FIB_HEAP_H

#include <algorithm>
#include <cmath>
#include <list>
#include "priority_queue.h"

typedef unsigned size_type;

template<typename TYPE, typename COMP= std::less<TYPE>>
class fib_heap: public priority_queue<TYPE, COMP> {
    class node {
    private:
        node* prev;
        node* next;
        node* child;
        node* parent;
        TYPE value;
        int degree;
        bool marked;
    public:
        friend class fib_heap<TYPE,COMP>;
    };

protected:
    node* heap;
public:
    fib_heap(COMP comp = COMP()){
        compare = comp;
        heap = nullptr;
    }

    ~fib_heap(){
        if(heap) {
            deleteAll(heap);
        }
    }

    virtual void enqueue(const TYPE &val){
        node* ret=_singleton(val);
        heap=_merge(heap,ret);
    }


    virtual TYPE dequeue_min(){
        node* old=heap;
        heap=_removeMinimum(heap);
        TYPE ret=old->value;
        delete old;
        return ret;
    }

    virtual const TYPE &get_min() const{
        return heap->value;
    }

    virtual size_type size() const{
        return 0;
    }

    virtual bool empty() const{
        return heap == nullptr;
    }

private:
    COMP compare;
    node* _singleton(TYPE value) {
        node* n=new node;
        n->value=value;
        n->prev=n->next=n;
        n->degree=0;
        n->marked=false;
        n->child=NULL;
        n->parent=NULL;
        return n;
    }

    void deleteAll(node* n) {
        if(n!=NULL) {
            node* c=n;
            do {
                node* d=c;
                c=c->next;
                deleteAll(d->child);
                delete d;
            } while(c!=n);
        }
    }

    node* _merge(node* a,node* b) {
        if(a==NULL)return b;
        if(b==NULL)return a;
        if(compare(b->value, a->value)) {
            node* temp=a;
            a=b;
            b=temp;
        }
        node* an=a->next;
        node* bp=b->prev;
        a->next=b;
        b->prev=a;
        an->prev=bp;
        bp->next=an;
        return a;
    }

    void _addChild(node* parent,node* child) {
        child->prev=child->next=child;
        child->parent=parent;
        parent->degree++;
        parent->child=_merge(parent->child,child);
    }

    void _unMarkAndUnParentAll(node* n) {
        if(n==NULL)return;
        node* c=n;
        do {
            c->marked=false;
            c->parent=NULL;
            c=c->next;
        }while(c!=n);
    }

    node* _removeMinimum(node* n) {
        _unMarkAndUnParentAll(n->child);
        if(n->next==n) {
            n=n->child;
        } else {
            n->next->prev=n->prev;
            n->prev->next=n->next;
            n=_merge(n->next,n->child);
        }
        if(n==NULL)return n;
        node* trees[64]={NULL};

        while(true) {
            if(trees[n->degree]!=NULL) {
                node* t=trees[n->degree];
                if(t==n)break;
                trees[n->degree]=NULL;
                if(compare(n->value,t->value)) {
                    t->prev->next=t->next;
                    t->next->prev=t->prev;
                    _addChild(n,t);
                } else {
                    t->prev->next=t->next;
                    t->next->prev=t->prev;
                    if(n->next==n) {
                        t->next=t->prev=t;
                        _addChild(t,n);
                        n=t;
                    } else {
                        n->prev->next=t;
                        n->next->prev=t;
                        t->next=n->next;
                        t->prev=n->prev;
                        _addChild(t,n);
                        n=t;
                    }
                }
                continue;
            } else {
                trees[n->degree]=n;
            }
            n=n->next;
        }
        node* min=n;
        node* start=n;
        do {
            if(compare(n->value,min->value)) min=n;
            n=n->next;
        } while(n!=start);
        return min;
    }

};

#endif //FIB_HEAP_H
