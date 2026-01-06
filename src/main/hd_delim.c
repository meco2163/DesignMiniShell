/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_delim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:35:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/01/03 05:39:29 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

static int	is_wrapped_quote(const char *s)
{
	size_t	n;

	n = strlen(s);
	if (n < 2)
		return (fprintf(stderr, "*is_wrapped_quote: len < 2*\n"), 0);
	if ((s[0] == '\'' && s[n - 1] == '\'') || (s[0] == '"' && s[n - 1] == '"'))
		return (1);
	return (0);
}

char	*norm_delim(const char *s)
{
	size_t	i;
	size_t	j;
	size_t	n;
	char	*out;

	if (!s)
		return (fprintf(stderr, "*norm_delim: input NULL*\n"), NULL);
	n = strlen(s);
	i = 0;
	while (i < n && isspace((unsigned char)s[i]))
		i++;
	j = n;
	while (j > i && isspace((unsigned char)s[j - 1]))
		j--;
	out = (char *)malloc(j - i + 1);
	if (!out)
		return (fprintf(stderr, "*norm_delim: malloc failed*\n"), NULL);
	memcpy(out, s + i, j - i);
	out[j - i] = '\0';
	if (is_wrapped_quote(out))
	{
		memmove(out, out + 1, strlen(out));
		out[strlen(out) - 1] = '\0';
	}
	return (out);
}
