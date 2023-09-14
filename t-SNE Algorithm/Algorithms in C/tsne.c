#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define the structure for a 2D point
typedef struct Point {
    double x;
    double y;
} Point;

// Define the structure for a 2D vector
typedef struct Vector {
    double x;
    double y;
} Vector;

// Define the structure for a Barnes-Hut quadtree node
typedef struct QuadTreeNode {
    double x;
    double y;
    struct QuadTreeNode* NW;
    struct QuadTreeNode* NE;
    struct QuadTreeNode* SW;
    struct QuadTreeNode* SE;
} QuadTreeNode;

// Function to create a new point
Point createPoint(double x, double y) {
    Point p;
    p.x = x;
    p.y = y;
    return p;
}

// Function to create a new vector
Vector createVector(double x, double y) {
    Vector v;
    v.x = x;
    v.y = y;
    return v;
}

// Function to calculate the Euclidean distance between two points
double distance(Point p1, Point p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return sqrt(dx*dx + dy*dy);
}

// Function to initialize a Barnes-Hut quadtree node
QuadTreeNode* createNode(double x, double y) {
    QuadTreeNode* node = (QuadTreeNode*)malloc(sizeof(QuadTreeNode));
    node->x = x;
    node->y = y;
    node->NW = NULL;
    node->NE = NULL;
    node->SW = NULL;
    node->SE = NULL;
    return node;
}

// Function to build the Barnes-Hut quadtree
QuadTreeNode* buildQuadTree(Point* points, int N, double x0, double y0, double x1, double y1) {
    if (N == 0) return NULL;
    if (N == 1) return createNode(points[0].x, points[0].y);

    double xm = (x0 + x1) / 2.0;
    double ym = (y0 + y1) / 2.0;

    QuadTreeNode* node = createNode(xm, ym);

    Point* NW_points = NULL;
    Point* NE_points = NULL;
    Point* SW_points = NULL;
    Point* SE_points = NULL;
    int NW_N = 0;
    int NE_N = 0;
    int SW_N = 0;
    int SE_N = 0;

    for (int i = 0; i < N; i++) {
        if (points[i].x < xm) {
            if (points[i].y < ym) {
                NW_N++;
                NW_points = (Point*)realloc(NW_points, NW_N * sizeof(Point));
                NW_points[NW_N - 1] = points[i];
            } else {
                SW_N++;
                SW_points = (Point*)realloc(SW_points, SW_N * sizeof(Point));
                SW_points[SW_N - 1] = points[i];
            }
        } else {
            if (points[i].y < ym) {
                NE_N++;
                NE_points = (Point*)realloc(NE_points, NE_N * sizeof(Point));
                NE_points[NE_N - 1] = points[i];
            } else {
                SE_N++;
                SE_points = (Point*)realloc(SE_points, SE_N * sizeof(Point));
                SE_points[SE_N - 1] = points[i];
            }
        }
    }

    node->NW = buildQuadTree(NW_points, NW_N, x0, y0, xm, ym);
    node->NE = buildQuadTree(NE_points, NE_N, xm, y0, x1, ym);
    node->SW = buildQuadTree(SW_points, SW_N, x0, ym, xm, y1);
    node->SE = buildQuadTree(SE_points, SE_N, xm, ym, x1, y1);

    free(NW_points);
    free(NE_points);
    free(SW_points);
    free(SE_points);

    return node;
}

// Function to compute the force between two points
Vector computeForce(Point p1, Point p2) {
    double epsilon = 1e-5;
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    double d = sqrt(dx*dx + dy*dy) + epsilon;
    double force = 1.0 / (d * d);
    return createVector(force * dx / d, force * dy / d);
}

