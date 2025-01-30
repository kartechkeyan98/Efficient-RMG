#pragma once

#include<iostream>

template<typename T>
class node{
public:
    T data;         // value/data in the node   
    node<T> *next;  // pointer to next node
public:
    node(): next(NULL)
    {
        this->data = static_cast<T>(0);
    }
    node(const T& value): data(value), next(NULL)
    {}

    node<T>* next_(){       
        return this->next;
    }
    T& get(){
        return this->data;
    }
};

template<typename T>
class list{
private:
    node<T>* _head;      // head node of list
    int _size;           // length of list

public:
    list():_head(NULL),_size(0)
    {}
    ~list(){
        node<T> *t=this->_head;
        for(int i=0;i<this->_size;++i){
            node<T>* p=t;
            t=t->next;
            delete p;
        }
    }

    /** 
     * All indices are 0-index, so please don't use 1-indexing and wonder why
     * it's not working
    */

    int size(){
        return this->_size;
    }

    void insert(const T &v, int k){
        // k is the 0-indexed position we gotta insert it at
        
        // 1. Go to k-1-th node [0-idx position]. 
        if(k==0){
            // special case, head node.....
            node<T>* n=new node(v);
            n->next=this->_head;
            this->_head = n;
            this->_size++;
            return;
        }
        node<T>* t = this->_head;
        for(int i=0;i<k-1;i++){
            t = t->next;
        }

        // 2. once there, create a new node to be inserted
        node<T>* n = new node(v);

        /**
         * 3. Create connections
         * n -> t->next
         * t -> n
         */
        n->next = t->next;
        t->next = n;
        
        // 4. update the size
        this->_size++;

        return;
    }

    void remove(int k){
        // k is the 0-indexed position we gotta insert it at
        if(this->_head==NULL)return; // empty list...still empty after removing
        if(k<0){
            std::cerr<<"Don't give negative indices! This ain't python. Get some help!\n";
            return;
        }

        // if k=0, i.e. we are removing head node
        if(k==0){
            node<T>* n = this->_head;
            this->_head = n->next;
            this->_size--;
            delete n;
            return;
        }

        // 1. you have to go to k-1-th node
        node<T> *t=this->_head;
        for(int i=0;i<k-1;i++){
            t=t->next;
            if(t==NULL)break;
        }
        if(t==NULL){
            std::cerr<<"Give the indices inside bounds, what are you doing?\n";
            return; // check if t went out of bounds
        }            

        // 2. make the necessary connections
        /**
         * p = t->next
         * t->next = p->next
         * delete p
         */
        
        node<T>* p=t->next;
        t->next = p->next;
        delete p;

        // 3. update size
        this->_size--;
        return;
    }

    // return the head node
    node<T>* head(){
        // starting node or head node
        return this->_head;
    }
    bool is_empty(){
        return this->_head==NULL;
    }

    T& operator[](int i){
        node<T>* t=this->_head;
        for(int j=0;j<i;j++){
            t=t->next;
        }
        return t->get();
    }
    T operator[](int i)const{
        node<T>* t=this->_head;
        for(int j=0;j<i;j++){
            t=t->next;
        }
        return t->data;
    }
};

template<typename T>
std::ostream& operator<<(std::ostream&out, list<T>& ls){
    node<T> *t=ls.head();
    for(int i=0;i<ls.size();i++){
        if(i!=ls.size()-1) out<<t->data<<" -> ";
        else out<<t->data;
        t=t->next;
    }
    return out;
}