using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using System.Threading;
using Interop.CryptXi;

namespace CryptXiClient
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public string PlaintText { get; set; }
        public string EncryptedText { get; set; }
        private ATLCryptXiObject ComATLCryptXiObject { get; set; }

        public MainWindow()
        {
            InitializeComponent();

            PlainTextBox.DataContext = PlaintText;
            EncryptedTextBox.DataContext = EncryptedText;

            ComATLCryptXiObject = new ATLCryptXiObject();

        }

        private void ButtonSetKey_Click(object sender, RoutedEventArgs e)
        {
            string testStr = KeyTextBox.Text;
            string result = ComATLCryptXiObject.SetKey(testStr);

            PlainTextBox.Text = result;
        }

        private void ButtonEncrypt_Click(object sender, RoutedEventArgs e)
        {

        }

        private void ButtonDecrypt_Click(object sender, RoutedEventArgs e)
        {

        }

        private void MainWindow_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            Marshal.ReleaseComObject(ComATLCryptXiObject);
        }
    }
}
