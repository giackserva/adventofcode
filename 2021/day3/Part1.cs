using System;
using System.IO;
using System.Linq;

namespace AdventOfCode
{
    public class Part1
    {
        public void Run()
        {
            int size = 12;
            var values = Enumerable.Repeat(0, size).ToList();
            int numValues = 0;
            foreach(var line in File.ReadLines("../../../input"))
            {
                for(int i = 0; i < size; i++)
                {
                    values[i] += line[i] == '0' ? 0 : 1;
                }
                numValues++;
            }

            string gamma = "";
            string epsilon = "";
            for(int i = 0; i < size; i++)
            {
                if(values[i] > numValues / 2) {
                    gamma += "1";
                    epsilon += "0";
                }
                else {
                    gamma += "0";
                    epsilon += "1";
                }
            }

            int gammaRate = Convert.ToInt32(gamma, 2);
            int epsilonRate = Convert.ToInt32(epsilon, 2);

            Console.WriteLine(gammaRate * epsilonRate);
        }
    }
}