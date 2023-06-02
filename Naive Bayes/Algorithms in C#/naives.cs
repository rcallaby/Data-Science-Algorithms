using System;
using System.Collections.Generic;

namespace NaiveBayesExample
{
    class Program
    {
        static void Main(string[] args)
        {
            // Training data
            List<Dictionary<string, bool>> trainingData = new List<Dictionary<string, bool>>()
            {
                new Dictionary<string, bool> { { "sunny", true }, { "hot", true }, { "high_humidity", false }, { "play", false } },
                new Dictionary<string, bool> { { "sunny", true }, { "hot", true }, { "high_humidity", true }, { "play", false } },
                new Dictionary<string, bool> { { "overcast", true }, { "hot", true }, { "high_humidity", false }, { "play", true } },
                new Dictionary<string, bool> { { "rainy", true }, { "mild", true }, { "high_humidity", false }, { "play", true } },
                new Dictionary<string, bool> { { "rainy", false }, { "cool", true }, { "normal_humidity", false }, { "play", true } },
                new Dictionary<string, bool> { { "rainy", false }, { "cool", false }, { "normal_humidity", true }, { "play", false } },
                new Dictionary<string, bool> { { "overcast", false }, { "cool", false }, { "normal_humidity", true }, { "play", true } },
                new Dictionary<string, bool> { { "sunny", true }, { "mild", true }, { "high_humidity", false }, { "play", false } },
                new Dictionary<string, bool> { { "sunny", false }, { "cool", true }, { "normal_humidity", false }, { "play", true } },
                new Dictionary<string, bool> { { "rainy", true }, { "mild", true }, { "normal_humidity", false }, { "play", true } },
                new Dictionary<string, bool> { { "sunny", false }, { "mild", false }, { "high_humidity", true }, { "play", true } },
                new Dictionary<string, bool> { { "overcast", true }, { "mild", true }, { "high_humidity", true }, { "play", true } },
                new Dictionary<string, bool> { { "overcast", false }, { "hot", true }, { "normal_humidity", false }, { "play", true } },
                new Dictionary<string, bool> { { "rainy", true }, { "mild", false }, { "high_humidity", true }, { "play", false } }
            };

            // Testing data
            Dictionary<string, bool> testData = new Dictionary<string, bool> { { "sunny", true }, { "hot", false }, { "high_humidity", false } };

            // Calculate the probabilities
            Dictionary<bool, double> probabilities = CalculateProbabilities(trainingData);

            // Classify the test data
            bool classification = ClassifyData(testData, probabilities);

            Console.WriteLine("The predicted classification for the test data is: " + classification);
            Console.ReadLine();
        }

        static Dictionary<bool, double> CalculateProbabilities(List<Dictionary<string, bool>> trainingData)
        {
            // Count the occurrences of each class
            Dictionary<bool, int> classCounts = new Dictionary<bool, int>();
            foreach (var data in trainingData)
            {
                bool classValue = data["play"];
                if (classCounts.ContainsKey(classValue))
                    classCounts[classValue]++;
                else
                    classCounts.Add(classValue, 1);
            }

            // Calculate the probabilities
            Dictionary<bool, double> probabilities = new Dictionary<bool, double>();
            foreach (var classCount in classCounts)
            {
                bool classValue = classCount.Key;
                int count = classCount.Value;
                double probability = (double)count / trainingData.Count;
                probabilities.Add(classValue, probability);
            }

            return probabilities;
        }

        static bool ClassifyData(Dictionary<string, bool> data, Dictionary<bool, double> probabilities)
        {
            bool bestClass = false;
            double bestProbability = double.MinValue;

            foreach (var classProbability in probabilities)
            {
                bool classValue = classProbability.Key;
                double probability = classProbability.Value;

                foreach (var feature in data)
                {
                    string featureName = feature.Key;
                    bool featureValue = feature.Value;

                    // Assume that all features are binary (true/false)
                    double featureProbability = CalculateFeatureProbability(featureName, featureValue, classValue);

                    // Multiply the probabilities together
                    probability *= featureProbability;
                }

                if (probability > bestProbability)
                {
                    bestClass = classValue;
                    bestProbability = probability;
                }
            }

            return bestClass;
        }

        static double CalculateFeatureProbability(string featureName, bool featureValue, bool classValue)
        {
            // Here you would calculate the probability of the feature given the class value
            // This is a simplified example, assuming that the probabilities are known

            Dictionary<string, Dictionary<bool, double>> featureProbabilities = new Dictionary<string, Dictionary<bool, double>>()
            {
                { "sunny", new Dictionary<bool, double> { { true, 2.0 / 5 }, { false, 3.0 / 9 } } },
                { "hot", new Dictionary<bool, double> { { true, 3.0 / 5 }, { false, 1.0 / 9 } } },
                { "high_humidity", new Dictionary<bool, double> { { true, 3.0 / 5 }, { false, 4.0 / 9 } } }
            };

            if (featureProbabilities.ContainsKey(featureName) && featureProbabilities[featureName].ContainsKey(featureValue))
                return featureProbabilities[featureName][featureValue];
            else
                return 0.0;
        }
    }
}
