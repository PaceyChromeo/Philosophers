/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 12:22:35 by pjacob            #+#    #+#             */
/*   Updated: 2021/08/24 11:35:16 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	my_gettime(void)
{
	int				my_time;
	struct timeval	t;

	gettimeofday(&t, NULL);
	my_time = micro_to_milli(t.tv_usec);
	return (my_time);
}

int	milli_to_micro(int milli)
{
	int	micro;

	micro = milli * 1000;
	return (micro);
}

int micro_to_milli(int micro)
{
	int milli;

	milli = micro / 1000;
	return (milli);
}

int	timestamp(int start)
{
	int	timestamp;

	timestamp = my_gettime();
	timestamp -= start;
	return (timestamp);
}