using CryptXiClient.Commands;
using Interop.CryptXi;
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

namespace CryptXiClient
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public string KeyText { get; set; }
        public string PlaintText { get; set; }
        public string EncryptedText { get; set; }
        private ATLCryptXiObject ComATLCryptXiObject { get; set; }

        public MainWindow()
        {
            InitializeComponent();

            KeyTextBox.DataContext = KeyText;
            PlainTextBox.DataContext = PlaintText;
            EncryptedTextBox.DataContext = EncryptedText;

            ComATLCryptXiObject = new ATLCryptXiObject();
            DataContext = this;
        }

        private RelayCommand newCommand;
        public ICommand NewCommand => newCommand ??= new RelayCommand(NewExecute);

        private void NewExecute(object commandParameter)
        {
            KeyTextBox.Text = "";
            PlainTextBox.Text = "";
            EncryptedTextBox.Text = "";
        }

        private RelayCommand exitAppCommand;
        public ICommand ExitAppCommand => exitAppCommand ??= new RelayCommand(ExitAppExecute);

        private void ExitAppExecute(object commandParameter)
        {
            App.Current.Shutdown();
        }


        private void ButtonSetKey_Click(object sender, RoutedEventArgs e)
        {
            string str = KeyTextBox.Text;
            string result = ComATLCryptXiObject.SetKey(str);

            // Debug
            PlainTextBox.Text = result;
        }

        private void ButtonEncrypt_Click(object sender, RoutedEventArgs e)
        {
            string str = PlainTextBox.Text;
            string result = ComATLCryptXiObject.Encrypt(str);

            EncryptedTextBox.Text = result;
        }

        private void ButtonDecrypt_Click(object sender, RoutedEventArgs e)
        {
            string str = EncryptedTextBox.Text;
            string result = ComATLCryptXiObject.Decrypt(str);

            PlainTextBox.Text = result;
        }

        private void MainWindow_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            Marshal.ReleaseComObject(ComATLCryptXiObject);
        }

        private void KeyTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            KeyTextSizeTextBlock.Text = (System.Text.ASCIIEncoding.Unicode.GetByteCount(KeyTextBox.Text) * 8).ToString();
        }

        private void PlainTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            PlainTextSizeTextBlock.Text = PlainTextBox.Text.Length.ToString();
        }

        private void EncryptedTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            EncryptedTextSizeTextBlock.Text = EncryptedTextBox.Text.Length.ToString();
        }
    }
}
