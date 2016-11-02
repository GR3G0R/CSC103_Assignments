//Gregory Delpe
//Assignment #5: Sudoku Initializer

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Cell {
    bool m_accu;
    bool m_mark;
public:
    Cell() : m_accu(false), m_mark(false) {}
    friend ostream& operator<<(ostream& o, const Cell& c) {
    if (!c.m_accu) return o << setw(2) << '.';
    return o << setw(2) << (c.m_mark? 'o' : 'x');
    }
};

class SudokuField {
    vector<vector<int> > m_map;
public:
    SudokuField() {
        vector<int> temp = {2,3,4,8,9,1,5,6,7}; m_map.push_back(temp);
        vector<int> temp1 = {5,6,7,2,3,4,8,9,1}; m_map.push_back(temp1);
        vector<int> temp2 = {8,9,1,5,6,7,2,3,4}; m_map.push_back(temp2);
        vector<int> temp3 = {3,4,5,9,1,2,6,7,8}; m_map.push_back(temp3);
        vector<int> temp4 = {6,7,8,3,4,5,9,1,2}; m_map.push_back(temp4);
        vector<int> temp5 = {9,1,2,6,7,8,3,4,5}; m_map.push_back(temp5);
        vector<int> temp6 = {1,2,3,7,8,9,4,5,6}; m_map.push_back(temp6);
        vector<int> temp7 = {4,5,6,1,2,3,7,8,9}; m_map.push_back(temp7);
        vector<int> temp8 = {7,8,9,4,5,6,1,2,3}; m_map.push_back(temp8);

        //vector<Cell> a_row(9);
        //for (int i = 0; i < 9; ++i) m_map.push_back(a_row);
    }
        friend ostream& operator<<(ostream& o, const SudokuField& b) {
        cout << "   ";
        for (int col = 0; col < 9; ++col) o << setw(2) << char('A' + col);
            o << endl;
        for (int row = 0; row < 9; ++row) {
            o << setw(3) << char('P' + row);
            for (int col = 0; col < 9; ++col) o << setw(2) <<  b.m_map[row][col];
            o << endl;
        }
        return o;
    }
};

int main() {
    char command;
    cout << "Welcome Sudoku Initializer!" << endl << endl;
    cout << "> ";
    cin >> command;
    cout << endl << endl;
    SudokuField b;
    cout << b;

}
