/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:11:10 by mekaplan          #+#    #+#             */
/*   Updated: 2026/01/03 05:24:39 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	sig_set_sa(int sig, void (*fn)(int), int flags)
{
	struct sigaction	sa;

	sa.sa_handler = fn;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = flags;
	(void)sigaction(sig, &sa, 0);
}

void	sig_init_prompt(void)
{
	sig_set_mode(SM_PROMPT);
	sig_set_sa(SIGINT, sig_on_int, SA_RESTART);
	sig_set_sa(SIGQUIT, SIG_IGN, SA_RESTART);
}

void	sig_init_wait_parent(void)
{
	sig_set_mode(SM_CHILD);
	sig_set_sa(SIGINT, SIG_IGN, SA_RESTART);
	sig_set_sa(SIGQUIT, SIG_IGN, SA_RESTART);
}

void	sig_init_child(void)
{
	sig_set_mode(SM_CHILD);
	sig_set_sa(SIGINT, SIG_DFL, 0);
	sig_set_sa(SIGQUIT, SIG_DFL, 0);
}
