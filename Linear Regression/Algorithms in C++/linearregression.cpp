#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double calculate_mean(vector<double> data) {
    double sum = 0;
    for (double d : data) {
        sum += d;
    }
    return sum / data.size();
}

double calculate_variance(vector<double> data) {
    double mean = calculate_mean(data);
    double variance = 0;
    for (double d : data) {
        variance += pow(d - mean, 2);
    }
    return variance / data.size();
}

double calculate_covariance(vector<double> x, vector<double> y) {
    double x_mean = calculate_mean(x);
    double y_mean = calculate_mean(y);
    double covariance = 0;
    for (int i = 0; i < x.size(); i++) {
        covariance += (x[i] - x_mean) * (y[i] - y_mean);
    }
    return covariance / x.size();
}

void linear_regression(vector<double> x, vector<double> y, double& slope, double& intercept) {
    double x_variance = calculate_variance(x);
    double y_variance = calculate_variance(y);
    double covariance = calculate_covariance(x, y);

    slope = covariance / x_variance;
    intercept = calculate_mean(y) - slope * calculate_mean(x);
}

int main() {
    vector<double> x = {1, 2, 3, 4, 5};
    vector<double> y = {2, 4, 6, 8, 10};

    double slope, intercept;
    linear_regression(x, y, slope, intercept);

    cout << "The equation of the line of best fit is y = " << slope << "x + " << intercept << endl;

    return 0;
}
