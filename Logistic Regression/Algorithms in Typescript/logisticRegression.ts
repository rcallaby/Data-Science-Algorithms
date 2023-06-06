// Helper function to calculate the sigmoid function
function sigmoid(z: number): number {
    return 1 / (1 + Math.exp(-z));
  }
  
  // Logistic regression class
  class LogisticRegression {
    private weights: number[];
  
    constructor(numFeatures: number) {
      this.weights = new Array(numFeatures).fill(0);
    }
  
    // Method to train the logistic regression model
    train(features: number[][], labels: number[], learningRate: number, numIterations: number): void {
      const numExamples = features.length;
      const numFeatures = this.weights.length;
  
      for (let iteration = 0; iteration < numIterations; iteration++) {
        // Initialize gradients
        const gradients = new Array(numFeatures).fill(0);
  
        // Calculate gradients
        for (let i = 0; i < numExamples; i++) {
          const prediction = this.predict(features[i]);
          const error = labels[i] - prediction;
  
          for (let j = 0; j < numFeatures; j++) {
            gradients[j] += error * features[i][j];
          }
        }
  
        // Update weights
        for (let j = 0; j < numFeatures; j++) {
          this.weights[j] += learningRate * gradients[j];
        }
      }
    }
  
    // Method to make predictions
    predict(features: number[]): number {
      let prediction = 0;
  
      for (let i = 0; i < this.weights.length; i++) {
        prediction += this.weights[i] * features[i];
      }
  
      return sigmoid(prediction);
    }
  }
  
  // Example usage
  const features = [
    [1, 2],
    [2, 3],
    [3, 4],
    [4, 5]
  ];
  const labels = [0, 0, 1, 1];
  
  const model = new LogisticRegression(features[0].length);
  model.train(features, labels, 0.1, 100);
  
  const testFeature = [2.5, 3.5];
  const prediction = model.predict(testFeature);
  
  console.log(`Predicted probability: ${prediction}`);
  