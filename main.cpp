#include <iostream>

using namespace std;

struct QueueNode {
    QueueNode* prevNode;
    QueueNode* nextNode;
    int value;
};

void enqueue(int);
void dequeue();
int get_size();
void printQueueValues();
void clean();

QueueNode*head = nullptr;

int main(){
    enqueue(5);
    enqueue(6);
    enqueue(7);
    printQueueValues();
    cout<<"Size: "<<get_size()<<endl;
    cout<<head;
    return 0;
}

void enqueue(int value){
    QueueNode* queue = new QueueNode;
    
    if(!head){
        queue->nextNode=nullptr;
        queue->prevNode=nullptr;
        queue->value=value;
        head = queue;
        return;
    }
    
    queue->nextNode=head;
    queue->prevNode=nullptr;
    queue->value=value;
    head->prevNode=queue;
    
    head = queue;
    return;
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

int get_size(){
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

void printQueueValues(){
    if(!head){
        cout<<"Queue is empty"<<endl;
        return;
    }
    
    int counter = 1;
    QueueNode * temp = head;
    
    cout<<"QUEUE: "<<endl;
    while (temp->nextNode) {
        cout<<temp->value<<"\t";
        counter++;
        temp = temp->nextNode;
    }
    cout<<temp->value<<"\t";
    cout<<endl;
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
