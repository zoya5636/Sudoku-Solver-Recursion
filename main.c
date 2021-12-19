#include <stdio.h>
#include <stdbool.h>

void printBoard(int arr[9][9]) {
    for(int i = 0; i < 9; i++) {
        if( (i % 3) == 0 ) printf("-------------------------\n");
        for(int j = 0; j < 9; j++) {
            if( (j % 3) == 0 ) printf("| ");
            printf("%d ", arr[i][j]);
            if(j == 8) printf("|\n");
        }
    }
    printf("-------------------------\n");
}

bool validMove(int arr[9][9], int row, int col) {
    for(int i = 0; i < 9; i++) {
        if( ( (arr[row][i] == arr[row][col]) && (i != col) ) ||
            ( (arr[i][col] == arr[row][col]) && (i != row) ) ) return false;
    }
    int corRow = row / 3 * 3, corCol = col / 3 * 3;
    for(int i = corRow; i < (corRow+3); i++) {
        for(int j = corCol; j < (corCol+3); j++) {
            if( (arr[i][j] == arr[row][col]) && ( (i != row) || (j != col) ) ) return false;
        }
    } 
    return true;
}

bool recSudoku(int arr[9][9], int arrIndex) {
    /*static int count;
    count++;
    printf("%d\n", count);*/
    if(arrIndex >= 81) return true;
    int row = arrIndex / 9, col = arrIndex - (row*9);
    while(arr[row][col] != 0) {
        arrIndex++;
        row = arrIndex / 9;
        col = arrIndex - (row*9);
        if(arrIndex >= 81) return true;
    }
    for(int i = 1; i <= 9; i++) {
        arr[row][col] = i;
        if(validMove(arr, row, col) == false) {
            arr[row][col] = 0;
        } else {
            if((recSudoku(arr, arrIndex+1)) == false) {
                arr[row][col] = 0;
            } else return true;
        }
    }
    return false;
}

int main(int argc, char **argv) {
    int board[9][9] = 
    {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
	recSudoku(board, 0);
    printBoard(board);
    return 0;
}
