//
//  main.cpp
//  sudoku_multi
//
//  Created by Polar Halim on 4/18/16.
//  Copyright © 2016 Polar Halim. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>

using namespace std;

typedef struct
{
    int row;                            //starting row
    int column;                         //starting column
    int (* sudoku)[9];
} parameters;


void * check_rows(void * params);       //check rows
void * check_columns(void * params);    //check columns
void * check_square(void * params);     //check 3x3 square

int main(void)
{
    // Input the sudoku board
    int sudoku[9][9] = {
        {6, 2, 4, 5, 3, 9, 1, 8, 7},
        {5, 1, 9, 7, 2, 8, 6, 3, 4},
        {8, 3, 7, 6, 1, 4, 2, 9, 5},
        {1, 4, 3, 8, 6, 5, 7, 2, 9},
        {9, 5, 8, 2, 4, 7, 3, 6, 1},
        {7, 6, 2, 3, 9, 1, 4, 5, 8},
        {3, 7, 1, 9, 5, 6, 8, 4, 2},
        {4, 9, 6, 1, 8, 2, 5, 7, 3},
        {2, 8, 5, 4, 7, 3, 9, 1, 6}
    };
    
    // Parameters to check each row and column
    parameters * zero = (parameters *) malloc(sizeof(parameters));
    zero -> row = 0;
    zero -> column = 0;
    zero -> sudoku = sudoku;
    
    // Parameter for 3x3 threads
    
    // First 3x3 Thread
    parameters * param1 = (parameters *) malloc(sizeof(parameters));
    param1 -> row = 0;
    param1 -> column = 0;
    param1 -> sudoku = sudoku;
    
    // Second 3x3 Thread
    parameters * param2 = (parameters *) malloc(sizeof(parameters));
    param2 -> row = 0;
    param2 -> column = 3;
    param2 -> sudoku = sudoku;
    
    // Third 3x3 Thread
    parameters * param3 = (parameters *) malloc(sizeof(parameters));
    param3 -> row = 0;
    param3 -> column = 6;
    param3 -> sudoku = sudoku;
    
    // Fourth 3x3 Thread
    parameters * param4 = (parameters *) malloc(sizeof(parameters));
    param4 -> row = 3;
    param4 -> column = 0;
    param4 -> sudoku = sudoku;
    
    // Fifth 3x3 Thread
    parameters * param5 = (parameters *) malloc(sizeof(parameters));
    param5 -> row = 3;
    param5 -> column = 3;
    param5 -> sudoku = sudoku;
    
    // Sixth 3x3 Thread
    parameters * param6 = (parameters *) malloc(sizeof(parameters));
    param6 -> row = 3;
    param6 -> column = 6;
    param6 -> sudoku = sudoku;
    
    // Seventh 3x3 Thread
    parameters * param7 = (parameters *) malloc(sizeof(parameters));
    param7 -> row = 6;
    param7 -> column = 0;
    param7 -> sudoku = sudoku;
    
    // Eighth 3x3 Thread
    parameters * param8 = (parameters *) malloc(sizeof(parameters));
    param8 -> row = 6;
    param8 -> column = 3;
    param8 -> sudoku = sudoku;
    
    // Ninth 3x3 Thread
    parameters * param9 = (parameters *) malloc(sizeof(parameters));
    param9 -> row = 6;
    param9 -> column = 6;
    param9 -> sudoku = sudoku;
    
    // Create all the threads
    pthread_t thread_rows, thread_columns, thread1, thread2, thread3, thread4, thread5, thread6, thread7, thread8, thread9;
    
    void * all_rows;
    void * all_columns;
    void * block1;
    void * block2;
    void * block3;
    void * block4;
    void * block5;
    void * block6;
    void * block7;
    void * block8;
    void * block9;
    
    // Threads Initialization
    pthread_create(&thread_rows, NULL, check_rows, (void *) zero);
    pthread_create(&thread_columns, NULL, check_columns, (void *) zero);
    pthread_create(&thread1, NULL, check_square, (void *) param1);
    pthread_create(&thread2, NULL, check_square, (void *) param2);
    pthread_create(&thread3, NULL, check_square, (void *) param3);
    pthread_create(&thread4, NULL, check_square, (void *) param4);
    pthread_create(&thread5, NULL, check_square, (void *) param5);
    pthread_create(&thread6, NULL, check_square, (void *) param6);
    pthread_create(&thread7, NULL, check_square, (void *) param7);
    pthread_create(&thread8, NULL, check_square, (void *) param8);
    pthread_create(&thread9, NULL, check_square, (void *) param9);
    
    // Joining the Threads
    pthread_join(thread_rows, &all_rows);
    pthread_join(thread_columns, &all_columns);
    pthread_join(thread1, &block1);
    pthread_join(thread2, &block2);
    pthread_join(thread3, &block3);
    pthread_join(thread4, &block4);
    pthread_join(thread5, &block5);
    pthread_join(thread6, &block6);
    pthread_join(thread7, &block7);
    pthread_join(thread8, &block8);
    pthread_join(thread9, &block9);
    
    // Check the Sudoku Puzzle
    if (    (int) (size_t) all_rows == 1 &&
            (int) (size_t) all_columns == 1 &&
            (int) (size_t) block1 == 1 &&
            (int) (size_t) block2 == 1 &&
            (int) (size_t) block3 == 1 &&
            (int) (size_t) block4 == 1 &&
            (int) (size_t) block5 == 1 &&
            (int) (size_t) block6 == 1 &&
            (int) (size_t) block7 == 1 &&
            (int) (size_t) block8 == 1 &&
            (int) (size_t) block9 == 1 )
    {
        cout << "The Sudoku Puzzle is Correct!" << endl;
    }
    else
    {
        cout << "The Sudoku Puzzle is NOT Correct!" << endl;
    }
    
    return 0;
}

