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
            var input = new Queue<string>(File.ReadLines("../../../input"));
            var numbers = input.Dequeue().Split(',').Select(int.Parse).ToList();

            var boards = new List<int[,]>();
            while (input.Count > 0)
            {
                input.Dequeue();
                var board = new int[5, 5];
                for (int i = 0; i < 5; i++)
                {
                    var line = input.Dequeue()
                                    .Split(' ', StringSplitOptions.RemoveEmptyEntries)
                                    .Select(int.Parse)
                                    .ToList();
                    for (int j = 0; j < 5; j++)
                    {
                        board[i, j] = line[j];
                    }
                }
                boards.Add(board);
            }

            foreach (var called in numbers)
            {
                var won = new List<int>();
                for (int i = boards.Count - 1; i >= 0; i--)
                {
                    if(CallNumber(boards[i], called))
                    {
                        won.Add(i);
                    }
                }

                if(won.Count > 0)
                {
                    if(boards.Count > 1)
                    {
                        foreach(var board in won)
                        {
                            boards.RemoveAt(board);
                        }
                    }
                    else
                    {
                        int score = ComputeScore(boards[0]);
                        Console.WriteLine(score * called);
                        return; 
                    }
                }
            }
        }

        private int ComputeScore(int[,] board)
        {
            int score = 0;
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    if(board[i,j] != -1)
                    {
                        score += board[i, j];
                    }
                }
            }
            return score;
        }

        public bool CallNumber(int[,] board, int number)
        {
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    if(board[i,j] == number)
                    {
                        board[i, j] = -1;
                        return CheckWin(board, i, j);
                    }
                }
            }

            return false;
        }

        private bool CheckWin(int[,] board, int ii, int jj)
        {
            bool win = true;
            for (int i = 0; i < 5; i++)
            {
                win &= board[ii, i] == -1;
            }

            if (win) return win;

            win = true;
            for (int j = 0; j < 5; j++)
            {
                win &= board[j, jj] == -1;
            }

            return win;
        }
    }
}