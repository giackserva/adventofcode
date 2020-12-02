using System;
using System.IO;
using System.Text.RegularExpressions;

namespace AdventOfCode
{
    public class Part1
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
                int from = Int32.Parse(match.Groups[1].Value);
                int to = Int32.Parse(match.Groups[2].Value);
                char letter = match.Groups[3].Value[0];
                string password = match.Groups[4].Value;

                int n = 0;
                foreach (char c in password)
                    if (letter == c) n++;

                return n >= from && n <= to;
            }
            return false;
        }
    }

}