#include "../h/ft_ping.h"

void free_li() {
    t_linked_list *tmp;

    while (list.li) {
        tmp = list.li;
        list.li = list.li->next;
        free(tmp);
    }
    list.li = NULL;
}

static t_linked_list *ptr_last_node() {
    t_linked_list *tmp = list.li;
    if (!tmp)
        return NULL;
    while (tmp->next)
        tmp = tmp->next;
    return tmp;
}

void add_end(float new)
{
    t_linked_list *new_node = malloc(sizeof(t_linked_list));
    if (!new_node)
        error_and_exit(RED "[ERROR]" RESET "Allocation failed for the linked list...\n");
    new_node->next = NULL;
    new_node->nbr = new;
    if (!list.li)
	{
        list.li = new_node;
    }
	else
	{
        t_linked_list *last = ptr_last_node();
        if (last)
		{
            last->next = new_node;
        }
    }
}
