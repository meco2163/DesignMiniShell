/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:12:05 by mekaplan          #+#    #+#             */
/*   Updated: 2026/01/03 05:25:56 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "token.h"

t_tok	*tokenize(const char *s);
int		read_op(t_tok **lst, const char *s, int *i);
int		read_word(t_tok **lst, const char *s, int *i);

int		count_len(const char *s, int pos, int *end);

#endif
