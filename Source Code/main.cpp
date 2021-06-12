#include<iostream>

#include<graphics.h>

#include<conio.h>

#include<dos.h>

#include<time.h>

#include<stdio.h>

#include<math.h>

#define ScWidth 1400
#define ScHeight 700
#define OpWidth 400

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define SPACEBAR 32

using namespace std;

// Dispaly YouWin screen and reset moves
void YouWin();

// Draw game board and moves / control area
void DrawBoard();

// Draw balls
void DrawBalls();

// Draw Handle that navigate between balls to swap them
void DrawHandles();

// swaps balls
void Swap(int & x, int & y);

int WinCondition();

// Ball Variables
// position , ballType (0-Hole, 1-Black, 2-White)
int balls[7][2] = {
  {
    200,
    1
  },
  {
    300,
    1
  },
  {
    400,
    1
  },
  {
    500,
    0
  },
  {
    600,
    2
  },
  {
    700,
    2
  },
  {
    800,
    2
  }
};
int bi = 0, bSize = 25;

int handleX = 200;
int handleY = 400;

// Other Variables
char option, txtMoves[5];
int moves = 0;

void Reset() {
  balls[0][1] = 1;
  balls[1][1] = 1;
  balls[2][1] = 1;
  balls[3][1] = 0;
  balls[4][1] = 2;
  balls[5][1] = 2;
  balls[6][1] = 2;

  moves = 0;
}

int main() {
  // to make sure generation of random numbers
  srand((unsigned) time(0));

  // Initialize Graphics
  int gd = DETECT, gm, err, tmp;
  initgraph( & gd, & gm, "C:\\tc\\bgi");

  setbkcolor(LIGHTGRAY);
  setlinestyle(1, 0, 3);
  while (1) { // for keeping game playing

    // Draws game board and moves/controls area
    DrawBoard();

    // Draw Balls and Hole
    DrawBalls();

    // Draw handle that navigate between balls to swap
    DrawHandles();

    // change direction if any of arrow keys is pressed
    if (kbhit()) { // checks if any key is pressed
      option = getch(); // catch input in options variable
      if (option == 'r') {
        Reset();
      }
      if (option == KEY_RIGHT) {
        if (handleX < 800) {
          handleX += 100; // update handle position
          bi++; // update ball index
        }
      } else if (option == KEY_LEFT) {
        if (handleX > 200) {
          handleX -= 100; //update handle position
          bi--; // update ball index
        }
      } else if (option == SPACEBAR) {
        if (balls[bi][1] != 0) {
          moves++;

          // In case of Black Ball ->
          if (balls[bi][1] == 1 && bi < 6) {
            if (balls[bi + 1][1] == 0) { // if hole is next to ball
              Swap(balls[bi][1], balls[bi + 1][1]);
            }
            if (balls[bi + 2][1] == 0) { // if hole is after a ball
              Swap(balls[bi][1], balls[bi + 2][1]);
            }
          }
          // In case of White Ball <-
          else if (balls[bi][1] == 2 && bi > 0) {
            if (balls[bi - 1][1] == 0) { // if hole is next to ball
              Swap(balls[bi][1], balls[bi - 1][1]);
            }
            if (balls[bi - 2][1] == 0) { //if hole is after a ball
              Swap(balls[bi][1], balls[bi - 2][1]);
            }
          }
        }

      } // end else if
    } // end kbhit

    // check if win condition is met
    if (WinCondition() == 1) {
      YouWin(); // display you win screen
      Reset(); // reset game
    }

    delay(40);
    cleardevice();
  }

  getch();
  closegraph();
}

void YouWin() {
  cleardevice(); // clear screen

  setcolor(WHITE);
  // Print Game Over Text
  settextstyle(4, 0, 9);
  outtextxy(300, 300, "You Win");

  settextstyle(4, 0, 2);
  outtextxy(500, 420, "Press any key to restart...");
  getch();
  moves = 0; // reset moves
}

void DrawBoard() {

  setcolor(BLACK);
  // draw board
  rectangle(0, 0, ScWidth - OpWidth, ScHeight);
  rectangle(ScWidth - OpWidth, 0, ScWidth, ScHeight);

  // draw title
  settextstyle(4, 0, 5);
  outtextxy(ScWidth - 330, 50, "Swap It");

  // print moves
  // itoa function converts number to character array
  settextstyle(4, 0, 9);
  if (moves < 10)
    outtextxy(ScWidth - 270, 250, itoa(moves, txtMoves, 10));
  else if (moves >= 10)
    outtextxy(ScWidth - 320, 250, itoa(moves, txtMoves, 10));

  settextstyle(4, 0, 1);
  outtextxy(ScWidth - 375, 500, "Controls: ");
  outtextxy(ScWidth - 375, 540, "- Arrow Keys to navigate");
  outtextxy(ScWidth - 375, 570, "- Spacebar to swap");
  outtextxy(ScWidth - 375, 600, "- R to Reset");
}

// Draws balls
void DrawBalls() {
  for (int i = 0; i < 7; i++) {
    setcolor(RED);
    circle(balls[i][0], 300, bSize);

    if (balls[i][1] == 0)
      setfillstyle(1, LIGHTGRAY);
    if (balls[i][1] == 1)
      setfillstyle(1, BLACK);
    if (balls[i][1] == 2)
      setfillstyle(1, WHITE);

    fillellipse(balls[i][0], 300, bSize, bSize);
  }
}

void DrawHandles() {
  setcolor(BLUE);
  circle(handleX, handleY, 10);
}

// swap balls
void Swap(int & x, int & y) {
  int tmpType = x;
  x = y;
  y = tmpType;
}

// check win condition
int WinCondition() {
  if (balls[0][1] == 2 && balls[1][1] == 2 && balls[2][1] == 2 && balls[3][1] == 0 &&
    balls[4][1] == 1 && balls[5][1] == 1 && balls[6][1] == 1) {
    return 1;
  }
  return 0;
}
