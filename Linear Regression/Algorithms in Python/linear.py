import numpy as np

# Sample input data
X = np.array([[1], [2], [3], [4], [5]])
y = np.array([2, 4, 6, 8, 10])

# Add a column of ones to X for the intercept term
X = np.concatenate((np.ones((X.shape[0], 1)), X), axis=1)

# Calculate the coefficients using the closed-form solution
coefficients = np.linalg.inv(X.T.dot(X)).dot(X.T).dot(y)

# Extract the intercept and slope
intercept = coefficients[0]
slope = coefficients[1]

# Predict the output for a new input
X_new = np.array([[6]])
X_new = np.concatenate((np.ones((X_new.shape[0], 1)), X_new), axis=1)
y_pred = X_new.dot(coefficients)

print("Predicted output:", y_pred)
