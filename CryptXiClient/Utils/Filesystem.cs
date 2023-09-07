﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace CryptXiClient.Utils
{
    internal static class Filesystem
    {
        internal const string DEFAULT_FILE_EXTENSION = ".txt";

        public static string NewOrDefaultFolder(string dirName)
        {
            var dirCurrent = Path.GetDirectoryName(Assembly.GetEntryAssembly().Location);
            var dirNew = Path.Combine(dirCurrent, dirName);
            if (!Directory.Exists(dirNew))
            {
                Directory.CreateDirectory(dirNew);
            }

            return Directory.Exists(dirNew) ? dirNew : dirCurrent;
        }

        public static string? GetContentFromFile(string dir)
        {
            string initialDir = NewOrDefaultFolder(dir);

            // Configure open file dialog box
            var dialog = new Microsoft.Win32.OpenFileDialog();
            dialog.InitialDirectory = initialDir;
            dialog.FileName = "Document"; // Default file name
            dialog.DefaultExt = DEFAULT_FILE_EXTENSION; // Default file extension
            dialog.Filter = "Text documents (.txt)|*.txt"; // Filter files by extension

            // Show open file dialog box
            bool? result = dialog.ShowDialog();

            // Process open file dialog box results
            if (result == true)
            {
                // Open document
                string filename = dialog.FileName;
                // Write the content to file
                using (StreamReader inputFile = new StreamReader(filename))
                {
                    var input = inputFile.ReadToEnd();
                    if (input.ToString().Length > 0)
                    {
                        return input.ToString();
                    }
                    else
                    {
                        MessageBox.Show("Content not found.",
                            "Error",
                            MessageBoxButton.OK,
                            MessageBoxImage.Error);
                    }
                }
            }

            return null;
        }

        public static void PutContentToFile(string dir, string content, string fPrefix = "")
        {
            string initialDir = Filesystem.NewOrDefaultFolder(dir);

            // Configure save file dialog box
            var dialog = new Microsoft.Win32.SaveFileDialog();
            dialog.InitialDirectory = initialDir;
            dialog.FileName = fPrefix + DateTime.Now.ToFileTimeUtc();   // Default file name
            dialog.DefaultExt = DEFAULT_FILE_EXTENSION;     // Default file extension
            dialog.Filter = "Text documents (.txt)|*.txt"; // Filter files by extension

            // Show save file dialog box
            bool? result = dialog.ShowDialog();

            // Process save file dialog box results
            if (result == true)
            {
                // Save document
                string filename = dialog.FileName;
                // Write the content to file
                using (StreamWriter outputFile = new StreamWriter(filename))
                {
                    outputFile.Write(content);
                }
            }
        }
    }
}
