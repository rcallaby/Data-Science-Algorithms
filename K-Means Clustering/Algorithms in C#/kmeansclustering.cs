using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    static void Main(string[] args)
    {
        // Input data points
        double[][] dataPoints = new double[][]
        {
            new double[] { 1, 2 },
            new double[] { 1, 4 },
            new double[] { 1, 0 },
            new double[] { 4, 2 },
            new double[] { 4, 4 },
            new double[] { 4, 0 }
        };

        // Number of clusters
        int k = 2;

        // Run k-means clustering
        KMeansClustering kmeans = new KMeansClustering();
        List<List<double[]>> clusters = kmeans.Cluster(dataPoints, k);

        // Print cluster results
        for (int i = 0; i < clusters.Count; i++)
        {
            Console.WriteLine("Cluster " + (i + 1) + ":");
            foreach (double[] point in clusters[i])
            {
                Console.WriteLine("(" + point[0] + ", " + point[1] + ")");
            }
            Console.WriteLine();
        }
    }
}

class KMeansClustering
{
    public List<List<double[]>> Cluster(double[][] dataPoints, int k)
    {
        // Randomly initialize centroids
        double[][] centroids = InitializeCentroids(dataPoints, k);

        // Initialize clusters
        List<List<double[]>> clusters = new List<List<double[]>>();
        for (int i = 0; i < k; i++)
        {
            clusters.Add(new List<double[]>());
        }

        // Assign data points to clusters
        bool converged = false;
        while (!converged)
        {
            // Clear clusters
            foreach (List<double[]> cluster in clusters)
            {
                cluster.Clear();
            }

            // Assign each data point to the nearest centroid
            for (int i = 0; i < dataPoints.Length; i++)
            {
                double[] point = dataPoints[i];
                int clusterIndex = FindNearestCentroid(point, centroids);
                clusters[clusterIndex].Add(point);
            }

            // Recalculate centroids
            double[][] newCentroids = CalculateCentroids(clusters);

            // Check for convergence
            converged = CentroidsConverged(centroids, newCentroids);

            // Update centroids
            centroids = newCentroids;
        }

        return clusters;
    }

    private double[][] InitializeCentroids(double[][] dataPoints, int k)
    {
        Random random = new Random();
        int numPoints = dataPoints.Length;
        double[][] centroids = new double[k][];
        HashSet<int> selectedIndices = new HashSet<int>();

        for (int i = 0; i < k; i++)
        {
            int selectedIndex;
            do
            {
                selectedIndex = random.Next(numPoints);
            } while (selectedIndices.Contains(selectedIndex));

            selectedIndices.Add(selectedIndex);
            centroids[i] = dataPoints[selectedIndex];
        }

        return centroids;
    }

    private int FindNearestCentroid(double[] point, double[][] centroids)
    {
        int nearestIndex = 0;
        double nearestDistance = Distance(point, centroids[0]);

        for (int i = 1; i < centroids.Length; i++)
        {
            double distance = Distance(point, centroids[i]);
            if (distance < nearestDistance)
            {
                nearestIndex = i;
                nearestDistance = distance;
            }
        }

        return nearestIndex;
    }

    private double[][] CalculateCentroids(List<List<double[]>> clusters)
    {
        int k = clusters.Count;
        double[][] centroids = new double[k][];

        for (int i = 0; i < k; i++)
        {
            List<double[]> cluster = clusters[i];
            int numPoints = cluster.Count;
            double[] centroid = new double[cluster[0].Length];

            for (int j = 0; j < centroid.Length; j++)
            {
                double sum = 0;
                for (int p = 0; p < numPoints; p++)
                {
                    sum += cluster[p][j];
                }
                centroid[j] = sum / numPoints;
            }

            centroids[i] = centroid;
        }

        return centroids;
    }

    private bool CentroidsConverged(double[][] centroids1, double[][] centroids2)
    {
        for (int i = 0; i < centroids1.Length; i++)
        {
            if (!centroids1[i].SequenceEqual(centroids2[i]))
            {
                return false;
            }
        }
        return true;
    }

    private double Distance(double[] point1, double[] point2)
    {
        double sum = 0;
        for (int i = 0; i < point1.Length; i++)
        {
            double diff = point1[i] - point2[i];
            sum += diff * diff;
        }
        return Math.Sqrt(sum);
    }
}
