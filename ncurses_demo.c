#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

char SYMBOL_LIVE = '*';
char SYMBOL_FREE = ' ';

char **world;

unsigned int
randr(int min, int max)
{
  return ((rand() % (max + 1 - min)) + min);
}

void
init_world(int world_size_x, int world_size_y)
{
  int i, j;

  world = (char **) calloc(world_size_x, sizeof(char *));
  for (i = 0; i < world_size_x; i++) {
    world[i] = calloc(world_size_y, sizeof(char));
  }

  for (i = 0; i < world_size_x; i++) {
    for (j = 0; j < world_size_y; j++) {
      world[i][j] = SYMBOL_FREE;
    }
  }

  world[1][3] = SYMBOL_LIVE;
  world[2][1] = SYMBOL_LIVE;
  world[2][3] = SYMBOL_LIVE;
  world[3][2] = SYMBOL_LIVE;
  world[3][3] = SYMBOL_LIVE;

  for (i = 0; i < world_size_x; i++) {
    for (j = 0; j < world_size_y; j++) {
      mvprintw(j, i, "%c", world[i][j]);
    }
  }
}

void
change_world(int world_size_x, int world_size_y)
{
  int i, j;

  i = randr(0, world_size_x - 1);
  j = randr(0, world_size_y - 1);

  world[i][j] = SYMBOL_LIVE;

  for (i = 0; i < world_size_x; i++) {
    for (j = 0; j < world_size_y; j++) {
      mvprintw(j, i, "%c", world[i][j]);
    }
  }
}

void
destroy_world(int world_size_x)
{
  int i;
  for (i = 0; i < world_size_x; i++) {
    free(world[i]);
  }
  free(world);
}

int
main(void)
{
  int WINDOW_SIZE_ROW, WINDOW_SIZE_COL;
  int i, j;

  srand(time(NULL));

  initscr();
  getmaxyx(stdscr, WINDOW_SIZE_ROW, WINDOW_SIZE_COL);

  init_world(WINDOW_SIZE_COL, WINDOW_SIZE_ROW);

  while (1) {
    change_world(WINDOW_SIZE_COL, WINDOW_SIZE_ROW);
    refresh();
  }

  destroy_world(WINDOW_SIZE_COL);

  getch();
  endwin();

  return 0;
}
