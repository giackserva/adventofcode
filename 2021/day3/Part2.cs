using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace AdventOfCode
{
    public class Part2
    {
        public void Run()
        {
            var input = File.ReadLines("../../../input").ToList();

            var oxygen = Filter(input, true);
            var co2 = Filter(input, false);

            Console.WriteLine(Convert.ToInt32(oxygen, 2) * Convert.ToInt32(co2, 2));
        }

        public char CommonAt(List<string> input, int index, bool most)
        {
            int ones = input.Where(s => s[index] == '1').Count();
            if (ones >= (float) input.Count / 2)
            {
                if (most) return '1';
                return '0';
            }
            else
            {
                if (most) return '0';
                return '1';
            }
        }

        public string Filter(List<string> input, bool most)
        {
            int index = 0;
            while(input.Count > 1)
            {
                var common = CommonAt(input, index, most);
                input = input.FindAll(s => s[index] == common);
                index++;
            }
            return input[0];
        }
    }
}