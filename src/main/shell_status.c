/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:10:50 by mekaplan          #+#    #+#             */
/*   Updated: 2026/01/03 05:16:49 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sh_status(t_shell *sh)
{
	return (sh->last_status);
}

void	sh_set_status(t_shell *sh, int st)
{
	sh->last_status = st;
}
