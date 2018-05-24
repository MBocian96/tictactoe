#include <iostream>
using namespace std;

char opposite_sign='o';
const int size_of_table=5;
char tab_symb[5][5]={'x','e','e','x','e',
                     'e','e','x','e','e',
                     'x','e','e','e','e',
                     'e','e','e','e','e',
                     'e','e','e','e','o'
                    };
int winSize=2;



bool left_diagonals(char player_sign) {

    for (int b = 0; b < size_of_table; b++) {                   //pętla dla zejscia w dół
        int ok_1 = 0;                                           // licznik znaków w rzędzie dla przekątnych poniżej i włącznie z środkową przekątna
        int ok_2 = 0;                                           // licznik znaków w rzędzie do wygranej powyżej środkowej przekątnej
         for (int a = 0; a+b<size_of_table; a++) {                      // pętla chodzenia po kolumnach
            ///////////////////////////////////////////////////////////////////////////////
            ////////////      WŁĄCZNIE I POWYZEJ ŚRODKOWEJ PRZEKĄTNEJ      ///////////////
            if (tab_symb[a][a+b] == player_sign) {
                ok_1 += 1;
                if (ok_1 == winSize) {                       //sprawdzamy warunek za każdym nowym rzędem znakow
                    return true;
                }
            } else if (tab_symb[a][a+b] == 'e' || opposite_sign) {
                ok_1 = 0;
            }
            /////////////////////////////////////////////////////////////////////////////
            /////////////    PONIZEJ ŚRODKOWEJ PRZEKĄTNEJ   ////////////////////////////
            if (tab_symb[b+a][a] == player_sign) {
                ok_2 += 1;
                if (ok_2 == winSize) {
                    return true;
                }
            } else if (tab_symb[b + a][a] == 'e'||opposite_sign) {
                ok_2 = 0;
            }
        }
    }
    return false;
}



bool right_diagonals(char player_sign) {
    bool tmp = false;                                 // zmienna potwierdzająca zwyciestwo
    int ok_1 = 0;                                     // licznik znaków w rzędzie dla przekątnych poniżej i włącznie z środkową przekątna
    int ok_2 = 0;                                      // licznik znaków w rzędzie do wygranej powyżej środkowej przekątnej

    for (int b = size_of_table; b > 0; b--) { //pętla dla zejscia w dół
        int t = 0;                                // zmienna ograniczająca długość przekątnej
        for (int a = size_of_table; t >= winSize; a--) {       // pętla chodzenia po kolumnach

            ///////////////////////////////////////////////////////////////////////////////
            ////////////      WŁĄCZNIE I PONIŻEJ ŚRODKOWEJ PRZEKĄTNEJ      ///////////////
            if (tab_symb[a][a + b] == player_sign) {
                ok_1 += 1;
                if (ok_1 == winSize) { //sprawdzamy warunek za każdym nowym rzędem znakow
                    return true;
                }
            } else if ((tab_symb[a][a + b] == 'e') || (tab_symb[a][a + b] == opposite_sign)) {
                ok_1 = 0;
            }

                /////////////////////////////////////////////////////////////////////////////
                /////////////    POWYŻEJ ŚRODKOWEJ PRZEKĄTNEJ   ////////////////////////////
            else if (tab_symb[b + a + 1][a] == player_sign) {
                ok_2 += 1;
                cout<<"{"<<b+a+1<<","<<a<<endl;
                if (ok_2 == winSize) {
                    cout<<"winSize"<<endl;
                    return true;
                }
            } else if ((tab_symb[b + a + 1][a] == 'e'||opposite_sign)) {
                ok_2 = 0;
            }
        }
    }
}

bool rows_and_columns(char player_sign) {

    for (int a = 0; a < size_of_table; a++) {
        int ok_1 = 0; // dla kazdej kolumny/rzedu liczymy od nowa
        int ok_2 = 0;
        for (int b = 0; b < size_of_table; b++) {

            //////////////////////////////////////////////////////
            /////////       KOLUMNY     /////////////////////////

            if (tab_symb[b][a] == player_sign) {
                ok_1 += 1;
                if (ok_1 == winSize) {
                    cout << "ok=winsize" << endl;
                    return true;
                }
            } else if (tab_symb[b][a] == opposite_sign || 'e') {
                ok_1 = 0;
            }
            //////////////////////////////////////////////////////
            /////////       RZĘDY       //////////////////////////

            if (tab_symb[a][b] == player_sign) {
                if (ok_2 == winSize)
                    return true;
            } else if (tab_symb[a][b] == opposite_sign || 'e') {
                ok_2 = 0;
            }
        }
    }
    return false;
}

bool isVictory(char player_sign) {
    bool left_diag = left_diagonals('x');
    bool right_diag = right_diagonals('x');
    bool row_and_column = rows_and_columns('x');
    if ((left_diag) == true)
        return true;
    else
        return false;
}



int main(){
    cout<<isVictory('x')<<endl;
}
