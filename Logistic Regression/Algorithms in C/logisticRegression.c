#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    // Defining the variables
    int i, j, k;
    double z, y, learning_rate, theta[3];
    double x[4][3] = {{1, 0.5, 0.5}, {1, 0.7, 0.3}, {1, 0.9, 0.1}, {1, 0.8, 0.2}};
    double y_hat[4], y_value[4] = {1, 0, 0, 1};
    double cost, cost_prev;
    
    // Initializing the theta values
    theta[0] = 0.1;
    theta[1] = 0.2;
    theta[2] = 0.3;
    
    // Setting the learning rate
    learning_rate = 0.05;
    
    // Iterating the gradient descent algorithm
    for (i = 0; i < 10000; i++) {
        
        // Computing the hypothesis
      cost_prev = cost;
        cost = 0;
        for (j = 0; j < 4; j++) {
            z = 0;
            for (k = 0; k < 3; k++) {
                z += theta[k] * x[j][k];
            }
            y = 1 / (1 + exp(-z));
            y_hat[j] = y;
            cost += (y - y_value[j]) * (y - y_value[j]);
        }
        
        // Updating the theta values
        for (j = 0; j < 3; j++) {
            theta[j] = theta[j] - learning_rate * (2 * (y_hat[j] - y_value[j]) * (1 - y_hat[j]) * y_hat[j] * x[j][k]);
        }
        
        // Checking for convergence
        if (fabs(cost - cost_prev) < 1e-6) break;
    }
    
    // Printing out the theta values
    printf("Theta values after convergence: \n");
    for (i = 0; i < 3; i++) {
        printf("theta[%d] = %lf\n", i, theta[i]);
    }
    
    return 0;
}