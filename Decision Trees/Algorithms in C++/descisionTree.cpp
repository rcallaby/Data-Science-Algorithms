#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>

struct TreeNode {
    std::string feature;
    std::string targetValue;
    std::unordered_map<std::string, TreeNode*> children;

    TreeNode() {
        children = {};
    }
};

class DecisionTree {
private:
    TreeNode* root;

public:
    DecisionTree() {
        root = nullptr;
    }

    void train(const std::vector<std::vector<std::string>>& data, const std::vector<std::string>& features, const std::string& targetFeature) {
        root = buildTree(data, features, targetFeature);
    }

    TreeNode* buildTree(const std::vector<std::vector<std::string>>& data, std::vector<std::string> features, const std::string& targetFeature) {
        if (areAllInstancesSameClass(data, targetFeature)) {
            TreeNode* leafNode = new TreeNode();
            leafNode->targetValue = data[0][data[0].size() - 1];
            return leafNode;
        }

        if (features.empty()) {
            TreeNode* leafNode = new TreeNode();
            leafNode->targetValue = getMajorityClass(data, targetFeature);
            return leafNode;
        }

        std::string bestFeature = selectBestFeature(data, features, targetFeature);

        TreeNode* node = new TreeNode();
        node->feature = bestFeature;

        auto it = std::find(features.begin(), features.end(), bestFeature);
        features.erase(it);

        std::unordered_map<std::string, std::vector<std::vector<std::string>>> splitData = splitDataByFeature(data, bestFeature);

        for (auto& kvp : splitData) {
            std::string featureValue = kvp.first;
            std::vector<std::vector<std::string>> subset = kvp.second;

            TreeNode* childNode = buildTree(subset, features, targetFeature);
            node->children[featureValue] = childNode;
        }

        return node;
    }

    bool areAllInstancesSameClass(const std::vector<std::vector<std::string>>& data, const std::string& targetFeature) {
        std::string firstClass = data[0][data[0].size() - 1];
        for (const auto& instance : data) {
            if (instance[instance.size() - 1] != firstClass) {
                return false;
            }
        }
        return true;
    }

    std::string getMajorityClass(const std::vector<std::vector<std::string>>& data, const std::string& targetFeature) {
        std::unordered_map<std::string, int> classCounts;
        for (const auto& instance : data) {
            std::string targetValue = instance[instance.size() - 1];
            classCounts[targetValue]++;
        }

        std::string majorityClass;
        int maxCount = 0;
        for (const auto& kvp : classCounts) {
            if (kvp.second > maxCount) {
                majorityClass = kvp.first;
                maxCount = kvp.second;
            }
        }

        return majorityClass;
    }

    std::string selectBestFeature(const std::vector<std::vector<std::string>>& data, const std::vector<std::string>& features, const std::string& targetFeature) {
        double maxInfoGain = -std::numeric_limits<double>::max();
        std::string bestFeature;

        double baseEntropy = calculateEntropy(data, targetFeature);

        for (const auto& feature : features) {
            int featureIndex = std::distance(features.begin(), std::find(features.begin(), features.end(), feature));
            double infoGain = baseEntropy - calculateFeatureEntropy(data, featureIndex, targetFeature);
            if (infoGain > maxInfoGain) {
                maxInfoGain = infoGain;
                bestFeature = feature;
            }
        }

        return bestFeature;
    }

    double calculateEntropy(const std::vector<std::vector<std::string>>& data, const std::string& targetFeature) {
        std::unordered_map<std::string, int> classCounts;
        int totalCount = data.size();

        for (const auto& instance : data) {
            std::string targetValue = instance[instance.size() - 1];
            classCounts[targetValue]++;
        }

        double entropy = 0.0;
        for (const auto& kvp : classCounts) {
            double probability = static_cast<double>(kvp.second) / totalCount;
            entropy -= probability * log2(probability);
        }

        return entropy;
    }

