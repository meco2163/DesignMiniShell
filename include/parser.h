/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:12:11 by mekaplan          #+#    #+#             */
/*   Updated: 2026/01/03 05:27:15 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "token.h"
# include "ast.h"

int		syntax_check(t_tok *lst);
t_cmd	*parse_tokens(t_tok *lst);
int		parse_redir(t_cmd *cur, t_tok **lst);

int		is_redir(t_ttype t);
t_cmd	*cmd_new(void);
void	cmd_add_back(t_cmd **lst, t_cmd *n);

#endif
