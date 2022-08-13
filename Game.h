#pragma once

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <Windows.h>

using matrix = std::vector<std::vector<int>>;

#define HANDLE GetStdHandle(STD_OUTPUT_HANDLE)
#define REPEAT(x) for (int _ = 0; _ < x; _++)

auto move(short x, short y) -> void;

class Game {
private:
  matrix *arr;
  int *score;

private:

public:
  Game(matrix *ptr, int *score): arr(ptr), score(score) {}

public:
  // Table stuff
  auto print_table(int pre_score) -> void;
  auto insert_random(matrix &pre) -> void;

  // Table movement
  auto move_cells_down() -> void;
  auto move_cells_up() -> void;
  auto move_cells_left() -> void;
  auto move_cells_right() -> void;
};

#endif // GAME_H
