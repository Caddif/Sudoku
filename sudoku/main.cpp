#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;

int var;
bool win = 0;

class Grid
{
private:
    int Sudoku[9][9];
    char vertical = 179;
    char cross = 196;
    char mid = 197;
    int NumOfMids;
public:
    void TopScale();
    void FullGrid();
    void menu();
    friend class Player;
    void show()
    {
        TopScale();
        FullGrid();
    }
    Grid()
    {
        int Tab[9][9]={{5,0,1,0,7,2,9,8,0},
                       {0,2,0,5,4,0,0,0,0},
                       {0,0,9,0,0,1,0,5,0},
                       {9,6,0,0,0,0,0,7,0},
                       {0,0,0,7,0,3,0,2,9},
                       {0,0,4,9,0,8,0,0,1},
                       {0,1,0,3,0,0,7,0,0},
                       {0,9,0,0,5,0,8,0,2},
                       {0,0,3,0,0,4,0,0,6}};
        for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 9; j++)
            {
                Sudoku[i][j] = Tab[i][j];
            }
        }
    }
};

class Player : public Grid
{
private:
    int x,y;
public:
    void ValueInput();
    void CheckValue();
    void CheckVictory();
    void save(const char * file);
    void load(const char * file);
    Player() : Grid()
    {
        x=0;
        y=0;
    }
};


int main()
{

    Player P;
    P.menu();
    system("cls");
    if (var == 1)
    {
        do
        {
            P.show();
            P.ValueInput();
            system("cls");
            P.CheckValue();
            P.CheckVictory();
            P.save("save.txt");
        }while (win == 0);
    }
    else if (var == 2)
    {
        P.load("save.txt");
        do
        {
            P.show();
            P.ValueInput();
            system("cls");
            P.CheckValue();
            P.CheckVictory();
            P.save("save.txt");
        }while (win == 0);
    }
    else if (var == 3) return 0;
    P.show();

}


void Grid::TopScale()
{
    cout << "   ";
    for(int i=0;i<9;i++)
    {
        if (i==2||i==5)
        {
            cout << " " << i+1 << "  ";
        }
        else
        {
            cout << " " << i+1 << " ";
        }
    }
    cout << endl << endl;
}

void Grid::FullGrid()
{
    NumOfMids = 0;
    for(int i=0;i<9;i++)
    {
        cout << i+1 << "  ";
       for(int j=0;j<3;j++)
       {
           if (Sudoku[NumOfMids][j]!=0) cout << " " << Sudoku[NumOfMids][j] << " ";
           else cout << "   ";
       }
       cout << vertical;
       for(int j=0;j<3;j++)
       {
           if (Sudoku[NumOfMids][j+3]!=0) cout << " " << Sudoku[NumOfMids][j+3] << " ";
           else cout << "   ";
       }
       cout << vertical;
       for(int j=0;j<3;j++)
       {
           if (Sudoku[NumOfMids][j+6]!=0) cout << " " << Sudoku[NumOfMids][j+6] << " ";
           else cout << "   ";
       }
    NumOfMids++;
    cout << endl;
    if (NumOfMids == 3 || NumOfMids == 6)
    {
        cout << "   ";
        for(int i=0;i<3;i++)
        {
           for(int j=0;j<9;j++)
           {
               cout << cross;
           }
           if(i!=2) cout << mid;
        }
    cout << endl;
    }
    }
    cout << endl;
}

void Player::ValueInput()
{
    do
    {
        cout << "Please enter vertical coordinate: ";
        cin >> x;
    }while (x < 0 || x > 9);

    do
    {
        cout << "Please enter horizontal coordinate: ";
        cin >> y;
    }while (y < 0 || y > 9);

    do
    {
        cout << "Please enter the value: ";
        cin >> Sudoku [x-1][y-1];
    }while (Sudoku [x-1][y-1] < 0 || Sudoku [x-1][y-1] > 9);
}

