/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:10:24 by mekaplan          #+#    #+#             */
/*   Updated: 2026/01/03 05:36:45 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stddef.h>
#include <stdio.h>

static int	is_ws(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

static int	handle_token(t_tok **lst, const char *s, int *i)
{
	int	ret;

	if (read_op(lst, s, i))
	{
		if (!*lst)
			return (fprintf(stderr, "*handle_token: read_op returned NULL*\n"), 0);
		return (1);
	}
	ret = read_word(lst, s, i);
	if (ret == 1)
		return (1);
	return (fprintf(stderr, "*handle_token: read_word failed*\n"), 0);
}

t_tok	*tokenize(const char *s)
{
	t_tok	*lst;
	t_tok	*eof;
	int		i;

	lst = NULL;
	i = 0;
	while (s && s[i])
	{
		if (is_ws(s[i]))
		{
			i++;
			continue ;
		}
		if (!handle_token(&lst, s, &i))
			return (tok_clear(&lst), fprintf(stderr, "*tokenize: handle_token failed*\n"), NULL);
	}
	eof = tok_new(T_EOF, NULL);
	if (!eof)
		return (tok_clear(&lst), fprintf(stderr, "*tokenize: tok_new EOF failed*\n"), NULL);
	tok_add_back(&lst, eof);
	return (lst);
}
