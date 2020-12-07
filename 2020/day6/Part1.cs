using System;
using System.Collections.Generic;
using System.IO;

namespace AdventOfCode
{
    public class Part1
    {
        static public void Run()
        {
            int sol = 0;

            foreach(var group in File.ReadAllText("../../../input").Split(Environment.NewLine + Environment.NewLine))
            {
                var count = new int[26];
                foreach(var line in group.Split(Environment.NewLine))
                {
                    foreach(var c in line)
                    {
                        count[c - 'a']++;
                    }
                }
                foreach(var c in count)
                {
                    if(c != 0)
                    {
                        sol++;
                    }
                }
            }

            Console.WriteLine(sol);
        }
    }
}
