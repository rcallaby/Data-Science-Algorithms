using System;

class LogisticRegression
{
    private double[] weights;

    public void Train(double[][] inputs, int[] labels, double learningRate, int numIterations)
    {
        int numFeatures = inputs[0].Length;
        weights = new double[numFeatures + 1]; // +1 for the bias term

        for (int iteration = 0; iteration < numIterations; iteration++)
        {
            for (int i = 0; i < inputs.Length; i++)
            {
                double[] inputWithBias = new double[numFeatures + 1];
                Array.Copy(inputs[i], inputWithBias, numFeatures); // Copy input features
                inputWithBias[numFeatures] = 1.0; // Bias term

                double prediction = Predict(inputWithBias);
                double error = labels[i] - prediction;

                for (int j = 0; j < weights.Length; j++)
                {
                    weights[j] += learningRate * error * inputWithBias[j];
                }
            }
        }
    }

    public double Predict(double[] input)
    {
        double linearOutput = 0.0;

        for (int i = 0; i < input.Length; i++)
        {
            linearOutput += weights[i] * input[i];
        }

        return Sigmoid(linearOutput);
    }

    private double Sigmoid(double x)
    {
        return 1.0 / (1.0 + Math.Exp(-x));
    }
}

class Program
{
    static void Main()
    {
        // Training data
        double[][] inputs = new double[][]
        {
            new double[] { 1.0, 1.0 },
            new double[] { 2.0, 2.0 },
            new double[] { 3.0, 3.0 },
            new double[] { 4.0, 4.0 },
            new double[] { 5.0, 5.0 }
        };

        int[] labels = new int[] { 0, 0, 0, 1, 1 };

        // Create and train logistic regression model
        LogisticRegression logisticRegression = new LogisticRegression();
        logisticRegression.Train(inputs, labels, 0.1, 1000);

        // Test the model
        double[] testInput = new double[] { 6.0, 6.0 };
        double prediction = logisticRegression.Predict(testInput);

        Console.WriteLine("Prediction: " + prediction);
    }
}
