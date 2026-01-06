/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:10:32 by mekaplan          #+#    #+#             */
/*   Updated: 2026/01/03 05:41:48 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>
#include <stdio.h>

static int	skip_quotes(const char *s, int *pos, int *q)
{
	if (*q == 0 && (s[*pos] == '\'' || s[*pos] == '"'))
	{
		*q = s[*pos];
		(*pos)++;
		return (1);
	}
	if (*q != 0 && s[*pos] == *q)
	{
		*q = 0;
		(*pos)++;
		return (1);
	}
	return (0);
}

static void	fill_word(char *out, const char *s, int start, int end)
{
	int	q;
	int	k;

	q = 0;
	k = 0;
	while (start < end)
	{
		if (skip_quotes(s, &start, &q))
			continue ;
		out[k] = s[start];
		k++;
		start++;
	}
	out[k] = '\0';
}

int	read_word(t_tok **lst, const char *s, int *i)
{
	int		end;
	int		len;
	char	*val;
	t_tok	*node;

	end = *i;
	len = count_len(s, *i, &end);
	if (len <= 0)
		return (len);
	val = malloc((size_t)len + 1);
	if (!val)
		return (fprintf(stderr, "*read_word: malloc failed*\n"), -1);
	fill_word(val, s, *i, end);
	node = tok_new(T_WORD, val);
	if (!node)
		return (free(val), fprintf(stderr, "*read_word: tok_new failed*\n"), -1);
	tok_add_back(lst, node);
	*i = end;
	return (1);
}
