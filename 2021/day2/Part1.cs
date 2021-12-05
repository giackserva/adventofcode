using System;
using System.IO;
using System.Collections.Generic;

namespace AdventOfCode
{
    public class Part1
    {
        public void Run()
        {
            int depth = 0;
            int position = 0;
            foreach(var line in File.ReadLines("input"))
            {
                var command = line.Split(' ');
                var value = Int32.Parse(command[1]);
                switch(command[0][0])
                {
                    case 'f':
                        position += value;
                        break;
                    case 'u':
                        depth -= value;
                        break;
                    case 'd':
                        depth += value;
                        break;
                }
            }

            Console.WriteLine(depth * position);
        }
    }
}