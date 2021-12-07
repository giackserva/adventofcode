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
            var lanterns = File.ReadLines("../../../input").First().Split(',').Select(int.Parse).ToList();
            for(int i = 0; i < 80; i++)
            {
                var temp = new List<int>(lanterns.Count * 2);
                foreach(var l in lanterns)
                {
                    if(l == 0)
                    {
                        temp.Add(6);
                        temp.Add(8);
                    } else
                    {
                        temp.Add(l - 1);
                    }
                }
                lanterns = temp;
            }
            Console.WriteLine(lanterns.Count);
        }
    }
}
