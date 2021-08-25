/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 12:22:35 by pjacob            #+#    #+#             */
/*   Updated: 2021/08/25 15:54:22 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	my_gettime(void)
{
	int				my_time;
	struct timeval	t;

	gettimeofday(&t, NULL);
	my_time = t.tv_usec / 1000;
	return (my_time);
}

int	time_since_lastmeal(int lastmeal, int current_time)
{
	int	diff;

	if (current_time >= lastmeal)
		diff = current_time - lastmeal;
	else
		diff = (current_time + 1000) - lastmeal;
	return (diff);
}