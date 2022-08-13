#include "Game.h"

// Function to move cursor around
auto move(short x, short y) -> void {
  SetConsoleCursorPosition(HANDLE, { x, y });
}

auto Game::print_table(int pre_score) -> void {
  move(0, 0);

  // Print score
  printf("Score: ");
  if (*score == pre_score) { 
    SetConsoleTextAttribute(HANDLE, 15); // Color: Bright White
    printf("%d", *score);
    SetConsoleTextAttribute(HANDLE, 7); // Color: Bright White
    printf("                      \n");
  }
  else { 
    SetConsoleTextAttribute(HANDLE, 15); // Color: Bright White
    printf("%d", *score);
    SetConsoleTextAttribute(HANDLE, 7); // Color: Bright White

    std::cout << " (";
    SetConsoleTextAttribute(HANDLE, 10); // Color: Green
    std::cout << '+' << *score - pre_score;
    SetConsoleTextAttribute(HANDLE, 7); // Color: White

    std::cout << ')' << "                            " << '\n';
  }

  printf("+-----------------------+\n");
  for (const std::vector<int> &vec : *arr) {
    for (const int &i : vec) {
      if (i) {
        std::cout << '|' << std::setw(4); 
        SetConsoleTextAttribute(HANDLE, 15); // Color: Bright White
        std::cout << i;
        SetConsoleTextAttribute(HANDLE, 7); // Color: White
        std::cout << std::setfill(' ') << ' ';
      } else {
        printf("|     ");
      }
    }
    printf("|\n");
  }
  printf("+-----------------------+\n");
}

auto Game::insert_random(matrix &pre) -> void {
  if (*(this->arr) != pre) {
    int n = 2;

    // A lambda to find random number between a range
    auto get_rand = [](int start, int end) {
      return rand() % (end - start + 1) + start; 
    };

    // what to insert ?
    // 2 or 4
    if (get_rand(0, 1) == 0) n = 4; // from 0 to 1 

    // Find empty spots
    std::vector<std::array<int, 2>> empty_spots;
    for (int y = 0; y < arr->size(); y++)
      for (int x = 0; x < arr->size(); x++)
        if ((*arr)[y][x] == 0) empty_spots.push_back({ y, x });

    if (empty_spots.size() == 0) return;

    // Choose a random empty spot
    auto RI_pos = empty_spots[get_rand(0, empty_spots.size() - 1)];

    (*arr)[RI_pos[0]][RI_pos[1]] = n;
    return;
  }
  
  // If there's not space left
  // Check if the game is over or not

  matrix post_pre = pre;
  Game g(&post_pre, this->score);

  g.move_cells_up();
  g.move_cells_down();
  g.move_cells_left();
  g.move_cells_right();

  if (post_pre == pre) {
    // Game over
    printf("==== Game Over ====\n\nPress enter to exit\n");
    std::cin.get();
    exit(0);
  }
}

auto Game::move_cells_down() -> void {
  static const int last_row = 3;
  REPEAT(4) {
    for (int y = arr->size() - 2; y > -1; y--)
      for (int x = 0; x < (*arr)[y].size(); x++) {

        if ((*arr)[y][x] != 0)
          for (int j = y + 1; j < last_row + 1; j++) {
            int &pre = (*arr)[j - 1][x];
            int &current = (*arr)[j][x];

            if (current == pre) {
              current += pre;
              *score += current;
              pre = 0;
            } else if (current == 0) {
              current = pre;
              pre = 0;
            }
          }
      }
  }
}

auto Game::move_cells_up() -> void {
  static const int last_row = 3;
  REPEAT(4) {
    for (int y = arr->size() - 1; y > 0; y--)
      for (int x = 0; x < (*arr)[y].size(); x++) {

        if ((*arr)[y][x] != 0)
          for (int j = y - 1; j > -1; j--) {
            int &pre = (*arr)[j + 1][x];
            int &current = (*arr)[j][x];

            if (current == pre) {
              current += pre;
              *score += current;
              pre = 0;
            } else if (current == 0) {
              current = pre;
              pre = 0;
            }
          }
      }
  }
}

auto Game::move_cells_left() -> void {
  static const int last_row = 3;
  REPEAT(4) {
    for (int y = arr->size() - 1; y > -1; y--)
      for (int x = 1; x < (*arr)[y].size(); x++) {

        if ((*arr)[y][x] != 0)
          for (int j = x - 1; j > -1; j--) {
            int &pre = (*arr)[y][j + 1];
            int &current = (*arr)[y][j];

            if (current == pre) {
              current += pre;
              *score += current;
              pre = 0;
            } else if (current == 0) {
              current = pre;
              pre = 0;
            }
          }
      }
  }
}

auto Game::move_cells_right() -> void {
  static const int last_row = 3;
  REPEAT(4) {
    for (int y = arr->size() - 1; y > -1; y--)
      for (int x = 0; x < (*arr)[y].size() - 1; x++) {

        if ((*arr)[y][x] != 0)
          for (int j = x + 1; j < last_row + 1; j++) {
            int &pre = (*arr)[y][j - 1];
            int &current = (*arr)[y][j];

            if (current == pre) {
              current += pre;
              *score += current;
              pre = 0;
            } else if (current == 0) {
              current = pre;
              pre = 0;
            }
          }
      }
  }
}
