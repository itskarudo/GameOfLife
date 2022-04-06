#include "main.h"

#include <curses.h>

char map[WIDTH * HEIGHT] = {[0 ...(WIDTH * HEIGHT - 1)] = ' '};

int window_y, window_x;

int edit_x = 0;
int edit_y = 0;

enum GAME_MODE mode = EDIT_MODE;

int main(int argc, char* argv[]) {
  WINDOW* win;

  win = initscr();
  keypad(stdscr, TRUE);
  curs_set(0);
  getmaxyx(stdscr, window_y, window_x);

  while (1) {
    print_map();
    print_mode();

    if (handle_input()) goto quit;
    erase();
  }

quit:
  endwin();
}

void print_mode(void) {
  attron(A_REVERSE);
  if (mode == EDIT_MODE)
    mvprintw(window_y - 1, 0, "EDIT MODE");
  else if (mode == RUN_MODE)
    mvprintw(window_y - 1, 0, "RUN MODE");
  attroff(A_REVERSE);
}

void print_map(void) {
  int i, j;
  for (i = 0; i < HEIGHT; i++) {
    for (j = 0; j < WIDTH; j++) {
      if ((mode == EDIT_MODE) && (edit_x == j) && (edit_y == i)) {
        attron(A_REVERSE);
        mvaddch(i, j, map[AT(i, j)]);
        attroff(A_REVERSE);
      } else
        mvaddch(i, j, map[AT(i, j)]);
    }
  }
}

void update_map(void) {
  char temp_map[WIDTH * HEIGHT] = {0};

  int i, j;
  for (i = 0; i < HEIGHT; i++) {
    for (j = 0; j < WIDTH; j++) {
      int live_cells = 0;

      if (i > 0) {
        if (map[AT(i - 1, j)] == '#') live_cells++;
        if (j > 0 && map[AT(i - 1, j - 1)] == '#') live_cells++;
        if (j < WIDTH - 1 && map[AT(i - 1, j + 1)] == '#') live_cells++;
      }

      if (i < HEIGHT - 1) {
        if (map[AT(i + 1, j)] == '#') live_cells++;
        if (j > 0 && map[AT(i + 1, j - 1)] == '#') live_cells++;
        if (j < WIDTH - 1 && map[AT(i + 1, j + 1)] == '#') live_cells++;
      }

      if (j > 0 && map[AT(i, j - 1)] == '#') live_cells++;
      if (j < WIDTH - 1 && map[AT(i, j + 1)] == '#') live_cells++;

      if (map[AT(i, j)] == '#') {
        if (live_cells != 2 && live_cells != 3)
          temp_map[AT(i, j)] = ' ';
        else
          temp_map[AT(i, j)] = '#';

      } else {
        if (live_cells == 3)
          temp_map[AT(i, j)] = '#';
        else
          temp_map[AT(i, j)] = ' ';
      }
    }
  }

  for (i = 0; i < WIDTH * HEIGHT; i++) map[i] = temp_map[i];
}

bool handle_input(void) {
  int c = getch();

  if (c == 'q') return true;

  if (mode == EDIT_MODE) {
    switch (c) {
      case KEY_UP:
      case 'k':
        if (edit_y == 0)
          edit_y = HEIGHT - 1;
        else
          edit_y--;
        break;

      case KEY_DOWN:
      case 'j':
        if (edit_y == HEIGHT - 1)
          edit_y = 0;
        else
          edit_y++;
        break;
      case KEY_LEFT:
      case 'h':
        if (edit_x == 0)
          edit_x = WIDTH - 1;
        else
          edit_x--;
        break;
      case KEY_RIGHT:
      case 'l':
        if (edit_x == WIDTH - 1)
          edit_x = 0;
        else
          edit_x++;
        break;

      case ' ':
        if (map[AT(edit_y, edit_x)] == ' ')
          map[AT(edit_y, edit_x)] = '#';
        else
          map[AT(edit_y, edit_x)] = ' ';
        break;

      case 'i':
        mode = RUN_MODE;
        break;

      default:
        break;
    }
  } else {
    switch (c) {
      case ' ':
        update_map();
        break;
      case 'i':
        mode = EDIT_MODE;
        break;
      default:
        break;
    }
  }

  return false;
}
