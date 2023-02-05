#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_FEATURES 4
#define NUM_LABELS 2
#define NUM_SAMPLES 8

float training_data[NUM_SAMPLES][NUM_FEATURES + 1] = 
{
  {1.0, 1.0, 1.0, 1.0, 1.0},
  {1.0, 1.0, 1.0, 0.0, 0.0},
  {0.0, 1.0, 1.0, 1.0, 0.0},
  {0.0, 1.0, 0.0, 1.0, 0.0},
  {0.0, 0.0, 1.0, 1.0, 0.0},
  {1.0, 0.0, 0.0, 0.0, 1.0},
  {0.0, 0.0, 0.0, 0.0, 1.0},
  {1.0, 1.0, 1.0, 0.0, 1.0}
};

float class_probabilities[NUM_LABELS];
float feature_probabilities[NUM_LABELS][NUM_FEATURES];

void calculate_class_probabilities()
{
  int i, j;
  int count[NUM_LABELS] = {0};
  
  for (i = 0; i < NUM_SAMPLES; i++) 
  {
    int class = (int)training_data[i][NUM_FEATURES];
    count[class]++;
  }
  
  for (i = 0; i < NUM_LABELS; i++) 
  {
    class_probabilities[i] = (float)count[i] / NUM_SAMPLES;
  }
}

void calculate_feature_probabilities()
{
  int i, j, k;
  int count[NUM_LABELS][NUM_FEATURES] = {{0}};
  int num_occurrences[NUM_LABELS] = {0};
  
  for (i = 0; i < NUM_SAMPLES; i++) 
  {
    int class = (int)training_data[i][NUM_FEATURES];
    num_occurrences[class]++;
    
    for (j = 0; j < NUM_FEATURES; j++) 
    {
      if (training_data[i][j] == 1.0) 
      {
        count[class][j]++;
      }
    }
  }
  
  for (i = 0; i < NUM_LABELS; i++) 
  {
    for (j = 0; j < NUM_FEATURES; j++) 
    {
      feature_probabilities[i][j] = (float)count[i][j] / num_occurrences[i];
    }
  }
}

int predict(float sample[NUM_FEATURES])
{
  int i, j;
  float probability[NUM_LABELS];
  
  for (i = 0; i < NUM_LABELS; i++) 
  {
    probability[i] = log(class_probabilities[i]);
    for (j = 0; j < NUM_FEATURES; j++) 
    {
      if (sample[j] == 1.0) 
      {
        probability[i] += log(feature_probabilities[i][j]);
      } 
      else 
      {
        probability[i] += log(1 - feature_probabilities[i][j]);
      }
    }
  }
  
  int max_index = 0;
  for (i = 1; i < NUM_LABELS; i++) 
  {
    if (probability[i] > probability[max_index]) 
    {
      max_index = i;
    }
  }
  
  return max_index;
}

int main()
{
  int i;
  float sample[NUM_FEATURES];
  
  calculate_class_probabilities();
  calculate_feature_probabilities();
  
  printf("Enter features for the sample: \n");
  for (i = 0; i < NUM_FEATURES; i++) 
  {
    printf("Feature %d: ", i+1);
    scanf("%f", &sample[i]);
  }
  
  int prediction = predict(sample);
  printf("\nPrediction: Class %d\n", prediction + 1);
  
  return 0;
}
