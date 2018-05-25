#include <iostream>
using namespace std;
int size_of_table=5;
char tab_symb[5][5]={'e','e','e','e','e',
                     'e','e','e','e','e',
                     'e','e','e','e','e',
                     'e','e','e','e','e',
                     'e','e','e','e','e'
                    };
int winSize=2;
char opposite_sign;
char player_sign='x';

char opposite_sign_function(char sign) {
    if (sign == 'x') {
        return 'o';
    } else if (sign == 'o') {
        return 'x';
    }
}

void  start_game() {
    char sign;
    cout << "Wybierz swój pionek" << endl << "o lub x" << endl;
    cin >> player_sign;
    opposite_sign = opposite_sign_function(sign);
    cout << "Wybierz wielkość kwadratowego pola do gry: " << endl;
    cin >> size_of_table;
    cout << "Wybierz ilość wygrywających znaków w rzędzie" << endl;
    cin >> winSize;
   tab_symb[size_of_table][size_of_table]; // nadpisywanie wyjsciowej tablicy pustymi polami
    for (int i = 0; i < size_of_table; i++) {
        for (int j = 0; j < size_of_table; j++) {
           tab_symb[i][j] = 'e';
        }
    }
}




bool left_diagonals() {                         //SPRAWDZANIE OBECNOSCI ZNAKÓW W LINII PRZEKATNEJ Z LEWEGO GORNEGO ROGU

    for (int b = 0; b<size_of_table; b++) {                   //pętla dla zejscia w dół
        int ok_1 = 0;                                           // licznik znaków w rzędzie dla przekątnych poniżej i włącznie z środkową przekątna
        int ok_2 = 0;                                           // licznik znaków w rzędzie do wygranej powyżej środkowej przekątnej
        for (int a = 0; a+b< size_of_table; a++) {                      // pętla chodzenia po kolumnach

            ///////////////////////////////////////////////////////////////////////////////
            ////////////      WŁĄCZNIE I POWYZEJ ŚRODKOWEJ PRZEKĄTNEJ      ///////////////

            if (tab_symb[a][a + b] == player_sign) {
                ok_1 += 1;
                if (ok_1 == winSize){                       //sprawdzamy warunek za każdym nowym rzędem znakow
                    return true;
                }
            } else if (tab_symb[a][a + b] == 'e' || opposite_sign)
                ok_1 = 0;

            /////////////////////////////////////////////////////////////////////////////
            /////////////    PONIZEJ ŚRODKOWEJ PRZEKĄTNEJ   ////////////////////////////

            if (tab_symb[b + a][a] == player_sign) {
                ok_2 += 1;
                if (ok_2 == winSize)
                    return true;
            } else if (tab_symb[b + a][a] == 'e' || opposite_sign)
                ok_2 = 0;
        }
    }
    return false;
}



bool right_diagonals() {    //SPRZAWDZANIE PRZEKATNEJ Z GORNEGO PRAWEGO ROGU
    int t = 1;
    for (int a = 0; a < size_of_table - 1; a++) {                   //pętla dla zejscia w dół
        int ok_1 = 0;                                           // licznik znaków w rzędzie dla przekątnych poniżej i włącznie z środkową przekątna
        int ok_2 = 0;
        t++;                                       // licznik znaków w rzędzie do wygranej powyżej środkowej przekątnej
        for (int b = 0; size_of_table - 1 - b - a > -1; b++) {
            int x = size_of_table - 1 - b - a;
            ///////////////////////////////////////////////////////////////////////////////
            ////////////      WŁĄCZNIE I POWYZEJ ŚRODKOWEJ PRZEKĄTNEJ      ///////////////
            if (tab_symb[b][x] == player_sign) {
                ok_1 += 1;
                if (ok_1 == winSize)                      //sprawdzamy warunek za każdym nowym rzędem znakow
                    return true;
            } else if (tab_symb[b][x] == 'e' || opposite_sign)
                ok_1 = 0;

            /////////////////////////////////////////////////////////////////////////////
            /////////////    PONIZEJ ŚRODKOWEJ PRZEKĄTNEJ   ////////////////////////////
            int y = size_of_table - 1 - b;
            if (tab_symb[a + b][y] == player_sign) {
                ok_2 += 1;
                if (ok_2 == winSize)
                    return true;

            } else if (tab_symb[a + b][y] == 'e' || opposite_sign)
                ok_2 = 0;
        }
    }
    return false;
}


bool rows_and_columns() {
    for (int a = 0; a < size_of_table; a++) {
        int ok_1 = 0; // dla kazdej kolumny/rzedu liczymy od nowa
        int ok_2 = 0;
        for (int b = 0; b < size_of_table; b++) {

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
                if (ok_2 == winSize)
                    return true;
            } else if (tab_symb[a][b] == opposite_sign || 'e')
                ok_2 = 0;
        }
    }
    return false;
}

bool isVictory() {
    bool left_diag = left_diagonals();
    bool right_diag = right_diagonals();
    bool rows_n_columns = rows_and_columns();
    if ((right_diag||left_diag||rows_n_columns) == true)
        return true;
    else
        return false;
}

void showBoard() {
    cout<<"\033[1;46m  \033[0m";
    for(int a=0;a<size_of_table;a++) {
        cout<<"\033[1;46m   "<<a<<"\033[0m";
        }
    cout<<"\033[1;46m    \033[0m";
    cout<<endl;
    int znak=65; // litera A
    for (int x = 0; x < size_of_table; x++) {
        cout<<"\033[1;46m "<<(char)znak<<" \033[0m"; // rzutowanie i kolorowanie znaku wiersza
        znak++;
        for (int y = 0; y < size_of_table; y++) {
            cout << "|";
            if(tab_symb[x][y]=='x')
                cout<<"\033[1;34m x \033[0m";
            if(tab_symb[x][y]=='o')
                cout<<"\033[1;33m o \033[0m";
            if(tab_symb[x][y]=='e')
            cout<<"   ";
        }
        cout << "|" <<"\033[1;46m  \033[0m"<<endl;
    }
    cout<<"\033[1;46m                          \033[0m"<<endl;
}
enum indicator{a=0,b,c,d};//,E,F,G,H,I,J,K,L,M,N,O,P,R,S,T,U,V,W,X,Y,Z};
indicator xz;
istream& operator >> (istream& in,char tmp){
    indicator a;
    in>>tmp;
    tmp=a;
    return in;
}

void makeStep(char sign) {
    bool ok = 0;
    while (ok != 1) {
        cout << "Wybierz pole: " << endl;
        int y;
        int x;
        cin >> xz;
        cin >> y;
        x-=1;
        y-=1;
        if((x||y)>size_of_table-1){
            showBoard();
            cout<<"Wybrane pole jest poza polem gry"<<endl;
            ok=0;
        }
        else if (tab_symb[x][y] == 'e') {
            tab_symb[x][y] = sign;
            ok = 1;
        }else if (tab_symb[x][y] == opposite_sign){
            showBoard();
            cout<<"Pole jest zajęte przez przeciwnika"<<endl;
            ok=0;
        }
        else {
            showBoard();
            cout << "Ruch w to miejsce jest niemożliwy" << endl;
            ok = 0;
        }
    }
}



int main() {
    start_game();
    while (!isVictory()) {
        showBoard();
        makeStep('x');
        showBoard();
        makeStep('o');
    }
}