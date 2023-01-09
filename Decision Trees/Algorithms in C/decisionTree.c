#include <stdio.h>
/*
    This is a very simplistic demonstration program that shows a rudimentary decision tree
*/

int main() {
  int age;
  char gender;
  printf("Enter your age: ");
  scanf("%d", &age);
  printf("Enter your gender (M/F): ");
  scanf(" %c", &gender);

  if (age < 18) {
    printf("You are a minor.\n");
  } else if (age < 65) {
    printf("You are an adult.\n");
  } else {
    printf("You are a senior citizen.\n");
  }

  if (gender == 'M') {
    printf("You are male.\n");
  } else if (gender == 'F') {
    printf("You are female.\n");
  } else {
    printf("Invalid gender.\n");
  }

  return 0;
}
