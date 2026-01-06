/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:11:04 by mekaplan          #+#    #+#             */
/*   Updated: 2026/01/03 05:39:29 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>
#include <stddef.h>

int	syntax_check(t_tok *lst)
{
	t_tok	*prev;

	prev = NULL;
	while (lst && lst->type != T_EOF)
	{
		if (lst->type == T_PIPE)
		{
			if (!prev || prev->type == T_PIPE)
				return (fprintf(stderr, "*syntax_check: invalid PIPE placement*\n"), 0);
			if (!lst->next || lst->next->type == T_EOF
				|| lst->next->type == T_PIPE)
				return (fprintf(stderr, "*syntax_check: PIPE at end or double PIPE*\n"), 0);
		}
		if (is_redir(lst->type))
		{
			if (!lst->next || lst->next->type != T_WORD)
				return (fprintf(stderr, "*syntax_check: redir needs WORD*\n"), 0);
		}
		prev = lst;
		lst = lst->next;
	}
	return (1);
}
