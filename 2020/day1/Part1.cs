using System;
using System.IO;
using System.Collections.Generic;

namespace AdventOfCode
{
    public class Part1
    {
        public void Run()
        {
            var set = new HashSet<int>();
            foreach(var line in File.ReadLines("../../../input"))
            {
                var num = Int32.Parse(line);
                if(set.Contains(2020 - num)) {
                    Console.WriteLine(num * (2020 - num));
                    break;
                } else {
                    set.Add(num);
                }
            }
        }
    }
}