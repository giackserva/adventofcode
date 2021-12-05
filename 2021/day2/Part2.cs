using System;
using System.IO;
using System.Collections.Generic;

namespace AdventOfCode
{
    public class Part2
    {
        public void Run()
        {
            int depth = 0;
            int position = 0;
            int aim = 0;
            foreach(var line in File.ReadLines("input"))
            {
                var command = line.Split(' ');
                var value = Int32.Parse(command[1]);
                switch(command[0][0])
                {
                    case 'f':
                        position += value;
                        depth += aim * value;
                        break;
                    case 'u':
                        aim -= value;
                        break;
                    case 'd':
                        aim += value;
                        break;
                }
            }

            Console.WriteLine(depth * position);
        }
    }
}