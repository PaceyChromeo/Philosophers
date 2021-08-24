/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 11:34:05 by pjacob            #+#    #+#             */
/*   Updated: 2021/08/24 12:46:47 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	taking_fork(t_philos *philo)
{
	int	time;

	time = my_gettime();
	pthread_mutex_lock(&philo->philo_p->fork[philo->left_fork]);
	philo->lf_status = 1;
	printf(GREEN"%d %d has taken a fork %d\n", time, philo->philo_id + 1, philo->left_fork);
	pthread_mutex_lock(&philo->philo_p->fork[philo->right_fork]);
	philo->rf_status = 1;
	printf(GREEN"%d %d has taken a fork %d\n", time, philo->philo_id + 1, philo->right_fork);
}

int	eating(t_philos *philo)
{
	int	time;

	time = my_gettime();
	if (philo->lf_status && philo->rf_status)
	{
		printf(RED"%d %d is eating\n", time, philo->philo_id + 1);
		if (philo->philo_p->max_eat > 0)
			philo->nb_eat--;
		usleep(philo->philo_p->time_to_eat);
		pthread_mutex_unlock(&philo->philo_p->fork[philo->left_fork]);
		philo->lf_status = 0;
		pthread_mutex_unlock(&philo->philo_p->fork[philo->right_fork]);
		philo->rf_status = 0;
	}
	if (philo->nb_eat == 0)
	{
		printf(WHITE"Philo %d is done eating\n", philo->philo_id + 1);
		return (0);
	}
	return (1);
}

void	sleeping(t_philos *philo)
{
	int	time;

	time = my_gettime();
	printf(YELLOW"%d %d is sleeping\n", time, philo->philo_id + 1);
	usleep(philo->philo_p->time_to_sleep);
}

void	thinking(t_philos *philo)
{
	int	time;

	time = my_gettime();
	printf(CYAN"%d %d is thinking\n", time ,philo->philo_id + 1);
}

int	philo_lives(t_philos *philo)
{
	if (philo->died)
		return (0);
	if (philo->nb_eat == 0)
		return (0);
	return (1);
}
