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
            var set = new HashSet<int>();
            foreach(var line in File.ReadLines("../../../input")) {
                set.Add(Int32.Parse(line));
            }
            foreach(var f in set) {
                foreach(var s in set) {
                    var t = 2020 - f - s;
                    if(set.Contains(t)) {
                        Console.WriteLine(f * s * t);
                        return;
                    }
                }
            }
        }
    }
}