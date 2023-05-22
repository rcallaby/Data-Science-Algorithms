package main

import (
	"fmt"
	"math"
	"math/rand"
)

// Point represents a 2D point in the dataset
type Point struct {
	X, Y float64
}

// Cluster represents a cluster of points
type Cluster struct {
	Center Point
	Points []Point
}

// euclideanDistance calculates the Euclidean distance between two points
func euclideanDistance(p1, p2 Point) float64 {
	dx := p2.X - p1.X
	dy := p2.Y - p1.Y
	return math.Sqrt(dx*dx + dy*dy)
}

// findNearestCluster finds the nearest cluster for a given point
func findNearestCluster(point Point, clusters []Cluster) int {
	nearestIndex := 0
	minDistance := math.Inf(1)

	for i, cluster := range clusters {
		distance := euclideanDistance(point, cluster.Center)
		if distance < minDistance {
			minDistance = distance
			nearestIndex = i
		}
	}

	return nearestIndex
}

// updateCenters updates the cluster centers based on the current points
func updateCenters(clusters []Cluster) {
	for i := range clusters {
		sumX := 0.0
		sumY := 0.0
		numPoints := len(clusters[i].Points)

		for _, point := range clusters[i].Points {
			sumX += point.X
			sumY += point.Y
		}

		if numPoints > 0 {
			clusters[i].Center.X = sumX / float64(numPoints)
			clusters[i].Center.Y = sumY / float64(numPoints)
		}
	}
}

// kMeans performs the K-means clustering algorithm
func kMeans(points []Point, k int) []Cluster {
	clusters := make([]Cluster, k)
	// Initialize random cluster centers
	for i := range clusters {
		clusters[i].Center = Point{X: rand.Float64(), Y: rand.Float64()}
	}

	for {
		// Assign points to the nearest cluster
		for i := range clusters {
			clusters[i].Points = nil
		}

		for _, point := range points {
			nearestIndex := findNearestCluster(point, clusters)
			clusters[nearestIndex].Points = append(clusters[nearestIndex].Points, point)
		}

		// Backup the old centers to check convergence
		oldCenters := make([]Point, k)
		copy(oldCenters, getCenters(clusters))

		// Update cluster centers
		updateCenters(clusters)

		// Check convergence
		newCenters := getCenters(clusters)
		converged := true
		for i := range oldCenters {
			if euclideanDistance(oldCenters[i], newCenters[i]) > 0.001 {
				converged = false
				break
			}
		}

		if converged {
			break
		}
	}

	return clusters
}

// getCenters returns the current cluster centers
func getCenters(clusters []Cluster) []Point {
	centers := make([]Point, len(clusters))
	for i, cluster := range clusters {
		centers[i] = cluster.Center
	}
	return centers
}

func main() {
	// Generate random points
	rand.Seed(42)
	numPoints := 100
	points := make([]Point, numPoints)
	for i := 0; i < numPoints; i++ {
		points[i] = Point{X: rand.Float64(), Y: rand.Float64()}
	}

	// Run K-means clustering
	k := 3
	clusters := kMeans(points, k)

	// Print cluster information
	for i, cluster := range clusters {
		fmt.Printf("Cluster %d:\n", i+1)
		fmt.Printf("Center: (%.2f, %.2f)\n", cluster.Center.X, cluster.Center.Y)
		fmt.Println("Points:")
		for _, point := range cluster.Points {
			fmt.Printf("(%.2f, %.2f)\n", point.X, point.Y)
		}
		fmt.Println()
	}
}
