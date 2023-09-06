using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace CryptXiClient.Utils
{
    internal static class Filesystem
    {
        internal const string KEYS_DIR_NAME = "keys/";

        public static string GetInitialDirectory()
        {
            return Path.Combine(Path.GetDirectoryName(Assembly.GetEntryAssembly().Location), KEYS_DIR_NAME);
        }

        public static string NewOrCreateFolder(string dirName)
        {
            var dirCurrent = Path.GetDirectoryName(Assembly.GetEntryAssembly().Location);
            var dirNew = Path.Combine(dirCurrent, dirName);
            if (!Directory.Exists(dirNew))
            {
                Directory.CreateDirectory(dirNew);
            }

            return Directory.Exists(dirNew) ? dirNew : dirCurrent;
        }
    }
}
