#ifndef __GAME_OF_LIFE_H__
#define __GAME_OF_LIFE_H__

#include <stdbool.h>

#define WIDTH 60
#define HEIGHT 40

#define AT(y, x) (y) * WIDTH + (x)

enum GAME_MODE { RUN_MODE, EDIT_MODE };

void print_map(void);
void update_map(void);
bool handle_input(void);
void print_mode(void);

#endif /* __GAME_OF_LIFE_H__ */
