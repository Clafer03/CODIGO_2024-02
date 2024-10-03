#include<iostream>

using namespace std;

struct Node{
    int data;
    Node * next;
    Node * prev;

    Node(int x){
        data = x;
        next=NULL;
        prev=NULL;
    }
};

void insertAtBeginning(Node*& head, int x){
    Node* newNode = new Node(x);

    if(head == nullptr){
        head = newNode;
        return;
    }

    newNode->next = head;
    head->prev = newNode;
    head = newNode;
}

void insertAtEnd(Node*& head, int x){
    Node* newNode = new Node(x);

    if(head == nullptr){
        head = newNode;
        return;
    }

    Node* temp = head;
    while(temp->next != nullptr){
        temp = temp->next;
    }

    temp->next = newNode;
    temp->prev = temp;
}

void printListForward(Node* head) //adelante hacia atras
{
    Node* temp = head;
    cout << "List: ";
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}


Node* rotate(Node* head, int k){
    
    Node* temp = head;
    int length = 1;

    //Si la lista está vacía o no hay rotación, retorna la lista original
    if(head == nullptr || k == 0){
        return head;
    }

    while(temp->next){
        temp = temp->next;
        length++;
    }

    temp->next = head; // Conectar el último nodo con la cabeza para hacerla circular

    k = k%length;
    if(k==0){ // Si k es 0, no se necesita rotación
        temp->next = nullptr;
        return head;
    }

    // Encontrar el nuevo final de la lista después de k rotaciones
    int steps_new_head = length + k;
    Node* new_tail = head;

    for(int i = 0; i < steps_new_head-1; i++){
        new_tail = new_tail->next;
    }

    Node* new_head = new_tail->next;
    new_tail->next = nullptr; // Romper la lista circular

    return new_head;
}

int main(){

    int k =5;
    // cout << "-\n";
    // cin >> n;
    Node* head = nullptr;
    for(int i = 0; i < 7; i++){
        insertAtEnd(head, i+2);
    }

    printListForward(head);
    Node* new_head = rotate(head, k);
    cout << "Head: " << new_head->data << "\n";
    printListForward(new_head);
};

// reporte
// q postes diarios

// ejecucion de obra 3 veces x sem
// revision avance 2 veces x sem
// sustentar

