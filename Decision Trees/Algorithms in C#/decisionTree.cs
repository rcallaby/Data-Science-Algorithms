using System;

class DecisionTree
{
    static void Main()
    {
        Console.WriteLine("Welcome to the Decision Tree!");
        Console.WriteLine("Please answer the following questions with 'yes' or 'no'.");

        bool result = PlayGame();
        Console.WriteLine("The result of the decision tree is: " + result);

        Console.ReadLine();
    }

    static bool PlayGame()
    {
        Console.WriteLine("Is the sky blue?");
        string answer = Console.ReadLine().ToLower();

        if (answer == "yes")
        {
            Console.WriteLine("Do you see any clouds?");
            answer = Console.ReadLine().ToLower();

            if (answer == "yes")
            {
                return true;
            }
            else if (answer == "no")
            {
                return false;
            }
            else
            {
                Console.WriteLine("Invalid input. Please try again.");
                return PlayGame();
            }
        }
        else if (answer == "no")
        {
            Console.WriteLine("Is it nighttime?");
            answer = Console.ReadLine().ToLower();

            if (answer == "yes")
            {
                return false;
            }
            else if (answer == "no")
            {
                Console.WriteLine("Is it raining?");
                answer = Console.ReadLine().ToLower();

                if (answer == "yes")
                {
                    return false;
                }
                else if (answer == "no")
                {
                    return true;
                }
                else
                {
                    Console.WriteLine("Invalid input. Please try again.");
                    return PlayGame();
                }
            }
            else
            {
                Console.WriteLine("Invalid input. Please try again.");
                return PlayGame();
            }
        }
        else
        {
            Console.WriteLine("Invalid input. Please try again.");
            return PlayGame();
        }
    }
}
