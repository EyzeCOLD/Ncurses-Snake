#include <ncurses.h>
#include "snake.h"

void	draw_borders(int h, int w, int score, int level, int level_up)
{
	int x;

	if (level_up)
		attron(COLOR_PAIR(3));
	for (x = 0; x < w; x++)
		mvaddch(0, x, '#');
	for (int y = 1; y < h - 1; y++)
	{
		mvaddch(y, 0, '#');
		mvaddch(y, w - 1, '#');
	}
	for (x = 0; x < w; x++)
		mvaddch(h - 1, x, '#');
	if (level_up)
		attroff(COLOR_PAIR(3));
	mvprintw(h, 3, "SCORE: %7i00                 LEVEL: %3i", score, level);
}

void	draw_snake(t_gameobject *head)
{
	attron(COLOR_PAIR(1));
	while (head)
	{
		mvaddch(head->y, head->x, '@');
		head = head->next;
	}
	attroff(COLOR_PAIR(1));
}

void	erase_snake(t_gameobject *head)
{
	while (head)
	{
		mvaddch(head->y, head->x, ' ');
		head = head->next;
	}
}
