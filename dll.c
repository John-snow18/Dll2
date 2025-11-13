#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *prev, *next;
};

struct Node *head = NULL;

struct Node* createNode(int val) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

void insertBegin(int val) {
    struct Node *newNode = createNode(val);
    if (head != NULL) {
        newNode->next = head;
        head->prev = newNode;
    }
    head = newNode;
}

void insertEnd(int val) {
    struct Node *newNode = createNode(val);
    if (head == NULL) { head = newNode; return; }
    struct Node *temp = head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = newNode;
    newNode->prev = temp;
}

void insertPos(int val, int pos) {
    struct Node *newNode = createNode(val);
    if (pos == 1) { insertBegin(val); return; }
    struct Node *temp = head;
    for (int i = 1; temp != NULL && i < pos - 1; i++) temp = temp->next;
    if (temp == NULL) return;
    newNode->next = temp->next;
    if (temp->next != NULL) temp->next->prev = newNode;
    temp->next = newNode;
    newNode->prev = temp;
}

void deleteBegin() {
    if (head == NULL) return;
    struct Node *temp = head;
    head = head->next;
    if (head != NULL) head->prev = NULL;
    free(temp);
}

void deleteEnd() {
    if (head == NULL) return;
    struct Node *temp = head;
    while (temp->next != NULL) temp = temp->next;
    if (temp->prev != NULL) temp->prev->next = NULL;
    else head = NULL;
    free(temp);
}

void deletePos(int pos) {
    if (head == NULL) return;
    struct Node *temp = head;
    for (int i = 1; temp != NULL && i < pos; i++) temp = temp->next;
    if (temp == NULL) return;
    if (temp->prev != NULL) temp->prev->next = temp->next;
    else head = temp->next;
    if (temp->next != NULL) temp->next->prev = temp->prev;
    free(temp);
}

void search(int key) {
    struct Node *temp = head;
    int pos = 1;
    while (temp != NULL) {
        if (temp->data == key) { 
            printf("Found %d at position %d\n", key, pos); 
            return; 
        }
        temp = temp->next; pos++;
    }
    printf("Element not found\n");
}

void display() {
    struct Node *temp = head;
    if (temp == NULL) { printf("List Empty\n"); return; }
    printf("Forward: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    int ch, val, pos;
    while (1) {
        printf("\n1.InsertBegin 2.InsertEnd 3.InsertPos\n4.DeleteBegin 5.DeleteEnd 6.DeletePos\n7.Search 8.Display 9.Exit\nEnter choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: printf("Enter value: "); scanf("%d", &val); insertBegin(val); break;
            case 2: printf("Enter value: "); scanf("%d", &val); insertEnd(val); break;
            case 3: printf("Enter value & pos: "); scanf("%d%d", &val, &pos); insertPos(val, pos); break;
            case 4: deleteBegin(); break;
            case 5: deleteEnd(); break;
            case 6: printf("Enter pos: "); scanf("%d", &pos); deletePos(pos); break;
            case 7: printf("Enter element: "); scanf("%d", &val); search(val); break;
            case 8: display(); break;
            case 9: exit(0);
            default: printf("Invalid choice\n");
        }
    }
    return 0;
}