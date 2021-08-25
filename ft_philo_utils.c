/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 10:40:32 by pjacob            #+#    #+#             */
/*   Updated: 2021/08/25 15:28:50 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	neg;
	int	nb;

	i = 0;
	nb = 0;
	neg = 1;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
		|| nptr[i] == '\r' || nptr[i] == '\v' || nptr[i] == '\f')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - 48);
		i++;
	}
	return (nb * neg);
}

int	free_stuffs(t_philos *philos, t_param *p, pthread_t *thread)
{
	int	i;

	i = -1;
	while (++i < p->nb_philo)
		pthread_mutex_destroy(&p->fork[i]);
	free(p->fork);
	free(philos);
	free(thread);
	return (0);
}
