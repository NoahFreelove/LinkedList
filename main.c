// ReSharper disable CppJoinDeclarationAndAssignment
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define null NULL
typedef struct node node;

struct node{
    char* val;
    node* next;
};

node* create(char* val) {
    node* ll = malloc(sizeof(node));
    if (ll->val == NULL) {
        free(ll);
        ll = NULL;
        return NULL;
    }
    ll->next = NULL;
    ll->val = val;
    return ll;
}

char* get_last(const node* base) {
    const node* curr = base;

    while (curr->next != NULL) {
        curr = curr->next;
    }
    if (curr == base) {
        return base->val;
    }
    return curr->val;
}

node* get_node_at(node* base, const int index) {
    if(index<0)
        return NULL;

    node* curr = base;
    int i = 0;

    while (curr->next != NULL && i < index) {
        curr = curr->next;
        i++;
    }
    if(i < index) {
        return NULL;
    }
    return curr;
}

int delete_node_at(node* base, const int index) {
    node* before;
    node* target;
    node* after;
    if(index == 0) {
        before = base;
    }else {
        before = get_node_at(base,index-1);
    }
    if(before == NULL)
        return 1;
    if(before->next == null)
        return 1;

    target = before->next;
    if(target->next != NULL) {
        after = target->next;
        before->next = after;
        target->next = NULL;
    }
    else {
        before->next = NULL;
    }

    return 0;
}

int determine_length(node* base) {
    int increment = 0;
    node* curr = base;
    while (curr->next != null) {
        curr = curr->next;
        increment++;
    }
    return increment;
}

int index_of(node* base, node* target) {
    node* curr = base;
    int i = 0;
    if(base == target) {
        return 0;
    }
    if(base->next == NULL || target == NULL)
        return -1;


    while (curr->next != null && curr != target) {
        curr = curr->next;
        i++;
    }
    if(curr == target)
        return i;

    return -1;
}
node* end(node* base) {
    node* end = base;
    while (end->next != null) {
        end = end->next;
    }
    return end;
}

int insert(node* base, node* target, int index) {
    node* curr = base;
    int i = 0;
    if(target == NULL) // invalid input
        return -1;

    while (curr->next != null && i < index-1) {
        curr = curr->next;
        i++;
    }
    if(i != (index-1)) // invalid index
        return -1;
    node* after = curr->next;
    curr->next = target;
    end(target)->next = after;
    return 0;

}

/**
 * \brief Converts a stack string into a heap one
 * \param stack_str input char to convert to move to the heap
 * \return pointer to heap address;
 */
char* alloc_str(const char* stack_str) {
    const int len = strlen(stack_str);
    char *heap_str = malloc(len + 1);
    strcpy(heap_str, stack_str);
    return heap_str;
}

void free_node(node* input) {
    if (input != NULL) {
        free(input->val);
        input->val = NULL;
        free(input);
        input = NULL;
    }
}

int main()
{
    node* base = create(alloc_str("base\n\0"));
    node* one = create(alloc_str("One\n\0"));
    node* two = create(alloc_str("Two\n\0"));
    node* three = create(alloc_str("Three\n\0"));
    node* four = create(alloc_str("Four\n\0"));
    base->next = one;
    one->next = two;
    three->next = four;

    insert(base,three,3);
    node* node = get_node_at(base, 4);
    if(node == null)
        return 1;
    printf(node->val);

    free_node(base);
    free_node(one);
    free_node(two);
    free_node(four);
    return 0;
}
