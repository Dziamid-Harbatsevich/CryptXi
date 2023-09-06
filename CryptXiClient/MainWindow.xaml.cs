using CryptXiClient.Commands;
using CryptXiClient.Utils;
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
        const int MAX_CHAR_KEY_LENGTH = 28;
        private string keyText;
        public string KeyText
        {
            get { return keyText; }
            set
            {
                keyText = value.Substring(0, FilterKeyLength(value.Length));
            }
        }
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
            KeyTextBox.MaxLength = MAX_CHAR_KEY_LENGTH;
            myUpDownControl.MaxLength = MAX_CHAR_KEY_LENGTH;
            DataContext = this;
        }

        private int FilterKeyLength(int length)
        {
            return length > MAX_CHAR_KEY_LENGTH || length < 2 ? MAX_CHAR_KEY_LENGTH : length;
        }

        #region File-> Commands



        #endregion File-> Commands

        #region General commands

        private RelayCommand resetCommand;
        public ICommand ResetCommand => resetCommand ??= new RelayCommand(ResetExecute);

        private void ResetExecute(object commandParameter)
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

        #endregion General commands

        #region Button Click handlers

        private void ButtonGenerateKey_Click(object sender, RoutedEventArgs e)
        {
            int length = MAX_CHAR_KEY_LENGTH;
            if (myUpDownControl.Value != null)
            {
                length = FilterKeyLength((int)myUpDownControl.Value);
            }

            string keyGenerated = GenerateRandomString.Generate(length);
            KeyText = keyGenerated;
            KeyTextBox.Text = KeyText;
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

        #endregion Button Click handlers

        #region Event handlers

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

        #endregion Event handlers
    }
}
