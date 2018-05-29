#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <iomanip> 

using namespace std;
int size_of_table;
int winSize;
char oponent;
char human_sign;

char imie;

void pokaz(vector<vector<char>>tab_symb){
    for(int i=0;i<size_of_table;i++){
        for (int j=0;j<size_of_table;j++){
            cout<<tab_symb[i][j];
        }
        cout<<endl;
    }
    cout<<endl<<endl<<endl;
}

char getOpposite_sign(char sign) {
    if (sign == 'x') {
        return 'o';
    } else if (sign == 'o') {
        return 'x';
    }
}

void start_game(char& player_sign,vector<vector<char>> &tab_symb){
    cout << "Wybierz swój pionek" << endl << "o lub x" << endl;
    cin >> player_sign;
    cout << "Wybierz wielkość kwadratowego pola do gry: " << endl;
    cin >> size_of_table;
    cout << "Wybierz ilość wygrywających znaków w rzędzie" << endl;
    cin >> winSize;
    tab_symb.resize(size_of_table, vector<char>(size_of_table, 'e'));
    oponent=getOpposite_sign(player_sign);
}




bool left_diagonals(char player_sign,vector<vector<char>> &tab_symb) {                         //SPRAWDZANIE OBECNOSCI ZNAKÓW W LINII PRZEKATNEJ Z LEWEGO GORNEGO ROGU
    char opposite_sign = getOpposite_sign(player_sign);

    for (int b = 0; b < size_of_table; b++) {                   //pętla dla zejscia w dół
        int ok_1 = 0;                                           // licznik znaków w rzędzie dla przekątnych poniżej i włącznie z środkową przekątna
        int ok_2 = 0;                                           // licznik znaków w rzędzie do wygranej powyżej środkowej przekątnej
        for (int a = 0; a + b < size_of_table; a++) {                      // pętla chodzenia po kolumnach

            ///////////////////////////////////////////////////////////////////////////////
            ////////////      WŁĄCZNIE I POWYZEJ ŚRODKOWEJ PRZEKĄTNEJ      ///////////////

            if (tab_symb[a][a + b] == player_sign) {
                ok_1 += 1;
                if (ok_1 == winSize) {                       //sprawdzamy warunek za każdym nowym rzędem znakow
                    cout<<"przekatna z lewej powyzej"<<endl;
                    return true;
                }
            } else if (tab_symb[a][a + b] == 'e' || opposite_sign)
                ok_1 = 0;

            /////////////////////////////////////////////////////////////////////////////
            /////////////    PONIZEJ ŚRODKOWEJ PRZEKĄTNEJ   ////////////////////////////

            if (tab_symb[b + a][a] == player_sign) {
                ok_2 += 1;
                if (ok_2 == winSize){
                        cout<<"przekatna z lewej ponizej"<<endl;
                    return true;}
            } else if (tab_symb[b + a][a] == 'e' || opposite_sign)
                ok_2 = 0;
        }
    }
    return false;
}



