#include "philosophers.h"

void out_of_eat_stack(t_philosopher *philo) {
  t_eat_stack *aux;

  aux = philo->eat_stack[0];
  pthread_mutex_lock(&(philo->kylix));
  while (aux->philo_next)
    aux = aux->philo_next;
  aux->philo_next = philo->eat_stack[0];
  philo->eat_stack[0] = philo->eat_stack[0]->philo_next;
  aux->philo_next->philo_next = NULL;
  pthread_mutex_unlock(&(philo->kylix));
}

void *philo_life(void *philo_info) {
  t_philosopher *philo = (t_philosopher *)philo_info;
  int can_eat;
  while (1) {
    /*
    printf("%d is thinking\n", philo->id + 1);
    can_eat = 0;
    while (!can_eat) {
      pthread_mutex_lock(&(philo->kylix));
      if (philo->id == philo->eat_stack[0]->philo_id)
        can_eat = 1;
      pthread_mutex_unlock(&(philo->kylix));
    }
    */
    if (philo->id % 2 == 0) {
      pthread_mutex_lock(&(philo->forks[philo->id]));
      printf("%d has taken a fork\n", philo->id + 1);
      pthread_mutex_lock(&(philo->forks[philo->id_left]));
      printf("%d has taken a fork\n", philo->id + 1);
    } else {
      pthread_mutex_lock(&(philo->forks[philo->id_left]));
      printf("%d has taken a fork\n", philo->id + 1);
      pthread_mutex_lock(&(philo->forks[philo->id]));
      printf("%d has taken a fork\n", philo->id + 1);
    }
    // out_of_eat_stack(philo);
    printf("%d is eating\n", philo->id + 1);
    usleep(philo->time_to_eat);
    if (philo->id % 2 == 0) {
      pthread_mutex_unlock(&(philo->forks[philo->id]));
      pthread_mutex_unlock(&(philo->forks[philo->id_left]));
    } else {
      pthread_mutex_unlock(&(philo->forks[philo->id]));
      pthread_mutex_unlock(&(philo->forks[philo->id_left]));
    }
    printf("%d is sleeping\n", philo->id + 1);
    usleep(philo->time_to_sleep);
  }
  return (NULL);
}
