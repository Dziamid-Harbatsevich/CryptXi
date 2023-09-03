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
        public MainWindow()
        {
            InitializeComponent();




            ////// TESSTING 
            ///
            var obj = new ATLCryptXiObject();
            IATLCryptXiObject iMath = obj;

            //string result = obj.SetKey("Testing ATL client.");

            //TestTextBlock.DataContext = result;

            //Marshal.ReleaseComObject(iMath);
            //Marshal.ReleaseComObject(obj);


            ///////////////////



        }
    }
}
