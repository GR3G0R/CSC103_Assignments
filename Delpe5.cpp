//Gregory Delpe
//Assignment #5: Sudoku Initializer

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <chrono>

using namespace std;

class SudokuField {
    vector<vector<char> > m_map;
    vector<int> m_list;
public:
    vector<char> column = {'A','B','C','D','E','F','G','H','I'};  //Column mapping vecor
    vector<char> row = {'P','Q','R','S','T','U','V','W','X'};  //Row mapping vector
    SudokuField() {  //SudokuField constructor intializes verified 9X9 sudoku board
        vector<char> temp = {'2','3','4','8','9','1','5','6','7'}; m_map.push_back(temp);
        vector<char> temp1 = {'5','6','7','2','3','4','8','9','1'}; m_map.push_back(temp1);
        vector<char> temp2 = {'8','9','1','5','6','7','2','3','4'}; m_map.push_back(temp2);
        vector<char> temp3 = {'3','4','5','9','1','2','6','7','8'}; m_map.push_back(temp3);
        vector<char> temp4 = {'6','7','8','3','4','5','9','1','2'}; m_map.push_back(temp4);
        vector<char> temp5 = {'9','1','2','6','7','8','3','4','5'}; m_map.push_back(temp5);
        vector<char> temp6 = {'1','2','3','7','8','9','4','5','6'}; m_map.push_back(temp6);
        vector<char> temp7 = {'4','5','6','1','2','3','7','8','9'}; m_map.push_back(temp7);
        vector<char> temp8 = {'7','8','9','4','5','6','1','2','3'}; m_map.push_back(temp8);

        }

    int GetSize() { return m_map.size(); }  //Return vector size
    vector<char> PrintRow(int index) { return m_map[index]; }
    vector<char> PrintColumn(int index) {
        vector<char> column;
        for (int i; i < 9; ++i) {
            column.push_back(m_map[i][index]);
        }
        return column;
    }
    void operator=(const SudokuField& l) { m_map = l.m_map; }  //Overload assignment operator
    void SetItem(char index, char value) { m_list[index] = value; }  //Assign subscript value
    char GetItem(char index) { return m_list[index]; }  //Return subscript value
    int GetLM(int in1, int in2) { return m_map[in1][in2]; }  //Return subscript value
    char GetRow (int index) { return row[index]; }  //Return index row
    char GetColumn(int index) { return column[index]; }  //Return index column
    vector<char> &operator[](int index) { return m_map[index]; }  //Overlaoad subscript operator
    friend ostream& operator<<(ostream& o, const SudokuField& b) {  //Overlad insertion operator
        cout << "     ";
        for (int col = 0; col < 9; ++col) o << setw(2) << char('A' + col);  //Build column reference id
            o << endl;
        for (int row = 0; row < 9; ++row) {  //Build row reference id
            o << setw(5) << char('P' + row);
            for (int col = 0; col < 9; ++col) o << setw(2) <<  b.m_map[row][col];  //Format 9X9 matrix
                o << endl;
            }
        return o;
    }
};


void SubVerify (SudokuField board) {  //Verify 3X3 submatrices
    char temp;
    int count = 0;
    bool subValid;

    for (int i = 0; i < 9; ++i) {
        subValid = false;
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                temp = board[ j + (i / 3) * 3 ][ k + (i % 3) * 3 ];
                if (temp == '_') {
                    count++;
                    cout << "Found inconsistency in componenet starting at row " << board.GetRow((i / 3) * 3)
                        << " and column " << board.GetColumn((i % 3) * 3) << endl;
                    break;
                }
                //count = 0;
                for (int m = 0; m < 3; ++m) {
                    for (int n = 0; n < 3; ++n) {
                        //if (board[ m + (i / 3) * 3 ][ n + (i % 3) * 3 ] == temp) count++;
                        /*if (count > 1) {
                            cout << "Found inconsistency in componenet starting at row " << board.GetRow((i / 3) * 3)
                                << " and column " << board.GetColumn((i % 3) * 3) << endl;
                            subValid = true; break;
                        }*/
                    }
                    if(subValid) break;
                }
                if(subValid) break;
            }
            if(subValid) continue;
        }
    }
    if(count <= 0) cout << "- All columns, rows, and componenets are OK..." << endl;
}

