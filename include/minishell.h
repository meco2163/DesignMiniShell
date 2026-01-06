/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:12:08 by mekaplan          #+#    #+#             */
/*   Updated: 2026/01/03 05:16:49 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lexer.h"
# include "parser.h"
# include "ast.h"

typedef struct s_shell
{
	int	last_status;
}	t_shell;

int		sh_status(t_shell *sh);
void	sh_set_status(t_shell *sh, int st);

int		run_once(t_shell *sh, const char *line);

#endif
