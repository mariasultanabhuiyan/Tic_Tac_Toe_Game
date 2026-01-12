#include <iostream>
using namespace std;

char board[3][3] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'}
};

char player1 = 'X';
char player2 = 'O';
int mode; // 1 = PvP, 2 = PvBot

void drawBoard() {
    cout << "\n";
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            cout << " " << board[i][j];
            if(j < 2) cout << " |";
        }
        cout << "\n";
        if(i < 2) cout << "---|---|---\n";
    }
    cout << "\n";
}

bool isFree(int r, int c) {
    return board[r][c] != 'X' && board[r][c] != 'O';
}

bool placeMark(int pos, char mark) {
    int r = (pos - 1) / 3;
    int c = (pos - 1) % 3;

    if(pos < 1 || pos > 9 || !isFree(r, c))
        return false;

    board[r][c] = mark;
    return true;
}

bool checkWin(char mark) {
    for(int i = 0; i < 3; i++) {
        if(board[i][0] == mark && board[i][1] == mark && board[i][2] == mark) return true;
        if(board[0][i] == mark && board[1][i] == mark && board[2][i] == mark) return true;
    }
    if(board[0][0] == mark && board[1][1] == mark && board[2][2] == mark) return true;
    if(board[0][2] == mark && board[1][1] == mark && board[2][0] == mark) return true;

    return false;
}

bool checkDraw() {
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(isFree(i, j)) return false;
    return true;
}

// SIMPLE BOT
void botMove() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(isFree(i, j)) {
                board[i][j] = player2;
                return;
            }
        }
    }
}

int main() {
    int move;
    char current = player1;

    cout << "Choose mode:\n";
    cout << "1. Player vs Player\n";
    cout << "2. Player vs Bot\n";
    cin >> mode;

    while(true) {
        drawBoard();

        if(mode == 2 && current == player2) {
            cout << "Bot is thinking...\n";
            botMove();
        } else {
            cout << "Player " << current << ", enter position (1-9): ";
            cin >> move;

            if(!placeMark(move, current)) {
                cout << "Invalid move. Try again.\n";
                continue;
            }
        }

        if(checkWin(current)) {
            drawBoard();
            if(mode == 2 && current == player2)
                cout << "Bot wins. Logic > luck.\n";
            else
                cout << "Player " << current << " wins!\n";
            break;
        }

        if(checkDraw()) {
            drawBoard();
            cout << "Game draw.\n";
            break;
        }

        current = (current == player1) ? player2 : player1;
    }

    return 0;
}
