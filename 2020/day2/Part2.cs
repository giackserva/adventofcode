using System;
using System.IO;
using System.Text.RegularExpressions;

namespace AdventOfCode
{
    public class Part2
    {
        static public void Run()
        {
            int sol = 0;
            foreach(var line in File.ReadLines("../../../input")) {
                if (ValidPassword(line))
                {
                    sol++;
                }
            }
            Console.WriteLine(sol);
        }

        static bool ValidPassword(string line)
        {
            string pattern = @"(\d+)-(\d+) (\w): (\w+)";
            var match = Regex.Match(line,pattern);
            if (match.Success)
            {
                int first = Int32.Parse(match.Groups[1].Value) - 1;
                int second = Int32.Parse(match.Groups[2].Value) - 1;
                char letter = match.Groups[3].Value[0];
                string password = match.Groups[4].Value;

                return password[first] == letter ^ password[second] == letter;
            }

            return false;
        }
    }

}
