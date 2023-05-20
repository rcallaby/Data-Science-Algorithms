#include <iostream>
#include <vector>
#include <svm.h>

int main() {
    // Create the training data
    std::vector<std::vector<double>> trainingData = {
        {2.0, 2.0},
        {1.0, 3.0},
        {3.0, 3.0},
        {4.0, 2.0}
    };

    // Create the labels for the training data
    std::vector<int> labels = {1, 1, -1, -1};

    // Create the SVM problem
    svm_problem prob;
    prob.l = trainingData.size();
    prob.x = new svm_node*[prob.l];
    prob.y = new double[prob.l];

    // Set up the SVM nodes
    for (int i = 0; i < prob.l; ++i) {
        prob.x[i] = new svm_node[3];
        prob.x[i][0].index = 1;
        prob.x[i][0].value = trainingData[i][0];
        prob.x[i][1].index = 2;
        prob.x[i][1].value = trainingData[i][1];
        prob.x[i][2].index = -1;  // Terminate the nodes with -1
        prob.y[i] = labels[i];
    }

    // Set up the SVM parameters
    svm_parameter param;
    svm_init_params(&param);
    param.svm_type = C_SVC;
    param.kernel_type = RBF;
    param.gamma = 0.5;
    param.C = 1;

    // Train the SVM model
    svm_model* model = svm_train(&prob, &param);

    // Create the test data
    std::vector<std::vector<double>> testData = {
        {2.5, 2.5},
        {1.5, 2.0},
        {3.5, 3.5},
        {4.5, 1.5}
    };

    // Predict the labels for the test data
    for (const auto& data : testData) {
        svm_node testNode[3];
        testNode[0].index = 1;
        testNode[0].value = data[0];
        testNode[1].index = 2;
        testNode[1].value = data[1];
        testNode[2].index = -1;

        double predictedLabel = svm_predict(model, testNode);
        std::cout << "Predicted label: " << predictedLabel << std::endl;
    }

    // Clean up memory
    for (int i = 0; i < prob.l; ++i) {
        delete[] prob.x[i];
    }
    delete[] prob.x;
    delete[] prob.y;
    svm_free_and_destroy_model(&model);

    return 0;
}
