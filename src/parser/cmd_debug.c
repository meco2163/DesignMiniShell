/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:10:53 by mekaplan          #+#    #+#             */
/*   Updated: 2026/01/03 05:24:39 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
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

static const char	*rtype_str(t_rtype t)
{
	if (t == R_IN)
		return ("<");
	if (t == R_OUT)
		return (">");
	if (t == R_APP)
		return (">>");
	return ("<<");
}

static void	print_redirs(t_redir *r)
{
	while (r)
	{
		putstr("  redir: ");
		putstr(rtype_str(r->type));
		putstr(" ");
		if (r->target)
			putstr(r->target);
		else
			putstr("(null)");
		putnl();
		r = r->next;
	}
}

void	cmd_print(t_cmd *cmds)
{
	int	i;

	while (cmds)
	{
		putstr("CMD\n");
		i = 0;
		while (cmds->argv && cmds->argv[i])
		{
			putstr("  argv: ");
			putstr(cmds->argv[i]);
			putnl();
			i++;
		}
		print_redirs(cmds->redirs);
		cmds = cmds->next;
	}
}
