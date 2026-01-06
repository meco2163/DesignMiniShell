/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:11:42 by mekaplan          #+#    #+#             */
/*   Updated: 2026/01/03 05:16:49 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "token.h"

typedef enum e_rtype
{
	R_IN,
	R_OUT,
	R_APP,
	R_HDOC
}	t_rtype;

typedef struct s_redir
{
	t_rtype			type;
	char			*target;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

void	cmd_print(t_cmd *cmds);
void	cmd_clear(t_cmd **cmds);

#endif
