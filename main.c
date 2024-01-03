#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void print_list(node* base) {
    node* curr = base;
    while (curr != NULL) {
        printf(curr->val);
        curr = curr->next;
    }
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
    if(before->next == NULL)
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
    while (curr->next != NULL) {
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


    while (curr->next != NULL && curr != target) {
        curr = curr->next;
        i++;
    }
    if(curr == target)
        return i;

    return -1;
}

node* end(node* base) {
    node* end = base;
    while (end->next != NULL) {
        end = end->next;
    }
    return end;
}

void make_swap(node* base, node* target) {
    node* tmp = base->next;
    base->next = target;
    end(target)->next = tmp;
}

int insert(node* base, node* target, int index) {
    node* curr = base;
    int i = 0;

    if(index == 0) {
        make_swap(base,target);
        return 0;
    }

    if(target == NULL) // invalid input
        return -1;

    while (curr->next != NULL && i < index-1) {
        curr = curr->next;
        i++;
    }
    if(i != (index-1)) // invalid index
        return -1;
    // Because the target could have attached nodes, we want to make sure we attach the node after curr
    // to the very end of the inserted node
    make_swap(curr,target);
    return 0;
}

int main()
{
    node* base = create(alloc_str("base\n\0")); // index 0
    node* one = create(alloc_str("One\n\0")); // index 1
    node* two = create(alloc_str("Two\n\0")); // etc.
    node* three = create(alloc_str("Three\n\0"));
    node* four = create(alloc_str("Four\n\0"));
    node* five = create(alloc_str("Five\n\0"));

    base->next = one;
    one->next = two;
    two->next = five;
    three->next = four;

    print_list(base->next);
    printf("-----\n");

    insert(base,three,3);

    print_list(base->next);

    free_node(base);
    free_node(one);
    free_node(two);
    free_node(four);

    return 0;
}
