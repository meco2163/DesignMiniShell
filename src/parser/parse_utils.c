/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:40:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/01/03 05:36:45 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include <stdio.h>

int	is_redir(t_ttype t)
{
	return (t == T_REDIR_IN || t == T_REDIR_OUT
		|| t == T_REDIR_APPEND || t == T_HEREDOC);
}

t_cmd	*cmd_new(void)
{
	t_cmd	*c;

	c = malloc(sizeof(*c));
	if (!c)
		return (fprintf(stderr, "*cmd_new: malloc failed*\n"), NULL);
	c->argv = NULL;
	c->redirs = NULL;
	c->next = NULL;
	return (c);
}

void	cmd_add_back(t_cmd **lst, t_cmd *n)
{
	t_cmd	*cur;

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
