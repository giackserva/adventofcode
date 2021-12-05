using System;
using System.IO;
using System.Collections.Generic;

namespace AdventOfCode
{
    public class Part1
    {
        public void Run()
        {
            int previous = int.MaxValue;
            int count = 0;
            foreach(var line in File.ReadLines("input"))
            {
                var num = Int32.Parse(line);
                if(num > previous)
                {
                    count++;
                }
                previous = num;
            }

            Console.WriteLine(count);
        }
    }
}