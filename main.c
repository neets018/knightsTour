#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

//set size of the board for the tour
#define boardSize 8

bool board[boardSize][boardSize] = {0};
unsigned boardSolve [boardSize][boardSize] = {0};
unsigned furthestMove = 0;

//possible moves
const int movesX[8] = {2, 1, -1, -2, -2, -1, 1, 2};
const int movesY[8] = {1, 2, 2, 1, -1, -2, -2, -1};

//function declarations
void printBoard();

void movePriority();

int rngMove(int y, int x, unsigned itt);

int bruteForce(int y, int x, unsigned itt);

int main(){
  //choose which version of the tour to run
  int userChoice;
  printf("Which tour would you like to take?\n1: random tour\n2: brute force tour full board (very slow for boards bigger than 5)\n3: brute force only from top left corner\n");
  scanf("%d",&userChoice);
  switch(userChoice){
  //make a nights tour board where each move is random
    case 1:
      srand(time(NULL));
      for(int y = 0; y < boardSize; y++){
        for(int x = 0; x < boardSize; x++){
          furthestMove = 0;
          board[y][x] = 1;
          rngMove(y,x,1);
          printf("%u ", furthestMove);
          memset(board, 0, sizeof board);
          memset(boardSolve, 0, sizeof boardSolve);
        }
        printf("\n");
      }
      break;
  //make a nights tour board where it brute forces a solution picking the same sequence of moves for each recursion
    case 2:
      for(int y = 0; y < boardSize; y++){
        for(int x = 0; x < boardSize; x++){
          furthestMove = 0;
          board[y][x] = 1;
          bruteForce(y,x,1);
          printf("%d ", furthestMove);
          memset(board, 0, sizeof board);
          memset(boardSolve, 0, sizeof boardSolve);
        }
        printf("\n");
      }
      break;
  //does the nights tour brute force starting the top left and prints the move sequence
    case 3:
      bruteForce(0,0,1);
      printBoard();
      break;
    default:
        printf("Run program again and write 1, 2 or 3\n");
  }
  return 0;
}

void printBoard(){
  printf("\n");
  for (int y = 0; y < boardSize; y++) {
    for (int x = 0; x < boardSize; x++) {
      printf("%d ", boardSolve[y][x]);   //print tour
      // printf("%d ", board[i][j]);     //print state
    }
    printf("\n");
  }
}

int rngMove(int y, int x, unsigned itt){
  // mark current square in solution and update furthest
  boardSolve[y][x] = itt;
  furthestMove = itt;

  int moveIndex = rand() % 8;
  for (int i = 0; i < 8; i++) {
    moveIndex--;
    if (moveIndex < 0){
      moveIndex = 7;
    }
    int localX = x + movesX[moveIndex];
    int localY = y + movesY[moveIndex];

    if (localX >= 0 && localX < boardSize && localY >= 0 && localY < boardSize && board[localY][localX] == 0) {
      board[localY][localX] = 1;
      rngMove(localY, localX, itt + 1);
      break;
    }
  }
  return 0;
}

int bruteForce(int y, int x, unsigned itt){
  // mark current square in solution and update furthest
  boardSolve[y][x] = itt;
  if (itt > furthestMove) {
    furthestMove = itt;
  }

  // If this is the last move (full tour), print and return success
  if (itt == boardSize * boardSize) {
    return 1; // success
  }

  for (int i = 0; i < 8; i++) {
    int localX = x + movesX[i];
    int localY = y + movesY[i];

    if (localX >= 0 && localX < boardSize && localY >= 0 && localY < boardSize && board[localY][localX] == 0) {
      // mark and recurse
      board[localY][localX] = 1;
      int found = bruteForce(localY, localX, itt + 1);
      if (found) {
        return 1; // propagate success
      }
      // backtrack: unmark visited and clear solution number
      board[localY][localX] = 0;
      boardSolve[localY][localX] = 0;
    }
  }
  return 0;
}
