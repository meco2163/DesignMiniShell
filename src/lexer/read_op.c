/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:10:36 by mekaplan          #+#    #+#             */
/*   Updated: 2026/01/03 05:36:45 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stddef.h>
#include <stdio.h>

static int	add_op(t_tok **lst, t_ttype type)
{
	t_tok	*new;

	new = tok_new(type, NULL);
	if (!new)
	{
		tok_clear(lst);
		return (0);
	}
	tok_add_back(lst, new);
	return (1);
}

int	read_op(t_tok **lst, const char *s, int *i)
{
	if (s[*i] == '<' && s[*i + 1] == '<')
		return ((*i += 2), add_op(lst, T_HEREDOC));
	if (s[*i] == '>' && s[*i + 1] == '>')
		return ((*i += 2), add_op(lst, T_REDIR_APPEND));
	if (s[*i] == '|')
		return ((*i += 1), add_op(lst, T_PIPE));
	if (s[*i] == '<')
		return ((*i += 1), add_op(lst, T_REDIR_IN));
	if (s[*i] == '>')
		return ((*i += 1), add_op(lst, T_REDIR_OUT));
	return (0);
}