bool right_diagonals(char player_sign, vector<vector<char>> &tab_symb) {    //SPRZAWDZANIE PRZEKATNEJ Z GORNEGO PRAWEGO ROGU
    char opposite_sign = getOpposite_sign(player_sign);
    for (int a = 0; a < size_of_table - 1; a++) {                   //pętla dla zejscia w dół
        int ok_1 = 0;                                           // licznik znaków w rzędzie dla przekątnych poniżej i włącznie z środkową przekątna
        int ok_2 = 0;
        for (int b = 0; size_of_table - 1 - b - a > -1; b++) {
            int x = size_of_table - 1 - b - a;
            ///////////////////////////////////////////////////////////////////////////////
            ////////////      WŁĄCZNIE I POWYZEJ ŚRODKOWEJ PRZEKĄTNEJ      ///////////////
            if (tab_symb[b][x] == player_sign) {
                ok_1 += 1;
                if (ok_1 == winSize)                      //sprawdzamy warunek za każdym nowym rzędem znakoW
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


bool rows_and_columns(char player_sign,vector<vector<char>> &tab_symb) {
    char opposite_sign = getOpposite_sign(player_sign);

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
                ok_2+=1;
                if (ok_2 == winSize)
                    return true;
            } else if (tab_symb[a][b] == opposite_sign || 'e')
                ok_2 = 0;
        }
    }
    return false;
}

bool isVictory(char player_sign, vector<vector<char>> &tab) {
    bool left_diag = left_diagonals(player_sign,tab);
    bool right_diag = right_diagonals(player_sign,tab);
    bool rows_n_columns = rows_and_columns(player_sign,tab);
    if ((right_diag || left_diag || rows_n_columns) == true)
        return true;
    else
        return false;
}


void showBoard(vector<vector<char>>& tab) {
    cout << "\033[1;46m  \033[0m";
    for (int a = 1; a <= size_of_table; a++) {
        cout << "\033[1;46m   " << a << "\033[0m";
    }
    cout << "\033[1;46m    \033[0m";
    cout << endl;
    int znak = 65; // litera A
    for (int x = 0; x < size_of_table; x++) {
        cout << "\033[1;46m " << (char) znak << " \033[0m"; // rzutowanie i kolorowanie znaku wiersza
        znak++;
        for (int y = 0; y < size_of_table; y++) {
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
    for (int a = 0; a < size_of_table; a++) {
        cout << "\033[1;46m    \033[0m";
    }
    cout << "\033[1;46m    \033[0m";
    cout << endl;
}

enum indicator{A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,R,S,T,U,V,W,X,Y,Z};

istream& operator >> (istream& input,indicator& tmp) {
    indicator tab[25] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, R, S, T, U, V, W, X, Y, Z};
    char znak='A';
    input >> znak;
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
        if ((x > size_of_table - 1)||(y>size_of_table-1)) {
            showBoard(tab_symb);
            cout << "Wybrane pole jest poza polem gry" << endl;
            ok = 0;
        }
        if ((x <= size_of_table - 1)&&(y<=size_of_table-1)) {
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
//musze miec funkcje ktora zwroci mi pola w ktore chce wejsc
//ta funkcja bedzie w sobie badała możliwe wybory
//gdy dojdzie do mozliwego końca drzewa zwroci mi wartosc o wygranej lub przegranej lub remisie lub wartosc oceny sytuacji jaka saistniala
//gdy bedzie szła z powrotem bedzie zbierać punkty tych zwroconych wartosci
//a funkcja oceniająca zwroci mi wartość dla danego ruchu i wyrzuci wspolrzedne ruchu dla którego
int ocenasytuacji(){}


int minimax(char sign,vector<vector<char>> &symulacja, int poziom) {
    poziom+=1;
    //  sign
    // chose the best
    // if oponent chose the worst

    int w,k;
    int vmax=0;
    for (int a = 0; a < size_of_table; a++) {
        for (int b = 0; b < size_of_table; ++b) {
            if (symulacja[a][b] == 'e') {
                symulacja[a][b] = sign;
                if((sign==oponent)&&(poziom==2)){
                    
                }
                if(sign==human_sign){
                    return

                }
                if((poziom<2)&&!isVictory(sign,symulacja)&&!isVictory(getOpposite_sign(sign),symulacja) vmax += symulacja(sign == 'o' ? 'x' : 'o', symulacja); // gdy skoncza sie poziomy lub zaitnieje zwyciestwo
                if (poziom == 2 || isVictory(sign, symulacja)) {
                    if (isVictory(sign, symulacja)) return 1;
                    sign == human_sign ? return ocenasytuacji(): return -ocenasytuacji();
                }
            }
        }
    }
}



int computerStep(char sign, vector<vector<char>> &tablica,int poziom) {
    vector<vector<char>> symulacja = tablica;
    if (poziom == 5) {
        return 0;
    }
    //tutaj ocena sytuacji i zwrot oceny
    if(isVictory(oponent,symulacja)){
        return  1;
    }
    //nizej symulacja
    int v=0;
    int vmax;
    int x,y;
    showBoard(symulacja);
    for (int a = 0; a < size_of_table; a++) {
        for (int b = 0; b < size_of_table; ++b) {
            if (symulacja[a][b] == 'e') {
                symulacja[a][b] = sign;
                vmax += computerStep(sign == 'o' ? 'x' : 'o', symulacja, poziom + 1);
                if(vmax>v){
                    x=a;
                    y=b;
                }
                symulacja[a][b] = 'e';
            }
        }//for
    }//for
            tablica[x][y]=sign;
}

int main() {
    vector<vector<char>> tab_symb;
    char your_sign;
    start_game(your_sign,tab_symb);
    char oponent = getOpposite_sign(your_sign);
    bool winning = false;
    // system("cls");
    showBoard(tab_symb);
    while (!winning) {
        makeStep(your_sign,tab_symb);
        winning = isVictory(your_sign,tab_symb);
        if (isVictory(your_sign,tab_symb)) {
            cout << "\033[1;32m      Wygrałeś \033[0m" << endl;
            return 0;
        }
        computerStep(oponent,tab_symb,0);
        //makeStep(oponent);
        //winning = isVictory(oponent);
        //if (isVictory(oponent)) {
        //  cout << "\033[1;31m     Przegrałeś \033[0m" << endl;
        // return 0;
    }
}
