#include <algorithm>
#include <ctime>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>
using namespace std;

class Player {
private:
  string name;
  bool isFirst = false;
  char symbol;

public:
  Player(string name) { this->name = name; }
  void setFirst(bool x) { isFirst = x; }
  bool getFirst() { return isFirst; }
  void setSymbol(char s) { this->symbol = s; }
  char getSymbol() { return this->symbol; }
};

class Game {
private:
  map<int, char> board = {
      {1, ' '}, {2, ' '}, {3, ' '}, {4, ' '}, {5, ' '},
      {6, ' '}, {7, ' '}, {8, ' '}, {9, ' '},
  };
  Player player{"Rando"};
  Player com{"Computer"};
  char winningSymbol = ' ';

public:
  Game() {
    srand(time(NULL));
    int x = rand() % 10 + 1;
    if (x % 2 == 0) {
      player.setFirst(true);
      com.setFirst(false);
      player.setSymbol('X');
      com.setSymbol('O');
    } else {
      player.setFirst(false);
      com.setFirst(true);
      player.setSymbol('O');
      com.setSymbol('X');
    }
  };

  void printBoard() {
    cout << endl << board[1] << '|' << board[2] << '|' << board[3] << endl;
    cout << "-+-+-";
    cout << endl << board[4] << '|' << board[5] << '|' << board[6] << endl;
    cout << "-+-+-";
    cout << endl << board[7] << '|' << board[8] << '|' << board[9] << endl;
  }
  void setWinner(char x) { this->winningSymbol = x; }
  int getWinner() {
    if (player.getSymbol() == winningSymbol) {
      return 1;
    } else
      return 0;
  }
  bool isEmpty(int pos) {
    if (board[pos] == ' ')
      return true;
    else
      return false;
  }
  bool isDraw() {
    if (board.find(' ') != board.end()) {
      return true;
    }
    return false;
  }
  bool isWin() {
    if (board[1] == board[2] and board[1] == board[3] and board[1] != ' ') {
      setWinner(board[1]);
      return true;
    } else if (board[4] == board[5] and board[4] == board[6] and
               board[4] != ' ') {
      setWinner(board[4]);
      return true;
    } else if (board[7] == board[8] and board[7] == board[9] and
               board[7] != ' ') {
      setWinner(board[7]);
      return true;
    } else if (board[1] == board[4] and board[1] == board[7] and
               board[1] != ' ') {
      setWinner(board[1]);
      return true;
    } else if (board[2] == board[5] and board[2] == board[8] and
               board[2] != ' ') {
      setWinner(board[2]);
      return true;
    } else if (board[3] == board[6] and board[3] == board[9] and
               board[3] != ' ') {
      setWinner(board[3]);
      return true;
    } else if (board[1] == board[5] and board[1] == board[9] and
               board[1] != ' ') {
      setWinner(board[1]);
      return true;
    } else if (board[7] == board[5] and board[7] == board[3] and
               board[7] != ' ') {
      setWinner(board[7]);
      return true;
    } else
      return false;
  }
  void insertMove(char symbol, int pos) {
    if (isEmpty(pos)) {
      board[pos] = symbol;
      printBoard();
      if (isDraw()) {
        cout << "Draw!" << endl;
        exit(2);
      }
      if (isWin()) {
        if (getWinner() == 1) {
          cout << "Rando wins!" << endl;
          exit(3);
        } else {
          cout << "Computer wins!" << endl;
          exit(3);
        }
      }
    } else {
      cout << "Someone played that already. Enter new position: " << endl;
      cin >> pos;
      insertMove(symbol, pos);
    }
  }
  void playerMove() {
    int pos;
    cout << "Enter position: " << endl;
    cin >> pos;
    insertMove(player.getSymbol(), pos);
  }
  void compMove() {
    int pos;
    cout << "Enter position for Comp: " << endl;
    cin >> pos;
    insertMove(com.getSymbol(), pos);
  }
  void startGame() {
    printBoard();
    do {
      if (player.getSymbol() == 'X') {
        playerMove();
        compMove();
      } else {
        compMove();
        playerMove();
      }
    } while (!isWin() && !isDraw());
  }
};

int main() {
  Game *g = new Game();
  g->startGame();
  delete g;
  return 0;
}