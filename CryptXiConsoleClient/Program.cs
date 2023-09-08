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

            string key = "Client key! Hello :)";
            string textPlain = "Some plain text";

            int keyUniByte = System.Text.ASCIIEncoding.Unicode.GetByteCount(key);
            int keyAsciiByte = System.Text.ASCIIEncoding.ASCII.GetByteCount(key);
            Console.WriteLine($"Client keyUniByte: {keyUniByte}");
            Console.WriteLine($"Client keyAsciiByte: {keyAsciiByte}");

            string keyAscii = System.Text.ASCIIEncoding.ASCII.GetString(System.Text.ASCIIEncoding.ASCII.GetBytes(key));
            int keyAsciiBytesCount = System.Text.ASCIIEncoding.ASCII.GetByteCount(keyAscii);
            Console.WriteLine($"Client keyAsciiBytesCount: {keyAsciiBytesCount}");
            var result = ComATLCryptXiObject.SetKey(keyAscii);
            Console.WriteLine($"Client SetKey() result: {result}");

            //string encryptedText = ComATLCryptXiObject.Encrypt(textPlain);
            //Console.WriteLine($"Client encryptedText: {encryptedText}");

            //string decryptedText = ComATLCryptXiObject.Decrypt(encryptedText);
            //Console.WriteLine($"Client decryptedText: {decryptedText}");


            Console.ReadLine();

            Marshal.ReleaseComObject(ComATLCryptXiObject);
        }
    }
}
