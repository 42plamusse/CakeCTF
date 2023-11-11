#include <stdio.h>
#include <stdlib.h>
#define GRID_SIZE 4

char g_puzzle[64] = {0xdb, 0x56, 0x58, 0x44,
                     0x04, 0x03, 0x23, 0x4c,
                     0x9f, 0x44, 0x22, 0x00,
                     0xb7, 0x96, 0x1a, 0x67,
                     0xf7, 0x44, 0x56, 0x6c,
                     0x87, 0x62, 0xf4, 0x7f,
                     0x29, 0xc8, 0xe9, 0x6e,
                     0x72, 0x2e, 0xda, 0x5c,
                     0x00, 0x00, 0x00, 0x00,
                     0xc9, 0x88, 0x8e, 0x69,
                     0x4f, 0x5a, 0xe6, 0x33,
                     0x54, 0x5c, 0xcc, 0x50,
                     0x1a, 0x83, 0x49, 0x13,
                     0x74, 0x8f, 0xc8, 0x53,
                     0xb9, 0x8a, 0x85, 0x25,
                     0xd8, 0x76, 0xf9, 0x72};

void print_puzzle()
{
    for (int row = 0; row < GRID_SIZE; row++)
    {
        for (int column = 0; column < GRID_SIZE; column++)
        {
            printf("0x%02X, ", g_puzzle[row * GRID_SIZE + column]);
        }
        puts("");
    }
}

void swap_values(int *firstValue, int *secondValue)
{
    *firstValue = *firstValue ^ *secondValue;
    *secondValue = *secondValue ^ *firstValue;
    *firstValue = *firstValue ^ *secondValue;
}

int *get_puzzle_element(int row, int column)
{
    return (int *)(g_puzzle + ((long)row * GRID_SIZE + (long)column) * sizeof(int));
}

void find_empty_space(int *row, int *column)
{
    int searchColumn;
    int searchRow;

    for (searchRow = 0; searchRow < GRID_SIZE; searchRow++)
    {
        for (searchColumn = 0; searchColumn < GRID_SIZE; searchColumn++)
        {
            if (*get_puzzle_element(searchRow, searchColumn) == 0)
            {
                *row = searchRow;
                *column = searchColumn;
                return;
            }
        }
    }
}

void move_piece(char direction)
{
    int currentColumn;
    int currentRow;

    find_empty_space(&currentRow, &currentColumn);
    printf("row: %d, col: %d\n", currentRow, currentColumn);

    switch (direction)
    {
    case 'U': // Move Up
        if (currentRow > 0)
        { // Ensure not at the top edge
            swap_values(get_puzzle_element(currentRow, currentColumn),
                        get_puzzle_element(currentRow - 1, currentColumn));
        }
        break;
    case 'R': // Move Right
        if (currentColumn < GRID_SIZE - 1)
        { // Ensure not at the right edge
            swap_values(get_puzzle_element(currentRow, currentColumn),
                        get_puzzle_element(currentRow, currentColumn + 1));
        }
        break;
    case 'D': // Move Down
        if (currentRow < GRID_SIZE - 1)
        { // Ensure not at the bottom edge
            swap_values(get_puzzle_element(currentRow, currentColumn),
                        get_puzzle_element(currentRow + 1, currentColumn));
        }
        break;
    case 'L': // Move Left
        if (currentColumn > 0)
        { // Ensure not at the left edge
            swap_values(get_puzzle_element(currentRow, currentColumn),
                        get_puzzle_element(currentRow, currentColumn - 1));
        }
        break;
    default:
        break;
    }
}

int check_solved(void)
{
    int row_index;
    int column_index;
    int *puzzle_ptr;

    for (row_index = 0; row_index < 2; row_index++)
    {
        for (column_index = 0; column_index < 3; column_index++)
        {
            puzzle_ptr = (int *)g_puzzle + (row_index * GRID_SIZE) + column_index;
            // Compare current element with the one to its right
            if (*(puzzle_ptr + 1) <= *puzzle_ptr)
            {
                return 1;
            }
            // Compare current element with the one below it
            if (*(puzzle_ptr + GRID_SIZE) <= *puzzle_ptr)
            {
                return 1;
            }
        }
    }
    return 0;
}

int main(void)
{
    int scan_result;
    int is_solved;
    char input[112];

    while (1)
    {
        print_puzzle();

        is_solved = check_solved();
        if ((int)is_solved == 0)
            puts("It's a WIN !");
        printf("> ");
        fflush(stdout);
        scan_result = scanf("%s", input);
        if (scan_result == -1)
            break;
        move_piece(input[0]);
    }
    return 0;
}
