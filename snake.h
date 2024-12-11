#ifndef SNAKE_H
#define SNAKE_H
#define INITIAL_LENGTH 5
#define DOWN 0
#define LEFT 1
#define UP 2
#define RIGHT 3
#define	SPEED 900
#define WINDOW_W 80
#define WINDOW_H 25
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct	s_gameobject
{
	int	x;
	int	y;
	struct s_gameobject *next;
}	t_gameobject;

void			draw_borders(int h, int w, int score, int level, int level_up);

void			draw_snake(t_gameobject *head);

void			erase_snake(t_gameobject *head);

void			spawn_collectible(t_gameobject *collectible);

t_gameobject	*new_part(int x, int y);

t_gameobject	*add_back(t_gameobject **head, int x, int y);

void			update_snake(t_gameobject *head, int x, int y);

int				collision(t_gameobject *gob1, t_gameobject *gob2);

void			free_snake(t_gameobject *head);

#endif
