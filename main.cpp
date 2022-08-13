#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <conio.h>

#include "Game.h"

using matrix = std::vector<std::vector<int>>;

auto game_loop(matrix &arr, int &score) -> void;

auto main() -> int {
  srand(time(0));
  matrix arr {
    { 0, 0, 0, 0 },
    { 0, 2, 4, 0 },
    { 0, 0, 0, 0 },
    { 2, 0, 0, 0 },
  };

  int score = 0;
  game_loop(arr, score);

  return 0;
}

auto game_loop(matrix &arr, int &score) -> void {
  Game game(&arr, &score);
  game.print_table(score);

  matrix pre_mat;
  char pre = ' ';

  while (true) {
    if (_kbhit()) {
      char c = _getch();
      pre_mat = arr;
      int pre_score = score;

      if (pre == -32) {
        switch (c) {
        case 72: // up
          game.move_cells_up();
          break;
        case 80: // down
          game.move_cells_down();
          break;
        case 75: // left
          game.move_cells_left();
          break;
        case 77: // right
          game.move_cells_right();
          break;
        }

        game.insert_random(pre_mat);
        game.print_table(pre_score);
      }
      pre = c;
    }
  }
  
}
