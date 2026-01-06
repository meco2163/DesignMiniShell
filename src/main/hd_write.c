/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:36:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/01/03 05:36:45 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "signals.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int	hd_child_write(int fd, const char *delim)
{
	char	*line;
	char	*d;

	d = norm_delim(delim);
	if (!d)
		return (fprintf(stderr, "*hd_child_write: norm_delim failed*\n"), 1);
	sig_init_heredoc();
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (strcmp(line, d) == 0)
			break ;
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	free(d);
	return (0);
}
