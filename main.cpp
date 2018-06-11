#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>


using namespace std;

int board_size;
unsigned int winSize;
char oponent;
char player_sign;


char getOpposite_sign(char sign) {
    if (sign == 'x') {
        return 'o';
    } else if (sign == 'o') {
        return 'x';
    }
}

void start_game(vector<vector<char>> &tab_symb) {
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

bool isEmpty(vector<vector<char>> tab) { // return true if empty
    bool idx=1;
    for (int a = 0; a < board_size; a++) {
        for (int b = 0; b < board_size; b++) {
            if(tab[a][b]=='e') idx=0;
        }
    }
    return idx;
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
double getLeftDiagGrade_1(const char& player_sign, vector<vector<char>>& tab_symb) {// skanowanie POWYŻEJ I RAZEM Z ŚRODK. PRZEKĄTNĄ
    vector<double> marks;
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


            // co linie sprawdzamy stan
            if(isVictory(player_sign,tab_symb)){
                  marks.push_back(1);
            }
            if(isVictory(opposite_sign,tab_symb)){
                     marks.push_back(-1);
            }
            if (ok_1) {                                 // jesli wystąpił znak gracza
                if (ok_1 + tmp_1 >= winSize)
                    marks.push_back(1 - ((winSize - ok_1) * 0.1));
            }
            if (!ok_1) {                                // jesli jest wystarczająca ilość miejsc do zwycięstwa załóż że jest to jakaś szansa na zwyciestwo
                if (tmp_1 >= winSize)
                      marks.push_back(tmp_1 * 0.01);
            }
        }
        if (tmp_1 + ok_1 < winSize)
             marks.push_back(0.000000001);
        // jesli nie ma miejsca na zwycięstwo daj duża wagę by zminimalizować szanse wejscia w
    }
    sort(marks.begin(), marks.end());

    return marks.back(); // zwróc najwyższą wartość czyli najbardziej prawdopodbne zwycięstwo,, tzn z konca tablicy
}



// poniżej środkowej przekątnej
double getLeftDiagGrade_2(const char& player_sign, vector<vector<char>>& tab_symb) {
    vector<double> marks;
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
            if(isVictory(player_sign,tab_symb)){
                marks.push_back(1);
            }
            if(isVictory(opposite_sign,tab_symb)){
                marks.push_back(-1);
            }
            if (ok_1) {                                 // jesli wystąpił znak gracza
                if (ok_1 + tmp_1 >= winSize)
                    marks.push_back(1-((winSize - ok_1) * 0.1));
            }

            if (!ok_1) {                                // jesli jest wystarczająca ilość miejsc do zwycięstwa załóż że jest to jakaś szansa na zwyciestwo
                if (tmp_1 >= winSize)
                    marks.push_back(tmp_1 * 0.01);
            }
        }
        if (tmp_1 + ok_1 < winSize)
            marks.push_back(0.000000001);
        // jesli nie ma miejsca na zwycięstwo daj duża wagę by zminimalizować szanse wejscia w
    }
    sort(marks.begin(), marks.end());
    return marks.back(); // zwróc najwyższą wartość czyli najbardziej prawdopodbne zwycięstwo
}


//WŁĄCZNIE I POWYZEJ ŚRODKOWEJ PRZEKĄTNEJ
double getRightDiagGrade_1(char& player_sign,vector<vector<char>>& tab_symb) {
    char opposite_sign = getOpposite_sign(player_sign);
    vector<double> marks;
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

            // co linie sprawdzamy stan
            if(isVictory(player_sign,tab_symb)){
                marks.push_back(1);
            }
            if(isVictory(opposite_sign,tab_symb)){
                marks.push_back(-1);
            }
            if (ok_1) {                                 // jesli wystąpił znak gracza
                if (ok_1 + tmp_1 >= winSize)
                    marks.push_back(1-((winSize - ok_1) * 0.1));
            }

            if (!ok_1) {                                // jesli jest wystarczająca ilość miejsc do zwycięstwa załóż że jest to jakaś szansa na zwyciestwo
                if (tmp_1 >= winSize)
                    marks.push_back(tmp_1 * 0.01);
            }
        }
        if (tmp_1 + ok_1 < winSize)
            marks.push_back(0.000000001);
        // jesli nie ma miejsca na zwycięstwo daj duża wagę by zminimalizować szanse wejscia w
    }
    sort(marks.begin(), marks.end());
    return marks.back(); // zwróc najwyższą wartość czyli najbardziej prawdopodbne zwycięstwo
}

