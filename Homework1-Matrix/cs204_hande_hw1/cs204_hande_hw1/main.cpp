//Copy and paste your code here
//Write your name and lastname as well
#include <iostream> //hande altunbas homework assignment 1
using namespace std;

#include <sstream>
#include <vector>
#include <fstream>
#include <string>

bool isAscii(char c) {
    // Check if the ASCII value of the character is within the ASCII range (0 to 127)
    return c >= 0 && c <= 127;
}

bool emptyMatrix(const vector<vector<char>> & matrix)
{
    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix[i].size(); ++j)
        {
            if (matrix[i][j] != '-') //if there is a char except for dash it returns false meaning it is not empty
            {
                return false;
            }
        }
    }
    return true;
}

bool gameEnd(const vector<vector<char>> & matrix)
{
    bool isGameEnd = true;
    for (unsigned int i = 0; i < matrix.size(); ++i) // i = rows
    {
        for (unsigned int j = 0; j < matrix[i].size(); ++j) // j = columns
        {
            if (matrix[i][j] == 'u')
            {
                if (i > 0 && matrix[i - 1][j] == '-') //CHECK FOR UP MOVE for up move to be applied i need to check the same column but upper row so i - 1
                {
                    isGameEnd = false;
                }
                else if (i == 0)
                {
                    isGameEnd = false;

                }
            }
            else if (matrix[i][j] == 'd')
            {
                if (i < matrix.size() - 1 && matrix[i + 1][j] == '-') //CHECK FOR DOWN MOVE similar approach (kind of reverse) as the upper move in this case
                {
                    isGameEnd = false;

                }
                else if (i == matrix.size() - 1)
                {
                    isGameEnd = false;
                }

            }
            else if (matrix[i][j] == 'l')
            {
                if (j > 0 && matrix[i][j - 1] == '-') //CHECK FOR LEFT MOVE
                {
                    isGameEnd = false;

                }
                else if (j == 0)
                {
                    isGameEnd = false;
                }
            }
            else if (matrix[i][j] == 'r')
            {
                if (j < matrix[i].size() - 1 && matrix[i][j + 1] == '-') // CHECK FOR RIGHT MOVE
                {
                    isGameEnd = false;

                }
                else if (j == matrix[i].size() - 1)
                {
                    isGameEnd = false;

                }
            }
        }
    }
    return isGameEnd;
}

void showMatrix(const vector<vector<char>> & matrix)
{
    for (const auto& row : matrix)
    {
        for (char ch : row)
        {
            cout << ch;
        }
        cout << endl;
    }
}

void gameplay(vector<vector<char>>& matrix, unsigned int row_idx, unsigned int col_idx)
{
    char direct = matrix[row_idx][col_idx];
    char original_direct = direct; // Store the original direction
    matrix[row_idx][col_idx] = '-'; // Empty the current cell

    int new_row_idx = row_idx;
    int new_col_idx = col_idx;
    bool isMoved = false;
    // Update new row and column indices based on the direction
    if (direct == 'u')
    {
        if (row_idx == 0)
        {
            matrix[row_idx][col_idx] = '-'; // Empty the current cell
            isMoved = true;
        }
        else
        {
            while (new_row_idx > 0 && matrix[new_row_idx - 1][col_idx] == '-') //if the upper cell empty check the next upper cell set the new row index
            {
                new_row_idx--;
                isMoved = true;
            }
            if ( new_row_idx == 0 && matrix[new_row_idx][col_idx] == '-')
            {
                matrix[new_row_idx][col_idx] = '-';
                isMoved = true;
            }
            else
            {
                matrix[new_row_idx][col_idx] = original_direct; //set the new cell as 'u'
            }
        }

    }
    else if (direct == 'd')
    {
        if (row_idx == matrix.size() -1)
        {
            matrix[row_idx][col_idx] = '-';
            isMoved = true;
        }
        else
        {
            while (new_row_idx < matrix.size() - 1 && matrix[new_row_idx + 1][col_idx] == '-') //reverse order that i did in u
            {
                new_row_idx++;
                isMoved = true;
            }
            if ( new_row_idx == matrix.size() - 1 && matrix[new_row_idx][col_idx] == '-')
            {
                matrix[new_row_idx][col_idx] = '-';
                isMoved = true;
            }
            else
            {
                matrix[new_row_idx][col_idx] = original_direct; //set the new cell as 'd'
            }

        }

    }
    else if (direct == 'l' )
    {
        if ( col_idx == 0)
        {
            matrix[row_idx][col_idx] = '-';
            isMoved = true;
        }
        else
        {
            while (new_col_idx > 0 && matrix[row_idx][new_col_idx - 1] == '-')
            {
                new_col_idx--;
                isMoved = true;
            }
            if (new_col_idx == 0 && matrix[row_idx][new_col_idx] == '-')
            {
                matrix[row_idx][new_col_idx] = '-';
                isMoved = true;
            }
            else
            {
                matrix[row_idx][new_col_idx] = original_direct; //set the new cell as 'l'
            }
        }
    }
    else if (direct == 'r')
    {
        if( col_idx == matrix[row_idx].size() - 1)
        {
            matrix[row_idx][col_idx] = '-';
            isMoved = true;

        }
        else
        {
            while (new_col_idx < matrix[row_idx].size() - 1 && matrix[row_idx][new_col_idx + 1] == '-')
            {
                new_col_idx++;
                isMoved = true;
            }
            if ( new_col_idx == matrix[row_idx].size() - 1 && matrix[row_idx][new_col_idx] == '-')
            {
                matrix[row_idx][new_col_idx] = '-';
                isMoved = true;
            }
            else
            {
                matrix[row_idx][new_col_idx] = original_direct; //set the new cell as 'r'
            }
        }
    }
    if (isMoved) //bool help us determine if it was moved
    {
        cout << "\nTile at (" << row_idx << "," << col_idx << ") has been moved." << endl;
    }
    else
    {
        // Restore the original cell if the move is invalid
        matrix[row_idx][col_idx] = original_direct;
        cout << "\nNo tiles have been moved." << endl;
    }
}





