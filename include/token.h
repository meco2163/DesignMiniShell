/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:12:17 by mekaplan          #+#    #+#             */
/*   Updated: 2026/01/03 05:16:49 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_ttype
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC,
	T_EOF
}	t_ttype;

typedef struct s_tok
{
	t_ttype			type;
	char			*val;
	struct s_tok	*next;
}	t_tok;

t_tok		*tok_new(t_ttype type, char *val);
void		tok_add_back(t_tok **lst, t_tok *n);
void		tok_clear(t_tok **lst);
const char	*tok_type_str(t_ttype type);
void		tok_print(t_tok *lst);

#endif
