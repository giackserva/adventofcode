using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;

namespace AdventOfCode
{
    public class Part1
    {
        static public void Run()
        {
            int sol = 0;
            var required = new string[]
            {
                "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"
            };

            foreach (var line in File.ReadAllText("../../../input").Split(Environment.NewLine + Environment.NewLine))
            {
                var fields = new List<string>();
                var match = Regex.Match(line, @"(\w{3}):(\S+)\s?");
                while (match.Success)
                {
                    fields.Add(match.Groups[1].Value);
                    match = match.NextMatch();
                }

                if (required.All(field => fields.Contains(field)))
                {
                    sol++;
                }
            } 

            Console.WriteLine(sol);
        }
    }
}