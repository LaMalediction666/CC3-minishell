/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:17:37 by mvogel            #+#    #+#             */
/*   Updated: 2023/04/24 14:20:54 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern sig_atomic_t	g_exitcode;

void	signal_handler(int signum)
{
	if (g_exitcode == 2 || g_exitcode == 3)
		return ;
	if (signum == SIGINT)
	{
		if (g_exitcode != 1)
			g_exitcode += 1;
		// printf("\n");
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		//rl_redisplay();
	}
}

void	signal_init(struct sigaction *sign)
{
	// sigemptyset(&sign->sa_mask);
	sign->sa_flags = SA_RESTART;
	sign->sa_handler = signal_handler;
	rl_catch_signals = 0;
	return ;
}

void	input_signal(struct sigaction sign)
{
	sigaction(SIGINT, &sign, NULL);
	sigaction(SIGQUIT, &sign, NULL);
}

// void	sig_handler_child(int signum)
// {
// 	if (signum == SIGINT)
// 		g_exitcode = 1;
// }

// void	sig_init(void (*handler)(int))
// {
// 	struct sigaction	act;

// 	act.sa_flags = SA_RESTART;
// 	act.sa_handler = handler;
// 	sigaction(SIGINT, &act, NULL);
// 	sigaction(SIGQUIT, &act, NULL);
// }

// void	exec_ctrl_c()
// {
// 	printf("\n");
// 	g_exitcode = 130;
// }
// void	exec_signal()
// {
// 	signal(SIGINT, exec_ctrl_c);
// 	signal(SIGQUIT, ctrl_backslash);
// }

// void	input_signal()
// {
// 	signal(SIGINT, ctrl_c);
// 	signal(SIGQUIT, SIG_IGN);
// }