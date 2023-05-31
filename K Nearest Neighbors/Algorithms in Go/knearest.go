package main

import (
	"fmt"
	"math"
	"sort"
)

type DataPoint struct {
	X float64
	Y float64
}

type Distance struct {
	Point  DataPoint
	Dist   float64
	Target string
}

type ByDistance []Distance

func (a ByDistance) Len() int           { return len(a) }
func (a ByDistance) Swap(i, j int)      { a[i], a[j] = a[j], a[i] }
func (a ByDistance) Less(i, j int) bool { return a[i].Dist < a[j].Dist }

func main() {
	// Training data
	trainingData := []DataPoint{
		{2.0, 4.0},
		{4.0, 6.0},
		{2.5, 5.0},
		{2.2, 4.3},
		{3.5, 5.5},
		{1.8, 3.8},
		{4.5, 6.7},
		{3.3, 4.9},
	}

	// Test point
	testPoint := DataPoint{3.0, 5.0}

	// Number of nearest neighbors
	k := 3

	// Compute distances
	distances := make([]Distance, len(trainingData))
	for i, point := range trainingData {
		distances[i] = Distance{
			Point:  point,
			Dist:   euclideanDistance(point, testPoint),
			Target: "unknown",
		}
	}

	// Sort distances
	sort.Sort(ByDistance(distances))

	// Get k nearest neighbors
	neighbors := distances[:k]

	// Count targets
	targets := make(map[string]int)
	for _, neighbor := range neighbors {
		targets[neighbor.Target]++
	}

	// Get most common target
	var maxCount int
	var target string
	for t, count := range targets {
		if count > maxCount {
			maxCount = count
			target = t
		}
	}

	fmt.Println("Test point:", testPoint)
	fmt.Println("Predicted target:", target)
}

// Euclidean distance between two data points
func euclideanDistance(a, b DataPoint) float64 {
	dx := a.X - b.X
	dy := a.Y - b.Y
	return math.Sqrt(dx*dx + dy*dy)
}
