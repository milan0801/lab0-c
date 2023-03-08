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
    if (!head)
        return false;

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
    if (!head)
        return false;

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
    if (!head || list_empty(head))
        return NULL;

    element_t *del_node = list_first_entry(head, element_t, list);
    if (sp && bufsize != 0) {
        size_t val_len = strlen(del_node->value);
        if (val_len > bufsize - 1) {
            val_len = bufsize - 1;
        }
        memcpy(sp, del_node->value, val_len);
        sp[val_len] = '\0';
    }
    list_del(&del_node->list);

    return del_node;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;

    element_t *del_node = list_last_entry(head, element_t, list);
    if (sp && bufsize != 0) {
        size_t val_len = strlen(del_node->value);
        if (val_len > bufsize - 1) {
            val_len = bufsize - 1;
        }
        memcpy(sp, del_node->value, val_len);
        sp[val_len] = '\0';
    }
    list_del(&del_node->list);

    return del_node;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head || list_empty(head))
        return 0;
    struct list_head *node;
    int cnt = 0;
    list_for_each (node, head) {
        cnt++;
    }
    return cnt;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    if (!head || list_empty(head))
        return false;

    struct list_head *two_step, *one_step;
    two_step = head->next->next;
    one_step = head->next;
    while (two_step != head && two_step != head->prev) {
        one_step = one_step->next;
        two_step = two_step->next->next;
    }
    list_del(one_step);

    element_t *mid = list_entry(one_step, element_t, list);
    free(mid->value);
    free(mid);

    return true;
}

/* Delete all nodes that have duplicate string */
/* All nodes have been sorted */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    if (!head || list_empty(head))
        return false;

    if (list_is_singular(head))
        return true;

    element_t *item = NULL, *safe = NULL, *tmp;
    list_for_each_entry_safe (item, safe, head, list) {
        bool dup_flag = false;
        while (&safe->list != head && !strcmp(safe->value, item->value)) {
            dup_flag = true;
            tmp = safe;
            safe = list_entry(safe->list.next, element_t, list);
            list_del(&tmp->list);
            free(tmp->value);
            free(tmp);
        }
        if (dup_flag) {
            list_del(&item->list);
            free(item->value);
            free(item);
        }
    }
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
    if (!head || list_empty(head))
        return;

    struct list_head **cur = &head->next;

    for (; *cur != head && *cur != head->prev; cur = &(*cur)->next->next) {
        struct list_head *first = *cur, *second = (*cur)->next;
        first->next = second->next;
        second->next = first;
        second->prev = first->prev;
        first->prev = second;
        *cur = second;
    }

}

/* Reverse elements in queue */
void q_reverse(struct list_head *head)
{
    if (!head || list_empty(head))
        return;
    element_t *item = NULL;

    struct list_head *cur, *safe;
    list_for_each_safe (cur, safe, head) {
        list_move(cur, head);
    }
}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
    if (!head || list_empty(head))
        return;

    struct list_head *insert_pos = head, *cur, *safe;
    int n = q_size(head) / k;
    int cnt_n = 0, cnt = 0;
    list_for_each_safe (cur, safe, head) {
        if (cnt_n == n)
            return;
        struct list_head *tmp = cur->prev;
        list_move(cur, insert_pos);
        cnt++;
        if (cnt == k) {
            insert_pos = tmp;
            cnt = 0;
            cnt_n++;
        }
    }
}

struct list_head *mergeTwoLists(struct list_head *list1,
                                struct list_head *list2)
{
    struct list_head *head = NULL, **ptr = &head, **node;

    for (node = NULL; list1 && list2; *node = (*node)->next) {
        char *s1 = list_entry(list1, element_t, list)->value;
        char *s2 = list_entry(list2, element_t, list)->value;
        node = (strcmp(s1, s2) < 0) ? &list1 : &list2;
        *ptr = *node;
        ptr = &(*ptr)->next;
    }

    *ptr = (struct list_head *) ((uintptr_t) list1 | (uintptr_t) list2);
    return head;
}

/* Sort elements of queue in ascending order */
/* Use merge sort (non-recursive version) */
void q_sort(struct list_head *head)
{
    if (!head || list_empty(head) || list_is_singular(head))
        return;

    int top = 0;
    int listsSize = 0;
    struct list_head *stack[1000] = {NULL};
    struct list_head *lists[100000] = {NULL};
    stack[top] = head->next;
    head->prev->next = NULL;

    while (top >= 0) {
        struct list_head *left = stack[top--];

        if (left) {
            struct list_head *slow = left;
            struct list_head *fast;

            for (fast = left->next; fast && fast->next;
                 fast = fast->next->next) {
                slow = slow->next;
            }
            struct list_head *right = slow->next;
            slow->next = NULL;

            stack[++top] = left;
            stack[++top] = right;
        } else {
            lists[listsSize++] = stack[top--];
        }
    }

    while (listsSize > 1) {
        for (int i = 0, j = listsSize - 1; i < j; i++, j--)
            lists[i] = mergeTwoLists(lists[i], lists[j]);
        listsSize = (listsSize + 1) / 2;
    }
    head->next = lists[0];
    struct list_head *ptr = head;
    for (; ptr->next; ptr = ptr->next) {
        ptr->next->prev = ptr;
    }
    ptr->next = head;
    head->prev = ptr;
}

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