//    PONIZEJ ŚRODKOWEJ PRZEKĄTNEJ
double getRightDiagGrade_2(char& player_sign, vector<vector<char>> tab_symb) {
    char opposite_sign = getOpposite_sign(player_sign);
    vector<double> marks;
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

            // co linie sprawdzamy stan
            if(isVictory(player_sign,tab_symb)){
                marks.push_back(1);
            }
            if(isVictory(opposite_sign,tab_symb)){
                marks.push_back(-1);
            }
            if (ok_1) {                                 // jesli wystąpił znak gracza
                if (ok_1 + tmp_1 >= winSize)
                    marks.push_back((winSize - ok_1)*0.1);
            }

            if (!ok_1) {                                // jesli jest wystarczająca ilość miejsc do zwycięstwa załóż że jest to jakaś szansa na zwyciestwo
                if (tmp_1 >= winSize)
                    marks.push_back(1-((winSize - ok_1) * 0.1));
            }
        }
        if (tmp_1 + ok_1 < winSize)
            marks.push_back(0.000000001);
        // jesli nie ma miejsca na zwycięstwo daj duża wagę by zminimalizować szanse wejscia w
    }
    sort(marks.begin(), marks.end());
    return marks.back(); // zwróc najwyższą wartość czyli najbardziej prawdopodbne zwycięstwo
}


double getRowsGrade(char& player_sign, vector<vector<char>> tab_symb) {
    char opposite_sign = getOpposite_sign(player_sign);
    vector<double> marks;
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
            if (isVictory(player_sign, tab_symb)) {
                marks.push_back(1);

            }
            if (isVictory(opposite_sign, tab_symb)) {
                marks.push_back(-1);

            }
            if (ok_1) {                                 // jesli wystąpił znak gracza
                if (ok_1 + tmp_1 >= winSize) {
                    marks.push_back(1-((winSize - ok_1) * 0.1));
                }
            }

            if (!ok_1) {                                // jesli jest wystarczająca ilość miejsc do zwycięstwa załóż że jest to jakaś szansa na zwyciestwo
                if (tmp_1 >= winSize) {

                    marks.push_back(tmp_1 * 0.01);
                }
            }
        }
        if (tmp_1 + ok_1 < winSize) {
             marks.push_back(0.000000001);
        }
        // jesli nie ma miejsca na zwycięstwo daj duża wagę by zminimalizować szanse wejscia w
    }

    sort(marks.begin(), marks.end());
      return marks.back(); // zwróc najwyższą wartość czyli najbardziej prawdopodbne zwycięstwo
}



double getColumnsGrade(char& player_sign, vector<vector<char>> tab_symb) {
    vector<double> marks;
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

            if (isVictory(player_sign, tab_symb)) {
                marks.push_back(1);
            }
            if (isVictory(opposite_sign, tab_symb)) {
                marks.push_back(-1);
            }
            if (ok_1) {                                 // jesli wystąpił znak gracza i jest miejsce do grania
                if (ok_1 + tmp_1 >= winSize)
                    marks.push_back(1-((winSize - ok_1) * 0.1));
            }

            if (!ok_1) {                                // jesli jest wystarczająca ilość miejsc do zwycięstwa załóż że jest to jakaś szansa na zwyciestwo
                if (tmp_1 >= winSize)
                    marks.push_back(tmp_1 * 0.01);
            }
        }
        if (tmp_1 + ok_1 < winSize)
            marks.push_back(0.000000001);
        // jesli nie ma miejsca na zwycięstwo daj małą wage by zminimalizować szanse wejscia w
    }
    sort(marks.begin(), marks.end());
    return marks.back(); // zwróc najwyższą wartość czyli najbardziej prawdopodbne zwycięstwo
}

double situationMark(char sign, vector<vector<char>> symulacja) {
    double l_g1 = getLeftDiagGrade_1(sign, symulacja);
    double l_g2 = getLeftDiagGrade_2(sign, symulacja);
    double r_g1 = getRightDiagGrade_1(sign, symulacja);
    double r_g2 = getRightDiagGrade_2(sign, symulacja);
    double rw_g = getRowsGrade(sign, symulacja);
    double cl_g = getColumnsGrade(sign, symulacja);
   /* cout << "OCENY WYPISANE ZE ZMIENNYCH: " << endl;
    cout << "l_g1: " << l_g1 << endl;
    cout << "l_g2: " << l_g2 << endl;
    cout << "r_g2: " << r_g1 << endl;
    cout << "r_g2: " << r_g2 << endl;
    cout << "rw_g: " << rw_g << endl;
    cout << "cl_g2: " << cl_g << endl;
*/
    double marks[6] = {l_g1, l_g2, r_g1, r_g2, rw_g, cl_g};
    sort(marks, marks + 6);
  //  cout<<"POSORTOWANA TABLICA OCEN: "<<endl;
   // for(auto i:marks) cout<<i<<endl;
    //cout<<"OCENA ZWRACANA: "<<marks[5]<<endl;
    return marks[5];
}

