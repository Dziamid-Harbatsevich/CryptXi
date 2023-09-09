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

            string key = "Client key! Hello :) abcdeFGHIG-12345";
            string textPlain = "Some plain text that makes no sense but has a great point. Enjoy encryption! :) To be continued.\n" +
                "I am just interested when the data to be corrupted..." +
                "Just thinking about how is it long can be, maybe, special char can corrupt this. Then let's checl it out..." +
                "!@#$%^&*()_+" +
                "Wow! it still works ;)";
            Console.WriteLine($"Client textPlain Length: {textPlain.Length}");

            string keyAscii = System.Text.ASCIIEncoding.ASCII.GetString(System.Text.ASCIIEncoding.ASCII.GetBytes(key));
            int keyAsciiBytesCount = System.Text.ASCIIEncoding.ASCII.GetByteCount(keyAscii);
            Console.WriteLine($"Client keyAsciiBytesCount: {keyAsciiBytesCount}");

            keyAscii = ComATLCryptXiObject.SetKey(keyAscii);
            Console.WriteLine($"Client SetKey() keyAscii: {keyAscii}");

            Console.WriteLine("==================");

            string keyUni = System.Text.ASCIIEncoding.Unicode.GetString(System.Text.ASCIIEncoding.Unicode.GetBytes(key));
            int keyUniBytesCount = System.Text.ASCIIEncoding.Unicode.GetByteCount(keyUni);
            Console.WriteLine($"Client keyUniBytesCount: {keyUniBytesCount}");

            keyUni = ComATLCryptXiObject.SetKey(keyUni);
            Console.WriteLine($"Client SetKey() resultUni: {keyUni}");

            Console.WriteLine("==================");

            //string textPlainAscii = System.Text.ASCIIEncoding.ASCII.GetString(System.Text.ASCIIEncoding.ASCII.GetBytes(textPlain));

            string encryptedText = ComATLCryptXiObject.Encrypt(textPlain);
            Console.WriteLine($"Client encryptedText: {encryptedText}");

            Console.WriteLine("==================");

            string decryptedText = ComATLCryptXiObject.Decrypt(encryptedText);
            Console.WriteLine($"Client decryptedText from ASCIIencryption: {decryptedText}");

            //Console.WriteLine("==================");

            //string encryptedTextAscii = System.Text.ASCIIEncoding.ASCII.GetString(System.Text.ASCIIEncoding.ASCII.GetBytes(encryptedText));
            ////encryptedText = System.Text.ASCIIEncoding.Unicode.GetString(System.Text.ASCIIEncoding.ASCII.GetBytes(encryptedText));
            //Console.WriteLine($"Client ASCII to UNI: {encryptedTextAscii}");
            //decryptedText = ComATLCryptXiObject.Decrypt(encryptedTextAscii);
            //Console.WriteLine($"Client decryptedText from UniEncryption: {decryptedText}");

            Console.ReadLine();

            Marshal.ReleaseComObject(ComATLCryptXiObject);
        }
    }
}
