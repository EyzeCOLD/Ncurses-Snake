#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include "snake.h"

void	spawn_collectible(t_gameobject *collectible)
{
	// range 2-78
	collectible->x = rand() % (WINDOW_W - 4) + 2;
	// range 2-23
	collectible->y = rand() % (WINDOW_H - 4) + 2;
}

t_gameobject	*new_part(int x, int y)
{
	t_gameobject *new;

	new = (t_gameobject *) malloc(sizeof(t_gameobject));
	if (!new)
		return (NULL);
	new->x = x;
	new->y = y;
	new->next = NULL;
	return (new);
}

t_gameobject	*add_back(t_gameobject **head, int x, int y)
{
	t_gameobject	*new;
	t_gameobject	*tmp;
	
	new = new_part(x, y);
	if (!new)
		return (NULL);
	if (!*head)
	{
		*head = new;
		return (new);
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (new);
}



void	update_snake(t_gameobject *head, int x, int y)
{
	int	prev_x;
	int	prev_y;
	int	this_x;
	int	this_y;

	prev_x = head->x;
	prev_y = head->y;
	head->x = x;
	head->y = y;
	while (head->next)
	{
		head = head->next;
		this_x = head->x;
		this_y = head->y;
		head->x = prev_x;
		head->y = prev_y;
		prev_x = this_x;
		prev_y = this_y;
	}
}

int		collision(t_gameobject *gob1, t_gameobject *gob2)
{
	t_gameobject	*ptr;
	int				x;
	int				y;

	ptr = gob2;
	x = gob1->x;
	y = gob1->y;
	while (ptr)
	{
		if (ptr->x == x && ptr->y == y)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

void	free_snake(t_gameobject *head)
{
	t_gameobject	*tmp;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

int main()
{
	int				ch;
	int				dir;
	int				snake_alive;
	int				score;
	int				v_speed;
	int				h_speed;
	int				level;
	int				level_up;
	int				v_delay;
	int				h_delay;
	t_gameobject	*head;
	t_gameobject	collectible;

	dir = DOWN;
	snake_alive = 1;
	score = 0;
	head = NULL;
	collectible.x = 0;
	collectible.y = 0;
	collectible.next = NULL;
	level = 1;
	level_up = 0;
	v_delay = SPEED * 120;
	h_delay = SPEED * 80;
	for (int i = 0; i < INITIAL_LENGTH; i++)
	{
		if (add_back(&head, WINDOW_W / 2, WINDOW_H / 2) == NULL)
			free_snake(head);
	}
	if (!head)
		return (1);
	spawn_collectible(&collectible);
	srand(getpid());

	initscr();
	if(has_colors() == FALSE)
	{
		endwin();
		free_snake(head);
		exit(1);
	}
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	nodelay(stdscr, TRUE);
	start_color();
	init_pair(1, COLOR_YELLOW, COLOR_MAGENTA);
	init_pair(2, COLOR_WHITE, COLOR_GREEN);
	init_pair(3, COLOR_BLACK, COLOR_WHITE);

	while (snake_alive)
	{
		ch = getch();
		switch (ch)
		{
			case KEY_DOWN:
				if (dir != UP) dir = DOWN;
				break;
			case KEY_LEFT:
				if (dir != RIGHT) dir = LEFT;
				break;
			case KEY_UP:
				if (dir != DOWN) dir = UP;
				break;
			case KEY_RIGHT:
				if (dir != LEFT) dir = RIGHT;
				break;
			case 'x':
				endwin();
				return (0);
				break;
		}
		v_speed = 0;
		h_speed = 0;
		switch (dir)
		{
			case DOWN:
				v_speed++;
				break;
			case LEFT:
				h_speed--;
				break;
			case UP:
				v_speed--;
				break;
			case RIGHT:
				h_speed++;
				break;
		}
		erase_snake(head);
		update_snake(head, head->x + h_speed, head->y + v_speed);
		draw_borders(WINDOW_H, WINDOW_W, score, level, level_up);
		level_up = 0;
		attron(COLOR_PAIR(2));
		mvaddch(collectible.y, collectible.x, '$');
		attroff(COLOR_PAIR(2));
		draw_snake(head);
        refresh();
		if (head->x < 1 || head->x > WINDOW_W - 2 || head->y < 1 || head->y > WINDOW_H - 2)
			break;
		if (collision(head, head->next))
			break;
		if (collision(head, &collectible))
		{
			spawn_collectible(&collectible);
			while (collision(&collectible, head))
				spawn_collectible(&collectible);
			score += 1;
			if (score % 5 == 0)
			{
				level_up = 1;
				level++;
				v_delay = v_delay * 7 / 8;
				h_delay = h_delay * 7 / 8;
			}
			if (add_back(&head, head->x, head->y) == NULL)
				break ;
		}
		if (dir % 2)
			usleep(h_delay);
		else
			usleep(v_delay);
	}
	free_snake(head);
	endwin();

	return 0;
}