class Situation {
public:
    double alfa;
    double beta;
    int w;
    int k;
    double mark;

    Situation() {
        w = 1;
        alfa=-999999;
        beta=999999;
        k = 1;
        mark = 0;
    }

    Situation(int a, int b, double c,double d, double e) {
        w = a;
        k = b;
        mark = c;
        alfa = d;
        beta = e;
    }

    Situation(const Situation &C
    ) : w(C.w), k(C.k), mark(C.mark){}
    ~Situation() {}
    Situation operator = (const Situation & E){
        this->w=E.w;
        this->k=E.k;
        this->mark=E.mark;
        this->alfa=E.alfa;
        this->beta=E.beta;
    }
};

Situation minimax(char sign,vector<vector<char>> symulacja, int poziom,double& alfa, double& beta,double V) {

    char oponent_sign = getOpposite_sign(sign);

    if (isEmpty(symulacja)) {
        Situation tmp;
        tmp.mark = situationMark(oponent, symulacja);
        return tmp;
    }

    if (poziom == 6) {
        Situation tmp;
        tmp.mark = situationMark(oponent, symulacja);
        return tmp;
        }

    Situation val;
    Situation var;
    double vmax = winSize * 10000;
    double vmin = 0;
    //cout<<"PRZED PĘTLAMI "<<endl;
    for (int a = 0; a < board_size; a++) {
        for (int b = 0; b < board_size; b++) {
            if (symulacja[a][b] == 'e') {
                symulacja[a][b] = sign;
                // showBoard(symulacja);
                var = minimax(oponent_sign, symulacja, ++poziom, alfa, beta, V);
                //    cout<<val.mark<<endl;
//minimax & alfabeta
                if (sign == oponent) { // maximiser, computer

                    ///////// alfa beta pruninng
                    // bedziemy przerywać pętle lub nie w zależności od załóżeń algorytmu
                    // warunki algorytmu sprawdzane na poczatku i albo jedziemy dalej albo nie
/*
                        if (V > beta) {
                            cout << "PRUNNING" << sign << endl;
                            break;
                        }
                        if (var.mark > V) {
                            if (var.mark > alfa) alfa = var.mark;
                            V = alfa;
                        }

*/
                    if (var.mark > vmin) {
                        vmin = var.mark;
                        val.k = a;
                        val.w = b;
                        val.mark = vmin;

                    }
                }

                if (sign == player_sign) { // minimiser, human player
                    ////////alfa beta prunning
                    /*
                            if (V < beta) {
                                cout << "PRUNNING" << sign << endl;
                                break;
                            }
                            if (B < alfa) {
                                cout << "PRUNNING" << sign << endl;
                                break;
                            }
                            if (var.mark < V) {
                                beta = var.mark;
                                V = beta;
                            }
    */

                    if (var.mark < vmax) { // sprawdzanie który węzeł dał najlepsze prawdopodobienstwo wygranej
                        vmax = var.mark;
                        val.k = a;
                        val.w = b;
                        val.mark = vmax;
                    }
                }

                symulacja[a][b] = 'e';
            }
        }
    }
    return val;
}


void computerMakeStep(Situation& x, vector<vector<char>> &tab_symb){
    tab_symb[x.k][x.w]=oponent;
}


int main() {
    Situation var;
    vector<vector<char>> tab_symb;
    start_game(tab_symb);
    char your_sign = player_sign;
    char oponent = getOpposite_sign(your_sign);
    bool winning = false;
    showBoard(tab_symb);
    double infinity = 9999999;
    double minus_infinity = -infinity;
    while (!winning) {

        makeStep(your_sign, tab_symb);
        winning = isVictory(your_sign, tab_symb);
        cout << "situationMark(): " << situationMark('x', tab_symb) << endl << "::::::::::::::::::::::::::::::" << endl;
        if (isVictory(your_sign, tab_symb)) {
            cout << "\033[1;32m      Wygrałeś \033[0m" << endl;
            return 0;
        }
        /////////// znak, ,stan gry, poziom, alfa,      beta,       V
        var=minimax(oponent,tab_symb,0,minus_infinity,infinity,minus_infinity);
        computerMakeStep(var,tab_symb);
        //makeStep(oponent, tab_symb);
        showBoard(tab_symb);
        winning = isVictory(oponent, tab_symb);
        if (isVictory(oponent, tab_symb)) {
            cout << "\033[1;31m     Przegrałeś \033[0m" << endl;
            return 0;
        }
    }
}
