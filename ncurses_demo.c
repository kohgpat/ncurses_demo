#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

char SYMBOL_LIVE = '*';
char SYMBOL_FREE = ' ';

int WINDOW_SIZE_ROW, WINDOW_SIZE_COL;

char **WORLD;

unsigned int
randr(int min, int max)
{
  return ((rand() % (max + 1 - min)) + min);
}

void
init_world()
{
  int i, j;

  WORLD = (char **) calloc(WINDOW_SIZE_COL, sizeof(char *));

  for (i = 0; i < WINDOW_SIZE_COL; i++) {
    WORLD[i] = calloc(WINDOW_SIZE_ROW, sizeof(char));
  }

  for (i = 0; i < WINDOW_SIZE_COL; i++) {
    for (j = 0; j < WINDOW_SIZE_ROW; j++) {
      WORLD[i][j] = SYMBOL_FREE;
    }
  }

  WORLD[1][3] = SYMBOL_LIVE;
  WORLD[2][1] = SYMBOL_LIVE;
  WORLD[2][3] = SYMBOL_LIVE;
  WORLD[3][2] = SYMBOL_LIVE;
  WORLD[3][3] = SYMBOL_LIVE;

  for (i = 0; i < WINDOW_SIZE_COL; i++) {
    for (j = 0; j < WINDOW_SIZE_ROW; j++) {
      mvprintw(j, i, "%c", WORLD[i][j]);
    }
  }
}

void
change_world()
{
  int i, j;

  i = randr(0, WINDOW_SIZE_COL - 1);
  j = randr(0, WINDOW_SIZE_ROW - 1);

  WORLD[i][j] = SYMBOL_LIVE;

  for (i = 0; i < WINDOW_SIZE_COL; i++) {
    for (j = 0; j < WINDOW_SIZE_ROW; j++) {
      mvprintw(j, i, "%c", WORLD[i][j]);
    }
  }
}

void
destroy_world()
{
  int i;

  for (i = 0; i < WINDOW_SIZE_COL; i++) {
    free(WORLD[i]);
  }

  free(WORLD);
}

int
main(void)
{
  srand(time(NULL));

  initscr();
  getmaxyx(stdscr, WINDOW_SIZE_ROW, WINDOW_SIZE_COL);

  init_world();

  while (1) {
    change_world();
    refresh();
  }

  destroy_world();

  getch();
  endwin();

  return 0;
}
