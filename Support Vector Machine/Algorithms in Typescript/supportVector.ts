import * as tf from '@tensorflow/tfjs-node';

// Generate some sample data for a binary classification problem
const numSamples = 200;
const features = tf.randomNormal([numSamples, 2]);
const labels = tf.tidy(() => {
  const xs = features.slice([0, 0], [-1, 1]);
  const ys = features.slice([0, 1], [-1, 1]);
  return tf.where(xs.sub(ys).less(0), tf.zeros([numSamples, 1]), tf.ones([numSamples, 1]));
});

// Define and train the Support Vector Machine
const svm = tf.sequential();
svm.add(tf.layers.dense({ units: 1, activation: 'linear', inputShape: [2] }));

const optimizer = tf.train.sgd(0.1);
svm.compile({
  loss: 'hinge',
  optimizer,
  metrics: ['accuracy'],
});

svm.fit(features, labels, {
  epochs: 100,
  batchSize: 32,
  validationSplit: 0.2,
  callbacks: tf.node.tensorBoard('/tmp/svm_logs'),
}).then(info => {
  console.log('Final accuracy', info.history.acc[0]);
});