void fileRead(ifstream& filename)
{
    string fileinput;
    cout << "Please enter the file name: " ;
    cin >> fileinput;
    filename.open(fileinput.c_str());
    while (filename.fail()) //asks for user input continuously if the file cannot open
    {
        cout << "\nCould not open the file. Please enter a valid file name: " ;
        cin >> fileinput;
        filename.open(fileinput.c_str());
    }

    vector<vector<char>> matrix;
    vector<int> lineLen; //I need to store each line's (row's) char # in order to determine whether it is a true matrix
    string line;

    int emptyline = 0;
    bool stoploop = false;
    while (getline(filename, line) && !stoploop)
    {
        if (line.empty())
        {
            cout << "\nErroneous file content. Program terminates." << endl; //if there is an empty line the loop should end which is why i have stoploop
            emptyline += 1;
            stoploop = true;

        }
        else
        {
            int len = line.length() + 0;
            lineLen.push_back(len);

            vector<char> row;
            for(int x=0; x < len; x++)
            {
                char ch = line[x];
                if (isAscii(ch)) //checks for ascii characters because i tried it with some turkish words and the input check (each char) gave me weird outputs such as the line lengths (row length was longer when i used turkish words)
                {
                    row.push_back(ch);
                }
                else
                {
                    cout << "\nErroneous file content. Program terminates." << endl; //if not ascii ends the loop
                    x = len; //this help me end the for loop
                    stoploop = true;
                }
            }
            if(!stoploop)
            {
                matrix.push_back(row);

            }
        }

    }
    filename.close();

    if (emptyline == 0 && !matrix.empty() && !stoploop) // Check if the matrix is not empty
    {
        // Proceed with further operations
        bool truematrix = true; //bool expression to check if it is a true matrix
        int lineSize = lineLen.size();
        int temp = lineLen[0]; //I am initializing a temp for row length to check whether each one matches

        for(int i=1; i < lineSize; i++) //CHECKING IF IT IS A REAL MATRIX (ROW LENGTHS MUST BE EQUAL)
        {
            if (temp != lineLen[i])
            {
                cout << "\nErroneous file content. Program terminates." << endl;
                truematrix = false;
                i = lineSize; // Return from the function to avoid further processing

            }
            else
            {
                temp = lineLen[i]; // update the temp each time that check and compare each line lengths
            }
        }

        if (emptyMatrix(matrix))
        {
            cout << "\nThe matrix file contains: " << endl;
            showMatrix(matrix);
            cout << "The matrix is empty." << endl;
        }
        else
        {
            // Proceed with checking character validity and gameplay
            bool charTrue = false;
            char movements [] = {'u', 'd', 'l', 'r','-' }; //i created an array manually to check the char validity
            for (int i = 0; i < matrix.size(); ++i)
            {
                for (int j = 0; j < matrix[i].size(); ++j)
                {
                    char eachChar = matrix[i][j];
                    charTrue = false;
                    for(auto & movement : movements) //c lion did this automatically normally i prefer range loops since i don't really know how this works
                    {
                        if (eachChar == movement)
                        {
                            charTrue = true;
                        }

                    }
                    if (!charTrue) //IF THIS EXPRESSION IS STILL FALSE I NEED TO TERMINATE THE LOOP.
                    {
                        cout << "\nErroneous file content. Program terminates." << endl;
                        j = matrix[i].size() ; // Return from the function to avoid further processing
                        i = matrix.size() ;
                    }
                }
            }
            if(charTrue and truematrix) //if chars are correct and row lengths are equal it should proceed with the game
            {
                cout << "\nThe matrix file contains: " << endl;
                showMatrix(matrix);
                int row_size = 0, col_size = 0;
                // Proceed with gameplay
                while(!gameEnd(matrix) && !emptyMatrix(matrix)) //the game ends if the matrix is empty full of dash line or there are no moves possible
                {
                    int user_row, user_col;
                    cout << "Please enter the row and column of the tile that you want to move: " ;
                    cin >> user_row >> user_col;

                    // Calculate row and column sizes
                    row_size = matrix.size();
                    if (row_size > 0)
                    {
                        col_size = matrix[0].size(); //this is to check for user input validity the matrix should be valid in order to get to this line in the program but double checking
                    }

                    // Check user input validity
                    while(user_row < 0 || user_row >= row_size || user_col < 0 || user_col >= col_size)
                    {
                        cout << "\nInvalid row or column index." << endl;
                        cout << "Please enter the row and column of the tile that you want to move: ";
                        cin >> user_row >> user_col;
                    }

                    gameplay(matrix, user_row, user_col);
                    showMatrix(matrix);
                }

                if(gameEnd(matrix) and !emptyMatrix(matrix) )
                {
                    cout << "No more moves are possible." << endl; //means matrix is not empty
                }
                else
                {
                    cout << "The matrix is empty." << endl; //game ends bc matrix is empty
                }
            }
        }
    }
    else if(matrix.empty() and !stoploop) //if the file content is empty it cannot go through getline so i chose to do something like that to prevent
    {
        cout << "\nErroneous file content. Program terminates." << endl;
    }

}


int main()
{
    ifstream inp_txt;
    fileRead(inp_txt);
    return 0;
}

