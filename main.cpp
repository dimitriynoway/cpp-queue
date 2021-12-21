#include <iostream>

using namespace std;

struct QueueNode {
    QueueNode* prevNode;
    QueueNode* nextNode;
    int value;
    int priority;
};

void enqueue(int, int);
void dequeue();
int getSize();
void printQueueValues();
void clean();

//Could pass every time as parametr, but did it globally for decrise code size
QueueNode*head = nullptr;

int main(){
    enqueue(5, 3);
    enqueue(7, 1);
    enqueue(6, 2);
    enqueue(8, 1);
    enqueue(7, 1);
    enqueue(6, 5);
    
    cout<<"TEST 1"<<endl;
    printQueueValues();
    cout<<"Size: "<<getSize()<<endl;
    
    cout<<"TEST 2"<<endl;
    dequeue();
    dequeue();
    dequeue();
    printQueueValues();
    cout<<"Size: "<<getSize()<<endl;
    
    cout<<"TEST 3"<<endl;
    clean();
    cout<<"Size: "<<getSize()<<endl;
    
    return 0;
}

void enqueue(int value, int priority){
    if(priority<0||priority>5){
        cout<<"Invalid priority input"<<endl;
        return;
    }
    
    QueueNode* queue = new QueueNode;
    queue->value=value;
    queue->priority=priority;
    
    if(!head){
        queue->nextNode=nullptr;
        queue->prevNode=nullptr;
        head = queue;
        return;
    }
    
    if(priority>=head->priority){
        queue->nextNode=head;
        queue->prevNode=nullptr;
        head->prevNode=queue;
        head = queue;
        return;
    }
    
    if(priority<head->priority&&!head->nextNode){
        queue->nextNode=nullptr;
        queue->prevNode=head;
        head->nextNode=queue;
        return;
    }
    
    QueueNode *next = head;
    QueueNode *prev = nullptr;
    
    while (next->priority>priority) {
        if(!next->nextNode){
            break;
        }
        next=next->nextNode;
    }

    if(!next->nextNode&&next->priority<=priority){
        prev = next->prevNode;
        prev->nextNode = queue;
        queue->nextNode = next;
        next->prevNode = queue;
        queue->prevNode = prev;
        return;
    }
    
    if(!next->nextNode){
        next->nextNode = queue;
        queue->nextNode = nullptr;
        queue->prevNode = next;
        return;
    }
    
    prev = next->prevNode;
    prev->nextNode = queue;
    next->prevNode = queue;
    queue->nextNode = next;
    queue->prevNode = prev;

}

void dequeue(){
    QueueNode* lastNode= head;
    
    if(!head){
        cout<<"Queue is empty"<<endl;
        return;
    }
    
    while (lastNode->nextNode) {
        lastNode = lastNode->nextNode;
    }
    
    QueueNode* newTail = lastNode->prevNode;
    newTail->nextNode=nullptr;
    
    cout<<"Enqueued value is: "<<lastNode->value<<endl;

    delete lastNode;
}

void printQueueValues(){
    if(!head){
        cout<<"Queue is empty"<<endl;
        return;
    }
    
    int counter = 1;
    QueueNode * temp = head;
    
    cout<<"QUEUE: "<<endl;
    while (temp->nextNode) {
        cout<<"priority: "<<temp->priority<<" value: "<<temp->value<<"\t";
        counter++;
        temp = temp->nextNode;
    }
    cout<<"priority: "<<temp->priority<<" value: "<<temp->value<<endl;
}

int getSize(){
    int counter = 1;
    
    if(!head){
        return 0;
    }
    
    QueueNode*headcopy = head;
    
    while (headcopy->nextNode) {
        counter++;
        headcopy=headcopy->nextNode;
    }
    
    return counter;
}

void clean(){
    while (head->nextNode!=NULL&&head->prevNode!=NULL) {
        head=head->nextNode;
        delete head->prevNode;
        head->prevNode=nullptr;
    }
    delete head->nextNode;
    head=nullptr;
}
