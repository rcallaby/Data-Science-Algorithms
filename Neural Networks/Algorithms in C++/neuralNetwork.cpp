#include <iostream>
#include <vector>
#include <random>
#include <cmath>

using namespace std;

class NeuralNetwork
{
public:
    NeuralNetwork(int num_inputs, int num_outputs, int num_hidden)
    {
        // Initialize the weights for the input layer
        for (int i = 0; i < num_inputs; i++)
        {
            vector<double> row;
            for (int j = 0; j < num_hidden; j++)
            {
                row.push_back(get_random());
            }
            input_weights.push_back(row);
        }

        // Initialize the weights for the output layer
        for (int i = 0; i < num_hidden; i++)
        {
            vector<double> row;
            for (int j = 0; j < num_outputs; j++)
            {
                row.push_back(get_random());
            }
            output_weights.push_back(row);
        }

        // Initialize the biases
        for (int i = 0; i < num_hidden; i++)
        {
            hidden_biases.push_back(get_random());
        }
        for (int i = 0; i < num_outputs; i++)
        {
            output_biases.push_back(get_random());
        }
    }

    double get_random()
    {
        static random_device rd;
        static mt19937 gen(rd());
        static uniform_real_distribution<double> dis(-1, 1);
        return dis(gen);
    }

    vector<double> predict(vector<double> input)
    {
        // Calculate the output of the hidden layer
        vector<double> hidden_output(hidden_biases.size());
        for (int i = 0; i < hidden_biases.size(); i++)
        {
            double weighted_sum = 0;
            for (int j = 0; j < input.size(); j++)
            {
                weighted_sum += input[j] * input_weights[j][i];
            }
            weighted_sum += hidden_biases[i];
            hidden_output[i] = sigmoid(weighted_sum);
        }

        // Calculate the output of the output layer
        vector<double> output(output_biases.size());
        for (int i = 0; i < output_biases.size(); i++)
        {
            double weighted_sum = 0;
            for (int j = 0; j < hidden_output.size(); j++)
            {
                weighted_sum += hidden_output[j] * output_weights[j][i];
            }
            weighted_sum += output_biases[i];
            output[i] = sigmoid(weighted_sum);
        }

        return output;
    }

    double sigmoid(double x)
    {
        return 1 / (1 + exp(-x));
    }

private:
    vector<vector<double>> input_weights;
    vector<vector<double>> output_weights;
    vector<double> hidden_biases;
    vector<double> output_biases;
};

int main()
{
    // Create a neural network with 2 inputs, 1 output, and 3 hidden neurons
    NeuralNetwork nn(2, 1, 3);

    // Test the neural network
    vector<double> input = {1, 2};
    vector<double> output = nn.predict(input);
    cout << "Output: " << output[0] << endl;

    return 0;
}