void ColumnVerify(SudokuField board, int i) {  //Verify column inconsistency
    vector<char> column;
    column = board.PrintColumn(i);  //Call member function to assign returned sudoku board column to column variable
    for (int j = 0; j < 9; ++j) {
        if (column[j] == '_') {
            cout << "Found inconsistency in column " << board.GetColumn(i) << endl;
        }
    }
    for (int n = 0; n < 9; ++n) {
        for (int k = 0; k < 9; ++k) {
            if (n != k && column[n] == column[k]) {
                cout << "Found inconsistency in column " << board.GetColumn(i) << endl;
            }
        }
    }
}

void RowVerify(SudokuField board) {  //Verify row inconsistency
    char temp;
    int counter;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            counter = 0;
            temp = board[i][j];
            if (board[i][j] == '_') {
                counter++;
            }
            if (counter > 0) {
                cout << "Found inconsistency in row " << board.GetRow(i) << endl;
                ++i;
            }
        }
    }
}

vector<int> SwapIndex() {  //Regulate swap index range
    vector<int> subColumn = {0,3,6};
    vector<int> swapColumn = {1,2};
    int rightIndex = subColumn[rand() % 3];
    int swapIndex = swapColumn[rand() % 2];
    vector<int> newIndex;
    newIndex.push_back(rightIndex);
    newIndex.push_back(rightIndex + swapIndex);
    return newIndex;
}

