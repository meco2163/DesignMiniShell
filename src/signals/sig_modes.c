/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_modes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:30:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/01/03 05:24:39 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	sig_set_mode(t_sigmode mode)
{
	g_sigmode = mode;
}

void	sig_init_heredoc(void)
{
	sig_set_mode(SM_HEREDOC);
	sig_set_sa(SIGINT, sig_on_int, SA_RESTART);
	sig_set_sa(SIGQUIT, SIG_IGN, SA_RESTART);
}
