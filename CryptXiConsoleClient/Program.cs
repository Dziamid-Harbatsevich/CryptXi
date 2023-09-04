using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Threading;
using Interop.CryptXi;
using System.Runtime.InteropServices;

namespace CryptXiConsoleClient
{
    internal class Program
    {
        static void Main(string[] args)
        {
            var ComATLCryptXiObject = new ATLCryptXiObject();

            string key = "Some test key";
            string textPlain = "Some plain text";

            string result = ComATLCryptXiObject.SetKey(key);
            Console.WriteLine($"Client key: {result}");

            string encryptedText = ComATLCryptXiObject.Encrypt(textPlain);
            Console.WriteLine($"Client encryptedText: {encryptedText}");

            string decryptedText = ComATLCryptXiObject.Decrypt(encryptedText);
            Console.WriteLine($"Client decryptedText: {decryptedText}");


            Console.ReadLine();

            Marshal.ReleaseComObject(ComATLCryptXiObject);
        }
    }
}
