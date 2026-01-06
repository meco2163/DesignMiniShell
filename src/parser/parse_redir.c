/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:10:58 by mekaplan          #+#    #+#             */
/*   Updated: 2026/01/03 05:36:45 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

static t_rtype	to_rtype(t_ttype t)
{
	if (t == T_REDIR_IN)
		return (R_IN);
	if (t == T_REDIR_OUT)
		return (R_OUT);
	if (t == T_REDIR_APPEND)
		return (R_APP);
	return (R_HDOC);
}

static void	redir_add_back(t_cmd *cur, t_redir *r)
{
	t_redir	*p;

	p = cur->redirs;
	if (!p)
		cur->redirs = r;
	else
	{
		while (p->next)
			p = p->next;
		p->next = r;
	}
}

int	parse_redir(t_cmd *cur, t_tok **lst)
{
	t_redir	*r;
	t_tok	*op;
	t_tok	*arg;

	op = *lst;
	if (!op || !op->next)
		return (fprintf(stderr, "*parse_redir: invalid token*\n"), 0);
	arg = op->next;
	if (arg->type != T_WORD)
		return (fprintf(stderr, "*parse_redir: arg not T_WORD*\n"), 0);
	r = malloc(sizeof(*r));
	if (!r)
		return (fprintf(stderr, "*parse_redir: malloc failed*\n"), 0);
	r->type = to_rtype(op->type);
	r->target = ft_strdup(arg->val);
	if (!r->target)
		return (free(r), fprintf(stderr, "*parse_redir: ft_strdup failed*\n"), 0);
	r->next = NULL;
	redir_add_back(cur, r);
	*lst = arg->next;
	return (1);
}
