using System;
using System.Collections.Generic;
using System.Linq;

namespace LinearRegressionExample
{
    class Program
    {
        static void Main(string[] args)
        {
            List<double> x = new List<double>() { 1, 2, 3, 4, 5 };
            List<double> y = new List<double>() { 2, 4, 6, 8, 10 };

            double slope, intercept;
            LinearRegression(x, y, out slope, out intercept);

            Console.WriteLine("The equation of the line of best fit is y = {0}x + {1}", slope, intercept);

            Console.ReadLine();
        }

        static void LinearRegression(List<double> x, List<double> y, out double slope, out double intercept)
        {
            double x_mean = x.Average();
            double y_mean = y.Average();

            double covariance = x.Zip(y, (xi, yi) => (xi - x_mean) * (yi - y_mean)).Sum();

            double x_variance = x.Sum(xi => Math.Pow(xi - x_mean, 2));
            double y_variance = y.Sum(yi => Math.Pow(yi - y_mean, 2));

            slope = covariance / x_variance;
            intercept = y_mean - slope * x_mean;
        }
    }
}
