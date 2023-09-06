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
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Windows.Navigation;
using static System.Net.Mime.MediaTypeNames;
using System.Xml.Linq;
using System.Diagnostics;
using System.Reflection;
using System.IO;

namespace CryptXiClient
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        const int MAX_CHAR_KEY_LENGTH = 28;
        const string KEYS_DIR_NAME = "keys";

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

        private RelayCommand openPlainFromFileCommand;
        public ICommand OpenPlainFromFileCommand => openPlainFromFileCommand ??= new RelayCommand(OpenPlainFromFileExecute);

        private void OpenPlainFromFileExecute(object commandParameter)
        {
            MessageBox.Show(commandParameter?.ToString(), "OpenPlainFromFileExecute");

            //// Configure open file dialog box
            //var dialog = new Microsoft.Win32.OpenFileDialog();
            //dialog.FileName = "Document"; // Default file name
            //dialog.DefaultExt = ".txt"; // Default file extension
            //dialog.Filter = "Text documents (.txt)|*.txt"; // Filter files by extension

            //// Show open file dialog box
            //bool? result = dialog.ShowDialog();

            //// Process open file dialog box results
            //if (result == true)
            //{
            //    // Open document
            //    string filename = dialog.FileName;
            //}
        }

        private RelayCommand openEncryptedFromFileCommand;
        public ICommand OpenEncryptedFromFileCommand => openEncryptedFromFileCommand ??= new RelayCommand(OpenEncryptedFromFileExecute);

        private void OpenEncryptedFromFileExecute(object commandParameter)
        {
            MessageBox.Show(commandParameter?.ToString(), "OpenEncryptedFromFileExecute");

            //// Configure open file dialog box
            //var dialog = new Microsoft.Win32.OpenFileDialog();
            //dialog.FileName = "Document"; // Default file name
            //dialog.DefaultExt = ".txt"; // Default file extension
            //dialog.Filter = "Text documents (.txt)|*.txt"; // Filter files by extension

            //// Show open file dialog box
            //bool? result = dialog.ShowDialog();

            //// Process open file dialog box results
            //if (result == true)
            //{
            //    // Open document
            //    string filename = dialog.FileName;
            //}
        }

        private RelayCommand savePlainToFileDialogCommand;
        public ICommand SavePlainToFileDialogCommand => savePlainToFileDialogCommand ??= new RelayCommand(SavePlainToFileDialogExecute);

        private void SavePlainToFileDialogExecute(object commandParameter)
        {
            MessageBox.Show(commandParameter?.ToString(), "SavePlainToFileDialogExecute");

            //// Configure save file dialog box
            //var dialog = new Microsoft.Win32.SaveFileDialog();
            //dialog.FileName = "Document"; // Default file name
            //dialog.DefaultExt = ".txt"; // Default file extension
            //dialog.Filter = "Text documents (.txt)|*.txt"; // Filter files by extension

            //// Show save file dialog box
            //bool? result = dialog.ShowDialog();

            //// Process save file dialog box results
            //if (result == true)
            //{
            //    // Save document
            //    string filename = dialog.FileName;
            //}
        }

        private RelayCommand saveEncryptedToFileDialogCommand;
        public ICommand SaveEncryptedToFileDialogCommand => saveEncryptedToFileDialogCommand ??= new RelayCommand(SaveEncryptedToFileDialogExecute);

        private void SaveEncryptedToFileDialogExecute(object commandParameter)
        {
            MessageBox.Show(commandParameter?.ToString(), "SaveEncryptedToFileDialogExecute");

            //// Configure save file dialog box
            //var dialog = new Microsoft.Win32.SaveFileDialog();
            //dialog.FileName = "Document"; // Default file name
            //dialog.DefaultExt = ".txt"; // Default file extension
            //dialog.Filter = "Text documents (.txt)|*.txt"; // Filter files by extension

            //// Show save file dialog box
            //bool? result = dialog.ShowDialog();

            //// Process save file dialog box results
            //if (result == true)
            //{
            //    // Save document
            //    string filename = dialog.FileName;
            //}
        }

        private RelayCommand importKeyCommand;
        public ICommand ImportKeyCommand => importKeyCommand ??= new RelayCommand(ImportKeyExecute);

        private void ImportKeyExecute(object commandParameter)
        {
            string initialDir = Filesystem.NewOrDefaultFolder(KEYS_DIR_NAME);

            // Configure open file dialog box
            var dialog = new Microsoft.Win32.OpenFileDialog();
            dialog.InitialDirectory = initialDir;
            dialog.FileName = "Document"; // Default file name
            dialog.DefaultExt = ".txt"; // Default file extension
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
                        KeyTextBox.Text = input.ToString();
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
        }

        private RelayCommand exportKeyCommand;
        public ICommand ExportKeyCommand => exportKeyCommand ??= new RelayCommand(ExportKeyExecute);

        private void ExportKeyExecute(object commandParameter)
        {
            string initialDir = Filesystem.NewOrDefaultFolder(KEYS_DIR_NAME);

            // Configure save file dialog box
            var dialog = new Microsoft.Win32.SaveFileDialog();
            dialog.InitialDirectory = initialDir;
            dialog.FileName = "key_" + DateTime.Now.ToFileTimeUtc();   // Default file name
            dialog.DefaultExt = ".txt";     // Default file extension
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
                    outputFile.Write(KeyTextBox.Text);
                }
            }
        }

        #endregion File->Commands

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

        private RelayCommand helpAppCommand;
        public ICommand HelpAppCommand => helpAppCommand ??= new RelayCommand(HelpAppExecute);

        private void HelpAppExecute(object commandParameter)
        {
            var directory = Path.GetDirectoryName(Assembly.GetEntryAssembly().Location);
            var file = Path.Combine(directory, "Help.txt");

            if (File.Exists(file))
            {
                Process.Start(file);
            }
            else
            {
                MessageBox.Show("Good Luck!", "Help");
            }
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
