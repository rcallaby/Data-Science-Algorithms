#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_INPUTS 2
#define NUM_HIDDEN_NODES 4
#define NUM_OUTPUTS 1

#define NUM_SAMPLES 4

double inputs[NUM_SAMPLES][NUM_INPUTS] = {
  {0, 0},
  {0, 1},
  {1, 0},
  {1, 1}
};

double expected_outputs[NUM_SAMPLES] = {0, 1, 1, 0};

double hidden_layer[NUM_HIDDEN_NODES];
double output;

double weights_input_hidden[NUM_INPUTS][NUM_HIDDEN_NODES];
double weights_hidden_output[NUM_HIDDEN_NODES];

void initialize_weights() {
  int i, j;
  for (i = 0; i < NUM_INPUTS; i++) {
    for (j = 0; j < NUM_HIDDEN_NODES; j++) {
      weights_input_hidden[i][j] = (double)rand() / RAND_MAX;
    }
  }
  for (i = 0; i < NUM_HIDDEN_NODES; i++) {
    weights_hidden_output[i] = (double)rand() / RAND_MAX;
  }
}

double sigmoid(double x) {
  return 1 / (1 + exp(-x));
}

void feedforward(double *input) {
  int i, j;

  for (i = 0; i < NUM_HIDDEN_NODES; i++) {
    hidden_layer[i] = 0;
    for (j = 0; j < NUM_INPUTS; j++) {
      hidden_layer[i] += input[j] * weights_input_hidden[j][i];
    }
    hidden_layer[i] = sigmoid(hidden_layer[i]);
  }

  output = 0;
  for (i = 0; i < NUM_HIDDEN_NODES; i++) {
    output += hidden_layer[i] * weights_hidden_output[i];
  }
  output = sigmoid(output);
}

int main(int argc, char *argv[]) {
  int i, j;

  initialize_weights();

  for (i = 0; i < NUM_SAMPLES; i++) {
    feedforward(inputs[i]);
    printf("Sample %d: predicted=%f, actual=%f\n", i, output, expected_outputs[i]);
  }

  return 0;
}
