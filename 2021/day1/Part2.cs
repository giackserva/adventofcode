using System;
using System.Linq;
using System.IO;
using System.Collections.Generic;

namespace AdventOfCode
{
    public class Part2
    {
        public void Run()
        {
            var nums = new List<int>();
            foreach(var line in File.ReadLines("../../../input")) {
                nums.Add(Int32.Parse(line));
            }
            int previous = int.MaxValue;
            int count = 0;
            for(int i = 2; i < nums.Count; i++)
            {
                int sum = nums[i] + nums[i-1] + nums[i-2];
                if(sum > previous) {
                    count++;
                }
                previous = sum;
            }

            Console.WriteLine(count);
        }
    }
}