/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 12:22:35 by pjacob            #+#    #+#             */
/*   Updated: 2021/09/20 12:41:28 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

long	my_gettime(void)
{
	long			my_time;
	struct timeval	t;

	gettimeofday(&t, NULL);
	my_time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (my_time);
}

void	ft_usleep(int milli)
{
	long	time;

	time = my_gettime();
	while ((my_gettime() - time) < milli)
		usleep(milli);
}