void Player::CheckValue()
{
    int Check1 = 0, Check2 = 0, Check3 = 0;
    for(int i=0; i<9; i++)
    {
        if(Sudoku [x-1][i] == Sudoku [x-1][y-1] && y-1 != i)
        {
            cout << "illegal move" << endl <<endl;
            Check1 = 1;
            break;
        }
    }
    if (Check1 == 0)
    {
        for(int i=0; i<9; i++)
        {
            if(Sudoku [i][y-1] == Sudoku [x-1][y-1] && x-1 != i)
            {
                cout << "illegal move" << endl << endl;
                Check2 = 1;
                break;
            }
        }
    }
    if (Check1 == 0 && Check2 == 0)
    {
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(Sudoku [i][j] == Sudoku [x-1][y-1] && x-1 != i && y-1 != j && x<=3 && y<=3)
            {
                cout << "illegal move" << endl << endl;
                Check3 = 1;
                break;
            }
            else if(Sudoku [i+3][j] == Sudoku [x-1][y-1] && x-1 != i+3 && y-1 != j && x>3 && x<=6 && y<=3)
            {
                cout << "illegal move" << endl << endl;
                Check3 = 1;
                break;
            }
            else if(Sudoku [i+6][j] == Sudoku [x-1][y-1] && x-1 != i+6 && y-1 != j && x>6 && x<=9 && y<=3)
            {
                cout << "illegal move" << endl << endl;
                Check3 = 1;
                break;
            }
            else if(Sudoku [i][j+3] == Sudoku [x-1][y-1] && x-1 != i && y-1 != j+3 && x<=3 && y>3 && y<=6)
            {
                cout << "illegal move" << endl << endl;
                Check3 = 1;
                break;
            }
            else if(Sudoku [i+3][j+3] == Sudoku [x-1][y-1] && x-1 != i+3 && y-1 != j+3 && x>3 && x<=6 && y>3&& y<=6)
            {
                cout << "illegal move" << endl << endl;
                Check3 = 1;
                break;
            }
            else if(Sudoku [i+6][j+3] == Sudoku [x-1][y-1] && x-1 != i+6 && y-1 != j+3 && x>6 && x<=9 && y>3 && y<=6)
            {
                cout << "illegal move" << endl << endl;
                Check3 = 1;
                break;
            }
            else if(Sudoku [i][j+6] == Sudoku [x-1][y-1] && x-1 != i && y-1 != j+6 && x<=3 && y>6 && y<=9)
            {
                cout << "illegal move" << endl << endl;
                Check3 = 1;
                break;
            }
            else if(Sudoku [i+3][j+6] == Sudoku [x-1][y-1] && x-1 != i+3 && y-1 != j+6 && x>3 && x<=6 && y>6 && y<=9)
            {
                cout << "illegal move" << endl << endl;
                Check3 = 1;
                break;
            }
            else if(Sudoku [i+6][j+6] == Sudoku [x-1][y-1] && x-1 != i+6 && y-1 != j+6 && x>6 && x<=9 && y>6 && y<=9)
            {
                cout << "illegal move" << endl << endl;
                Check3 = 1;
                break;
            }
        if (Check3 != 0) break;
        }
    if (Check3 != 0) break;
    }
    }
    if(Check1 != 0 || Check2 != 0 || Check3 != 0)
        Sudoku [x-1][y-1] = 0;
}

void Player::CheckVictory()
{
    int flag = 0;
    for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 9; j++)
            {
                if (Sudoku [i][j] == 0) flag++;
            }
        }
    if(flag == 0)
    {
        win = true;
        cout << "Congratulations you solved the puzzle!!" << endl << endl;
    }
}

void Grid::menu()
{
    cout << "   Welcome to Sudoku game!" << endl << endl;
    cout << "Please choose your action:" << endl;
    cout << "1) new game" << endl << "2) load game" << endl << "3) exit" << endl;
    cin >>  var;
    while (var != 1 && var != 2 && var != 3)
    {
        cout << "wrong value input, try again" << endl;
        cin >> var;
    }
}

void Player::save(const char * file)
{
    fstream fin;
    fin.open(file, ios::out);
    if(fin.is_open())
    {
        fin.write((char *) this, sizeof(Player));
        fin.close();
    }
    else
    {
        cout << "ERROR: File cannot be found";
        exit(EXIT_FAILURE);
    }
}

void Player::load(const char * file)
{
    fstream fout;
    fout.open(file, ios::in);
    if(fout.is_open())
    {
        Player P;
        fout.read((char *) & P, sizeof(P));
        *this = P;
        fout.close();
    }
    else
    {
        cout << "ERROR: File cannot be found";
        exit(EXIT_FAILURE);
    }
}
