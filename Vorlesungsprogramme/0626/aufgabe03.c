#include <stdio.h>
#include <stdint.h>

// Aufgabe 1
struct node
{
    int id;
    struct node* next;
    struct node* prev;
};

// Aufgabe 2
struct node createNode(int id)
{
    struct node elem;
    elem.id = id;
    elem.next = NULL;
    elem.prev = NULL;
    return elem;
}

// Aufgabe 3
void addNode(struct node* root, struct node* newNode)
{
    struct node* curNode = root;
    while (curNode->next != NULL)
    {
        curNode = curNode->next;
    }
    
    curNode->next = newNode;
    newNode->prev = curNode;
}

void printNode(struct node* root)
{
    do
    {
        printf("%d ", root->id);
    } while((root = root->next)!= NULL);
    printf("\n");
}

void printNode_rec(struct node* root)
{
    if (root != NULL)
    {
        printf("%d ", root->id);
        printNode_rec(root->next);
    }
}

int main()
{
    // Erstes Element der Struktur anlegen
    struct node root = createNode(0);
    struct node elem1 = createNode(5);
    struct node elem2 = createNode(3);
    struct node elem3 = createNode(8);
    addNode(&root, &elem1);
    addNode(&root, &elem2);
    addNode(&root, &elem3);
    printNode_rec(&root);
    
    return 0;
}
