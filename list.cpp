#include "list.hpp"

// Constructors/Assignment Operators
template<typename T>
List<T>::List():head(NULL),tail(NULL){}

template<typename T>
List<T>::List(List<T> const& o):head(NULL),tail(NULL){
    Node<T> * cur = o.head;
    for(int i = 0; i < o.size(); i++){
        this->push_back(cur->val);
        cur = cur->next;
    }
}


template<typename T>
List<T>& List<T>::operator=(List<T> const& o){
    if(this!=&o){
        clear();
        Node<T> * cur = o.head;
        for(int i = 0; i < o.size(); i++){
            this->push_back(cur->val);
            cur = cur->next;
        }
    }
    return *this;
}


// Destructor
template<typename T>
List<T>::~List(){
    clear();
}

// Accessors
template<typename T>
bool List<T>::empty() const{
    if(size() == 0){
        return true;
    }
    return false;
}

template<typename T>
size_t List<T>::size() const{
    size_t count = 0;
    Node<T>* v = this->head;
    while(v!=NULL){
        v=v->next;
        ++count;
    }
    return count;
}

template<typename T>
T& List<T>::front() const{
    if(this->head == NULL){
        T random;
        return random;
    }
    return this->head->val;
}

template<typename T>
T& List<T>::back() const{
    if(this->tail == NULL){
        T random;
        return random;
    }
    return this->tail->val;
}

template<typename T>
T& List<T>::at(size_t index) const{
    Node<T>* v = this->head;
    while(index>0){
        v = v->next;
        --index;
    }
    return v->val;
}

// Mutators
template<typename T>
void List<T>::clear(){
    while(this->head != NULL){
        pop_front();
    }
}

template<typename T>
void List<T>::insert(size_t index, T const& value){
    if(index > size()){
        return;
    }else if(index == 0){
        this->push_front(value);
    }else if(index == size()){
        this->push_back(value);
    }else{
        Node<T>* prev = this->head;
        --index;
        while(index>0){
            prev = prev->next;
            --index;
        }
        prev->next = new Node<T>(value,prev->next);
        if(prev == this->tail)
            this->tail->next = prev->next;
    }
}

template<typename T>
void List<T>::pop_front(){
    if(empty()){
        return;
    }else if(this->head->next == NULL){
        delete this->head;
        this->head = this->tail = NULL;
    }else{
        Node<T>* const temp = this->head;
        this->head = this->head->next;
        temp->next = NULL;
        delete temp;
    }
}

template<typename T>
void List<T>::push_front(T const& value){
    if(empty()){
        this->head = new Node<T>(value,NULL);
    }else{
        Node<T> * temp = this->head;
        this->head = new Node<T>(value,temp);
    }
    if(this->tail == NULL) this->tail = this->head;
}

template<typename T>
void List<T>::pop_back(){
    if(empty()){
        return;
    }else if(this->head->next == NULL){
        delete this->head;
        this->head = this->tail = NULL;
    }else{
        Node<T>* newTail = this->head;
        while(newTail->next != this->tail){
            newTail = newTail->next;
        }
        newTail->next = NULL;
        delete this->tail;
        this->tail = newTail;
    }
}

template<typename T>
void List<T>::push_back(T const& value){
    if(this->empty()){
        this->head = this->tail = new Node<T>(value,NULL);
    }else{
        this->tail->next = new Node<T>(value,NULL);
        this->tail = this->tail->next;
    }
}

template<typename T>
void List<T>::erase(size_t index){
    if(!this->empty()){
        if(index==0){
            this->pop_front();
        }else if(index == size()-1){
            this->pop_back();
        }else{
            Node<T>* tgt = this->head->next;
            Node<T>* prev = this->head;
            --index;
            while(index>0 && tgt != NULL){
                prev=tgt;
                tgt=tgt->next;
                --index;
            }
            if(tgt != NULL){
                prev->next = tgt->next;
                tgt->next = NULL;
                delete tgt;
            }
        }
    }
}

template<typename T>
void List<T>::erase(size_t index,size_t count){
    if(count>0 && !this->empty()){
        if(index==0){
            for(count>0 && !this->empty();count--;){
                this->pop_front();
            }
        }else if(index + count >= size()){
            while(!this->empty() && count-- && size() - 1 >= index){
                this->pop_back();
            }
        }else{
            Node<T>* prev = this->head;
            Node<T>* tgt = this->head->next;
            --index;
            while(index>0 && tgt != NULL){
                prev=tgt;
                tgt=tgt->next;
                --index;
            }
            if(tgt != NULL){
                Node<T>* nextPrev = prev;
                Node<T>* next = tgt;
                while(count>0 && next != this->tail){
                    nextPrev = next;
                    next = next->next;
                    --count;
                }
                nextPrev->next = NULL;
                prev->next = next;
                if(next == NULL) this->tail = prev;
                delete tgt;
            }
        }
    }
}

template<typename T>
bool operator==(List<T> const& lhs, List<T> const& rhs){
    Node<T> const* lhsIter = lhs.head;
    Node<T> const* rhsIter = rhs.head;
    while(lhsIter != rhsIter && (lhsIter != NULL && rhsIter != NULL && lhsIter->val == rhsIter->val)){
        lhsIter = lhsIter->next;
        rhsIter = rhsIter->next;
    }
    return (lhsIter == NULL && rhsIter == NULL);
}

template class List<int>;
template bool operator==(List<int> const& lhs, List<int> const& rhs);