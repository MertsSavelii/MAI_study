using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace RegularExpression
{
    internal class Program
    {
        static void Main(string[] args)
        {
            //вариант 5
            string pattern_1 = @"192\.168\.0\.";
            var reg1 = new Regex(pattern_1);
  
            string[] str1 = {"192.168.0.1", "192.168.0.123", "192.168.0.1234",
                            "192.168.0.", "+919678967101","Hello world"};

            foreach (var s in str1)
            {
                Console.WriteLine(" {0} {1} a valid", s, reg1.IsMatch(s) ? "is" : " is not");
            }
            Console.WriteLine("");


            //вариант 6
            string pattern_2 = @"(\W|^)po[#\-]{0,1}\s{0,1}\d{2}[\s-]{0,1}\d{4}(\W|$)";
            var reg2 = new Regex(pattern_2);
  
            string[] str2 = {"po 12-3456", "po as-dfa", "po# 12-3456", "po1234", "pa- 1234"};

            foreach (var s in str2)
            {
                Console.WriteLine(" {0} {1} a valid", s, reg2.IsMatch(s) ? "is" : " is not");
            } 
            Console.WriteLine("");

            //вариант 5
            string pattern_3 = @"192\.168\.0\.\d{1,3}";
            var reg3 = new Regex(pattern_3);
  
            string[] str3 = {"192.168.0.1", "192.168.0.123", "192.168.0.1234",
                            "192.168.0.", "+919678967101","Hello world"};

            foreach (var s in str3)
            {
                Console.WriteLine(" {0} {1} a valid", s, reg3.IsMatch(s) ? "is" : " is not");
            }

            // Console.ReadKey();

        }
    }
}
