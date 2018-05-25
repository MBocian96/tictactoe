#include <iostream>
using namespace std;
const int size_of_table=5;
char tab_symb[5][5]={'x','e','e','e','e',
                     'x','e','x','e','e',
                     'x','e','e','e','e',
                     'e','e','e','e','e',
                     'e','e','e','e','o'
                    };
int winSize=2;

void  start_game(){
    cout<<"Wybierz wielkość kwadratowego pola do gry: "<<endl;
    cin>>size_of_table;
    cout<<"Wybierz wielkość znaków w rzędzie"<<endl;
    cin>>winSize;
    tab_symb[size_of_table][size_of_table]; // nadpisywanie wyjsciowej tablicy pustymi polami
    for(int i =0; i<size_of_table; i++){
        for(int j=0; j<size_of_table; i++){
            tab_symb[i][j]='e';
        }
    }

}


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
int t=1;
    for (int a = 0; a<size_of_table-1; a++) {                   //pętla dla zejscia w dół
        int ok_1 = 0;                                           // licznik znaków w rzędzie dla przekątnych poniżej i włącznie z środkową przekątna
        int ok_2 = 0;    t++;                                       // licznik znaków w rzędzie do wygranej powyżej środkowej przekątnej
        for (int b = 0; size_of_table-1-b-a>-1; b++) {
            ///////////////////////////////////////////////////////////////////////////////
            ////////////      WŁĄCZNIE I POWYZEJ ŚRODKOWEJ PRZEKĄTNEJ      ///////////////
            if (tab_symb[b][size_of_table-1-b-a] == player_sign) {
                ok_1 += 1;
                if (ok_1 == winSize) {                       //sprawdzamy warunek za każdym nowym rzędem znakow
                    return true;
                }
            } else if (tab_symb[b][size_of_table-1-b-a] == 'e' || opposite_sign) {
                ok_1 = 0;
            }
            /////////////////////////////////////////////////////////////////////////////
            /////////////    PONIZEJ ŚRODKOWEJ PRZEKĄTNEJ   ////////////////////////////
            cout<<"["<<a+b<<","<<size_of_table-1-b<<"]"<<endl;
            if (tab_symb[a+b][size_of_table-1-b] == player_sign) {
                ok_2 += 1;
                cout<<a+b<<","<<size_of_table-1-b<<endl;
                if (ok_2 == winSize) {
                    return true;
                }
            } else if (tab_symb[a+b][size_of_table-1-b] == 'e'||opposite_sign) {
                ok_2 = 0;
            }
        }
    }
    return false;
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
    if ((right_diag) == true)
        return true;
    else
        return false;
}



int main(){
    cout<<isVictory('x')<<endl;
}
