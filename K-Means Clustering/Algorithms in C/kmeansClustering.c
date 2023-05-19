#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 100  // Number of data points
#define K 3    // Number of clusters
#define D 2    // Dimension of data points

double data[N][D] = {{1.0, 2.0}, {2.0, 1.0}, {4.0, 4.0}, {5.0, 5.0}, {6.0, 5.0}, {9.0, 10.0}, {10.0, 8.0}, {10.0, 10.0}, {12.0, 9.0}, {13.0, 11.0}};

double centroids[K][D] = {{1.0, 2.0}, {4.0, 4.0}, {10.0, 8.0}}; // Initial centroids

int cluster[N]; // Cluster assignment of each data point

void assign_clusters() {
    for (int i = 0; i < N; i++) {
        double min_distance = INFINITY;
        int closest_cluster = 0;
        for (int j = 0; j < K; j++) {
            double distance = 0.0;
            for (int d = 0; d < D; d++) {
                distance += pow(data[i][d] - centroids[j][d], 2);
            }
            if (distance < min_distance) {
                min_distance = distance;
                closest_cluster = j;
            }
        }
        cluster[i] = closest_cluster;
    }
}

void update_centroids() {
    int counts[K] = {0};
    for (int j = 0; j < K; j++) {
        for (int d = 0; d < D; d++) {
            centroids[j][d] = 0.0;
        }
    }
    for (int i = 0; i < N; i++) {
        int j = cluster[i];
        for (int d = 0; d < D; d++) {
            centroids[j][d] += data[i][d];
        }
        counts[j]++;
    }
    for (int j = 0; j < K; j++) {
        for (int d = 0; d < D; d++) {
            centroids[j][d] /= counts[j];
        }
    }
}

void print_clusters() {
    for (int j = 0; j < K; j++) {
        printf("Cluster %d:\n", j);
        for (int i = 0; i < N; i++) {
            if (cluster[i] == j) {
                printf("(%f, %f)\n", data[i][0], data[i][1]);
            }
        }
    }
}

int main() {
    for (int iter = 0; iter < 10; iter++) {
        assign_clusters();
        update_centroids();
    }
    print_clusters();
    return 0;
}
