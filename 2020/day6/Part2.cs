using System;
using System.Collections.Generic;
using System.IO;

namespace AdventOfCode
{
    public class Part2
    {
        static public void Run()
        {
            int sol = 0;

            foreach(var group in File.ReadAllText("../../../input").Split(Environment.NewLine + Environment.NewLine))
            {
                var count = new int[26];
                var lines = group.Split(Environment.NewLine);
                foreach(var line in lines)
                {
                    foreach(var c in line)
                    {
                        count[c - 'a']++;
                    }
                }
                foreach(var c in count)
                {
                    if(c == lines.Length)
                    {
                        sol++;
                    }
                }
            }

            Console.WriteLine(sol);
        }
    }
}
