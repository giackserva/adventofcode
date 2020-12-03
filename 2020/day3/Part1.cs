using System;
using System.IO;

namespace AdventOfCode
{
    public class Part1
    {
        static public void Run()
        {
            int sol = 0;
            int column = 0;
            foreach (var line in File.ReadLines("../../../input"))
            {
                if (line[column % line.Length] == '#')
                {
                    sol++;
                }

                column += 3;
            }
            Console.WriteLine(sol);
        }
    }
}