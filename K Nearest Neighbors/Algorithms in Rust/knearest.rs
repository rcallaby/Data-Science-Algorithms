use std::collections::HashMap;
use std::cmp::Ordering;
use ndarray::{Array1, Array2};
use ndarray::s;
use ndarray_stats::DeviationExt;

// Define a struct to represent a data point
#[derive(Debug)]
struct DataPoint {
    features: Array1<f64>,
    label: String,
}

// Implement a function to calculate the Euclidean distance between two data points
fn euclidean_distance(a: &Array1<f64>, b: &Array1<f64>) -> f64 {
    let squared_diff: Array1<f64> = a - b;
    squared_diff.dot(&squared_diff).sqrt()
}

// Implement the KNN algorithm
fn knn(training_data: &[DataPoint], input: &Array1<f64>, k: usize) -> String {
    // Calculate the distances between the input and all training data points
    let distances: Vec<(f64, &DataPoint)> = training_data
        .iter()
        .map(|data| (euclidean_distance(&data.features, input), data))
        .collect();

    // Sort the distances in ascending order
    let sorted_distances = distances.into_iter().sorted_by(|a, b| a.0.partial_cmp(&b.0).unwrap());

    // Count the labels of the k nearest neighbors
    let mut label_counts: HashMap<&str, usize> = HashMap::new();
    for (_, data) in sorted_distances.take(k) {
        *label_counts.entry(&data.label).or_insert(0) += 1;
    }

    // Find the label with the highest count
    let (label, _) = label_counts
        .into_iter()
        .max_by(|(_, count1), (_, count2)| count1.cmp(count2))
        .unwrap();

    label.to_string()
}

fn main() {
    // Create some sample training data
    let training_data = vec![
        DataPoint {
            features: Array1::from(vec![2.0, 4.0]),
            label: String::from("A"),
        },
        DataPoint {
            features: Array1::from(vec![4.0, 6.0]),
            label: String::from("A"),
        },
        DataPoint {
            features: Array1::from(vec![1.0, 3.0]),
            label: String::from("B"),
        },
        DataPoint {
            features: Array1::from(vec![5.0, 7.0]),
            label: String::from("B"),
        },
    ];

    // Create an input data point
    let input = Array1::from(vec![3.0, 5.0]);

    // Perform KNN classification with k=3
    let predicted_label = knn(&training_data, &input, 3);

    println!("Input: {:?}", input);
    println!("Predicted Label: {}", predicted_label);
}
