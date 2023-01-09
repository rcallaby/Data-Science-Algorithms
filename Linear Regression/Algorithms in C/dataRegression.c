
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// TODO: Fix the error and possibly come up with some more tests

struct dataPoint {
    int x;
    int y;
};
 
// Function to calculate coefficients 
void coefficient(struct dataPoint data[], int n)
{
    int sum_x = 0;
    int sum_y = 0;
    int sum_xy = 0;
    int sum_x2 = 0;
 
    for (int i = 0; i < n; i++)
    {
        // sum of elements of array x[] 
        sum_x = sum_x + data[i].x;
 
        // sum of elements of array y[] 
        sum_y = sum_y + data[i].y;
 
        // sum of X[i] * Y[i]. 
        sum_xy = sum_xy + data[i].x * data[i].y;
 
        // sum of square of array elements 
        sum_x2 = sum_x2 + data[i].x * data[i].x;
    }
 
    float m = (float)(n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
    float c = (float)(sum_y - m * sum_x) / n;
 
    printf("m = %f c = %f\n", m, c);
}


// ? There is an issue in the main() program? Weird.
int main()
{
    int n = 5;
    struct dataPoint data[n];
    data[0].x = 0;
    data[0].y = 2;
    data[1].x = 1;
    data[1].y = 3;
    data[2].x = 2;
    data[2].y = 4;
    data[3].x = 3;
    data[3].y = 4;
    data[4].x = 4;
    data[4].y = 5;
    coefficient(data, n);
    return 0;
}