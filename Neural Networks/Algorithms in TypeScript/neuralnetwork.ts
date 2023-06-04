class NeuralNetwork {
    private inputSize: number;
    private hiddenSize: number;
    private outputSize: number;
    private weightsIH: number[][];
    private weightsHO: number[][];
  
    constructor(inputSize: number, hiddenSize: number, outputSize: number) {
      this.inputSize = inputSize;
      this.hiddenSize = hiddenSize;
      this.outputSize = outputSize;
  
      // Initialize weights randomly between -1 and 1
      this.weightsIH = this.initializeWeights(inputSize, hiddenSize);
      this.weightsHO = this.initializeWeights(hiddenSize, outputSize);
    }
  
    private initializeWeights(rows: number, cols: number): number[][] {
      const weights = [];
      for (let i = 0; i < rows; i++) {
        weights[i] = [];
        for (let j = 0; j < cols; j++) {
          weights[i][j] = Math.random() * 2 - 1;
        }
      }
      return weights;
    }
  
    private sigmoid(x: number): number {
      return 1 / (1 + Math.exp(-x));
    }
  
    public predict(inputs: number[]): number[] {
      // Convert input array to matrix
      const inputMatrix = [inputs];
  
      // Perform feedforward calculations
      const hidden = this.multiply(inputMatrix, this.weightsIH);
      const hiddenActivated = this.activateMatrix(hidden);
      const output = this.multiply(hiddenActivated, this.weightsHO);
      const outputActivated = this.activateMatrix(output);
  
      return outputActivated[0];
    }
  
    private multiply(a: number[][], b: number[][]): number[][] {
      const rowsA = a.length;
      const colsA = a[0].length;
      const colsB = b[0].length;
      const result = [];
  
      for (let i = 0; i < rowsA; i++) {
        result[i] = [];
        for (let j = 0; j < colsB; j++) {
          let sum = 0;
          for (let k = 0; k < colsA; k++) {
            sum += a[i][k] * b[k][j];
          }
          result[i][j] = sum;
        }
      }
  
      return result;
    }
  
    private activateMatrix(matrix: number[][]): number[][] {
      const result = [];
  
      for (let i = 0; i < matrix.length; i++) {
        result[i] = [];
        for (let j = 0; j < matrix[i].length; j++) {
          result[i][j] = this.sigmoid(matrix[i][j]);
        }
      }
  
      return result;
    }
  }
  
  // Example usage
  const inputSize = 2;
  const hiddenSize = 4;
  const outputSize = 1;
  
  const neuralNetwork = new NeuralNetwork(inputSize, hiddenSize, outputSize);
  const inputs = [0.5, 0.7];
  const predictions = neuralNetwork.predict(inputs);
  
  console.log("Predictions:", predictions);
  