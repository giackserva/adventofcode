using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace AdventOfCode
{
    public class Part1
    {
        public void Run()
        {
            var crabs = File.ReadLines("../../../input").First().Split(',').Select(int.Parse).ToList();
            var max = crabs.Max();
            var min = crabs.Min();
            int solution= int.MaxValue;
            for(int i = min; i <= max; i++)
            {
                var cost = crabs.Select(c => Math.Abs(c - i)).Sum();
                solution = Math.Min(cost, solution);
            }
            Console.WriteLine(solution);
        }
    }
}
