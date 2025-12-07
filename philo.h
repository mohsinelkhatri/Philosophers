/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 08:50:55 by melkhatr          #+#    #+#             */
/*   Updated: 2025/10/22 09:59:13 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_sim	t_sim;

typedef struct s_philo
{
	int					id;
	int					left;
	int					right;
	long				last_meal_ms;
	int					meals_done;
	pthread_t			thread;
	pthread_mutex_t		meal_mtx;
	t_sim				*sim;
}						t_philo;

struct					s_sim
{
	int					n;
	long				t_die;
	long				t_eat;
	long				t_sleep;
	int					must_eat;
	long				start_ms;
	pthread_mutex_t		*forks;
	int					stopped;
	pthread_mutex_t		stop_mtx;
	pthread_mutex_t		print_mtx;
	int					room_tokens;
	pthread_mutex_t		room_mtx;
	pthread_t			monitor;
	t_philo				*philos;
};

void					init_forks(t_sim *sim);
int						sim_init(t_sim *sim);
int						start_threads(t_sim *sim);
long					now_ms(void);
void					busy_sleep_ms(long ms);
void					chunk_sleep(t_sim *sim, long ms);
void					print_state(t_sim *sim, int id, const char *msg,
							int force);
int						get_stopped(t_sim *sim);
void					set_stopped(t_sim *sim, int val);
int						ft_atoi(const char *s, long *out);
void					*philo_routine(void *arg);
void					*monitor_routine(void *arg);
void					cleanup_and_join(t_sim *sim);
void					destroy_sim(t_sim *sim);
void					room_enter(t_sim *sim);
void					room_leave(t_sim *sim);
void					take_forks(t_philo *p);
void					drop_forks(t_philo *p);
int						ft_putstr_fd(const char *s, int fd);
int						parse_args(int ac, char **av, t_sim *sim);
void					do_eat(t_philo *p);
void					do_sleep_think(t_philo *p);

#endif
