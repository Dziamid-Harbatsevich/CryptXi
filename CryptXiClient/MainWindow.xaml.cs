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

        public MainWindow()
        {
            InitializeComponent();

            PlainTextBox.DataContext = PlaintText;
            EncryptedTextBox.DataContext = EncryptedText;


            ////// TESSTING 
            ///
            var obj = new ATLCryptXiObject();
            IATLCryptXiObject iCryptXi = obj;


            string result = obj.SetKey(KeyTextBox.Text);

            // Debug
            Console.WriteLine(result);

            PlainTextBox.Text = result;

            Marshal.ReleaseComObject(iCryptXi);
            Marshal.ReleaseComObject(obj);


            ///////////////////



        }
    }
}