// Function to compute the net force on a point using the Barnes-Hut quadtree
Vector computeNetForce(Point* points, int N, QuadTreeNode* node, double theta, Point p) {
    if (node == NULL) return createVector(0, 0);

    double dx = node->x - p.x;
    double dy = node->y - p.y;
    double d = sqrt(dx*dx + dy*dy);
    
    if (d == 0) return createVector(0, 0);

    if (d / sqrt((node->NE->x - node->NW->x)*(node->NE->x - node->NW->x) + 
                (node->NW->y - node->SW->y)*(node->NW->y - node->SW->y)) < theta) {
        Vector force = computeForce(p, createPoint(node->x, node->y));
        return force;
    } else {
        Vector netForce = createVector(0, 0);
        if (node->NW != NULL) {
            Vector force = computeNetForce(points, N, node->NW, theta, p);
            netForce.x += force.x;
            netForce.y += force.y;
        }
        if (node->NE != NULL) {
            Vector force = computeNetForce(points, N, node->NE, theta, p);
            netForce.x += force.x;
            netForce.y += force.y;
        }
        if (node->SW != NULL) {
            Vector force = computeNetForce(points, N, node->SW, theta, p);
            netForce.x += force.x;
            netForce.y += force.y;
        }
        if (node->SE != NULL) {
            Vector force = computeNetForce(points, N, node->SE, theta, p);
            netForce.x += force.x;
            netForce.y += force.y;
        }
        return netForce;
    }
}

// Function to perform t-SNE
void tSNE(Point* X, int N, int D, Point* Y, int no_dims, double perplexity, int max_iter, double theta) {
    // Initialize low-dimensional representation randomly
    for (int i = 0; i < N; i++) {
        Y[i].x = (double)rand() / RAND_MAX;
        Y[i].y = (double)rand() / RAND_MAX;
    }

    // Compute pairwise affinities
    double* P = (double*)malloc(N * N * sizeof(double));
    double* sum_P = (double*)malloc(N * sizeof(double));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i != j) {
                double d = distance(X[i], X[j]);
                P[i*N + j] = exp(-d * d / (2 * perplexity * perplexity));
                sum_P[i] += P[i*N + j];
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            P[i*N + j] /= (sum_P[i] + 1e-10);
        }
    }

    // Perform iterations
    for (int iter = 0; iter < max_iter; iter++) {
        // Build the Barnes-Hut quadtree
        QuadTreeNode* root = buildQuadTree(Y, N, 0, 0, 1, 1);

        // Compute pairwise affinities in low-dimensional space
        double* Q = (double*)malloc(N * N * sizeof(double));
        double* sum_Q = (double*)malloc(N * sizeof(double));

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i != j) {
                    Vector force = computeNetForce(Y, N, root, theta, Y[i]);
                    double d = distance(Y[i], Y[j]);
                    Q[i*N + j] = 1.0 / (1.0 + (force.x * force.x + force.y * force.y) / (d * d));
                    sum_Q[i] += Q[i*N + j];
                }
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                Q[i*N + j] /= (sum_Q[i] + 1e-10);
            }
        }

        // Update low-dimensional representation
        for (int i = 0; i < N; i++) {
            for (int d = 0; d < no_dims; d++) {
                Y[i].x -= 4 * (P[i*N + i] - Q[i*N + i]) * (Y[i].x - Y[i].x);
                Y[i].y -= 4 * (P[i*N + i] - Q[i*N + i]) * (Y[i].y - Y[i].y);
            }
        }

        // Clean up
        free(Q);
        free(sum_Q);
        free(root);
    }

    // Clean up
    free(P);
    free(sum_P);
}

int main() {
    // Example usage
    int N = 10; // Number of data points
    Point X[] = { {0.0, 0.0}, {1.0, 1.0}, {2.0, 2.0}, {3.0, 3.0}, {4.0, 4.0},
                  {5.0, 5.0}, {6.0, 6.0}, {7.0, 7.0}, {8.0, 8.0}, {9.0, 9.0} };
    int D = 2; // Dimensionality of the input data
    Point Y[N]; // Array to store low-dimensional representation

    int no_dims = 2; // Output dimensionality (usually 2 for visualization)
    double perplexity = 5.0; // Perplexity parameter (adjust as needed)
    int max_iter = 1000; // Maximum number of iterations
    double theta = 0.5; // Barnes-Hut approximation parameter

    tSNE(X, N, D, Y, no_dims, perplexity, max_iter, theta);

    // Print the result
    for (int i = 0; i < N; i++) {
        printf("Point %d: (%lf, %lf)\n", i, Y[i].x, Y[i].y);
    }

    return 0;
}
