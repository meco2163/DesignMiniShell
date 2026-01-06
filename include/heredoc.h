/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:12:02 by mekaplan          #+#    #+#             */
/*   Updated: 2026/01/03 05:24:39 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "minishell.h"
# include "ast.h"
# include <sys/types.h>

int		prepare_heredocs(t_shell *sh, t_cmd *cmds);
int		prepare_heredocs_one_cmd(t_shell *sh, t_cmd *c, int *n);

char	*hd_path(int n);
pid_t	hd_run_one(const char *path, const char *delim);
int		hd_wait_set(t_shell *sh, pid_t pid);

char	*norm_delim(const char *s);
int		hd_child_write(int fd, const char *delim);

#endif
