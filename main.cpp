#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>


using namespace std;

int board_size;
unsigned int winSize;
char oponent;



char getOpposite_sign(char sign) {
    if (sign == 'x') {
        return 'o';
    } else if (sign == 'o') {
        return 'x';
    }
}

void start_game(char& player_sign,vector<vector<char>> &tab_symb) {
    cout << "Wybierz swój pionek" << endl << "o lub x" << endl;
    cin >> player_sign;
    if (player_sign == 'X') player_sign = 'x';
    if (player_sign == 'O') player_sign = 'o';
    cout << "Wybierz wielkość kwadratowego pola do gry: " << endl;
    cin >> board_size;
    cout << "Wybierz ilość wygrywających znaków w rzędzie" << endl;
    cin >> winSize;
    while (winSize > board_size) {
        cout << "Wybierz większy rozmiar lub zredukuj liczbę znaków w rzędzie" << endl;
        cout << "Wybierz wielkość kwadratowego pola do gry: " << endl;
        cin >> board_size;
        cout << "Wybierz ilość wygrywających znaków w rzędzie" << endl;
        cin >> winSize;
    }
    tab_symb.resize(board_size, vector<char>(board_size, 'e'));
    oponent = getOpposite_sign(player_sign);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //ZNAJDYWANIE ZWYCIESTWA
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool left_diagonals(char player_sign,vector<vector<char>> &tab_symb) {                         //SPRAWDZANIE OBECNOSCI ZNAKÓW W LINII PRZEKATNEJ Z LEWEGO GORNEGO ROGU
    char opposite_sign = getOpposite_sign(player_sign);

    for (int b = 0; b < board_size; b++) {                   //pętla dla zejscia w dół
        int ok_1 = 0;                                           // licznik znaków w rzędzie dla przekątnych poniżej i włącznie z środkową przekątna
        int ok_2 = 0;                                           // licznik znaków w rzędzie do wygranej powyżej środkowej przekątnej
        for (int a = 0; a + b < board_size; a++) {                      // pętla chodzenia po kolumnach

            ///////////////////////////////////////////////////////////////////////////////
            ////////////      WŁĄCZNIE I POWYZEJ ŚRODKOWEJ PRZEKĄTNEJ      ///////////////

            if (tab_symb[a][a + b] == player_sign) {
                ok_1 += 1;
                if (ok_1 == winSize) {                       //sprawdzamy warunek za każdym nowym rzędem znakow
                    return true;
                }
            } else if (tab_symb[a][a + b] == 'e' || opposite_sign)
                ok_1 = 0;

            /////////////////////////////////////////////////////////////////////////////
            /////////////    PONIZEJ ŚRODKOWEJ PRZEKĄTNEJ   ////////////////////////////

            if (tab_symb[b + a][a] == player_sign) {
                ok_2 += 1;
                if (ok_2 == winSize) {
                    return true;
                }
            } else if (tab_symb[b + a][a] == 'e' || opposite_sign)
                ok_2 = 0;
        }
    }
    return false;
}



bool right_diagonals(char player_sign, vector<vector<char>> &tab_symb) {    //SPRZAWDZANIE PRZEKATNEJ Z GORNEGO PRAWEGO ROGU
    char opposite_sign = getOpposite_sign(player_sign);
    for (int a = 0; a < board_size - 1; a++) {

        int ok_1 = 0;
        int ok_2 = 0;
        int znak = -1;
        for (int b = 0; znak < (board_size - 1 - b - a); b++) {
            int x = board_size - 1 - b - a;
            if (tab_symb[b][x] == player_sign) {
                ok_1 += 1;
                if (ok_1 == winSize) return true;

            } else if (tab_symb[b][x] == 'e' || opposite_sign) ok_1 = 0;

            /////////////////////////////////////////////////////////

            int y = board_size - 1 - b;

            if (tab_symb[a + b][y] == player_sign) {
                ok_2 += 1;
                if (ok_2 == winSize) return true;

            } else if (tab_symb[a + b][y] == 'e' || opposite_sign) ok_2 = 0;
        }
    }
    return false;
}


bool rows_and_columns(char player_sign,vector<vector<char>> &tab_symb) {
    char opposite_sign = getOpposite_sign(player_sign);
    for (int a = 0; a < board_size; a++) {
        int ok_1 = 0; // dla kazdej kolumny/rzedu liczymy od nowa
        int ok_2 = 0;
        for (int b = 0; b < board_size; b++) {

            //////////////////////////////////////////////////////
            /////////       KOLUMNY     /////////////////////////

            if (tab_symb[b][a] == player_sign) {
                ok_1 += 1;
                if (ok_1 == winSize)
                    return true;
            } else if (tab_symb[b][a] == opposite_sign || 'e') {
                ok_1 = 0;
            }
            //////////////////////////////////////////////////////
            /////////       RZĘDY       //////////////////////////

            if (tab_symb[a][b] == player_sign) {
                ok_2 += 1;
                if (ok_2 == winSize)
                    return true;
            } else if (tab_symb[a][b] == opposite_sign || 'e')
                ok_2 = 0;
        }
    }
    return false;
}



bool isVictory(char player_sign, vector<vector<char>> &tab) {
    bool left_diag = left_diagonals(player_sign, tab);
    bool right_diag = right_diagonals(player_sign, tab);
    bool rows_n_columns = rows_and_columns(player_sign, tab);
    if ((right_diag || left_diag || rows_n_columns) == true)
        return true;
    else
        return false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//DZIAŁANIA NA GRZE
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void showBoard(vector<vector<char>>& tab) {
    cout << "\033[1;46m  \033[0m";
    for (int a = 1; a <= board_size; a++) {
        cout << "\033[1;46m   " << a << "\033[0m";
    }
    cout << "\033[1;46m    \033[0m";
    cout << endl;
    int znak = 65; // litera A
    for (int x = 0; x < board_size; x++) {
        cout << "\033[1;46m " << (char) znak << " \033[0m"; // rzutowanie i kolorowanie znaku wiersza
        znak++;
        for (int y = 0; y < board_size; y++) {
            cout << "|";
            if (tab[x][y] == 'x')
                cout << "\033[1;34m x \033[0m";
            if (tab[x][y] == 'o')
                cout << "\033[1;33m o \033[0m";
            if (tab[x][y] == 'e')
                cout << "   ";
        }
        cout << "|" << "\033[1;46m  \033[0m" << endl;
    }
    cout << "\033[1;46m  \033[0m";
    for (int a = 0; a < board_size; a++) {
        cout << "\033[1;46m    \033[0m";
    }
    cout << "\033[1;46m    \033[0m";
    cout << endl;
}


enum indicator{A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,R,S,T,U,V,W,X,Y,Z};

istream& operator >> (istream& input,indicator& tmp) {
    indicator tab[25] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, R, S, T, U, V, W, X, Y, Z};
    char znak='A';
    input >> znak; // POPRAWIAC WPISYWANE ZNAKI NA WIELKIE
    if (strchr("ABCDEFGHIJKLMNOPRSTUVWXYZ", znak))
        tmp = tab[znak - 'A'];
    return input;
}


void makeStep(char player_sign, vector<vector<char>> &tab_symb) {
    char opposite_sign = getOpposite_sign(player_sign);
    bool ok = 0;
    while (ok != 1) {
        cout << "Wybierz pole: " << endl;
        indicator x;
        int y;
        cin >> x;
        cin >> y;
        y -= 1;
        if ((x > board_size - 1) || (y > board_size - 1)) {
            showBoard(tab_symb);
            cout << "Wybrane pole jest poza polem gry" << endl;
            ok = 0;
        }
        if ((x <= board_size - 1) && (y <= board_size - 1)) {
            if (tab_symb[x][y] == 'e') {
                tab_symb[x][y] = player_sign;
                showBoard(tab_symb);
                ok = 1;
            } else if (tab_symb[x][y] == opposite_sign) {
                showBoard(tab_symb);
                cout << "Pole jest zajęte przez przeciwnika" << endl;
                ok = 0;
            } else {
                showBoard(tab_symb);
                cout << "Ruch w to miejsce jest niemożliwy" << endl;
                ok = 0;
            }
        }
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//OCENIANIE SYTUACJI NA PLANSZY
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// skanowanie POWYŻEJ I RAZEM Z ŚRODK. PRZEKĄTNĄ
int getLeftDiagGrade_1(const char& player_sign,const vector<vector<char>>& tab_symb) {// skanowanie POWYŻEJ I RAZEM Z ŚRODK. PRZEKĄTNĄ
    vector<int> marks;
    marks.reserve(board_size);
    char opposite_sign = getOpposite_sign(player_sign);

    for (int b = 0; b < board_size; b++) {
        int ok_1 = 0;                                                       // licznik znaków w rzędzie dla przekątnych poniżej i włącznie z środkową przekątna;                                                       // licznik znaków w rzędzie do wygranej powyżej środkowej przekątnej
        int tmp_1 = 0;
        for (int a = 0; a + b < board_size; a++) {

            if (tab_symb[a][a + b] == 'e') tmp_1 += 1;
            if (tab_symb[a][a + b] == player_sign) ok_1 += 1;
            if (tab_symb[a][a + b] == opposite_sign) {
                ok_1 = 0;
                tmp_1 = 0;
            }


            // co znak sprawdza stan, i natychmiast daje znać

            if (ok_1) {                                                                // jesli wystąpił znak gracza
                if (ok_1 + tmp_1 >= winSize) {
                    marks.push_back(winSize - ok_1);
                }                                                                      // sprawdź czy ilość pustych pól starczy do zwycięstwa
            }
            if (!ok_1) {
                if (tmp_1 >= winSize) marks.push_back(tmp_1 * 2);
            }
            // po sprawdzeniu całej linni sprawdza czy nie ma wgl miejsca
        }// jesli jest wystarczająca ilość miejsc do zwycięstwa załóż że jest to jakaś szansa na zwyciestwo
        if (tmp_1 + ok_1 < winSize) marks.push_back(winSize * 10);
        // jesli nie ma miejsca na zwycięstwo daj duża wagę by zminimalizować szanse wejscia w

    }

    sort(marks.begin(), marks.end());
    return marks[0];
}



// poniżej środkowej przekątnej
int getLeftDiagGrade_2(const char& player_sign,const vector<vector<char>>& tab_symb) {
    vector<int> marks;
    marks.reserve(board_size);
    char opposite_sign = getOpposite_sign(player_sign);

    for (int b = 0; b < board_size; b++) {                               //pętla dla zejscia w dół
        int ok_1 = 0;                                                       // licznik znaków w rzędzie dla przekątnych poniżej i włącznie z środkową przekątna
        int tmp_1 = 0;
        for (int a = 0; a + b < board_size; a++) {
            if (tab_symb[a + b][a] == 'e') tmp_1 += 1;
            if (tab_symb[a + b][a] == player_sign) ok_1 += 1;
            if (tab_symb[a + b][a] == opposite_sign) {
                ok_1 = 0;
                tmp_1 = 0;
            }


            // co linie sprawdzamy stan

            if (ok_1) {                                                             // jesli wystąpił znak gracza
                if (ok_1 + tmp_1 >= winSize) marks.push_back(winSize -
                                                             ok_1);                                               // sprawdź czy ilość pustych pól starczy do zwycięstwa
            }
            if (!ok_1) {                                                              //jesli nie ma znaku gracza
                if (tmp_1 >= winSize)
                    marks.push_back(tmp_1 * 2);
            }
        }// jesli jest wystarczająca ilość miejsc do zwycięstwa załóż że jest to jakaś szansa na zwyciestwo
        if (tmp_1 + ok_1 < winSize)
            marks.push_back(winSize *
                            10);                             // jesli nie ma miejsca na zwycięstwo daj duża wagę by zminimalizować szanse wejscia w

    }
    sort(marks.begin(), marks.end());
    return marks[0];
}


//WŁĄCZNIE I POWYZEJ ŚRODKOWEJ PRZEKĄTNEJ
int getRightDiagGrade_1(char& player_sign,vector<vector<char>>& tab_symb) {
    char opposite_sign = getOpposite_sign(player_sign);
    vector<int> marks;
    marks.reserve(board_size);
    for (int a = 0; a < board_size - 1; a++) {                         //pętla dla zejscia w dół
        int ok_1 = 0;
        int tmp_1 = 0;
        int x = 0;
        for (int b = 0; board_size - 1 - b - a > -1; b++) {

            x = board_size - 1 - b - a;


            if (tab_symb[b][x] == 'e')
                tmp_1 += 1;
            if (tab_symb[b][x] == player_sign)
                ok_1 += 1;
            if (tab_symb[b][x] == opposite_sign) {
                ok_1 = 0;
                tmp_1 = 0;
            }


        if (ok_1) {                                                           // jesli wystąpił znak gracza
            if (ok_1 + tmp_1 >= winSize)
                marks.push_back(winSize -
                                ok_1);                                            // sprawdź czy ilość pustych pól starczy do zwycięstwa
        }
        if (!ok_1) {
            if (tmp_1 >= winSize)
                marks.push_back(tmp_1 * 2);
        }                                                            // jesli jest wystarczająca ilość miejsc do zwycięstwa załóż że jest to jakaś szansa na zwyciestwo
        if (tmp_1 + ok_1 < winSize)
            marks.push_back(winSize * 10);
        // jesli nie ma miejsca na zwycięstwo daj duża wagę by zminimalizować szanse wejscia w
    }
    }
    sort(marks.begin(), marks.end());
    return marks[0];
}

//    PONIZEJ ŚRODKOWEJ PRZEKĄTNEJ
int getRightDiagGrade_2(char& player_sign, vector<vector<char>> tab_symb) {
    char opposite_sign = getOpposite_sign(player_sign);
    vector<int> marks;
    marks.reserve(board_size);

    for (int a = 0; a < board_size - 1; a++) {                   //pętla dla zejscia w dół
        int ok_1 = 0;
        int tmp_1 = 0;
        for (int b = 0; board_size - 1 - b - a > -1; b++) {
            int y = board_size - 1 - b;

            if (tab_symb[a + b][y] == 'e') tmp_1 += 1;
            if (tab_symb[a + b][y] == player_sign) ok_1 += 1;
            if (tab_symb[a + b][y] == opposite_sign) {
                ok_1 = 0;
                tmp_1 = 0;
            }


            if (ok_1) {                                                                // jesli wystąpił znak gracza
                if (ok_1 + tmp_1 >= winSize)
                    marks.push_back(winSize - ok_1);
            }

            if (!ok_1) {
                if (tmp_1 >= winSize)
                    marks.push_back(tmp_1 * 2);
            }
        }// jesli jest wystarczająca ilość miejsc do zwycięstwa załóż że jest to jakaś szansa na zwyciestwo
        if (tmp_1 + ok_1 < winSize)
            marks.push_back(winSize * 10);
        // jesli nie ma miejsca na zwycięstwo daj duża wagę by zminimalizować szanse wejscia w
    }
    sort(marks.begin(), marks.end());
    return marks[0];
}


int getRowsGrade(char& player_sign, vector<vector<char>> tab_symb) {
    char opposite_sign = getOpposite_sign(player_sign);
    vector<int> marks;
    marks.reserve(board_size);

    for (int a = 0; a < board_size; a++) {
        int ok_1 = 0;
        int tmp_1 = 0;
        for (int b = 0; b < board_size; b++) {
            if (tab_symb[a][b] == 'e') tmp_1 += 1;
            if (tab_symb[a][b] == player_sign)ok_1 += 1;
            if (tab_symb[a][b] == opposite_sign) {
                ok_1 = 0;
                tmp_1 = 0;
            }


            // co linie sprawdzamy stan

            if (ok_1) {                                                            // jesli wystąpił znak gracza
                if (ok_1 + tmp_1 >= winSize)
                    marks.push_back(winSize -
                                    ok_1);                                                                 // sprawdź czy ilość pustych pól starczy do zwycięstwa
            }
            if (!ok_1) {
                if (tmp_1 >= winSize)
                    marks.push_back(tmp_1 * 2);
            }
        }// jesli jest wystarczająca ilość miejsc do zwycięstwa załóż że jest to jakaś szansa na zwyciestwo
        if (tmp_1 + ok_1 < winSize)
            marks.push_back(winSize * 10);
        // jesli nie ma miejsca na zwycięstwo daj duża wagę by zminimalizować szanse wejscia w

    }
    sort(marks.begin(), marks.end());
    return marks[0];
}



int getColumnsGrade(char& player_sign, vector<vector<char>> tab_symb) {
    vector<int> marks;
    marks.reserve(board_size);
    char opposite_sign = getOpposite_sign(player_sign);

    for (int a = 0; a < board_size; a++) {
        int ok_1 = 0; // dla kazdej kolumny/rzedu liczymy od nowa
        int tmp_1 = 0;
        for (int b = 0; b < board_size; b++) {
            if (tab_symb[b][a] == 'e') tmp_1 += 1;
            if (tab_symb[b][a] == player_sign) ok_1 += 1;
            if (tab_symb[b][a] == opposite_sign) {
                ok_1 = 0;
                tmp_1 = 0;
            }


            // co linie sprawdzamy stan

            if (ok_1) {                                                                          // jesli wystąpił znak gracza
                if (ok_1 + tmp_1 >= winSize)
                    marks.push_back(winSize - ok_1);
            }

            if (!ok_1) {
                if (tmp_1 >= winSize)
                    marks.push_back(tmp_1 * 2);
            }
        }// jesli jest wystarczająca ilość miejsc do zwycięstwa załóż że jest to jakaś szansa na zwyciestwo
        if (tmp_1 + ok_1 < winSize)
            marks.push_back(winSize * 10);
        // jesli nie ma miejsca na zwycięstwo daj duża wagę by zminimalizować szanse wejscia w
    }
    sort(marks.begin(), marks.end());
    return marks[0];
}

int situationMark(char sign, vector<vector<char>> symulacja) {
     int l_g1 = getLeftDiagGrade_1(sign, symulacja);
     int l_g2 = getLeftDiagGrade_2(sign, symulacja);
     int r_g1 = getRightDiagGrade_1(sign, symulacja);
     int r_g2 = getRightDiagGrade_2(sign, symulacja);
     int rw_g = getRowsGrade(sign, symulacja);
     int cl_g = getColumnsGrade(sign, symulacja);
     int marks[6] = {l_g1, l_g2, r_g1, r_g2, rw_g, cl_g};
     sort(marks, marks + 6);
     return marks[0];
     
}


int minimax(char sign,vector<vector<char>> symulacja, int poziom) {

    showBoard(symulacja);
    char oponent_sign = getOpposite_sign(sign);
    if (poziom == 2) return 0;//situationMark(sign, symulacja);
    poziom += 1;
    for (int b = 0; b < board_size; b++) {
        for (int a = 0; a < board_size; a++) {
            if (symulacja[a][b] == 'e') {
                symulacja[a][b] = sign;
                cout << "OCENA: " << situationMark('x', symulacja)<<endl;//<<"  " <<sign<<endl<<endl<<endl;
                minimax(oponent_sign, symulacja, poziom);
                symulacja[a][b] = 'e';
            }
        }
    }
}




int main() {

    vector<vector<char>> tab_symb;
    char your_sign;
    start_game(your_sign, tab_symb);
    char oponent = getOpposite_sign(your_sign);
    bool winning = false;
    showBoard(tab_symb);
    while (!winning) {

        makeStep(your_sign, tab_symb);
        winning = isVictory(your_sign, tab_symb);
        cout << situationMark('x', tab_symb) << endl;
        if (isVictory(your_sign, tab_symb)) {
            cout << "\033[1;32m      Wygrałeś \033[0m" << endl;
            return 0;
        }
        // minimax(oponent,tab_symb,0);

        makeStep(oponent, tab_symb);
        winning = isVictory(oponent, tab_symb);
        cout << situationMark('x', tab_symb) << endl;
        if (isVictory(oponent, tab_symb)) {
            cout << "\033[1;31m     Przegrałeś \033[0m" << endl;
            return 0;
        }
    }
}
