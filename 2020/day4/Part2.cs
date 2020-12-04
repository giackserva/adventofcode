using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;

namespace AdventOfCode
{
    public class Part2
    {
        static public void Run()
        {
            int sol = 0;

            var required = new Dictionary<string, Predicate<string>>
            {
                { "byr", x => { return Regex.Match(x, @"^\d{4}$").Success && int.Parse(x) >= 1920 && int.Parse(x) <=2002; } },
                { "iyr", x => { return Regex.Match(x, @"^\d{4}$").Success && int.Parse(x) >= 2010 && int.Parse(x) <=2020; } },
                { "eyr", x => { return Regex.Match(x, @"^\d{4}$").Success && int.Parse(x) >= 2020 && int.Parse(x) <=2030; } },
                { "hgt", x => { return Regex.Match(x, @"^\d{3}cm$").Success && int.Parse(x.Substring(0,3)) >= 150 && int.Parse(x.Substring(0,3)) <= 193 ||
                                       Regex.Match(x, @"^\d{2}in$").Success && int.Parse(x.Substring(0,2)) >= 59 && int.Parse(x.Substring(0,2)) <= 76; } },
                { "hcl", x => { return Regex.Match(x, @"^#(\d|[a-f]){6}$").Success; } },
                { "ecl", x => { return Regex.Match(x, @"^(amb|blu|brn|gry|grn|hzl|oth)$").Success; } },
                { "pid", x => { return Regex.Match(x, @"^\d{9}$").Success; } },
            };

            foreach (var line in File.ReadAllText("../../../input").Split(Environment.NewLine + Environment.NewLine))
            {
                var fields = new Dictionary<string, string>();
                var match = Regex.Match(line, @"(\w{3}):(\S+)\s?");
                while (match.Success)
                {
                    fields.Add(match.Groups[1].Value, match.Groups[2].Value);
                    match = match.NextMatch();
                }

                if (required.All((k) => fields.ContainsKey(k.Key) && k.Value(fields[k.Key])))
                {
                    sol++;
                }
            }

            Console.WriteLine(sol);
        }
    }
}