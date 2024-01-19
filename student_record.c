#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int id;
    float gpa;
    struct Node *prev;
    struct Node *next;
};

void add_at_end(struct Node *head, int id, float gpa)
{
    struct Node *temp2 = (struct Node *)malloc(sizeof(struct Node));
    temp2->id = id;
    temp2->gpa = gpa;
    temp2->next = NULL;

    struct Node *trav = head;
    while (trav->next != NULL)
    {
        trav = trav->next;
    }
    trav->next = temp2;
    temp2->prev = trav;
}

// Rest of the functions remain the same
struct Node *deleteHead(struct Node *head)
{
    if (head == NULL)
    {
        return NULL; // If the list is already empty, return NULL
    }
    struct Node *p = head;
    head = p->next;
    if (head != NULL)
    {
        head->prev = NULL; // Update the prev pointer of the new head
    }
    free(p);
    return head; // Return the new head of the list
}

struct Node *removeDuplicates(struct Node *head, int id)
{
    if (!head)
    {
        return NULL;
    }

    struct Node *current = head;
    int firstEncounter = 0; // Flag to check the first encounter
    while (current != NULL)
    {
        if (current->id == id)
        {
            if (firstEncounter == 0)
            {
                firstEncounter = 1;
            }
            else
            {
                struct Node *temp = current;
                current->prev->next = current->next;
                if (current->next != NULL)
                {
                    current->next->prev = current->prev;
                }
                current = current->next;
                free(temp);
                continue;
            }
        }
        current = current->next;
    }
    return head;
}

struct Node *reverse(struct Node *head)
{
    struct Node *current = head;
    struct Node *temp = NULL;

    while (current != NULL)
    {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    head->next = NULL;
    if (temp != NULL)
    {
        head = temp->prev;
        // Set the next pointer of the new head to NULL
    }
    return head;
}

struct Node *shift(struct Node *head, int k)
{
    if (!head || !head->next || k == 0)
    {
        return head; // No change needed if the list is empty, has only one node, or if k is 0
    }

    struct Node *current = head;
    int length = 1;

    // Get the length of the list and the last node
    while (current->next != NULL)
    {
        current = current->next;
        length++;
    }

    // Calculate the actual shift value
    k = k % length;
    if (k == 0)
    {
        return head; // No change needed if k is a multiple of the list length
    }

    // Find the new head and the new tail
    int stepsToNewHead = length - k;
    struct Node *newTail = head;
    for (int i = 1; i < stepsToNewHead; i++)
    {
        newTail = newTail->next;
    }

    // Perform the rotation
    struct Node *newHead = newTail->next;
    newTail->next = NULL;
    newHead->prev = NULL;
    current->next = head;
    head->prev = current;

    return newHead;
}

struct Node *createSortedList(struct Node *head)
{
    if (!head || !head->next)
    {
        return head;
    }

    int swapped;
    struct Node *ptr1;
    struct Node *lptr = NULL;

    do
    {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr)
        {
            if (ptr1->gpa < ptr1->next->gpa)
            {
                float temp = ptr1->gpa;
                int t = ptr1->id;
                ptr1->gpa = ptr1->next->gpa;
                ptr1->id = ptr1->next->id;
                ptr1->next->gpa = temp;
                ptr1->next->id = t;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    return head;
}

int main()
{
    struct Node *head;
    struct Node *sorted_head;
    head = (struct Node *)malloc(sizeof(struct Node));
    sorted_head = (struct Node *)malloc(sizeof(struct Node));
    head->next = NULL;
    head->prev = NULL;
    int n, k, duplicate_id;
    scanf("%d", &n);            
    scanf("%d", &k);            
    scanf("%d", &duplicate_id); 

    // Input n records and build a doubly linked list
    for (int i = 0; i < n; i++)
    {
        int id;
        float gpa;
        scanf("%d %f", &id, &gpa);
        if (i == 0)
        {
            head->id = id;
            head->gpa = gpa;
        }
        else
        {
            add_at_end(head, id, gpa);
        }
    }

    head = deleteHead(head);
    head = removeDuplicates(head, duplicate_id);
    head = reverse(head);
    head = shift(head, k);

    // Print the doubly linked list and its reverse
    struct Node *curr = head;
    struct Node *tail = head;

    // Print the doubly linked list
    while (curr != NULL)
    {
        printf("%d,%.1f->", curr->id, curr->gpa);
        tail = curr;
        curr = curr->next;
    }
    printf("\n");

    // Print the doubly linked list in reverse order
    while (tail != NULL)
    {
        printf("%d,%.1f->", tail->id, tail->gpa);
        tail = tail->prev;
    }
    printf("\n");
    sorted_head = createSortedList(head);
    curr = sorted_head;
    tail = curr;

    // Print the sorted doubly linked list
    while (curr != NULL)
    {
        printf("%d,%.1f->", curr->id, curr->gpa);
        tail = curr;
        curr = curr->next;
    }
    printf("\n");

    // Print the sorted doubly linked list in reverse order
    while (tail != NULL)
    {
        printf("%d,%.1f->", tail->id, tail->gpa);
        tail = tail->prev;
    }
    printf("\n");

    return 0;
}