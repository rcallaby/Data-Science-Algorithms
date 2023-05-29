#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class NaiveBayesClassifier {
private:
    unordered_map<string, int> classCounts;
    unordered_map<string, unordered_map<string, int>> featureCounts;
    unordered_map<string, int> featureTotalCounts;
    int totalCount;

public:
    NaiveBayesClassifier() : totalCount(0) {}

    void train(const vector<vector<string>>& data, const vector<string>& labels) {
        for (size_t i = 0; i < data.size(); ++i) {
            const vector<string>& features = data[i];
            const string& label = labels[i];

            // Increment class count
            ++classCounts[label];

            // Increment feature counts for each feature
            for (const string& feature : features) {
                ++featureCounts[label][feature];
                ++featureTotalCounts[feature];
            }

            ++totalCount;
        }
    }

    string predict(const vector<string>& features) {
        string bestLabel;
        double bestScore = -1.0;

        for (const auto& entry : classCounts) {
            const string& label = entry.first;
            int classCount = entry.second;

            double score = static_cast<double>(classCount) / totalCount;

            for (const string& feature : features) {
                int featureCount = featureCounts[label][feature];
                int totalFeatureCount = featureTotalCounts[feature];

                // Apply Laplace smoothing
                score *= (static_cast<double>(featureCount) + 1) / (totalFeatureCount + featureTotalCounts.size());
            }

            if (score > bestScore) {
                bestScore = score;
                bestLabel = label;
            }
        }

        return bestLabel;
    }
};

int main() {
    // Example usage
    NaiveBayesClassifier classifier;

    // Training data
    vector<vector<string>> data = {
        {"good", "awesome", "nice"},
        {"bad", "awful"},
        {"good", "excellent"},
        {"bad", "terrible", "horrible"}
    };

    vector<string> labels = {"positive", "negative", "positive", "negative"};

    classifier.train(data, labels);

    // Prediction
    vector<string> features = {"awesome", "nice"};
    string predictedLabel = classifier.predict(features);

    cout << "Predicted label: " << predictedLabel << endl;

    return 0;
}
