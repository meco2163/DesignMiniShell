/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:10:30 by mekaplan          #+#    #+#             */
/*   Updated: 2026/01/03 05:21:15 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include <unistd.h>

static void	putstr(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	write(1, s, i);
}

static void	putnl(void)
{
	write(1, "\n", 1);
}

const char	*tok_type_str(t_ttype t)
{
	if (t == T_WORD)
		return ("WORD");
	if (t == T_PIPE)
		return ("PIPE");
	if (t == T_REDIR_IN)
		return ("R_IN");
	if (t == T_REDIR_OUT)
		return ("R_OUT");
	if (t == T_REDIR_APPEND)
		return ("R_APP");
	if (t == T_HEREDOC)
		return ("HEREDOC");
	return ("EOF");
}

void	tok_print(t_tok *lst)
{
	while (lst)
	{
		putstr(tok_type_str(lst->type));
		putstr(" : ");
		if (lst->val)
			putstr(lst->val);
		else
			putstr("(null)");
		putnl();
		lst = lst->next;
	}
}
