/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_heredocs_one_cmd.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:10:44 by mekaplan          #+#    #+#             */
/*   Updated: 2026/01/03 05:36:45 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include <stdlib.h>
#include <stdio.h>

static int	is_heredoc(t_redir *r)
{
	return (r && r->type == R_HDOC);
}

static void	set_as_input(t_redir *r, char *path)
{
	free(r->target);
	r->type = R_IN;
	r->target = path;
}

int	prepare_heredocs_one_cmd(t_shell *sh, t_cmd *c, int *n)
{
	t_redir	*r;
	char	*path;
	pid_t	pid;

	r = c->redirs;
	while (r)
	{
		if (is_heredoc(r))
		{
			path = hd_path((*n)++);
			if (!path)
				return (fprintf(stderr, "*prepare_heredocs_one_cmd: hd_path failed*\n"), 1);
			pid = hd_run_one(path, r->target);
			if (pid < 0)
				return (free(path), fprintf(stderr, "*prepare_heredocs_one_cmd: hd_run_one failed*\n"), 1);
			if (hd_wait_set(sh, pid) != 0)
				return (free(path), fprintf(stderr, "*prepare_heredocs_one_cmd: hd_wait_set failed*\n"), 1);
			set_as_input(r, path);
		}
		r = r->next;
	}
	return (0);
}