/**
 * Checks each row if it contains all digits 1-9.
 * @param   void *      The parameters (pointer).
 * @return  void *      1 if all rows contain all digits from 1-9, 0 otherwise.
 */
void * check_rows(void * params) {
    parameters * data = (parameters *) params;
    int rowCheck = data -> row;
    int columnCheck = data -> column;
    for (int i = rowCheck; i < 9; ++i) {
        int row[10] = {0};
        for (int j = columnCheck; j < 9; ++j) {
            int val = data -> sudoku[i][j];
            if (row[val] != 0) {
                return (void *) 0;
            }
            else{
                row[val] = 1;
            }
        }
    }
    return (void *) 1;
}

/**
 * Checks each column if it contains all digits 1-9.
 * @param   void *      The parameters (pointer).
 * @return  void *      1 if all rows contain all digits from 1-9, 0 otherwise.
 */
void * check_columns(void * params) {
    parameters * data = (parameters *) params;
    int rowCheck = data -> row;
    int columnCheck = data -> column;
    for (int i = columnCheck; i < 9; ++i) {
        int column[10] = {0};
        for (int j = rowCheck; j < 9; ++j) {
            int val = data -> sudoku[j][i];
            if (column[val] != 0) {
                return (void *) 0;
            }
            else{
                column[val] = 1;
            }
        }
    }
    return (void *) 1;
}

/**
 * Checks if a square of size 3x3 contains all numbers from 1-9.
 * @param   void *      The parameters (pointer).
 * @return  void *      1 if all rows contain all digits from 1-9, 0 otherwise.
 */
void * check_square(void * params) {
    parameters * data = (parameters *) params;
    int rowCheck = data -> row;
    int columnCheck = data -> column;
    int saved[10] = {0};
    for (int i = rowCheck; i < rowCheck + 3; ++i) {
        for (int j = columnCheck; j < columnCheck + 3; ++j) {
            int val = data -> sudoku[i][j];
            if (saved[val] != 0) {
                return (void *) 0;
            }
            else{
                saved[val] = 1;
            }
        }
    }
    return (void *) 1;
}