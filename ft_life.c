/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 11:34:05 by pjacob            #+#    #+#             */
/*   Updated: 2021/09/20 12:27:26 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	taking_fork(t_philos *philo)
{
	long	time;

	pthread_mutex_lock(&philo->philo_p->fork[philo->left_fork]);
	pthread_mutex_lock(&philo->philo_p->write);
	time = my_gettime() - philo->philo_p->start_time;
	printf(GREEN"[%ld] %d has taken his left fork\n", time, philo->philo_id);
	pthread_mutex_unlock(&philo->philo_p->write);
	pthread_mutex_lock(&philo->philo_p->fork[philo->right_fork]);
	pthread_mutex_lock(&philo->philo_p->write);
	time = my_gettime() - philo->philo_p->start_time;
	printf(GREEN"[%ld] %d has taken his right fork\n", time, philo->philo_id);
	pthread_mutex_unlock(&philo->philo_p->write);
	return (1);
}

int	eating(t_philos *philo)
{
	long	time;

	time = my_gettime() - philo->philo_p->start_time;
	philo->lastmeal = time;
	pthread_mutex_lock(&philo->philo_p->write);
	printf(RED"[%ld] %d is eating\n", time, philo->philo_id);
	pthread_mutex_unlock(&philo->philo_p->write);
	ft_usleep(philo->philo_p->time_to_eat);
	pthread_mutex_unlock(&philo->philo_p->fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->philo_p->fork[philo->right_fork]);
	if (philo->philo_p->max_eat > 0)
		philo->nb_eat--;
	if (philo->nb_eat == 0)
		return (0);
	return (1);
}

int	sleeping(t_philos *philo)
{
	long	time;

	pthread_mutex_lock(&philo->philo_p->write);
	time = my_gettime() - philo->philo_p->start_time;
	printf(YELLOW"[%ld] %d is sleeping\n", time, philo->philo_id);
	pthread_mutex_unlock(&philo->philo_p->write);
	ft_usleep(philo->philo_p->time_to_sleep);
	return (1);
}

int	thinking(t_philos *philo)
{
	long	time;

	pthread_mutex_lock(&philo->philo_p->write);
	time = my_gettime() - philo->philo_p->start_time;
	printf(CYAN"[%ld] %d is thinking\n", time, philo->philo_id);
	pthread_mutex_unlock(&philo->philo_p->write);
	return (1);
}

int	philo_lives(t_philos *philo)
{
	if (philo->nb_eat == 0)
		return (0);
	return (1);
}
