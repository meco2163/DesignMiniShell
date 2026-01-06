/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:10:56 by mekaplan          #+#    #+#             */
/*   Updated: 2026/01/03 05:21:15 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include <stdlib.h>

static void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

static void	free_redirs(t_redir *r)
{
	t_redir	*next;

	while (r)
	{
		next = r->next;
		free(r->target);
		free(r);
		r = next;
	}
}

void	cmd_clear(t_cmd **cmds)
{
	t_cmd	*next;

	if (!cmds)
		return ;
	while (*cmds)
	{
		next = (*cmds)->next;
		free_argv((*cmds)->argv);
		free_redirs((*cmds)->redirs);
		free(*cmds);
		*cmds = next;
	}
}
