/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:10:39 by mekaplan          #+#    #+#             */
/*   Updated: 2026/01/03 05:39:29 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "heredoc.h"
#include "signals.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

char	*hd_path(int n)
{
	char	buf[128];
	int		pid;

	pid = (int)getpid();
	if (snprintf(buf, sizeof(buf), "/tmp/msh_hd_%d_%d", pid, n) <= 0)
		return (fprintf(stderr, "*hd_path: snprintf failed*\n"), NULL);
	return (ft_strdup(buf));
}

pid_t	hd_run_one(const char *path, const char *delim)
{
	int		fd;
	pid_t	pid;
	int		rc;

	fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0600);
	if (fd < 0)
		return (perror("heredoc open"), fprintf(stderr, "*hd_run_one: open failed*\n"), (pid_t)(-1));
	pid = fork();
	if (pid < 0)
	{
		close(fd);
		return (perror("heredoc fork"), fprintf(stderr, "*hd_run_one: fork failed*\n"), (pid_t)(-1));
	}
	if (pid == 0)
	{
		rc = hd_child_write(fd, delim);
		close(fd);
		_exit(rc);
	}
	close(fd);
	return (pid);
}

int	hd_wait_set(t_shell *sh, pid_t pid)
{
	int	st;

	sig_init_wait_parent();
	if (waitpid(pid, &st, 0) < 0)
	{
		perror("heredoc waitpid");
		sig_init_prompt();
		sh_set_status(sh, 1);
		return (fprintf(stderr, "*hd_wait_set: waitpid failed*\n"), 1);
	}
	sig_init_prompt();
	if (WIFSIGNALED(st) && WTERMSIG(st) == SIGINT)
	{
		sh_set_status(sh, 130);
		return (fprintf(stderr, "*hd_wait_set: SIGINT received*\n"), 1);
	}
	return (0);
}

int	prepare_heredocs(t_shell *sh, t_cmd *cmds)
{
	int		n;
	t_cmd	*c;

	n = 0;
	c = cmds;
	while (c)
	{
		if (prepare_heredocs_one_cmd(sh, c, &n) != 0)
			return (fprintf(stderr, "*prepare_heredocs: one_cmd failed*\n"), 1);
		c = c->next;
	}
	return (0);
}
