import numpy as np
import pandas as pd
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error
import matplotlib.pyplot as plt

# Load stock data from a CSV file
df = pd.read_csv('stock_data.csv')

# Extract the 'Date' and 'Close' columns
dates = pd.to_datetime(df['Date'])
closing_prices = df['Close']

# Convert dates to ordinal values
dates = dates.map(lambda date: date.toordinal())

# Prepare the data for linear regression
X = np.array(dates).reshape(-1, 1)
y = np.array(closing_prices)

# Create a linear regression model
model = LinearRegression()

# Fit the model to the data
model.fit(X, y)

# Predict the closing prices for future dates
future_dates = pd.date_range(start='2023-06-02', end='2023-06-09')
future_dates = future_dates.map(lambda date: date.toordinal())
future_dates = np.array(future_dates).reshape(-1, 1)
predicted_prices = model.predict(future_dates)

# Calculate the root mean squared error (RMSE) of the model
y_pred = model.predict(X)
rmse = np.sqrt(mean_squared_error(y, y_pred))

# Plot the actual and predicted prices
plt.figure(figsize=(10, 6))
plt.scatter(dates, closing_prices, color='blue', label='Actual Prices')
plt.plot(dates, y_pred, color='red', label='Predicted Prices')
plt.scatter(future_dates, predicted_prices, color='green', label='Predicted Future Prices')
plt.xlabel('Date')
plt.ylabel('Closing Price')
plt.title('Stock Price Prediction')
plt.legend()
plt.show()

print("RMSE:", rmse)
