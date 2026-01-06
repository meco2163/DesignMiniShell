/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:10:27 by mekaplan          #+#    #+#             */
/*   Updated: 2026/01/03 05:36:45 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include <stdlib.h>
#include <stdio.h>

t_tok	*tok_new(t_ttype type, char *val)
{
	t_tok	*t;

	t = malloc(sizeof(*t));
	if (!t)
		return (NULL);
	t->type = type;
	t->val = val;
	t->next = NULL;
	return (t);
}

void	tok_add_back(t_tok **lst, t_tok *n)
{
	t_tok	*cur;

	if (!lst || !n)
		return ;
	if (!*lst)
	{
		*lst = n;
		return ;
	}
	cur = *lst;
	while (cur->next)
		cur = cur->next;
	cur->next = n;
}

void	tok_clear(t_tok **lst)
{
	t_tok	*next;

	if (!lst)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		free((*lst)->val);
		free(*lst);
		*lst = next;
	}
}
