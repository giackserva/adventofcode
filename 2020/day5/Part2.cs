using System;
using System.Collections.Generic;
using System.IO;

namespace AdventOfCode
{
    public class Part2
    {
        static int GetSeatID(string code)
        {
            int row;
            int column;

            int high = 127, low = 0;
            for(int i = 0; i < 6; i++)
            {
                int mid = low + (high - low) / 2;
                if (code[i] == 'F')
                    high = mid;
                else
                    low = mid + 1;
            }

            row = code[6] == 'F' ? low : high;

            high = 7;
            low = 0;
            for(int i = 7; i < 9; i++)
            {
                int mid = low + (high - low) / 2;
                if (code[i] == 'L')
                    high = mid;
                else
                    low = mid + 1;
            }

            column = code[9] == 'L' ? low : high;

            return row * 8 + column;
        }

        static public void Run()
        {
            int sol = 0;
            var seats = new List<int>();

            foreach(var seat in File.ReadLines("../../../input"))
            {
                seats.Add(GetSeatID(seat));
            }

            seats.Sort();

            for(int i = 1; i < seats.Count; i++)
            {
                if (seats[i] != seats[i - 1] + 1)
                {
                    sol = seats[i] - 1;
                    break;
                }
            }

            Console.WriteLine(sol);
        }
    }
}
