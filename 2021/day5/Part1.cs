using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace AdventOfCode
{
    public class Part1
    {
        public void Run()
        {
            var lines = new List<int[][]>();
            foreach(var line in File.ReadLines("../../../input"))
            {
                lines.Add(line.Split(" -> ").Select(ps => ps.Split(',').Select(int.Parse).ToArray()).ToArray());
            }

            int[,] graph = new int[1000,1000];
            foreach(var line in lines)
            {
                if (line[0][0] == line[1][0])
                {
                    int s = Math.Min(line[0][1], line[1][1]);
                    int f = Math.Max(line[0][1], line[1][1]);
                    for (int i = s; i <= f; i++)
                    {
                        graph[line[0][0], i]++;
                    }
                } else if (line[0][1] == line[1][1])
                {
                    int s = Math.Min(line[0][0], line[1][0]);
                    int f = Math.Max(line[0][0], line[1][0]);
                    for (int i = s; i <= f; i++)
                    {
                        graph[i, line[0][1]]++;
                    }
                }
            }

            int count = 0;
            for (int i = 0; i < 1000; i++)
            {
                for (int j = 0; j < 1000; j++)
                {
                    if (graph[i, j] > 1)
                    {
                        count++;
                    }
                }
            }
            Console.WriteLine(count);
        }
    }
}
