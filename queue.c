#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *queue = malloc(sizeof(struct list_head));
    if (!queue) {
        return NULL;
    }
    INIT_LIST_HEAD(queue);
    return queue;
}

/* Free all storage used by queue */
void q_free(struct list_head *l)
{
    if (!l)
        return;
    element_t *node, *safe;
    list_for_each_entry_safe (node, safe, l, list) {
        free(node->value);
        free(node);
    }
    free(l);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    element_t *node = malloc(sizeof(element_t));
    if (!node) {
        return false;
    }
    /* Allocate space for value in element_te */
    int s_len = strlen(s) + 1;
    node->value = malloc(s_len * sizeof(char));
    if (!node->value) {
        free(node);
        return false;
    }
    memcpy(node->value, s, s_len);
    list_add(&node->list, head);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    element_t *node = malloc(sizeof(element_t));
    if (!node) {
        return false;
    }
    /* Allocate space for value in element_te */
    int s_len = strlen(s) + 1;
    node->value = malloc(s_len * sizeof(char));
    if (!node->value) {
        free(node);
        return false;
    }
    memcpy(node->value, s, s_len);
    list_add_tail(&node->list, head);
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    element_t *del_node = list_first_entry(head, element_t, list);
    size_t val_len = strlen(del_node->value);
    if (val_len > bufsize - 1) {
        val_len = bufsize - 1;
    }
    memcpy(sp, del_node->value, val_len);
    sp[val_len] = '\0';
    list_del(&del_node->list);

    return del_node;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    element_t *del_node = list_last_entry(head, element_t, list);
    size_t val_len = strlen(del_node->value);
    if (val_len > bufsize - 1) {
        val_len = bufsize - 1;
    }
    memcpy(sp, del_node->value, val_len);
    sp[val_len] = '\0';
    list_del(&del_node->list);

    return del_node;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    return -1;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head) {}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending order */
void q_sort(struct list_head *head) {}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending order */
int q_merge(struct list_head *head)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
