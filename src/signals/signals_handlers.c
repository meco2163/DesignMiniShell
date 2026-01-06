/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:11:07 by mekaplan          #+#    #+#             */
/*   Updated: 2026/01/03 05:11:08 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <readline/readline.h>
#include <unistd.h>

volatile sig_atomic_t	g_sig = 0;
t_sigmode				g_sigmode = SM_PROMPT;

void	sig_on_int(int signo)
{
	(void)signo;
	g_sig = SIGINT;
	if (g_sigmode == SM_PROMPT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (g_sigmode == SM_HEREDOC)
	{
		write(1, "\n", 1);
		rl_done = 1;
	}
}

void	sig_on_quit(int signo)
{
	(void)signo;
	g_sig = SIGQUIT;
}
