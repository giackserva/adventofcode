using System;
using System.IO;
using System.Linq;

namespace AdventOfCode
{
    public class Part2
    {
        public void Run()
        {
            var pop = new Int64[9];
            var lanterns = File.ReadLines("../../../input").First().Split(',').Select(int.Parse).ToList();
            foreach (var l in lanterns)
            {
                pop[l]++;
            }

            var newPop = new Int64[9];
            for (int i = 0; i < 256; i++)
            {
                newPop[0] = pop[1];
                newPop[1] = pop[2];
                newPop[2] = pop[3];
                newPop[3] = pop[4];
                newPop[4] = pop[5];
                newPop[5] = pop[6];
                newPop[6] = pop[7] + pop[0];
                newPop[7] = pop[8];
                newPop[8] = pop[0];
                (pop, newPop) = (newPop, pop);
            }
            Console.WriteLine(pop.Sum());
        }
    }
}