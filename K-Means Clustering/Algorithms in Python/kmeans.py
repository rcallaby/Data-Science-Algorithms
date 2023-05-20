import numpy as np
from sklearn.cluster import KMeans
import matplotlib.pyplot as plt

# Generate random data points
np.random.seed(0)
X = np.random.randn(100, 2)

# Perform k-means clustering
k = 3
kmeans = KMeans(n_clusters=k)
kmeans.fit(X)

# Get cluster labels and cluster centers
labels = kmeans.labels_
centers = kmeans.cluster_centers_

# Plot the data points and cluster centers
plt.scatter(X[:, 0], X[:, 1], c=labels)
plt.scatter(centers[:, 0], centers[:, 1], c='red', marker='x')
plt.title("K-means Clustering")
plt.xlabel("X")
plt.ylabel("Y")
plt.show()