int main() {
    string command;
    SudokuField s_board;
    vector<vector<int> > m_map;

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();  //Seed for random number generation
    srand(seed);  //Random number generator

    cout << "Welcome Sudoku Initializer!" << endl;  //User greeting
    while(true) {
        cout << "> ";  //User command prompt
        cin >> command;
        //cout << endl;
        if (command == "show") {  //Show command prints current state of sudoku board
            cout << s_board << endl;
        }
        if (command == "quit") {  //Command quit exits initializer
            cout << "Bye...";
            return 0;
        }
        if (command == "erase") {  //Command erase replaces random cell of sudoku board with '_'
           int r_index = rand() % s_board.GetSize();  //Random row index
           int c_index = rand() % s_board.GetSize();  //Random column index
           s_board[r_index][c_index] = '_';  //Replace random cell with '_'
           cout << "Erasing row " << s_board.GetRow(r_index) << " column " << s_board.GetColumn(c_index) << endl;  //Reveal modification
        }
        if (command == "swap") {  //Command swap interchanges random rows/colums
            int r1 = rand() % 9;  //Random row index
            int r2 = rand() % 9;  //Random column index
            //vector<int> index = SwapIndex();
            //int r1 = index[0];
            //int r2 = index[1];
            int RowCol = rand();
            if (RowCol % 2  == 0) {
                if((r1 >= 0 && r1 <= 2) && (r2 >= 0 && r2 <= 2)) {  //Verify swap range
                    swap(s_board[r1],s_board[r2]);  //Swap method interchanges rows
                    cout << "- Rows " << s_board.GetRow(r1) << " and " << s_board.GetRow(r2) << " were swapped..." << endl;
                }
                if((r1 >= 3 && r1 <= 5) && (r2 >= 3 && r2 <= 5)) {  //Verify swap range
                    swap(s_board[r1],s_board[r2]);  //Swap method interchanges rows
                    cout << "- Rows " << s_board.GetRow(r1) << " and " << s_board.GetRow(r2) << " were swapped..." << endl;
                }
                if((r1 >= 6 && r1 <= 8) && (r2 >= 6 && r2 <= 8)) {  //Verify swap range
                    swap(s_board[r1],s_board[r2]);  //Swap method interchanges rows
                    cout << "- Rows " << s_board.GetRow(r1) << " and " << s_board.GetRow(r2) << " were swapped..." << endl;
                }
                else {  //Swap row components
                    cout << "Trying to swap rows " << s_board.GetRow(r1) << " and " << s_board.GetRow(r2) << endl;
                    swap(s_board[(r1 / 3) * 3],s_board[(r2 / 3) * 3]);
                    swap(s_board[((r1 / 3) * 3) + 1],s_board[((r2 / 3) * 3) + 1]);
                    swap(s_board[((r1 / 3) * 3) + 2],s_board[((r2 / 3) * 3) + 2]);
                    cout << "- Rows " << s_board.GetRow((r1 / 3) * 3) << " and " << s_board.GetRow((r2 / 3) * 3) << " were swapped..." << endl;
                    cout << "- Rows " << s_board.GetRow(((r1 / 3) * 3) + 1) << " and " << s_board.GetRow(((r2 / 3) * 3) + 1) << " were swapped..." << endl;
                    cout << "- Rows " << s_board.GetRow(((r1 / 3) * 3) + 2) << " and " << s_board.GetRow(((r2 / 3) * 3) + 2) << " were swapped..." << endl;

                }
            }
            else {
                if((r1 >= 0 && r1 <= 2) && (r2 >= 0 && r2 <= 2)) {  //Verify column range
                    for (int i = 0; i < 9; ++i) {  //Column swaping for loop
                        double temp;
                        temp = s_board[i][r2];
                        s_board[i][r2] = s_board[i][r1];
                        s_board[i][r1] = temp;
                        cout << "- Columns " << s_board.GetColumn(r1) << " and " << s_board.GetColumn(r2) << " were swapped..." << endl;
                    }
                }
                if((r1 >= 3 && r1 <= 5) && (r2 >= 3 && r2 <= 5)) {  //Verify column range 
                    for (int i = 0; i < 9; ++i) {  //Column swaping for loop
                        double temp;
                        temp = s_board[i][r2];
                        s_board[i][r2] = s_board[i][r1];
                        s_board[i][r1] = temp;
                        cout << "- Columns " << s_board.GetColumn(r1) << " and " << s_board.GetColumn(r2) << " were swapped..." << endl;
                    }
                }
                if((r1 >= 6 && r1 <= 8) && (r2 >= 6 && r2 <= 8)) {  //Verify column range 
                    for (int i = 0; i < 9; ++i) {  //Column swaping for loop
                        double temp;
                        temp = s_board[i][r2];
                        s_board[i][r2] = s_board[i][r1];
                        s_board[i][r1] = temp;
                        cout << "- Columns " << s_board.GetColumn(r1) << " and " << s_board.GetColumn(r2) << " were swapped..." << endl;
                    }
                }
                else {  //Swap column range 
                    cout << "Trying to swap columns " << s_board.GetColumn(r1) << " and " << s_board.GetColumn(r2) << endl;
                    for (int i = 0; i < 9; ++i) {  //Column swaping for loop

                    double temp;
                    double temp1;
                    double temp2;
                    temp = s_board[i][(r2 / 3) * 3];
                    s_board[i][(r2 / 3) * 3] = s_board[i][(r1 / 3) * 3];
                    s_board[i][(r1 / 3) * 3] = temp;

                    temp1 = s_board[i][((r2 / 3) * 3) + 1];
                    s_board[i][((r2 / 3) * 3) + 1] = s_board[i][((r1 / 3) * 3) + 1];
                    s_board[i][((r1 / 3) * 3) + 1] = temp1;

                    temp2 = s_board[i][((r2 / 3) * 3) + 2];
                    s_board[i][((r2 / 3) * 3) + 2] = s_board[i][((r1 / 3) * 3) + 2];
                    s_board[i][((r1 / 3) * 3) + 2] = temp2;


                    }

                    cout << "- Columns " << s_board.GetColumn((r1 / 3) * 3) << " and " << s_board.GetColumn((r2 / 3) * 3) << " were swapped..." << endl;
                    cout << "- Columns " << s_board.GetColumn(((r1 / 3) * 3) + 1) << " and " << s_board.GetColumn(((r2 / 3) * 3) + 1) << " were swapped..." << endl;
                    cout << "- Columns " << s_board.GetColumn(((r1 / 3) * 3) + 2) << " and " << s_board.GetColumn(((r2 / 3) * 3) + 2) << " were swapped..." << endl;

                }
            }
        }
        if (command == "verify") {  //Verify concistency with sudoku rules and print erroneous positions
            RowVerify(s_board);  //Verify sudoku board rows
            for (int i = 0; i < 9; ++i) {  //Verify sudoku board columns
                ColumnVerify(s_board,i);
            }
            SubVerify(s_board);  //Verify sudoku board sum-components
        }
    }
}
