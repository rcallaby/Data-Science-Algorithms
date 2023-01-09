#include<stdio.h>
#include<math.h>

//Define a structure to store data
struct data {
	float x;
	float y;
};

//Function to calculate Euclidean distance between two data points
float euclidean_distance(struct data point1, struct data point2)
{
	return sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
}

//Function to find K nearest neighbors
void knn(struct data *points, int k, struct data point)
{
	float distances[10];
	int index[10];
	
	//Calculate the distance of the point from all other points
	for(int i=0; i<10; i++) {
		distances[i] = euclidean_distance(points[i], point);
		index[i] = i;
	}
	
	//Sort the distances in ascending order
	for(int i=0; i<10; i++) {
		// outer loop
		for(int j=i+1; j<10; j++) {
			if(distances[i] > distances[j]) {
				float temp = distances[i];
				distances[i] = distances[j];
				distances[j] = temp;
				
				int temp2 = index[i];
				index[i] = index[j];
				index[j] = temp2;
			}
		}
	}
	
	//Print the K nearest neighbors
	printf("K Nearest Neighbors:\n");
	for(int i=0; i<k; i++) {
		printf("Point %d: (%.2f, %.2f)\n", index[i], points[index[i]].x, points[index[i]].y);
	}
}

int main()
{
	//Create an array of 10 data points
	struct data points[10] = {
		{1.0, 0.0},
		{3.0, 1.0},
		{2.0, 3.0},
		{2.0, 1.0},
		{1.0, 2.0},
		{3.0, 2.0},
		{4.0, 1.0},
		{2.0, 2.0},
		{4.0, 0.0},
		{3.0, 0.0}
	};
	
	//Call the knn function to find the K nearest neighbors
	knn(points, 3, points[5]);
	
	return 0;
}