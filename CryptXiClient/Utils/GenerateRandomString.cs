﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CryptXiClient.Utils
{
    internal class GenerateRandomString
    {
        /**
         * Generates string token from decimal ASCII code range {48; 122}.
         */
        public static string Generate(int length = 40)
        {
            StringBuilder str_build = new StringBuilder();
            Random random = new Random();

            char letter;

            for (int i = 0; i < length; i++)
            {
                double flt = random.NextDouble();
                int shift = Convert.ToInt32(Math.Floor(75 * flt));
                letter = Convert.ToChar(shift + 48);
                str_build.Append(letter);
            }

            return str_build.ToString();
        }
    }
}
