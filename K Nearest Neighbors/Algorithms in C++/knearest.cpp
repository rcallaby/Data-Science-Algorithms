#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

// Structure to represent a data point
struct DataPoint {
    double x;
    double y;
    int label;
};

// Function to calculate the Euclidean distance between two points
double calculateDistance(const DataPoint& p1, const DataPoint& p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return std::sqrt(dx * dx + dy * dy);
}

// Function to predict the label of a data point using the KNN algorithm
int predictLabel(const std::vector<DataPoint>& dataset, const DataPoint& queryPoint, int k) {
    // Create a vector to store the distances between the query point and dataset points
    std::vector<std::pair<double, int>> distances;

    // Calculate the distances between the query point and all dataset points
    for (const DataPoint& dataPoint : dataset) {
        double distance = calculateDistance(dataPoint, queryPoint);
        distances.emplace_back(distance, dataPoint.label);
    }

    // Sort the distances in ascending order
    std::sort(distances.begin(), distances.end());

    // Count the labels of the k nearest neighbors
    std::vector<int> labelCount(k, 0);
    for (int i = 0; i < k; ++i) {
        int label = distances[i].second;
        labelCount[label]++;
    }

    // Find the most frequent label among the k nearest neighbors
    int predictedLabel = -1;
    int maxCount = 0;
    for (int i = 0; i < k; ++i) {
        if (labelCount[i] > maxCount) {
            predictedLabel = i;
            maxCount = labelCount[i];
        }
    }

    return predictedLabel;
}

int main() {
    // Create a dataset with labeled points
    std::vector<DataPoint> dataset = {
        {1.0, 1.5, 0},
        {2.0, 1.0, 0},
        {3.0, 3.0, 1},
        {4.0, 4.0, 1}
    };

    // Create a query point
    DataPoint queryPoint = {2.5, 2.5, 0};

    // Set the value of k (number of nearest neighbors)
    int k = 3;

    // Predict the label for the query point using the KNN algorithm
    int predictedLabel = predictLabel(dataset, queryPoint, k);

    // Print the predicted label
    std::cout << "Predicted Label: " << predictedLabel << std::endl;

    return 0;
}
