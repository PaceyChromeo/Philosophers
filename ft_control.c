/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_control.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 10:57:53 by pjacob            #+#    #+#             */
/*   Updated: 2021/09/20 12:31:02 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

static	int	z_is_dead(t_philos *philo, int i)
{
	int		j;
	long	time;

	time = my_gettime() - philo->philo_p->start_time;
	if (time - philo[i].lastmeal > philo[i].philo_p->time_to_die)
	{
		j = -1;
		while (++j < philo->philo_p->nb_philo)
			philo[i].dead = 1;
	}
	if (philo[i].dead)
	{
		pthread_mutex_lock(&philo->philo_p->write);
		time = my_gettime() - philo->philo_p->start_time;
		printf(WHITE"[%ld] %d died\n", time, philo->philo_id);
		return (0);
	}
	if (philo->nb_eat == 0)
		return (0);
	return (1);
}

void	*time_control(void *philos)
{
	t_philos	*philo;
	int			i;

	philo = (t_philos *)philos;
	i = 0;
	while (i < philo->philo_p->nb_philo)
	{
		if (z_is_dead(philo, i) == 0)
			return (NULL);
		i++;
		if (i == philo->philo_p->nb_philo)
			i = 0;
	}
	return (NULL);
}
