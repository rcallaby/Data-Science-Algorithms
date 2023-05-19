#include <iostream>
#include <vector>
#include <cmath>

struct Point {
    double x;
    double y;

    Point(double _x, double _y) : x(_x), y(_y) {}
};

double euclideanDistance(const Point& p1, const Point& p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return std::sqrt(dx * dx + dy * dy);
}

int assignCluster(const Point& point, const std::vector<Point>& centroids) {
    int cluster = 0;
    double minDistance = euclideanDistance(point, centroids[0]);

    for (int i = 1; i < centroids.size(); ++i) {
        double distance = euclideanDistance(point, centroids[i]);
        if (distance < minDistance) {
            minDistance = distance;
            cluster = i;
        }
    }

    return cluster;
}

Point calculateCentroid(const std::vector<Point>& points) {
    double sumX = 0.0;
    double sumY = 0.0;
    int numPoints = points.size();

    for (const Point& point : points) {
        sumX += point.x;
        sumY += point.y;
    }

    double centroidX = sumX / numPoints;
    double centroidY = sumY / numPoints;
    return Point(centroidX, centroidY);
}

std::vector<Point> kMeansClustering(const std::vector<Point>& data, int k, int maxIterations) {
    // Initialize centroids randomly
    std::vector<Point> centroids;
    for (int i = 0; i < k; ++i) {
        int randIndex = rand() % data.size();
        centroids.push_back(data[randIndex]);
    }

    std::vector<int> clusterAssignments(data.size(), -1); // -1 indicates unassigned

    int iter = 0;
    bool centroidsChanged = true;

    while (centroidsChanged && iter < maxIterations) {
        centroidsChanged = false;

        // Assign points to the nearest centroid
        for (int i = 0; i < data.size(); ++i) {
            int assignedCluster = assignCluster(data[i], centroids);
            if (clusterAssignments[i] != assignedCluster) {
                clusterAssignments[i] = assignedCluster;
                centroidsChanged = true;
            }
        }

        // Update centroids
        for (int i = 0; i < k; ++i) {
            std::vector<Point> clusterPoints;
            for (int j = 0; j < data.size(); ++j) {
                if (clusterAssignments[j] == i) {
                    clusterPoints.push_back(data[j]);
                }
            }

            if (!clusterPoints.empty()) {
                centroids[i] = calculateCentroid(clusterPoints);
            }
        }

        ++iter;
    }

    return centroids;
}

int main() {
    // Sample data points
    std::vector<Point> data = {
        {2.0, 3.0}, {3.0, 4.0}, {3.0, 3.0}, {5.0, 2.0},
        {6.0, 3.0}, {7.0, 4.0}, {7.0, 3.0}, {9.0, 2.0}
    };

    int k = 2;  // Number of clusters
    int maxIterations = 10;

    std::vector<Point> centroids = kMeansClustering(data, k, maxIterations);

    // Print final centroids
    std::cout << "Final centroids:\n";
    for (int i = 0; i < centroids.size(); ++i) {
        std::cout << "Centroid " << i + 1 << ": (" << centroids[i].x << ", " << centroids[i].y << ")\n";
    }

    return 0;
}
