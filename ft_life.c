/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 11:34:05 by pjacob            #+#    #+#             */
/*   Updated: 2021/08/25 16:54:54 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	taking_fork(t_philos *philo)
{
	int	time;

	time = my_gettime();
	if (time_since_lastmeal(philo->lastmeal, time) > philo->philo_p->time_to_die)
	{
		philo->dead = 1;
		printf(WHITE"%d %d died\n", time, philo->philo_id);
		return (0);
	}
	pthread_mutex_lock(&philo->philo_p->fork[philo->left_fork]);
	printf(GREEN"%d %d has taken a fork\n", time, philo->philo_id);
	pthread_mutex_lock(&philo->philo_p->fork[philo->right_fork]);
	printf(GREEN"%d %d has taken a fork\n", time, philo->philo_id);
	return (1);
}

int	eating(t_philos *philo)
{
	int	time;

	time = my_gettime();
	if (time_since_lastmeal(philo->lastmeal, time) > philo->philo_p->time_to_die)
	{
		philo->dead = 1;
		pthread_mutex_unlock(&philo->philo_p->fork[philo->left_fork]);
		pthread_mutex_unlock(&philo->philo_p->fork[philo->right_fork]);
		printf(WHITE"%d %d died\n", time, philo->philo_id);
		return (0);
	}
	philo->lastmeal = my_gettime();
	printf(RED"%d %d is eating\n", philo->lastmeal, philo->philo_id);
	if (philo->philo_p->max_eat > 0)
		philo->nb_eat--;
	usleep(philo->philo_p->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->philo_p->fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->philo_p->fork[philo->right_fork]);
	if (philo->nb_eat == 0)
		return (0);
	return (1);
}

int	sleeping(t_philos *philo)
{
	int	time;

	time = my_gettime();
	if (time_since_lastmeal(philo->lastmeal, time) > philo->philo_p->time_to_die)
	{
		philo->dead = 1;
		printf(WHITE"%d %d died\n", time, philo->philo_id);
		return (0);
	}
	printf(YELLOW"%d %d is sleeping\n", time, philo->philo_id);
	usleep(philo->philo_p->time_to_sleep * 1000);
	return (1);
}

int	thinking(t_philos *philo)
{
	int	time;

	time = my_gettime();
	if (time_since_lastmeal(philo->lastmeal, time) > philo->philo_p->time_to_die)
	{
		philo->dead = 1;
		printf(WHITE"%d %d died\n", time, philo->philo_id);
		return (0);
	}
	printf(CYAN"%d %d is thinking\n", time, philo->philo_id);
	return (1);
}

int	philo_lives(t_philos *philo)
{
	if (philo->dead)
		return (0);
	if (philo->nb_eat == 0)
		return (0);
	return (1);
}
