#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

class Board {
    private:
        int N;
        char **A;
        bool ok = true;
    public:
        Board() {};                             // konstruktor inicializacii
        Board(int x);                           // 
        void out();                             // output board 
        void out_all();                         // output board with attacked cages
        bool check(int x, int y);               // check field is free
        void put(int x, int y, bool player);    // putting horse at the board
        void move(string step);                 // release one move
        void game();                            // start games
        ~Board();
};

/*
. - empty
P - players horse
C - computers horse
p - cage, attaked by players horse
c - cage, attaked by computers horse
*/ 

Board::Board(int x) {
    N = x;
    A = new char *[N];
    for (int i = 0; i < N; i++) {
        A[i] = new char[N];
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = '.';
        }
    }
}

void Board::out() {
    cout << ' ' << ' ';
    for (int i = 0; i < N; i++) {
        cout << char('A' + i) << ' ';
    }
    cout << '\n';
    for (int i = 0; i < N; i++) {
        cout << N - i << ' ';
        for (int j = 0; j < N; j++) {
            if (A[i][j] == 'p' || A[i][j] == 'c') {
                cout << '.';
            } else {
                cout << A[i][j];
            }
            cout << ' ';
        }
        cout << N - i << '\n';                          // chisla sprava
    }
    cout << ' ' << ' ';
    for (int i = 0; i < N; i++) {
        cout << char('A' + i) << ' ';
    }
    cout << '\n' << '\n';
}

void Board::out_all() {
    cout << "Out all\n";
    cout << ' ' << ' ';
    for (int i = 0; i < N; i++) {
        cout << char('A' + i) << ' ';
    }
    cout << '\n';
    for (int i = 0; i < N; i++) {
        cout << N - i << ' ';
        for (int j = 0; j < N; j++) {
            cout << A[i][j] << ' ';
        }
        cout << N - i << '\n';
    }
    cout << ' ' << ' ';
    for (int i = 0; i < N; i++) {
        cout << char('A' + i) << ' ';
    }
    cout << '\n' << '\n';
}  

bool Board::check(int x, int y) {
    char t = A[x][y];
    return (t == '.' || t == 'p');
}

void Board::put(int x, int y, bool player) {
    if (player) {
        A[x][y] = 'P';
    } else {
        A[x][y] = 'C';
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if ((abs(x - i) == 2 && abs(y - j) == 1) || (abs(x - i) == 1 && abs(y - j) == 2)) {
                if (A[i][j] == '.') {
                    if (!player) {
                        A[i][j] = 'c';
                    }
                }
            }
        }
    }
} 

void Board::move(string step) {
    int x = step[0];
    if ('A' <= x && x < (char)('A' + N)) {
        x -= 'A'; 
    } else {
        x -= 'a';
    }
    int y = step[1] - '1';
    //cout << step << endl;
    //cout << x << ' ' << y << endl;
    int X = N - y - 1;
    int Y = x;
    //cout << X << ' ' << Y << endl;
    if (!check(X, Y)) {
        if (A[X][Y] == 'P') {
            cout << "This field is already occupied by your horse";
        } else if (A[X][Y] == 'C') {
            cout << "This field is already occupied by computers horse";
        } else if (A[X][Y] == 'c') {
            cout << "This field is under computers horse attack";
        }
        cout << '\n';
        ok = false;
        return;
    }
    put(X, Y, 1);
    out();
    
    put(X, N - Y - 1, 0);
    out();
    //out_all();
}

void Board::game() {
    do {
        string step;
        do {
            cout << "Input string in format: E2 / e2\n";
            getline(cin, step);
        } while (!(step.size() == 2 && 
        (('a' <= step[0] && step[0] < (char)('a' + N)) || 
        ('A' <= step[0] && step[0] < (char)('A' + N))) &&
        ('1' <= step[1] && step[1] < (char)('1' + N))
        ));
        move(step); 
    } while (ok);
}

Board::~Board() {
    for (int i = 0; i < N; i++) {
        delete [] A[i];
    }
    delete [] A;
}

int main(int argc, char* argv[]) {
    Board B(8);
    B.out();
    B.game();
    return 0;
}
