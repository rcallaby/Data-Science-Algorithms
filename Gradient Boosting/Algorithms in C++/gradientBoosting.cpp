#include <iostream>
#include <vector>
#include <xgboost/c_api.h>

int main() {
    // Sample data
    std::vector<float> labels = {1.0, 0.0, 1.0, 1.0, 0.0};
    std::vector<float> feature1 = {1.2, 0.5, 3.1, 1.7, 2.8};
    std::vector<float> feature2 = {0.8, 2.0, 1.5, 2.5, 1.0};

    // Create DMatrix for training data
    DMatrixHandle trainMatrix;
    XGDMatrixCreateFromMat(reinterpret_cast<float*>(&feature1[0]), labels.size(), 1, 0.0f, &trainMatrix);
    XGDMatrixSetFloatInfo(trainMatrix, "label", reinterpret_cast<float*>(&labels[0]));

    // Set feature names for better understanding
    std::vector<const char*> featureNames = {"Feature1", "Feature2"};
    XGDMatrixSetStrFeatureInfo(trainMatrix, "feature_names", &featureNames[0], featureNames.size());

    // Set booster parameters
    std::vector<const char*> boosterParams = {
        "objective", "binary:logistic",
        "eta", "0.3",
        "max_depth", "3",
        "eval_metric", "error"
    };

    // Train the model
    BoosterHandle booster;
    XGBoosterCreate(&trainMatrix, 1, &booster);
    XGBoosterSetParam(booster, "booster", "gbtree");
    for (int i = 0; i < boosterParams.size(); i += 2) {
        XGBoosterSetParam(booster, boosterParams[i], boosterParams[i + 1]);
    }
    XGBoosterTrain(booster, trainMatrix, 10, &booster);

    // Predict using the trained model
    std::vector<float> testFeature1 = {1.9, 0.1};
    std::vector<float> testFeature2 = {1.1, 2.6};
    DMatrixHandle testMatrix;
    XGDMatrixCreateFromMat(reinterpret_cast<float*>(&testFeature1[0]), testFeature1.size(), 1, 0.0f, &testMatrix);
    XGDMatrixSetFloatInfo(testMatrix, "feature_names", reinterpret_cast<const float*>(&featureNames[0]));
    bst_ulong outSize;
    const float* outResult;
    XGBoosterPredict(booster, testMatrix, 0, 0, &outSize, &outResult);

    // Print predictions
    std::cout << "Predictions:" << std::endl;
    for (bst_ulong i = 0; i < outSize; ++i) {
        std::cout << "Sample " << i + 1 << ": " << outResult[i] << std::endl;
    }

    // Clean up resources
    XGDMatrixFree(trainMatrix);
    XGDMatrixFree(testMatrix);
    XGBoosterFree(booster);

    return 0;
}
