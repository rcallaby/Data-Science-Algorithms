using System;

class NeuralNetwork
{
    static void Main()
    {
        // Define the neural network architecture
        int inputNodes = 2;
        int hiddenNodes = 3;
        int outputNodes = 1;

        // Initialize the weights
        double[,] inputToHiddenWeights = new double[inputNodes, hiddenNodes];
        double[,] hiddenToOutputWeights = new double[hiddenNodes, outputNodes];
        Random rand = new Random();
        for (int i = 0; i < inputNodes; i++)
        {
            for (int j = 0; j < hiddenNodes; j++)
            {
                inputToHiddenWeights[i, j] = rand.NextDouble() - 0.5;
            }
        }
        for (int i = 0; i < hiddenNodes; i++)
        {
            for (int j = 0; j < outputNodes; j++)
            {
                hiddenToOutputWeights[i, j] = rand.NextDouble() - 0.5;
            }
        }

        // Define the input and output data
        double[,] inputData = new double[,]
        {
            {0, 0},
            {0, 1},
            {1, 0},
            {1, 1}
        };
        double[,] outputData = new double[,]
        {
            {0},
            {1},
            {1},
            {0}
        };

        // Train the neural network
        double learningRate = 0.1;
        int epochs = 10000;
        for (int epoch = 0; epoch < epochs; epoch++)
        {
            double error = 0;
            for (int i = 0; i < inputData.GetLength(0); i++)
            {
                double[] input = new double[inputNodes];
                for (int j = 0; j < inputNodes; j++)
                {
                    input[j] = inputData[i, j];
                }

                // Forward pass
                double[] hidden = new double[hiddenNodes];
                for (int j = 0; j < hiddenNodes; j++)
                {
                    double sum = 0;
                    for (int k = 0; k < inputNodes; k++)
                    {
                        sum += input[k] * inputToHiddenWeights[k, j];
                    }
                    hidden[j] = Sigmoid(sum);
                }

                double[] output = new double[outputNodes];
                for (int j = 0; j < outputNodes; j++)
                {
                    double sum = 0;
                    for (int k = 0; k < hiddenNodes; k++)
                    {
                        sum += hidden[k] * hiddenToOutputWeights[k, j];
                    }
                    output[j] = Sigmoid(sum);
                }

                // Backward pass
                double[] target = new double[outputNodes];
                for (int j = 0; j < outputNodes; j++)
                {
                    target[j] = outputData[i, j];
                    double errorSignal = (target[j] - output[j]) * SigmoidDerivative(output[j]);
                    error += Math.Abs(target[j] - output[j]);

                    for (int k = 0; k < hiddenNodes; k++)
                    {
                        hiddenToOutputWeights[k, j] += learningRate * errorSignal * hidden[k];
                    }
                }

                for (int j = 0; j < hiddenNodes; j++)
                {
                    double errorSignal = 0;
                    for (int k = 0; k < outputNodes; k++)
                    {
                        errorSignal += (errorSignal *= SigmoidDerivative(hidden[j]));
                    }
                   

                    for (int k = 0; k < inputNodes; k++)
                    {
                        inputToHiddenWeights[k, j] += learningRate * errorSignal * input[k];
                    }
                }
            }

            // Print the error every 1000 epochs
            if (epoch % 1000 == 0)
            {
                Console.WriteLine($"Epoch {epoch}: Error = {error}");
            }

            // Stop early if the error is below a threshold
            if (error < 0.01)
            {
                Console.WriteLine($"Training complete after {epoch} epochs");
                break;
            }
        }

        // Test the neural network
        Console.WriteLine("Testing...");
        for (int i = 0; i < inputData.GetLength(0); i++)
        {
            double[] input = new double[inputNodes];
            for (int j = 0; j < inputNodes; j++)
            {
                input[j] = inputData[i, j];
            }

            double[] hidden = new double[hiddenNodes];
            for (int j = 0; j < hiddenNodes; j++)
            {
                double sum = 0;
                for (int k = 0; k < inputNodes; k++)
                {
                    sum += input[k] * inputToHiddenWeights[k, j];
                }
                hidden[j] = Sigmoid(sum);
            }

            double[] output = new double[outputNodes];
            for (int j = 0; j < outputNodes; j++)
            {
                double sum = 0;
                for (int k = 0; k < hiddenNodes; k++)
                {
                    sum += hidden[k] * hiddenToOutputWeights[k, j];
                }
                output[j] = Sigmoid(sum);
            }

            Console.WriteLine($"Input: {input[0]}, {input[1]} => Output: {output[0]}");
        }
    }

    // Sigmoid activation function
    static double Sigmoid(double x)
    {
        return 1.0 / (1.0 + Math.Exp(-x));
    }

    // Derivative of the sigmoid activation function
    static double SigmoidDerivative(double x)
    {
        return x * (1 - x);
    }
}