    double calculateFeatureEntropy(const std::vector<std::vector<std::string>>& data, int featureIndex, const std::string& targetFeature) {
        std::unordered_map<std::string, int> featureCounts;
        std::unordered_map<std::string, std::unordered_map<std::string, int>> featureClassCounts;

        for (const auto& instance : data) {
            std::string featureValue = instance[featureIndex];
            if (featureCounts.find(featureValue) == featureCounts.end()) {
                featureCounts[featureValue] = 0;
                featureClassCounts[featureValue] = {};
            }

            std::string targetValue = instance[instance.size() - 1];
            if (featureClassCounts[featureValue].find(targetValue) == featureClassCounts[featureValue].end()) {
                featureClassCounts[featureValue][targetValue] = 0;
            }

            featureCounts[featureValue]++;
            featureClassCounts[featureValue][targetValue]++;
        }

        double featureEntropy = 0.0;
        int totalCount = data.size();

        for (const auto& kvp : featureClassCounts) {
            std::string featureValue = kvp.first;
            double featureProbability = static_cast<double>(featureCounts[featureValue]) / totalCount;

            double classEntropy = 0.0;
            for (const auto& classCount : kvp.second) {
                double classProbability = static_cast<double>(classCount.second) / featureCounts[featureValue];
                classEntropy -= classProbability * log2(classProbability);
            }

            featureEntropy += featureProbability * classEntropy;
        }

        return featureEntropy;
    }

    std::unordered_map<std::string, std::vector<std::vector<std::string>>> splitDataByFeature(const std::vector<std::vector<std::string>>& data, int featureIndex) {
        std::unordered_map<std::string, std::vector<std::vector<std::string>>> splitData;

        for (const auto& instance : data) {
            std::string featureValue = instance[featureIndex];
            splitData[featureValue].push_back(instance);
        }

        return splitData;
    }

    std::string classify(const std::vector<std::string>& instance) {
        return traverseTree(root, instance);
    }

    std::string traverseTree(TreeNode* node, const std::vector<std::string>& instance) {
        if (node->children.empty()) {
            return node->targetValue;
        }

        std::string featureValue = instance[std::distance(features.begin(), std::find(features.begin(), features.end(), node->feature))];
        if (node->children.find(featureValue) == node->children.end()) {
            return "";
        }

        TreeNode* childNode = node->children[featureValue];
        return traverseTree(childNode, instance);
    }
};

int main() {
    std::vector<std::vector<std::string>> trainingData = {
        {"Sunny", "Hot", "High", "Weak", "No"},
        {"Sunny", "Hot", "High", "Strong", "No"},
        {"Overcast", "Hot", "High", "Weak", "Yes"},
        {"Rain", "Mild", "High", "Weak", "Yes"},
        {"Rain", "Cool", "Normal", "Weak", "Yes"},
        {"Rain", "Cool", "Normal", "Strong", "No"},
        {"Overcast", "Cool", "Normal", "Strong", "Yes"},
        {"Sunny", "Mild", "High", "Weak", "No"},
        {"Sunny", "Cool", "Normal", "Weak", "Yes"},
        {"Rain", "Mild", "Normal", "Weak", "Yes"},
        {"Sunny", "Mild", "Normal", "Strong", "Yes"},
        {"Overcast", "Mild", "High", "Strong", "Yes"},
        {"Overcast", "Hot", "Normal", "Weak", "Yes"},
        {"Rain", "Mild", "High", "Strong", "No"}
    };

    std::vector<std::string> features = { "Outlook", "Temperature", "Humidity", "Wind" };
    std::string targetFeature = "PlayTennis";

    DecisionTree decisionTree;
    decisionTree.train(trainingData, features, targetFeature);

    std::vector<std::string> instance = { "Rain", "Mild", "High", "Weak" };
    std::string predictedClass = decisionTree.classify(instance);

    std::cout << "Predicted class: " << predictedClass << std::endl;

    return 0;
}
