using System;
using System.Collections.Generic;
using System.Linq;

// Structure to represent a data point
struct DataPoint
{
    public double X;
    public double Y;
    public int Label;
}

class Program
{
    // Function to calculate the Euclidean distance between two points
    static double CalculateDistance(DataPoint p1, DataPoint p2)
    {
        double dx = p1.X - p2.X;
        double dy = p1.Y - p2.Y;
        return Math.Sqrt(dx * dx + dy * dy);
    }

    // Function to predict the label of a data point using the KNN algorithm
    static int PredictLabel(List<DataPoint> dataset, DataPoint queryPoint, int k)
    {
        // Create a list to store the distances between the query point and dataset points
        List<Tuple<double, int>> distances = new List<Tuple<double, int>>();

        // Calculate the distances between the query point and all dataset points
        foreach (DataPoint dataPoint in dataset)
        {
            double distance = CalculateDistance(dataPoint, queryPoint);
            distances.Add(new Tuple<double, int>(distance, dataPoint.Label));
        }

        // Sort the distances in ascending order
        distances.Sort();

        // Count the labels of the k nearest neighbors
        int[] labelCount = new int[k];
        for (int i = 0; i < k; i++)
        {
            int label = distances[i].Item2;
            labelCount[label]++;
        }

        // Find the most frequent label among the k nearest neighbors
        int predictedLabel = -1;
        int maxCount = 0;
        for (int i = 0; i < k; i++)
        {
            if (labelCount[i] > maxCount)
            {
                predictedLabel = i;
                maxCount = labelCount[i];
            }
        }

        return predictedLabel;
    }

    static void Main(string[] args)
    {
        // Create a dataset with labeled points
        List<DataPoint> dataset = new List<DataPoint>
        {
            new DataPoint { X = 1.0, Y = 1.5, Label = 0 },
            new DataPoint { X = 2.0, Y = 1.0, Label = 0 },
            new DataPoint { X = 3.0, Y = 3.0, Label = 1 },
            new DataPoint { X = 4.0, Y = 4.0, Label = 1 }
        };

        // Create a query point
        DataPoint queryPoint = new DataPoint { X = 2.5, Y = 2.5, Label = 0 };

        // Set the value of k (number of nearest neighbors)
        int k = 3;

        // Predict the label for the query point using the KNN algorithm
        int predictedLabel = PredictLabel(dataset, queryPoint, k);

        // Print the predicted label
        Console.WriteLine("Predicted Label: " + predictedLabel);
    }
}
