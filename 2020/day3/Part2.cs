using System;
using System.Collections.Generic;
using System.IO;

namespace AdventOfCode
{
    public class Part2
    {
        static public void Run()
        {
            long sol = 1;

            var steps = new (int X, int Y)[]
            {
                (3, 1), (5, 1), (1, 1), (7, 1), (4, 2)
            };

            var grid = new List<string>(File.ReadLines("../../../input"));
            foreach (var (X, Y) in steps)
            {
                int trees = 0;
                int x = 0, y = 0;
                while (y < grid.Count)
                {
                    if (grid[y][x % grid[y].Length] == '#')
                    {
                        trees++;
                    }

                    x += X;
                    y += Y;
                }
                sol *= trees;
            }

            Console.WriteLine(sol);
        }
    }
}
