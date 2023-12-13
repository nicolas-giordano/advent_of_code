#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // File path
    const char* fname = "input.txt";
    // Open file
    FILE* fp = fopen(fname, "r");

    int c; 
    int sum = 0; // Summation of calibrations
    const int ZERO = 48; // ASCII decimal value of 0 (used to get value of integer character)
    const int NEW_LINE = 10; // ASCII decimal value of new line ( used to reset integer counter)
    int counter = 0; // Counter of integers in each line. i
    int prev_integer; // Keep track of last integer seen
    int calibration_value;

    // Read through the file character by character
    while ((c = fgetc(fp)) != EOF)
    {
        
        // Check if at new line character (c == 10)
        if (c == NEW_LINE)
        {
            if (counter == 1) 
            {
                calibration_value += prev_integer; // The first integer is also the last integer so add it to the sum
            }
            counter = 0;
            sum += calibration_value;
            continue;
        }
        // If character has decimal value of an integer
        if (c >= 48 && c <= 57)
        {
            int current_int = c - ZERO;
            // If we have seen 2 or more integers we need to remove the previous from our sum and add the new integer in
            if (counter == 0)
            {
                calibration_value = current_int * 10; // The first integer of the line represents the 10s place
            }
            else if (counter == 1) 
            {
                calibration_value += current_int; // If we have only seen 1 integer we can simply add to sum
            }
            else 
            {
                calibration_value = calibration_value - prev_integer + current_int; // We have seen 2 integers already this line so we must subtract the previous and add the current
            }
            prev_integer = c - ZERO;
            counter++;
        }        
    }
    // We need to check if the last line had only 1 calibration value in it if so we add it again as the last integer
    if (counter == 1)
    {
        sum += prev_integer;
    }
    // Add the last lines calibration value since the while loop does not reach it for the last line
    sum += calibration_value;

    printf("%i", sum);

    fclose(fp);

    return EXIT_FAILURE;
}
