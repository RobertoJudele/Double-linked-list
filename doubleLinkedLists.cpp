#include <iostream>
using namespace std;
class node{
    int value;
    node* next;
    node* prev;
public:
    friend class doubleLinkedList;
    node(){
        value=NULL;
        next= nullptr;
        prev= nullptr;
    }
    node(int v){
        value=v;
        next= nullptr;
        prev= nullptr;
    }
    node(int v, node* nextptr, node* prevptr){
        value=v;
        next= nextptr;
        prev= prevptr;
    }

    //destructorul este lasat gol deoarece nodul este sters in cadrul destructorului clasei
    //doubleLinkedList

    ~node(){}

    //in opinia mea nu are sens sa facem setteri si getteri pentru pointeri deoarece acestia sunt modificati in cadrul
    //clasei double linked list si nu am avea de ce sa i modificam manual

    //nu are rost sa facem un constructor de copiere deoarece nu avem cazuri in care am avea nevoie
    //iar daca este nevoie avem un constructor parametrizat si ii putem da (note.getValue)

    int getValue(){
        return value;
    }
    void setValue(int val){
        value=val;
    }

    node*  operator=(const node& other) {
        node* toReturn=new node(other.value,other.next,other.prev);
        return toReturn;
    }
};
class doubleLinkedList{
    node* head= new node();
    node* tail= new node();
public:
    doubleLinkedList(){
        tail->prev=head;
        head->next=tail;
    }
    doubleLinkedList(int value){
        while(value){
            int aux;
            cin>>aux;
            addAtEnd(aux);
            value--;
        }
    }
    doubleLinkedList(doubleLinkedList const &dll){
        node* temp=dll.head;
        while (temp){
            this->addAtEnd(temp->value);
            temp=temp->next;
        }
    }
    ~doubleLinkedList() {
        while (head != nullptr) {
            node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void addAtPos(int val,int pos){
        node *newNode = new node(val);
        node* temp=tail;
        if (head->value == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            node *temp = head;
            int count = 1;
            while (count < pos-1) {
                temp = temp->next;
                count++;
            }
            newNode->next = temp->next;
            temp->next->prev = newNode;
            temp->next = newNode;
            newNode->prev = temp;
        }
    }
    void addAtEnd(int val) {
        node* newNode = new node(val);
        if (head->value == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    void addAtStart(int val){
        node* newNode=new node(val);
        if(head->value == NULL){
            head=newNode;
            tail= newNode;
        }else{
            newNode->next=head;
            head->prev=newNode;
            head=newNode;
        }
    }
    void updatePos(int val, int pos){
        node* temp=head;
        int count=1;
        while(count<pos){
            temp=temp->next;
            count++;
        }
        temp->value=val;
    }
    void printForward(){
        node* temp=head;
        while(temp != nullptr){
            cout<<temp->value<<"<->";
            temp=temp->next;
        }cout<<"end";
        cout<<endl;
    }
    void deleteAtPos(int pos){
        node* temp = head;
        for(int i=1;i<pos;i++){
            temp=temp->next;
        }
        node* prev=temp->prev;
        node* next=temp->next;
        prev->next=next;
        next->prev=prev;
        delete temp;
    }
    void nLists(int n){
        while (n){
            int aux;
            cout<<"Cate elemente ati dori sa aiba lista?"<<endl;
            cin>>aux;
            doubleLinkedList dll(aux);
            dll.printForward();
            cout<<endl;
            n--;
        }
        //Asta am inteles eu prin cerinta 5, nu stiu sigur daca este ce ati vrut dumneavoastra
    }
    void clearList() {
        while (head->next != tail) {
            node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    friend ostream& operator<<(ostream& os, const doubleLinkedList dll){
        node* temp=dll.head;
        while(temp){
            os<<temp->value<<"<->";
            temp=temp->next;
        }os<<"END"<<endl;

        temp=dll.tail;
        while(temp!=dll.head){
            os<<temp->value<<"<->";
            temp=temp->prev;
        }
        os<<temp->value<<"<->";
        os<<"END";
        return os;
    }
    friend istream& operator>>(istream& is, doubleLinkedList& dll) {
        int val;
        dll.clearList();
        if (is >> val) {
            dll.addAtEnd(val);
        }
        return is;
    }
    friend doubleLinkedList operator+(const doubleLinkedList& dll1, const doubleLinkedList& dll2) {
        doubleLinkedList result;

        for (node* current = dll1.head; current != nullptr; current = current->next) {
            result.addAtEnd(current->value);
        }

        for (node* current = dll2.head; current != nullptr ; current = current->next) {
            result.addAtEnd(current->value);
        }

        return result;
    }

    friend doubleLinkedList operator-(doubleLinkedList& dll1, doubleLinkedList& dll2){
        doubleLinkedList result;
        node* current1=dll1.head;
        node* current2=dll2.head;
        while (current1!=dll1.tail && current2!=dll2.tail && current1->value==current2->value){
            current1=current1->next;
            current2=current2->next;
        }
        while (current1!= nullptr){
            result.addAtEnd(current1->value);
            current1=current1->next;
        }
        return result;
    }
    doubleLinkedList& operator=(const doubleLinkedList& dll) {
        node* temp= dll.head;
        while (temp){
            this->addAtEnd(temp->value);
            temp=temp->next;
        }
        return *this;
    }
};
class testDoubleLinkedList{
public:
    void testConstructorCopiereNodeDefault(){
        node n(3);
        node n1(n);
        cout<<n.getValue()<<endl;
    }
    void testSetGetValueNode(){
        node n(3);
        n.setValue(4);
        cout<<n.getValue()<<endl;
    }
    void testConstructor(){
        doubleLinkedList dll;
        dll.printForward();
    }
    void testAddAtEnd(){
        doubleLinkedList dll;
        dll.addAtEnd(1);
        dll.addAtEnd(4);
        dll.addAtEnd(6);
        dll.printForward();
    }
    void testAddAtStart(){
        doubleLinkedList dll;
        dll.addAtStart(1);
        dll.addAtStart(2);
        dll.addAtStart(3);
        dll.printForward();
    }
    void testAddAtPos(){
        doubleLinkedList dll;
        dll.addAtEnd(1);
        dll.addAtEnd(2);
        dll.addAtEnd(3);
        dll.addAtPos(3,2);
        dll.printForward();
    }
    void testUpdateAtPos(){
        doubleLinkedList dll;
        dll.addAtEnd(1);
        dll.addAtEnd(2);
        dll.addAtEnd(3);
        dll.updatePos(3,2);
        dll.printForward();
    }
    void deleteAtPos(){
        doubleLinkedList dll;
        dll.addAtEnd(1);
        dll.addAtEnd(2);
        dll.addAtEnd(3);
        dll.deleteAtPos(2);
        dll.printForward();
    }
    void nLists(){
        doubleLinkedList dll;
        cout<<"Cate liste ati vrea sa creeati si sa afisati?";
        int aux;
        cin>>aux;
        dll.nLists(aux);
    }
    void testSupraIncarcare1(){
        doubleLinkedList dll;

        dll.addAtEnd(1);
        dll.addAtEnd(2);
        cout<<"Introduceti valorile ce vreti sa le adaugati";
        cin>>dll>>dll>>dll;
        dll.printForward();
    }
    void testSupraIncarcare2(){
        doubleLinkedList dll;
        doubleLinkedList dll1;
        dll.addAtEnd(1);
        dll.addAtEnd(2);
        dll.addAtEnd(3);
        dll.addAtEnd(7);
        dll.addAtEnd(5);
        dll.addAtEnd(6);

        dll1.addAtEnd(1);
        dll1.addAtEnd(2);
        dll1.addAtEnd(3);
        dll1.addAtEnd(4);
        dll1.addAtEnd(7);
        dll1.addAtEnd(5);
        dll1.addAtEnd(6);

        //operatorul '=' din cele testate de mine creeaza o lista noua cu noduri si pointeri noi
        // asa ca nu-i vad rostul supraincarcarii acestuia

        doubleLinkedList dll3=dll-dll1;

        dll3.printForward();
    }
    void testSupraIncarcare3(){
        doubleLinkedList dll;
        dll.addAtEnd(1);
        dll.addAtEnd(2);
        dll.addAtEnd(3);
        doubleLinkedList dll1;
        dll1.addAtEnd(4);
        dll1.addAtEnd(5);
        dll1.addAtEnd(6);
        doubleLinkedList dll2(dll+dll1);
        dll2.printForward();
    }
    void testSupraIncarcare4(){
        doubleLinkedList dll;
        dll.addAtEnd(1);
        dll.addAtEnd(2);
        dll.addAtEnd(3);
        cout<<dll<<endl;
    }
    void testSupraIncarcare5(){
        doubleLinkedList dll;
        dll.addAtEnd(1);
        dll.addAtEnd(13);
        dll.addAtEnd(21);
        dll.addAtEnd(16);
        doubleLinkedList dll1;
        dll1=dll;
        dll1.printForward();
    }
};
int main() {
    testDoubleLinkedList test;
    test.testSetGetValueNode();
    test.testConstructorCopiereNodeDefault();
    test.testConstructor();
    test.testAddAtEnd();
    test.testAddAtStart();
    test.testAddAtPos();
    test.testUpdateAtPos();
    test.deleteAtPos();
    test.nLists();
    //supraincarcarea operatorului >>
    test.testSupraIncarcare1();
    //supraincarcarea operatorului -
    test.testSupraIncarcare2();
    //supraincarcarea operatorului +
    test.testSupraIncarcare3();
    //supraincarcarea operatorului <<
    test.testSupraIncarcare4();
    //supraincarcarea operatorului =
    test.testSupraIncarcare5();
//    doubleLinkedList dll;
//    dll.nLists(3);
    return 0;
}
