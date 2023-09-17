#include <stdio.h>
#include <math.h>

// Define hyperparameters
#define NUM_FEATURES 3
#define NUM_FACTORS 2
#define LEARNING_RATE 0.01
#define NUM_EPOCHS 1000

// Function to compute the dot product of two arrays
double dot_product(double* a, double* b, int size) {
    double result = 0.0;
    for (int i = 0; i < size; i++) {
        result += a[i] * b[i];
    }
    return result;
}

int main() {
    // Initialize data
    double X[NUM_FEATURES] = {1.0, 2.0, 3.0}; // Input features
    double y = 1.0; // True label for binary classification (1 or -1)

    // Initialize model parameters
    double w[NUM_FEATURES] = {0.0}; // Linear weights
    double v[NUM_FEATURES][NUM_FACTORS] = {{0.1, 0.2}, {0.2, 0.3}, {0.3, 0.4}}; // Factorized weights

    // Training loop
    for (int epoch = 0; epoch < NUM_EPOCHS; epoch++) {
        // Compute prediction
        double linear_term = dot_product(w, X, NUM_FEATURES);

        double interaction_term = 0.0;
        for (int i = 0; i < NUM_FEATURES; i++) {
            for (int j = i+1; j < NUM_FEATURES; j++) {
                interaction_term += v[i][0] * v[j][1] * X[i] * X[j];
                interaction_term += v[j][0] * v[i][1] * X[j] * X[i];
            }
        }

        double y_hat = linear_term + 0.5 * interaction_term;

        // Compute error
        double error = y_hat - y;

        // Update weights
        for (int i = 0; i < NUM_FEATURES; i++) {
            w[i] -= LEARNING_RATE * error * X[i];
            for (int f = 0; f < NUM_FACTORS; f++) {
                v[i][f] -= LEARNING_RATE * (error * (X[i] * (dot_product(v[i], X, NUM_FEATURES) - v[i][f] * X[i])));
            }
        }
    }

    // Print learned parameters
    printf("Learned linear weights (w):\n");
    for (int i = 0; i < NUM_FEATURES; i++) {
        printf("%f ", w[i]);
    }

    printf("\n\nLearned factorized weights (v):\n");
    for (int i = 0; i < NUM_FEATURES; i++) {
        for (int j = 0; j < NUM_FACTORS; j++) {
            printf("%f ", v[i][j]);
        }
        printf("\n");
    }

    return 0;
}
