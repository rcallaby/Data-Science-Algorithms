#include <iostream>
#include <cmath>
#include <vector>

// Define the Logistic Regression class
class LogisticRegression {
private:
    std::vector<double> weights;
    double learningRate;
    int numIterations;

public:
    LogisticRegression(double learningRate, int numIterations)
        : learningRate(learningRate), numIterations(numIterations) {}

    // Sigmoid function
    double sigmoid(double z) {
        return 1 / (1 + exp(-z));
    }

    // Training function
    void train(const std::vector<std::vector<double>>& X, const std::vector<int>& y) {
        int numSamples = X.size();
        int numFeatures = X[0].size();

        // Initialize weights with zeros
        weights.resize(numFeatures, 0.0);

        // Gradient descent optimization
        for (int iter = 0; iter < numIterations; ++iter) {
            std::vector<double> gradients(numFeatures, 0.0);

            // Compute gradients
            for (int i = 0; i < numSamples; ++i) {
                double prediction = predict(X[i]);
                double error = prediction - y[i];

                for (int j = 0; j < numFeatures; ++j) {
                    gradients[j] += error * X[i][j];
                }
            }

            // Update weights
            for (int j = 0; j < numFeatures; ++j) {
                weights[j] -= learningRate * gradients[j];
            }
        }
    }

    // Prediction function
    double predict(const std::vector<double>& sample) {
        double z = 0.0;
        int numFeatures = sample.size();

        for (int j = 0; j < numFeatures; ++j) {
            z += weights[j] * sample[j];
        }

        return sigmoid(z);
    }
};

int main() {
    // Training data
    std::vector<std::vector<double>> X = { {2.0, 1.0}, {4.0, 5.0}, {6.0, 3.0}, {8.0, 7.0} };
    std::vector<int> y = { 0, 1, 0, 1 };

    // Create and train the logistic regression model
    LogisticRegression model(0.1, 1000);
    model.train(X, y);

    // Test data
    std::vector<double> sample = { 3.0, 2.0 };

    // Make a prediction
    double prediction = model.predict(sample);
    std::cout << "Prediction: " << prediction << std::endl;

    return 0;
}
