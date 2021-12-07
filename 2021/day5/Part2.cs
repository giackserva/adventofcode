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
            var lines = new List<int[][]>();
            foreach(var line in File.ReadLines("../../../input"))
            {
                lines.Add(line.Split(" -> ").Select(ps => ps.Split(',').Select(int.Parse).ToArray()).ToArray());
            }

            int dimension = 1000;
            int[,] graph = new int[dimension,dimension];
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
                    continue;
                } 
                if (line[0][1] == line[1][1])
                {
                    int s = Math.Min(line[0][0], line[1][0]);
                    int f = Math.Max(line[0][0], line[1][0]);
                    for (int i = s; i <= f; i++)
                    {
                        graph[i, line[0][1]]++;
                    }
                    continue;
                }

                int slope = (line[1][1] - line[0][1]) / (line[1][0] - line[0][0]);
                if (slope == 1 || slope == -1)
                {
                    int[] p1;
                    int[] p2;
                    if(line[0][0] > line[1][0])
                    {
                        p1 = line[1];
                        p2 = line[0];
                    }
                    else
                    {
                        p1 = line[0];
                        p2 = line[1];
                    }
                    for(int i = p1[0], j = p1[1]; i <= p2[0]; i++, j += slope)
                    {
                        graph[i,j]++;
                    }
                }
            }

            int count = 0;
            for (int i = 0; i < dimension; i++)
            {
                for (int j = 0; j < dimension; j++)
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