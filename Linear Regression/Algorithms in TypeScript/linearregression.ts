// Importing required libraries
import * as tf from '@tensorflow/tfjs';
import '@tensorflow/tfjs-node';

// Sample training data
const xTrain = tf.tensor2d([[1], [2], [3], [4]], [4, 1]);
const yTrain = tf.tensor2d([[2], [4], [6], [8]], [4, 1]);

// Creating a sequential model
const model = tf.sequential();
model.add(tf.layers.dense({ units: 1, inputShape: [1] }));

// Compiling the model
model.compile({ loss: 'meanSquaredError', optimizer: 'sgd' });

// Training the model
async function trainModel() {
  await model.fit(xTrain, yTrain, { epochs: 100 });
  console.log('Model training completed.');
}

// Making predictions with the trained model
function predict(input: number) {
  const inputTensor = tf.tensor2d([[input]], [1, 1]);
  const outputTensor = model.predict(inputTensor) as tf.Tensor;
  const output = outputTensor.dataSync()[0];
  console.log(`Prediction for input ${input}: ${output}`);
}

// Training and using the model
trainModel().then(() => {
  predict(5);
  predict(10);
});
