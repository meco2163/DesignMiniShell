/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:45:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/01/03 05:36:45 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static int	is_ws(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

static int	is_op(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static int	handle_quote(const char *s, int *pos, int *q, int *n)
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
	(*n)++;
	(*pos)++;
	return (0);
}

int	count_len(const char *s, int pos, int *end)
{
	int	q;
	int	n;

	q = 0;
	n = 0;
	while (s[pos])
	{
		if (q == 0 && (is_ws(s[pos]) || is_op(s[pos])))
			break ;
		handle_quote(s, &pos, &q, &n);
	}
	if (q != 0)
		return (fprintf(stderr, "*count_len: unclosed quote*\n"), -1);
	*end = pos;
	return (n);
}
