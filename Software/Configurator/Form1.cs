using System.Diagnostics;
using System;
using System.Windows.Forms;
using System.Collections;
using System.Drawing;
using Microsoft.VisualBasic;
using System.Data;
using System.Collections.Generic;
using System.Globalization;
using System.Text;
using System.IO.Ports;
using System.Threading;
using System.Runtime.InteropServices;
using System.Text.RegularExpressions;
using System.IO;



namespace USB_termo_2
{
    public partial class Form1 : Form
    {
        int vid = 0x0483; //VID
        int pid = 0x5711; //PID 5711
        short ver = -1; // Версия устройства
        short ind = 0;
        int Handless = 0;
        public int KEY = 33; // Ключ для шифрования
        //int state = 0;
        byte[] Buffer = new byte[20];//Буфер приема данных из устройства
        byte[] ReadBuffer = new byte[60];
        byte[] Buf_Erase = new byte[64]; // Erase Buffer
        byte[] BufferSystem = new byte[64]; //Буфер общих настроек
        byte[] Buf_MSG1 = new byte[64];
        byte[] Buf_MSG2 = new byte[64];
        byte[] Buf_MSG3 = new byte[64];
        byte[] Buf_MSG4 = new byte[64];
        byte[] Buf_MSG5 = new byte[64];
        byte[] Buf_MSG6 = new byte[64];
        byte[] Buf_MSG7 = new byte[64];
        byte[] Buf_MSG8 = new byte[64];

        int State;
				int windowsState = 0;
        int res;
				byte inOneThread = 0;
        byte autoReboot = 0;
        //long t = 0;
       // byte Baudrate = 0;


        // переменные для хренения данных 1 -го сообщения
        public string Msg1_1 = "0";
        public string Msg1_2 = "0";
        public string Msg1_3 = "0";
        public string Msg1_4 = "0";
        public string Msg1_5 = "0";
        public string Msg1_6 = "0";
        public string Msg1_7 = "0";
        public string Msg1_8 = "0";
        public string Msg1_9 = "0";
        public string Msg1_10 = "5";
        public string Msg1_11 = "0";
        public string Msg1_12 = "0";
        public string Msg1_13 = "0";
        public string Msg1_14 = "0";
        public string Msg1_15 = "0";
        public string Msg1_16 = "0";
        public string Msg1_17 = "0";
        public string Msg1_18 = "0";
        public string Msg1_19 = "0";
        public string Msg1_20 = "1";
        // переменные для хренения данных 2  сообщения
        public string Msg2_1 = "0";
        public string Msg2_2 = "0";
        public string Msg2_3 = "0";
        public string Msg2_4 = "0";
        public string Msg2_5 = "0";
        public string Msg2_6 = "0";
        public string Msg2_7 = "0";
        public string Msg2_8 = "0";
        public string Msg2_9 = "0";
        public string Msg2_10 = "5";
        public string Msg2_11 = "0";
        public string Msg2_12 = "0";
        public string Msg2_13 = "0";
        public string Msg2_14 = "0";
        public string Msg2_15 = "0";
        public string Msg2_16 = "0";
        public string Msg2_17 = "0";
        public string Msg2_18 = "0";
        public string Msg2_19 = "0";
        public string Msg2_20 = "1";
        // переменные для хренения данных 3  сообщения
        public string Msg3_1 = "0";
        public string Msg3_2 = "0";
        public string Msg3_3 = "0";
        public string Msg3_4 = "0";
        public string Msg3_5 = "0";
        public string Msg3_6 = "0";
        public string Msg3_7 = "0";
        public string Msg3_8 = "0";
        public string Msg3_9 = "0";
        public string Msg3_10 = "5";
        public string Msg3_11 = "0";
        public string Msg3_12 = "0";
        public string Msg3_13 = "0";
        public string Msg3_14 = "0";
        public string Msg3_15 = "0";
        public string Msg3_16 = "0";
        public string Msg3_17 = "0";
        public string Msg3_18 = "0";
        public string Msg3_19 = "0";
        public string Msg3_20 = "1";
        // переменные для хренения данных 4 сообщения
        public string Msg4_1 = "0";
        public string Msg4_2 = "0";
        public string Msg4_3 = "0";
        public string Msg4_4 = "0";
        public string Msg4_5 = "0";
        public string Msg4_6 = "0";
        public string Msg4_7 = "0";
        public string Msg4_8 = "0";
        public string Msg4_9 = "0";
        public string Msg4_10 = "5";
        public string Msg4_11 = "0";
        public string Msg4_12 = "0";
        public string Msg4_13 = "0";
        public string Msg4_14 = "0";
        public string Msg4_15 = "0";
        public string Msg4_16 = "0";
        public string Msg4_17 = "0";
        public string Msg4_18 = "0";
        public string Msg4_19 = "0";
        public string Msg4_20 = "1";
        // переменные для хренения данных 5  сообщения
        public string Msg5_1 = "0";
        public string Msg5_2 = "0";
        public string Msg5_3 = "0";
        public string Msg5_4 = "0";
        public string Msg5_5 = "0";
        public string Msg5_6 = "0";
        public string Msg5_7 = "0";
        public string Msg5_8 = "0";
        public string Msg5_9 = "0";
        public string Msg5_10 = "5";
        public string Msg5_11 = "0";
        public string Msg5_12 = "0";
        public string Msg5_13 = "0";
        public string Msg5_14 = "0";
        public string Msg5_15 = "0";
        public string Msg5_16 = "0";
        public string Msg5_17 = "0";
        public string Msg5_18 = "0";
        public string Msg5_19 = "0";
        public string Msg5_20 = "1";
        // переменные для хренения данных 6  сообщения
        public string Msg6_1 = "0";
        public string Msg6_2 = "0";
        public string Msg6_3 = "0";
        public string Msg6_4 = "0";
        public string Msg6_5 = "0";
        public string Msg6_6 = "0";
        public string Msg6_7 = "0";
        public string Msg6_8 = "0";
        public string Msg6_9 = "0";
        public string Msg6_10 = "5";
        public string Msg6_11 = "0";
        public string Msg6_12 = "0";
        public string Msg6_13 = "0";
        public string Msg6_14 = "0";
        public string Msg6_15 = "0";
        public string Msg6_16 = "0";
        public string Msg6_17 = "0";
        public string Msg6_18 = "0";
        public string Msg6_19 = "0";
        public string Msg6_20 = "1";
        // переменные для хренения данных 7  сообщения
        public string Msg7_1 = "0";
        public string Msg7_2 = "0";
        public string Msg7_3 = "0";
        public string Msg7_4 = "0";
        public string Msg7_5 = "0";
        public string Msg7_6 = "0";
        public string Msg7_7 = "0";
        public string Msg7_8 = "0";
        public string Msg7_9 = "0";
        public string Msg7_10 = "5";
        public string Msg7_11 = "0";
        public string Msg7_12 = "0";
        public string Msg7_13 = "0";
        public string Msg7_14 = "0";
        public string Msg7_15 = "0";
        public string Msg7_16 = "0";
        public string Msg7_17 = "0";
        public string Msg7_18 = "0";
        public string Msg7_19 = "0";
        public string Msg7_20 = "1";
        // переменные для хренения данных 8 сообщения
        public string Msg8_1 = "0";
        public string Msg8_2 = "0";
        public string Msg8_3 = "0";
        public string Msg8_4 = "0";
        public string Msg8_5 = "0";
        public string Msg8_6 = "0";
        public string Msg8_7 = "0";
        public string Msg8_8 = "0";
        public string Msg8_9 = "0";
        public string Msg8_10 = "5";
        public string Msg8_11 = "0";
        public string Msg8_12 = "0";
        public string Msg8_13 = "0";
        public string Msg8_14 = "0";
        public string Msg8_15 = "0";
        public string Msg8_16 = "0";
        public string Msg8_17 = "0";
        public string Msg8_18 = "0";
        public string Msg8_19 = "0";
        public string Msg8_20 = "1";





        public Form1()
        {
            InitializeComponent();

            comboBox1.SelectedItem = "1";
            comboBox2.SelectedItem = "Std";
            comboBox3.SelectedItem = "500";
            comboBox4.SelectedItem = "1";
            comboBox5.SelectedItem = "3";
            comboBox6.SelectedItem = "3";
            comboBox7.SelectedItem = "3";
            comboBox8.SelectedItem = "3";
            comboBox9.SelectedItem = "3";
            comboBox10.SelectedItem = "3";
            comboBox11.SelectedItem = "3";

            checkBox1.Checked = false;
            checkBox2.Checked = true;
            checkBox3.Checked = false;
            checkBox4.Checked = false;

        }

        private void Form1_Load(object sender, EventArgs e)//При открытии формы открыть девайс 
        {
            //При открытии формы открыть девайс 
            Handless = v_usb.HID_OpenDevice(pid, vid, ver, ind);

            toolTip1.ToolTipIcon = ToolTipIcon.Warning;



            toolTip1.ToolTipTitle = "Attention-the date format:";



            toolTip1.IsBalloon = true;



            toolTip1.SetToolTip(maskedTextBox1, "Day-Month-Year");



        }


        class Win32 // Класс для использования консоли 
        {
            [DllImport("kernel32.dll")]
            public static extern Boolean AllocConsole();
            [DllImport("kernel32.dll")]
            public static extern Boolean FreeConsole();
        }


        private void timer1_Tick(object sender, EventArgs e) // Таймер проверяющий подключение устройства 
        {

            State = v_usb.HID_DeviceTest(pid, vid, ver, ind);

            if (State == 0) //если устройство отключено
            {
                label1.Text = "Девайс отключен";
                label2.Text = "Девайс отключен";
                textBox3.BackColor = Color.Black;
                textBox3.ForeColor = Color.Red;
                textBox3.Text = ">Device not connected!!";
                checkBox1.Checked = false;
                checkBox2.Checked = true;
                checkBox3.Checked = false;
                checkBox4.Checked = false;
                button3.Enabled = false;
								OneThreadcheckBox.Enabled = false;
                autoRebootcheckBox.Enabled = false;
                Buffer[1] = 1;
                Buffer[2] = 0;
                Buffer[3] = 0;
                Buffer[4] = 0;

            }
            else    //если устройство подключено, то вычисляем температуру
            {
                Handless = v_usb.HID_OpenDevice(pid, vid, ver, ind);
                res = v_usb.HID_ReadDevice(Handless, ReadBuffer, ReadBuffer.Length);
                textBox3.BackColor = Color.LightGreen;
                textBox3.ForeColor = Color.Black;
                textBox3.Text = ">ОК. Press Erase before writing!";
                checkBox1.Checked = true;
                checkBox3.Checked = true;
                button3.Enabled = true;
                //smallToBig(2,4,Buffer);
                label11.Text = Convert.ToString(smallToBig(6, 4, ReadBuffer));
                label12.Text = Convert.ToString(smallToBig(2, 4, ReadBuffer));
                //label11.Text = Convert.ToString(ReadBuffer[6]);
								if (ReadBuffer[10] == 0x33)
								{
									OneThreadcheckBox.Enabled = true;
                  autoRebootcheckBox.Enabled = false;
								}
                else if (ReadBuffer[10] == 0x44)
								{
                  OneThreadcheckBox.Enabled = true;
                  autoRebootcheckBox.Enabled = true;
								}
                  else 
                  {
                    OneThreadcheckBox.Enabled = false;
                    autoRebootcheckBox.Enabled = false;
                  }
							
                //######################################################################################
                // ВЫЧИСЛЕНИЕ ТЕМПЕРАТУРЫ ИЗ ПРИНЯТЫХ БАЙТОВ И ОТОБРАЖЕНИЕ В НЕОБХОДИМОМ ФОРМАТЕ
                double zamer;
                string temperatura;

                if (Buffer[0] == 4)
                {
                    label1.ForeColor = Color.Red;
                    label1.Text = Convert.ToString(Buffer[4]);  //Buffer[1]
                }
                else
                {
                    zamer = Convert.ToDouble(Buffer[1]) / 16 + Convert.ToDouble(Buffer[2]) * 16;
                    if (zamer < 150 && zamer > -50)
                    {
                        temperatura = Strings.Format(zamer, ".0");
                        label1.ForeColor = Color.Black;
                        label1.Text = temperatura + " °C";
                    }
                }

                if (Buffer[0] == 3)
                {
                    label2.ForeColor = Color.Red;
                    label2.Text = "4";
                }
                else
                {
                    zamer = Convert.ToDouble(Buffer[3]) / 16 + Convert.ToDouble(Buffer[4]) * 16;
                    if (zamer < 150 && zamer > -50)
                    {
                        temperatura = Strings.Format(zamer, ".0");
                        label2.ForeColor = Color.Black;
                        label2.Text = temperatura + " °C";
                    }
                }
								
            }
            if (checkBox1.Checked == true & checkBox2.Checked == true)
            {
                button12.Enabled = true;
            }
            else
            {
                button12.Enabled = false;
            }

            if (checkBox3.Checked == true & checkBox4.Checked == true)
            {
                button13.Enabled = true;
            }
            else
            {
                button13.Enabled = false;
            }

            //######################################################################################


        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)//При закрытии формы закрыть девайс 
        {
            //При закрытии формы закрыть девайс
            res = v_usb.HID_CloseDevice(Handless);

        }



        private void button1_Click(object sender, EventArgs e) // Обработчик кнопки 1 чтение
        {
            openFileDialog1.Filter = "Configuration file (*.can)|*.can|Все файлы (*.*)|*.*";
            openFileDialog1.FilterIndex = 0;
            
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
               
                label9.Text = Path.GetFileNameWithoutExtension(openFileDialog1.FileName);
                string[] f = File.ReadAllLines(openFileDialog1.FileName, Encoding.Default); // Массив для хранения прочитанных из файла данных

                comboBox1.SelectedItem = XorCrypt(f[0], KEY);
                comboBox2.SelectedItem = XorCrypt(f[1], KEY);
                comboBox3.SelectedItem = XorCrypt(f[2], KEY);
                comboBox4.SelectedItem = XorCrypt(f[3], KEY);
                comboBox5.SelectedItem = XorCrypt(f[4], KEY);
                comboBox6.SelectedItem = XorCrypt(f[5], KEY);
                comboBox7.SelectedItem = XorCrypt(f[6], KEY);
                comboBox8.SelectedItem = XorCrypt(f[7], KEY);
                comboBox9.SelectedItem = XorCrypt(f[8], KEY);
                comboBox10.SelectedItem = XorCrypt(f[9], KEY);
                comboBox11.SelectedItem = XorCrypt(f[10], KEY);

                textBox1.Text = "0";//f[11];
                maskedTextBox1.Text = "0";//f[12];

                // Чтение 1-го сообщения c 13-32 
                Msg1_1 = XorCrypt(f[13], KEY);
                Msg1_2 = XorCrypt(f[14], KEY);
                Msg1_3 = XorCrypt(f[15], KEY);
                Msg1_4 = XorCrypt(f[16], KEY);
                Msg1_5 = XorCrypt(f[17], KEY);
                Msg1_6 = XorCrypt(f[18], KEY);
                Msg1_7 = XorCrypt(f[19], KEY);
                Msg1_8 = XorCrypt(f[20], KEY);
                Msg1_9 = XorCrypt(f[21], KEY);
                Msg1_10 = XorCrypt(f[22], KEY);
                Msg1_11 = XorCrypt(f[23], KEY);
                Msg1_12 = XorCrypt(f[24], KEY);
                Msg1_13 = XorCrypt(f[25], KEY);
                Msg1_14 = XorCrypt(f[26], KEY);
                Msg1_15 = XorCrypt(f[27], KEY);
                Msg1_16 = XorCrypt(f[28], KEY);
                Msg1_17 = XorCrypt(f[29], KEY);
                Msg1_18 = XorCrypt(f[30], KEY);
                Msg1_19 = XorCrypt(f[31], KEY);
                Msg1_20 = XorCrypt(f[32], KEY);
                // Чтение 2-го сообщения c 33 - 52
                Msg2_1 = XorCrypt(f[33], KEY);
                Msg2_2 = XorCrypt(f[34], KEY);
                Msg2_3 = XorCrypt(f[35], KEY);
                Msg2_4 = XorCrypt(f[36], KEY);
                Msg2_5 = XorCrypt(f[37], KEY);
                Msg2_6 = XorCrypt(f[38], KEY);
                Msg2_7 = XorCrypt(f[39], KEY);
                Msg2_8 = XorCrypt(f[40], KEY);
                Msg2_9 = XorCrypt(f[41], KEY);
                Msg2_10 = XorCrypt(f[42], KEY);
                Msg2_11 = XorCrypt(f[43], KEY);
                Msg2_12 = XorCrypt(f[44], KEY);
                Msg2_13 = XorCrypt(f[45], KEY);
                Msg2_14 = XorCrypt(f[46], KEY);
                Msg2_15 = XorCrypt(f[47], KEY);
                Msg2_16 = XorCrypt(f[48], KEY);
                Msg2_17 = XorCrypt(f[49], KEY);
                Msg2_18 = XorCrypt(f[50], KEY);
                Msg2_19 = XorCrypt(f[51], KEY);
                Msg2_20 = XorCrypt(f[52], KEY);
                // Чтение 3-го сообщения c 53 - 72
                Msg3_1 = XorCrypt(f[53], KEY);
                Msg3_2 = XorCrypt(f[54], KEY);
                Msg3_3 = XorCrypt(f[55], KEY);
                Msg3_4 = XorCrypt(f[56], KEY);
                Msg3_5 = XorCrypt(f[57], KEY);
                Msg3_6 = XorCrypt(f[58], KEY);
                Msg3_7 = XorCrypt(f[59], KEY);
                Msg3_8 = XorCrypt(f[60], KEY);
                Msg3_9 = XorCrypt(f[61], KEY);
                Msg3_10 = XorCrypt(f[62], KEY);
                Msg3_11 = XorCrypt(f[63], KEY);
                Msg3_12 = XorCrypt(f[64], KEY);
                Msg3_13 = XorCrypt(f[65], KEY);
                Msg3_14 = XorCrypt(f[66], KEY);
                Msg3_15 = XorCrypt(f[67], KEY);
                Msg3_16 = XorCrypt(f[68], KEY);
                Msg3_17 = XorCrypt(f[79], KEY);
                Msg3_18 = XorCrypt(f[70], KEY);
                Msg3_19 = XorCrypt(f[71], KEY);
                Msg3_20 = XorCrypt(f[72], KEY);
                // Чтение 4-го сообщения 73 - 92
                Msg4_1 = XorCrypt(f[73], KEY);
                Msg4_2 = XorCrypt(f[74], KEY);
                Msg4_3 = XorCrypt(f[75], KEY);
                Msg4_4 = XorCrypt(f[76], KEY);
                Msg4_5 = XorCrypt(f[77], KEY);
                Msg4_6 = XorCrypt(f[78], KEY);
                Msg4_7 = XorCrypt(f[79], KEY);
                Msg4_8 = XorCrypt(f[80], KEY);
                Msg4_9 = XorCrypt(f[81], KEY);
                Msg4_10 = XorCrypt(f[82], KEY);
                Msg4_11 = XorCrypt(f[83], KEY);
                Msg4_12 = XorCrypt(f[84], KEY);
                Msg4_13 = XorCrypt(f[85], KEY);
                Msg4_14 = XorCrypt(f[86], KEY);
                Msg4_15 = XorCrypt(f[87], KEY);
                Msg4_16 = XorCrypt(f[88], KEY);
                Msg4_17 = XorCrypt(f[89], KEY);
                Msg4_18 = XorCrypt(f[90], KEY);
                Msg4_19 = XorCrypt(f[91], KEY);
                Msg4_20 = XorCrypt(f[92], KEY);
                // Чтение 5-го сообщения
                int i = 93;
                Msg5_1 = XorCrypt(f[i], KEY);i++;
                Msg5_2 = XorCrypt(f[i], KEY); i++;
                Msg5_3 = XorCrypt(f[i], KEY); i++;
                Msg5_4 = XorCrypt(f[i], KEY); i++;
                Msg5_5 = XorCrypt(f[i], KEY); i++;
                Msg5_6 = XorCrypt(f[i], KEY); i++;
                Msg5_7 = XorCrypt(f[i], KEY); i++;
                Msg5_8 = XorCrypt(f[i], KEY); i++;
                Msg5_9 = XorCrypt(f[i], KEY); i++;
                Msg5_10 = XorCrypt(f[i], KEY); i++;
                Msg5_11 = XorCrypt(f[i], KEY); i++;
                Msg5_12 = XorCrypt(f[i], KEY); i++;
                Msg5_13 = XorCrypt(f[i], KEY); i++;
                Msg5_14 = XorCrypt(f[i], KEY); i++;
                Msg5_15 = XorCrypt(f[i], KEY); i++;
                Msg5_16 = XorCrypt(f[i], KEY); i++;
                Msg5_17 = XorCrypt(f[i], KEY); i++;
                Msg5_18 = XorCrypt(f[i], KEY); i++;
                Msg5_19 = XorCrypt(f[i], KEY); i++;
                Msg5_20 = XorCrypt(f[i], KEY); i++;
                // Чтение 6-го сообщения
                Msg6_1 = XorCrypt(f[i], KEY); i++;
                Msg6_2 = XorCrypt(f[i], KEY); i++;
                Msg6_3 = XorCrypt(f[i], KEY); i++;
                Msg6_4 = XorCrypt(f[i], KEY); i++;
                Msg6_5 = XorCrypt(f[i], KEY); i++;
                Msg6_6 = XorCrypt(f[i], KEY); i++;
                Msg6_7 = XorCrypt(f[i], KEY); i++;
                Msg6_8 = XorCrypt(f[i], KEY); i++;
                Msg6_9 = XorCrypt(f[i], KEY); i++;
                Msg6_10 = XorCrypt(f[i], KEY); i++;
                Msg6_11 = XorCrypt(f[i], KEY); i++;
                Msg6_12 = XorCrypt(f[i], KEY); i++;
                Msg6_13 = XorCrypt(f[i], KEY); i++;
                Msg6_14 = XorCrypt(f[i], KEY); i++;
                Msg6_15 = XorCrypt(f[i], KEY); i++;
                Msg6_16 = XorCrypt(f[i], KEY); i++;
                Msg6_17 = XorCrypt(f[i], KEY); i++;
                Msg6_18 = XorCrypt(f[i], KEY); i++;
                Msg6_19 = XorCrypt(f[i], KEY); i++;
                Msg6_20 = XorCrypt(f[i], KEY); i++;
                // Чтение 7-го сообщения
                Msg7_1 = XorCrypt(f[i], KEY); i++;
                Msg7_2 = XorCrypt(f[i], KEY); i++;
                Msg7_3 = XorCrypt(f[i], KEY); i++;
                Msg7_4 = XorCrypt(f[i], KEY); i++;
                Msg7_5 = XorCrypt(f[i], KEY); i++;
                Msg7_6 = XorCrypt(f[i], KEY); i++;
                Msg7_7 = XorCrypt(f[i], KEY); i++;
                Msg7_8 = XorCrypt(f[i], KEY); i++;
                Msg7_9 = XorCrypt(f[i], KEY); i++;
                Msg7_10 = XorCrypt(f[i], KEY); i++;
                Msg7_11 = XorCrypt(f[i], KEY); i++;
                Msg7_12 = XorCrypt(f[i], KEY); i++;
                Msg7_13 = XorCrypt(f[i], KEY); i++;
                Msg7_14 = XorCrypt(f[i], KEY); i++;
                Msg7_15 = XorCrypt(f[i], KEY); i++;
                Msg7_16 = XorCrypt(f[i], KEY); i++;
                Msg7_17 = XorCrypt(f[i], KEY); i++;
                Msg7_18 = XorCrypt(f[i], KEY); i++;
                Msg7_19 = XorCrypt(f[i], KEY); i++;
                Msg7_20 = XorCrypt(f[i], KEY); i++;
                // Чтение 8-го сообщения
                Msg8_1 = XorCrypt(f[i], KEY); i++;
                Msg8_2 = XorCrypt(f[i], KEY); i++;
                Msg8_3 = XorCrypt(f[i], KEY); i++;
                Msg8_4 = XorCrypt(f[i], KEY); i++;
                Msg8_5 = XorCrypt(f[i], KEY); i++;
                Msg8_6 = XorCrypt(f[i], KEY); i++;
                Msg8_7 = XorCrypt(f[i], KEY); i++;
                Msg8_8 = XorCrypt(f[i], KEY); i++;
                Msg8_9 = XorCrypt(f[i], KEY); i++;
                Msg8_10 = XorCrypt(f[i], KEY); i++;
                Msg8_11 = XorCrypt(f[i], KEY); i++;
                Msg8_12 = XorCrypt(f[i], KEY); i++;
                Msg8_13 = XorCrypt(f[i], KEY); i++;
                Msg8_14 = XorCrypt(f[i], KEY); i++;
                Msg8_15 = XorCrypt(f[i], KEY); i++;
                Msg8_16 = XorCrypt(f[i], KEY); i++;
                Msg8_17 = XorCrypt(f[i], KEY); i++;
                Msg8_18 = XorCrypt(f[i], KEY); i++;
                Msg8_19 = XorCrypt(f[i], KEY); i++;
                Msg8_20 = XorCrypt(f[i], KEY); i++;
								if (i < f.Length)
								{
									string tmp = XorCrypt(f[i], KEY); i++;

									if (tmp == "True")
									{
										OneThreadcheckBox.Checked = true;
									}
									else
									{
										OneThreadcheckBox.Checked = false;
									}
								}
								else 
								{
									OneThreadcheckBox.Checked = false;
								}
            }

            /*Buffer1[0] = 3;
            Buffer1[1] = 1;
            Buffer1[2] = 2;
            Buffer1[3] = 1;
            Buffer1[4] = 2;
            Buffer1[5] = 0xAA;
          

            v_usb.HID_SetFeature(Handless, Buffer1, Buffer1.Length); // Отправка данных методом Set_Future*/

        }
        private void ConsoleWrite(string message) // Простая функция звписи текста в консоль 
        {
            Win32.AllocConsole();
            Console.Title = "Scanning ...";
            Console.WriteLine(message + "\n");

        }

        private void LoadProgress(string message) // Индикатор загрузки сообщения в косоли 
        {
            Win32.AllocConsole();
            Console.Title = "Scanning ...";
            Console.WriteLine(message + "\n");
            int i = 0;
            for (i = 0; i < 60; i++)
            {

                Console.Write("#");
                Thread.Sleep(20);
            }

            Win32.AllocConsole();
            Console.Title = "Scanning ...";
            Console.WriteLine("\n");
            Console.WriteLine("OK!\n");

        }

        private void button2_Click(object sender, EventArgs e) // Обработчик кнопки 2 сохранение
        {

            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.FileName = textBox4.Text + "-" + textBox5.Text + "-2006г-2.0i-300km_h";
            saveFileDialog.Filter = "Текстовый документ (*.can)|*.can|Все файлы (*.*)|*.*";

            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                StreamWriter streamWriter = new StreamWriter(saveFileDialog.FileName);

                streamWriter.WriteLine((string)(comboBox1.SelectedItem), "\r\n");
                streamWriter.WriteLine((string)(comboBox2.SelectedItem), "\r\n");
                streamWriter.WriteLine((string)(comboBox3.SelectedItem), "\r\n");
                streamWriter.WriteLine((string)(comboBox4.SelectedItem), "\r\n");
                streamWriter.WriteLine((string)(comboBox5.SelectedItem), "\r\n");
                streamWriter.WriteLine((string)(comboBox6.SelectedItem), "\r\n");
                streamWriter.WriteLine((string)(comboBox7.SelectedItem), "\r\n");
                streamWriter.WriteLine((string)(comboBox8.SelectedItem), "\r\n");
                streamWriter.WriteLine((string)(comboBox9.SelectedItem), "\r\n");
                streamWriter.WriteLine((string)(comboBox10.SelectedItem), "\r\n");
                streamWriter.WriteLine((string)(comboBox11.SelectedItem), "\r\n");

                streamWriter.WriteLine(textBox1.Text, "\r\n");
                streamWriter.WriteLine(maskedTextBox1.Text, "\r\n");
                // Записываем 1-ое сообщение
                streamWriter.WriteLine(Msg1_1, "\r\n");
                streamWriter.WriteLine(Msg1_2, "\r\n");
                streamWriter.WriteLine(Msg1_3, "\r\n");
                streamWriter.WriteLine(Msg1_4, "\r\n");
                streamWriter.WriteLine(Msg1_5, "\r\n");
                streamWriter.WriteLine(Msg1_6, "\r\n");
                streamWriter.WriteLine(Msg1_7, "\r\n");
                streamWriter.WriteLine(Msg1_8, "\r\n");
                streamWriter.WriteLine(Msg1_9, "\r\n");
                streamWriter.WriteLine(Msg1_10, "\r\n");
                streamWriter.WriteLine(Msg1_11, "\r\n");
                streamWriter.WriteLine(Msg1_12, "\r\n");
                streamWriter.WriteLine(Msg1_13, "\r\n");
                streamWriter.WriteLine(Msg1_14, "\r\n");
                streamWriter.WriteLine(Msg1_15, "\r\n");
                streamWriter.WriteLine(Msg1_16, "\r\n");
                streamWriter.WriteLine(Msg1_17, "\r\n");
                streamWriter.WriteLine(Msg1_18, "\r\n");
                streamWriter.WriteLine(Msg1_19, "\r\n");
                streamWriter.WriteLine(Msg1_20, "\r\n");
                // Записываем 2-ое сообщение
                streamWriter.WriteLine(Msg2_1, "\r\n");
                streamWriter.WriteLine(Msg2_2, "\r\n");
                streamWriter.WriteLine(Msg2_3, "\r\n");
                streamWriter.WriteLine(Msg2_4, "\r\n");
                streamWriter.WriteLine(Msg2_5, "\r\n");
                streamWriter.WriteLine(Msg2_6, "\r\n");
                streamWriter.WriteLine(Msg2_7, "\r\n");
                streamWriter.WriteLine(Msg2_8, "\r\n");
                streamWriter.WriteLine(Msg2_9, "\r\n");
                streamWriter.WriteLine(Msg2_10, "\r\n");
                streamWriter.WriteLine(Msg2_11, "\r\n");
                streamWriter.WriteLine(Msg2_12, "\r\n");
                streamWriter.WriteLine(Msg2_13, "\r\n");
                streamWriter.WriteLine(Msg2_14, "\r\n");
                streamWriter.WriteLine(Msg2_15, "\r\n");
                streamWriter.WriteLine(Msg2_16, "\r\n");
                streamWriter.WriteLine(Msg2_17, "\r\n");
                streamWriter.WriteLine(Msg2_18, "\r\n");
                streamWriter.WriteLine(Msg2_19, "\r\n");
                streamWriter.WriteLine(Msg2_20, "\r\n");
                // Записываем 3 сообщение
                streamWriter.WriteLine(Msg3_1, "\r\n");
                streamWriter.WriteLine(Msg3_2, "\r\n");
                streamWriter.WriteLine(Msg3_3, "\r\n");
                streamWriter.WriteLine(Msg3_4, "\r\n");
                streamWriter.WriteLine(Msg3_5, "\r\n");
                streamWriter.WriteLine(Msg3_6, "\r\n");
                streamWriter.WriteLine(Msg3_7, "\r\n");
                streamWriter.WriteLine(Msg3_8, "\r\n");
                streamWriter.WriteLine(Msg3_9, "\r\n");
                streamWriter.WriteLine(Msg3_10, "\r\n");
                streamWriter.WriteLine(Msg3_11, "\r\n");
                streamWriter.WriteLine(Msg3_12, "\r\n");
                streamWriter.WriteLine(Msg3_13, "\r\n");
                streamWriter.WriteLine(Msg3_14, "\r\n");
                streamWriter.WriteLine(Msg3_15, "\r\n");
                streamWriter.WriteLine(Msg3_16, "\r\n");
                streamWriter.WriteLine(Msg3_17, "\r\n");
                streamWriter.WriteLine(Msg3_18, "\r\n");
                streamWriter.WriteLine(Msg3_19, "\r\n");
                streamWriter.WriteLine(Msg3_20, "\r\n");
                // Записываем 4 сообщение
                streamWriter.WriteLine(Msg4_1, "\r\n");
                streamWriter.WriteLine(Msg4_2, "\r\n");
                streamWriter.WriteLine(Msg4_3, "\r\n");
                streamWriter.WriteLine(Msg4_4, "\r\n");
                streamWriter.WriteLine(Msg4_5, "\r\n");
                streamWriter.WriteLine(Msg4_6, "\r\n");
                streamWriter.WriteLine(Msg4_7, "\r\n");
                streamWriter.WriteLine(Msg4_8, "\r\n");
                streamWriter.WriteLine(Msg4_9, "\r\n");
                streamWriter.WriteLine(Msg4_10, "\r\n");
                streamWriter.WriteLine(Msg4_11, "\r\n");
                streamWriter.WriteLine(Msg4_12, "\r\n");
                streamWriter.WriteLine(Msg4_13, "\r\n");
                streamWriter.WriteLine(Msg4_14, "\r\n");
                streamWriter.WriteLine(Msg4_15, "\r\n");
                streamWriter.WriteLine(Msg4_16, "\r\n");
                streamWriter.WriteLine(Msg4_17, "\r\n");
                streamWriter.WriteLine(Msg4_18, "\r\n");
                streamWriter.WriteLine(Msg4_19, "\r\n");
                streamWriter.WriteLine(Msg4_20, "\r\n");
                // Записываем 5 сообщение
                streamWriter.WriteLine(Msg5_1, "\r\n");
                streamWriter.WriteLine(Msg5_2, "\r\n");
                streamWriter.WriteLine(Msg5_3, "\r\n");
                streamWriter.WriteLine(Msg5_4, "\r\n");
                streamWriter.WriteLine(Msg5_5, "\r\n");
                streamWriter.WriteLine(Msg5_6, "\r\n");
                streamWriter.WriteLine(Msg5_7, "\r\n");
                streamWriter.WriteLine(Msg5_8, "\r\n");
                streamWriter.WriteLine(Msg5_9, "\r\n");
                streamWriter.WriteLine(Msg5_10, "\r\n");
                streamWriter.WriteLine(Msg5_11, "\r\n");
                streamWriter.WriteLine(Msg5_12, "\r\n");
                streamWriter.WriteLine(Msg5_13, "\r\n");
                streamWriter.WriteLine(Msg5_14, "\r\n");
                streamWriter.WriteLine(Msg5_15, "\r\n");
                streamWriter.WriteLine(Msg5_16, "\r\n");
                streamWriter.WriteLine(Msg5_17, "\r\n");
                streamWriter.WriteLine(Msg5_18, "\r\n");
                streamWriter.WriteLine(Msg5_19, "\r\n");
                streamWriter.WriteLine(Msg5_20, "\r\n");
                // Записываем 6 сообщение
                streamWriter.WriteLine(Msg6_1, "\r\n");
                streamWriter.WriteLine(Msg6_2, "\r\n");
                streamWriter.WriteLine(Msg6_3, "\r\n");
                streamWriter.WriteLine(Msg6_4, "\r\n");
                streamWriter.WriteLine(Msg6_5, "\r\n");
                streamWriter.WriteLine(Msg6_6, "\r\n");
                streamWriter.WriteLine(Msg6_7, "\r\n");
                streamWriter.WriteLine(Msg6_8, "\r\n");
                streamWriter.WriteLine(Msg6_9, "\r\n");
                streamWriter.WriteLine(Msg6_10, "\r\n");
                streamWriter.WriteLine(Msg6_11, "\r\n");
                streamWriter.WriteLine(Msg6_12, "\r\n");
                streamWriter.WriteLine(Msg6_13, "\r\n");
                streamWriter.WriteLine(Msg6_14, "\r\n");
                streamWriter.WriteLine(Msg6_15, "\r\n");
                streamWriter.WriteLine(Msg6_16, "\r\n");
                streamWriter.WriteLine(Msg6_17, "\r\n");
                streamWriter.WriteLine(Msg6_18, "\r\n");
                streamWriter.WriteLine(Msg6_19, "\r\n");
                streamWriter.WriteLine(Msg6_20, "\r\n");
                // Записываем 7 сообщение
                streamWriter.WriteLine(Msg7_1, "\r\n");
                streamWriter.WriteLine(Msg7_2, "\r\n");
                streamWriter.WriteLine(Msg7_3, "\r\n");
                streamWriter.WriteLine(Msg7_4, "\r\n");
                streamWriter.WriteLine(Msg7_5, "\r\n");
                streamWriter.WriteLine(Msg7_6, "\r\n");
                streamWriter.WriteLine(Msg7_7, "\r\n");
                streamWriter.WriteLine(Msg7_8, "\r\n");
                streamWriter.WriteLine(Msg7_9, "\r\n");
                streamWriter.WriteLine(Msg7_10, "\r\n");
                streamWriter.WriteLine(Msg7_11, "\r\n");
                streamWriter.WriteLine(Msg7_12, "\r\n");
                streamWriter.WriteLine(Msg7_13, "\r\n");
                streamWriter.WriteLine(Msg7_14, "\r\n");
                streamWriter.WriteLine(Msg7_15, "\r\n");
                streamWriter.WriteLine(Msg7_16, "\r\n");
                streamWriter.WriteLine(Msg7_17, "\r\n");
                streamWriter.WriteLine(Msg7_18, "\r\n");
                streamWriter.WriteLine(Msg7_19, "\r\n");
                streamWriter.WriteLine(Msg7_20, "\r\n");
                // Записываем 8 сообщение
                streamWriter.WriteLine(Msg8_1, "\r\n");
                streamWriter.WriteLine(Msg8_2, "\r\n");
                streamWriter.WriteLine(Msg8_3, "\r\n");
                streamWriter.WriteLine(Msg8_4, "\r\n");
                streamWriter.WriteLine(Msg8_5, "\r\n");
                streamWriter.WriteLine(Msg8_6, "\r\n");
                streamWriter.WriteLine(Msg8_7, "\r\n");
                streamWriter.WriteLine(Msg8_8, "\r\n");
                streamWriter.WriteLine(Msg8_9, "\r\n");
                streamWriter.WriteLine(Msg8_10, "\r\n");
                streamWriter.WriteLine(Msg8_11, "\r\n");
                streamWriter.WriteLine(Msg8_12, "\r\n");
                streamWriter.WriteLine(Msg8_13, "\r\n");
                streamWriter.WriteLine(Msg8_14, "\r\n");
                streamWriter.WriteLine(Msg8_15, "\r\n");
                streamWriter.WriteLine(Msg8_16, "\r\n");
                streamWriter.WriteLine(Msg8_17, "\r\n");
                streamWriter.WriteLine(Msg8_18, "\r\n");
                streamWriter.WriteLine(Msg8_19, "\r\n");
                streamWriter.WriteLine(Msg8_20, "\r\n");

                streamWriter.Close();
            }
            /////////////////////////////////////////////////////////////////
            /* Buffer1[0] = 3;
             Buffer1[1] = 0;
             Buffer1[2] = 2;
             Buffer1[3] = 1;
             Buffer1[4] = 2;
             Buffer1[5] = 9;


             v_usb.HID_SetFeature(Handless, Buffer1, Buffer1.Length); // Отправка данных методом Set_Future. Комбинируем отправку нескольких сообщений с промежутком Sleep()
             LoadProgress("Message 1");
             Thread.Sleep(200);
             LoadProgress("Message 2");
             v_usb.HID_SetFeature(Handless, Buffer1, Buffer1.Length);
             ConsoleWrite("OK");*/

        }

        private void button3_Click(object sender, EventArgs e)
        {
            Form11 f = new Form11();
            f.Owner = this;
            f.ShowDialog();

            /* t = long.Parse(textBox1.Text, NumberStyles.HexNumber); // Пребразование TextBox в HEX
             //Разбиваем переменную на байты
             Buffer[3] = (byte)((t & 0XFF000000) >> 24); 
             Buffer[4] = (byte)((t & 0X00FF0000) >> 16);
             Buffer[5] = (byte)((t & 0X0000FF00) >> 8);
             Buffer[6] = (byte)((t & 0X000000FF) >> 0);
             //Собираем в одноцелое
            ConsoleWrite(Convert.ToString((Buffer[3] << 24) | (Buffer[4] << 16) | (Buffer[5] << 8) | (Buffer[6]<<0), 16));*/


        }

        private void comboBox4_SelectedIndexChanged(object sender, EventArgs e) // ОТвечает за цвет кнопки Button4 || Msg1 1 
        {

            switch (Convert.ToInt32(comboBox4.SelectedItem))
            {
                case 2:
                    button4.BackColor = Color.LightGreen;
                    break;
                case 1:
                    button4.BackColor = Color.LightCoral;
                    break;
                case 3:
                    button4.BackColor = Color.LightGray;
                    break;
            }

        }

        private void comboBox5_SelectedIndexChanged(object sender, EventArgs e) // ОТвечает за цвет кнопки Button5 || Msg1 2 
        {
            switch (Convert.ToInt32(comboBox5.SelectedItem))
            {
                case 2:
                    button5.BackColor = Color.LightGreen;
                    break;
                case 1:
                    button5.BackColor = Color.LightCoral;
                    break;
                case 3:
                    button5.BackColor = Color.LightGray;
                    break;
            }
        }

        private void comboBox6_SelectedIndexChanged(object sender, EventArgs e) // ОТвечает за цвет кнопки Button6 || Msg1 3 
        {
            switch (Convert.ToInt32(comboBox6.SelectedItem))
            {
                case 2:
                    button6.BackColor = Color.LightGreen;
                    break;
                case 1:
                    button6.BackColor = Color.LightCoral;
                    break;
                case 3:
                    button6.BackColor = Color.LightGray;
                    break;
            }
        }

        private void comboBox7_SelectedIndexChanged(object sender, EventArgs e) // ОТвечает за цвет кнопки Button7 || Msg1 4 
        {
            switch (Convert.ToInt32(comboBox7.SelectedItem))
            {
                case 2:
                    button7.BackColor = Color.LightGreen;
                    break;
                case 1:
                    button7.BackColor = Color.LightCoral;
                    break;
                case 3:
                    button7.BackColor = Color.LightGray;
                    break;
            }
        }

        private void comboBox8_SelectedIndexChanged(object sender, EventArgs e) // ОТвечает за цвет кнопки Button8 || Msg1 5 
        {
            switch (Convert.ToInt32(comboBox8.SelectedItem))
            {
                case 2:
                    button8.BackColor = Color.LightGreen;
                    break;
                case 1:
                    button8.BackColor = Color.LightCoral;
                    break;
                case 3:
                    button8.BackColor = Color.LightGray;
                    break;
            }
        }

        private void comboBox9_SelectedIndexChanged(object sender, EventArgs e) // ОТвечает за цвет кнопки Button9 || Msg1 6 
        {
            switch (Convert.ToInt32(comboBox9.SelectedItem))
            {
                case 2:
                    button9.BackColor = Color.LightGreen;
                    break;
                case 1:
                    button9.BackColor = Color.LightCoral;
                    break;
                case 3:
                    button9.BackColor = Color.LightGray;
                    break;
            }
        }

        private void comboBox10_SelectedIndexChanged(object sender, EventArgs e) // ОТвечает за цвет кнопки Button10 || Msg1 7 
        {
            switch (Convert.ToInt32(comboBox10.SelectedItem))
            {
                case 2:
                    button10.BackColor = Color.LightGreen;
                    break;
                case 1:
                    button10.BackColor = Color.LightCoral;
                    break;
                case 3:
                    button10.BackColor = Color.LightGray;
                    break;
            }
        }

        private void comboBox11_SelectedIndexChanged(object sender, EventArgs e) // ОТвечает за цвет кнопки Button11 || Msg1 8 
        {
            switch (Convert.ToInt32(comboBox11.SelectedItem))
            {
                case 2:
                    button11.BackColor = Color.LightGreen;
                    break;
                case 1:
                    button11.BackColor = Color.LightCoral;
                    break;
                case 3:
                    button11.BackColor = Color.LightGray;
                    break;
            }
        }

        private void button4_Click(object sender, EventArgs e) //
        {
            Form2 f = new Form2();
            f.Owner = this;
            f.ShowDialog();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            Form3 f = new Form3();
            f.Owner = this;
            f.ShowDialog();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            Form4 f = new Form4();
            f.Owner = this;
            f.ShowDialog();
        }

        private void button7_Click(object sender, EventArgs e)
        {
            Form5 f = new Form5();
            f.Owner = this;
            f.ShowDialog();
        }

        private void button8_Click(object sender, EventArgs e)
        {
            Form6 f = new Form6();
            f.Owner = this;
            f.ShowDialog();
        }

        private void button9_Click(object sender, EventArgs e)
        {
            Form7 f = new Form7();
            f.Owner = this;
            f.ShowDialog();
        }

        private void button10_Click(object sender, EventArgs e)
        {
            Form8 f = new Form8();
            f.Owner = this;
            f.ShowDialog();
        }

        private void button11_Click(object sender, EventArgs e)
        {
            Form9 f = new Form9();
            f.Owner = this;
            f.ShowDialog();
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e) // выбор количества сообщений
        {
            switch (Convert.ToInt16(comboBox1.SelectedItem))
            {
                case 1:
                    button4.Enabled = true; comboBox4.SelectedItem = "1";
                    button5.Enabled = false; comboBox5.SelectedItem = "3";
                    button6.Enabled = false; comboBox6.SelectedItem = "3";
                    button7.Enabled = false; comboBox7.SelectedItem = "3";
                    button8.Enabled = false; comboBox8.SelectedItem = "3";
                    button9.Enabled = false; comboBox9.SelectedItem = "3";
                    button10.Enabled = false; comboBox10.SelectedItem = "3";
                    button11.Enabled = false; comboBox11.SelectedItem = "3";
                    break;
                case 2:
                    button4.Enabled = true; comboBox4.SelectedItem = "1";
                    button5.Enabled = true; comboBox5.SelectedItem = "1";
                    button6.Enabled = false; comboBox6.SelectedItem = "3";
                    button7.Enabled = false; comboBox7.SelectedItem = "3";
                    button8.Enabled = false; comboBox8.SelectedItem = "3";
                    button9.Enabled = false; comboBox9.SelectedItem = "3";
                    button10.Enabled = false; comboBox10.SelectedItem = "3";
                    button11.Enabled = false; comboBox11.SelectedItem = "3";
                    break;
                case 3:
                    button4.Enabled = true; comboBox4.SelectedItem = "1";
                    button5.Enabled = true; comboBox5.SelectedItem = "1";
                    button6.Enabled = true; comboBox6.SelectedItem = "1";
                    button7.Enabled = false; comboBox7.SelectedItem = "3";
                    button8.Enabled = false; comboBox8.SelectedItem = "3";
                    button9.Enabled = false; comboBox9.SelectedItem = "3";
                    button10.Enabled = false; comboBox10.SelectedItem = "3";
                    button11.Enabled = false; comboBox11.SelectedItem = "3";
                    break;
                case 4:
                    button4.Enabled = true; comboBox4.SelectedItem = "1";
                    button5.Enabled = true; comboBox5.SelectedItem = "1";
                    button6.Enabled = true; comboBox6.SelectedItem = "1";
                    button7.Enabled = true; comboBox7.SelectedItem = "1";
                    button8.Enabled = false; comboBox8.SelectedItem = "3";
                    button9.Enabled = false; comboBox9.SelectedItem = "3";
                    button10.Enabled = false; comboBox10.SelectedItem = "3";
                    button11.Enabled = false; comboBox11.SelectedItem = "3";
                    break;
                case 5:
                    button4.Enabled = true; comboBox4.SelectedItem = "1";
                    button5.Enabled = true; comboBox5.SelectedItem = "1";
                    button6.Enabled = true; comboBox6.SelectedItem = "1";
                    button7.Enabled = true; comboBox7.SelectedItem = "1";
                    button8.Enabled = true; comboBox8.SelectedItem = "1";
                    button9.Enabled = false; comboBox9.SelectedItem = "3";
                    button10.Enabled = false; comboBox10.SelectedItem = "3";
                    button11.Enabled = false; comboBox11.SelectedItem = "3";
                    break;
                case 6:
                    button4.Enabled = true; comboBox4.SelectedItem = "1";
                    button5.Enabled = true; comboBox5.SelectedItem = "1";
                    button6.Enabled = true; comboBox6.SelectedItem = "1";
                    button7.Enabled = true; comboBox7.SelectedItem = "1";
                    button8.Enabled = true; comboBox8.SelectedItem = "1";
                    button9.Enabled = true; comboBox9.SelectedItem = "1";
                    button10.Enabled = false; comboBox10.SelectedItem = "3";
                    button11.Enabled = false; comboBox11.SelectedItem = "3";
                    break;
                case 7:
                    button4.Enabled = true; comboBox4.SelectedItem = "1";
                    button5.Enabled = true; comboBox5.SelectedItem = "1";
                    button6.Enabled = true; comboBox6.SelectedItem = "1";
                    button7.Enabled = true; comboBox7.SelectedItem = "1";
                    button8.Enabled = true; comboBox8.SelectedItem = "1";
                    button9.Enabled = true; comboBox9.SelectedItem = "1";
                    button10.Enabled = true; comboBox10.SelectedItem = "1";
                    button11.Enabled = false; comboBox11.SelectedItem = "3";
                    break;
                case 8:
                    button4.Enabled = true; comboBox4.SelectedItem = "1";
                    button5.Enabled = true; comboBox5.SelectedItem = "1";
                    button6.Enabled = true; comboBox6.SelectedItem = "1";
                    button7.Enabled = true; comboBox7.SelectedItem = "1";
                    button8.Enabled = true; comboBox8.SelectedItem = "1";
                    button9.Enabled = true; comboBox9.SelectedItem = "1";
                    button10.Enabled = true; comboBox10.SelectedItem = "1";
                    button11.Enabled = true; comboBox11.SelectedItem = "1";
                    break;

            }
        }

        private void button12_Click(object sender, EventArgs e) // Обработка кнопки стереть Erase
        {
            //-Erase-Buffer---------------------------------------------------------
            Buf_Erase[0] = 0x03;
            Buf_Erase[1] = 0xCC;                        //Erase Comand
            progressBar1.Maximum = 1;
            progressBar1.Value = 0;
            Thread.Sleep(100);
            v_usb.HID_SetFeature(Handless, Buf_Erase, Buf_Erase.Length); // Отправка данных методом Set_Future
            progressBar1.Value = 1;
            checkBox2.Checked = false;
            Thread.Sleep(100);
            //MessageBox.Show("Data Erased","",MessageBoxButtons.OKCancel);
            checkBox4.Checked = true;
            Thread.Sleep(100);
            MessageBox.Show("Successfully Erased", "", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);

        }

        private void button13_Click(object sender, EventArgs e) // Обработка кнопки Program
        {
            //-Get Big Number------------------------------------------------------
					if (OneThreadcheckBox.Checked == true)
					{
						inOneThread = 0x01;
					}
					else 
					{
						inOneThread = 0x00;
					}

          if (autoRebootcheckBox.Checked == true)
          {
            autoReboot = 0x01;
          }
          else
          {
            autoReboot = 0x01;
          }


            //-Fill Buffer---------------------------------------------------------
            //-Systen-Buffer-------------------------------------------------------
            BufferSystem[0] = 0x03;
            BufferSystem[1] = 0xAA;
            BigToSmall(2, 4, BufferSystem, Convert.ToInt32(maskedTextBox1.Text));
            BigToSmall(6, 3, BufferSystem, Convert.ToInt32(textBox1.Text));
            BufferSystem[10] = Convert.ToByte(comboBox1.SelectedItem);
            BufferSystem[11] = Convert.ToByte(comboBox2.SelectedIndex);
            BufferSystem[12] = Convert.ToByte(comboBox3.SelectedIndex);
						BufferSystem[13] = inOneThread;
            BufferSystem[14] = autoReboot;
            BigToSmall(15, 2, BufferSystem, Convert.ToInt32(rebootTime.Value));
            BufferSystem[17] = Convert.ToByte(delayTime.Value.ToString(), 16);
            //-Buffer-Msg1--------------------------------------------------------
            Buf_MSG1[0] = 0x03;
            Buf_MSG1[1] = 0xA1;
            Buf_MSG1[2] = 0x01;
            Buf_MSG1[3] = Convert.ToByte(Msg1_20, 16);
            BigToSmall(4, 4, Buf_MSG1, Convert.ToInt32(Msg1_1, 16));
            Buf_MSG1[8] = Convert.ToByte(Msg1_2, 16);
            Buf_MSG1[9] = Convert.ToByte(Msg1_3, 16);
            Buf_MSG1[10] = Convert.ToByte(Msg1_4, 16);
            Buf_MSG1[11] = Convert.ToByte(Msg1_5, 16);
            Buf_MSG1[12] = Convert.ToByte(Msg1_6, 16);
            Buf_MSG1[13] = Convert.ToByte(Msg1_7, 16);
            Buf_MSG1[14] = Convert.ToByte(Msg1_8, 16);
            Buf_MSG1[15] = Convert.ToByte(Msg1_9, 16);

						if (int.Parse(Msg1_10) > 255)
						{
							Buf_MSG1[16] = Convert.ToByte("255");
						}
						else 
						{
							Buf_MSG1[16] = Convert.ToByte(Msg1_10);
						}
        
            Buf_MSG1[17] = Convert.ToByte(Msg1_11, 16);

            Buf_MSG1[18] = Convert.ToByte(Msg1_12, 16);
            Buf_MSG1[19] = Convert.ToByte(Msg1_13, 16);
            Buf_MSG1[20] = Convert.ToByte(Msg1_14, 16);
            Buf_MSG1[21] = Convert.ToByte(Msg1_15, 16);
            Buf_MSG1[22] = Convert.ToByte(Msg1_16, 16);
            Buf_MSG1[23] = Convert.ToByte(Msg1_17, 16);
            Buf_MSG1[24] = Convert.ToByte(Msg1_18, 16);
            Buf_MSG1[25] = Convert.ToByte(Msg1_19, 16);

						BigToSmall(26,2,Buf_MSG1,Convert.ToInt32(Msg1_10));
            //-Buffer-Msg2--------------------------------------------------------
            Buf_MSG2[0] = 0x03;
            Buf_MSG2[1] = 0xA2;
            Buf_MSG2[2] = 0x02;
            Buf_MSG2[3] = Convert.ToByte(Msg2_20, 16);
            BigToSmall(4, 4, Buf_MSG2, Convert.ToInt32(Msg2_1, 16));
            Buf_MSG2[8] = Convert.ToByte(Msg2_2, 16);
            Buf_MSG2[9] = Convert.ToByte(Msg2_3, 16);
            Buf_MSG2[10] = Convert.ToByte(Msg2_4, 16);
            Buf_MSG2[11] = Convert.ToByte(Msg2_5, 16);
            Buf_MSG2[12] = Convert.ToByte(Msg2_6, 16);
            Buf_MSG2[13] = Convert.ToByte(Msg2_7, 16);
            Buf_MSG2[14] = Convert.ToByte(Msg2_8, 16);
            Buf_MSG2[15] = Convert.ToByte(Msg2_9, 16);

						if (int.Parse(Msg2_10) > 255)
						{
							Buf_MSG2[16] = Convert.ToByte("255");
						}
						else
						{
							Buf_MSG2[16] = Convert.ToByte(Msg2_10);
						}

            Buf_MSG2[17] = Convert.ToByte(Msg2_11, 16);

            Buf_MSG2[18] = Convert.ToByte(Msg2_12, 16);
            Buf_MSG2[19] = Convert.ToByte(Msg2_13, 16);
            Buf_MSG2[20] = Convert.ToByte(Msg2_14, 16);
            Buf_MSG2[21] = Convert.ToByte(Msg2_15, 16);
            Buf_MSG2[22] = Convert.ToByte(Msg2_16, 16);
            Buf_MSG2[23] = Convert.ToByte(Msg2_17, 16);
            Buf_MSG2[24] = Convert.ToByte(Msg2_18, 16);
            Buf_MSG2[25] = Convert.ToByte(Msg2_19, 16);

						BigToSmall(26, 2, Buf_MSG2, Convert.ToInt32(Msg2_10));
            //-Buffer-Msg3--------------------------------------------------------
            Buf_MSG3[0] = 0x03;
            Buf_MSG3[1] = 0xA3;
            Buf_MSG3[2] = 0x03;
            Buf_MSG3[3] = Convert.ToByte(Msg3_20, 16);
            BigToSmall(4, 4, Buf_MSG3, Convert.ToInt32(Msg3_1, 16));
            Buf_MSG3[8] = Convert.ToByte(Msg3_2, 16);
            Buf_MSG3[9] = Convert.ToByte(Msg3_3, 16);
            Buf_MSG3[10] = Convert.ToByte(Msg3_4, 16);
            Buf_MSG3[11] = Convert.ToByte(Msg3_5, 16);
            Buf_MSG3[12] = Convert.ToByte(Msg3_6, 16);
            Buf_MSG3[13] = Convert.ToByte(Msg3_7, 16);
            Buf_MSG3[14] = Convert.ToByte(Msg3_8, 16);
            Buf_MSG3[15] = Convert.ToByte(Msg3_9, 16);

						if (int.Parse(Msg3_10) > 255)
						{
							Buf_MSG3[16] = Convert.ToByte("255");
						}
						else
						{
							Buf_MSG3[16] = Convert.ToByte(Msg3_10);
						}

            Buf_MSG3[17] = Convert.ToByte(Msg3_11, 16);

            Buf_MSG3[18] = Convert.ToByte(Msg3_12, 16);
            Buf_MSG3[19] = Convert.ToByte(Msg3_13, 16);
            Buf_MSG3[20] = Convert.ToByte(Msg3_14, 16);
            Buf_MSG3[21] = Convert.ToByte(Msg3_15, 16);
            Buf_MSG3[22] = Convert.ToByte(Msg3_16, 16);
            Buf_MSG3[23] = Convert.ToByte(Msg3_17, 16);
            Buf_MSG3[24] = Convert.ToByte(Msg3_18, 16);
            Buf_MSG3[25] = Convert.ToByte(Msg3_19, 16);

						BigToSmall(26, 2, Buf_MSG3, Convert.ToInt32(Msg3_10));
            //-Buffer-Msg4--------------------------------------------------------
            Buf_MSG4[0] = 0x03;
            Buf_MSG4[1] = 0xA4;
            Buf_MSG4[2] = 0x04;
            Buf_MSG4[3] = Convert.ToByte(Msg4_20, 16);
            BigToSmall(4, 4, Buf_MSG4, Convert.ToInt32(Msg4_1, 16));
            Buf_MSG4[8] = Convert.ToByte(Msg4_2, 16);
            Buf_MSG4[9] = Convert.ToByte(Msg4_3, 16);
            Buf_MSG4[10] = Convert.ToByte(Msg4_4, 16);
            Buf_MSG4[11] = Convert.ToByte(Msg4_5, 16);
            Buf_MSG4[12] = Convert.ToByte(Msg4_6, 16);
            Buf_MSG4[13] = Convert.ToByte(Msg4_7, 16);
            Buf_MSG4[14] = Convert.ToByte(Msg4_8, 16);
            Buf_MSG4[15] = Convert.ToByte(Msg4_9, 16);

						if (int.Parse(Msg4_10) > 255)
						{
							Buf_MSG4[16] = Convert.ToByte("255");
						}
						else
						{
							Buf_MSG4[16] = Convert.ToByte(Msg4_10);
						}

            Buf_MSG4[17] = Convert.ToByte(Msg4_11, 16);

            Buf_MSG4[18] = Convert.ToByte(Msg4_12, 16);
            Buf_MSG4[19] = Convert.ToByte(Msg4_13, 16);
            Buf_MSG4[20] = Convert.ToByte(Msg4_14, 16);
            Buf_MSG4[21] = Convert.ToByte(Msg4_15, 16);
            Buf_MSG4[22] = Convert.ToByte(Msg4_16, 16);
            Buf_MSG4[23] = Convert.ToByte(Msg4_17, 16);
            Buf_MSG4[24] = Convert.ToByte(Msg4_18, 16);
            Buf_MSG4[25] = Convert.ToByte(Msg4_19, 16);

						BigToSmall(26, 2, Buf_MSG4, Convert.ToInt32(Msg4_10));
            //-Buffer-Msg5--------------------------------------------------------
            Buf_MSG5[0] = 0x03;
            Buf_MSG5[1] = 0xA5;
            Buf_MSG5[2] = 0x05;
            Buf_MSG5[3] = Convert.ToByte(Msg5_20, 16);
            BigToSmall(4, 4, Buf_MSG5, Convert.ToInt32(Msg5_1, 16));
            Buf_MSG5[8] = Convert.ToByte(Msg5_2, 16);
            Buf_MSG5[9] = Convert.ToByte(Msg5_3, 16);
            Buf_MSG5[10] = Convert.ToByte(Msg5_4, 16);
            Buf_MSG5[11] = Convert.ToByte(Msg5_5, 16);
            Buf_MSG5[12] = Convert.ToByte(Msg5_6, 16);
            Buf_MSG5[13] = Convert.ToByte(Msg5_7, 16);
            Buf_MSG5[14] = Convert.ToByte(Msg5_8, 16);
            Buf_MSG5[15] = Convert.ToByte(Msg5_9, 16);

						if (int.Parse(Msg5_10) > 255)
						{
							Buf_MSG5[16] = Convert.ToByte("255");
						}
						else
						{
							Buf_MSG5[16] = Convert.ToByte(Msg5_10);
						}
            Buf_MSG5[17] = Convert.ToByte(Msg5_11, 16);

            Buf_MSG5[18] = Convert.ToByte(Msg5_12, 16);
            Buf_MSG5[19] = Convert.ToByte(Msg5_13, 16);
            Buf_MSG5[20] = Convert.ToByte(Msg5_14, 16);
            Buf_MSG5[21] = Convert.ToByte(Msg5_15, 16);
            Buf_MSG5[22] = Convert.ToByte(Msg5_16, 16);
            Buf_MSG5[23] = Convert.ToByte(Msg5_17, 16);
            Buf_MSG5[24] = Convert.ToByte(Msg5_18, 16);
            Buf_MSG5[25] = Convert.ToByte(Msg5_19, 16);

						BigToSmall(26, 2, Buf_MSG5, Convert.ToInt32(Msg5_10));
            //-Buffer-Msg6--------------------------------------------------------
            Buf_MSG6[0] = 0x03;
            Buf_MSG6[1] = 0xA6;
            Buf_MSG6[2] = 0x06;
            Buf_MSG6[3] = Convert.ToByte(Msg6_20, 16);
            BigToSmall(4, 4, Buf_MSG6, Convert.ToInt32(Msg6_1, 16));
            Buf_MSG6[8] = Convert.ToByte(Msg6_2, 16);
            Buf_MSG6[9] = Convert.ToByte(Msg6_3, 16);
            Buf_MSG6[10] = Convert.ToByte(Msg6_4, 16);
            Buf_MSG6[11] = Convert.ToByte(Msg6_5, 16);
            Buf_MSG6[12] = Convert.ToByte(Msg6_6, 16);
            Buf_MSG6[13] = Convert.ToByte(Msg6_7, 16);
            Buf_MSG6[14] = Convert.ToByte(Msg6_8, 16);
            Buf_MSG6[15] = Convert.ToByte(Msg6_9, 16);

						if (int.Parse(Msg6_10) > 255)
						{
							Buf_MSG6[16] = Convert.ToByte("255");
						}
						else
						{
							Buf_MSG6[16] = Convert.ToByte(Msg6_10);
						}
            Buf_MSG6[17] = Convert.ToByte(Msg6_11, 16);

            Buf_MSG6[18] = Convert.ToByte(Msg6_12, 16);
            Buf_MSG6[19] = Convert.ToByte(Msg6_13, 16);
            Buf_MSG6[20] = Convert.ToByte(Msg6_14, 16);
            Buf_MSG6[21] = Convert.ToByte(Msg6_15, 16);
            Buf_MSG6[22] = Convert.ToByte(Msg6_16, 16);
            Buf_MSG6[23] = Convert.ToByte(Msg6_17, 16);
            Buf_MSG6[24] = Convert.ToByte(Msg6_18, 16);
            Buf_MSG6[25] = Convert.ToByte(Msg6_19, 16);

						BigToSmall(26, 2, Buf_MSG6, Convert.ToInt32(Msg6_10));
            //-Buffer-Msg7--------------------------------------------------------
            Buf_MSG7[0] = 0x03;
            Buf_MSG7[1] = 0xA7;
            Buf_MSG7[2] = 0x07;
            Buf_MSG7[3] = Convert.ToByte(Msg7_20, 16);
            BigToSmall(4, 4, Buf_MSG7, Convert.ToInt32(Msg7_1, 16));
            Buf_MSG7[8] = Convert.ToByte(Msg7_2, 16);
            Buf_MSG7[9] = Convert.ToByte(Msg7_3, 16);
            Buf_MSG7[10] = Convert.ToByte(Msg7_4, 16);
            Buf_MSG7[11] = Convert.ToByte(Msg7_5, 16);
            Buf_MSG7[12] = Convert.ToByte(Msg7_6, 16);
            Buf_MSG7[13] = Convert.ToByte(Msg7_7, 16);
            Buf_MSG7[14] = Convert.ToByte(Msg7_8, 16);
            Buf_MSG7[15] = Convert.ToByte(Msg7_9, 16);

						if (int.Parse(Msg7_10) > 255)
						{
							Buf_MSG7[16] = Convert.ToByte("255");
						}
						else
						{
							Buf_MSG7[16] = Convert.ToByte(Msg7_10);
						}

            Buf_MSG7[17] = Convert.ToByte(Msg7_11, 16);

            Buf_MSG7[18] = Convert.ToByte(Msg7_12, 16);
            Buf_MSG7[19] = Convert.ToByte(Msg7_13, 16);
            Buf_MSG7[20] = Convert.ToByte(Msg7_14, 16);
            Buf_MSG7[21] = Convert.ToByte(Msg7_15, 16);
            Buf_MSG7[22] = Convert.ToByte(Msg7_16, 16);
            Buf_MSG7[23] = Convert.ToByte(Msg7_17, 16);
            Buf_MSG7[24] = Convert.ToByte(Msg7_18, 16);
            Buf_MSG7[25] = Convert.ToByte(Msg7_19, 16);

						BigToSmall(26, 2, Buf_MSG7, Convert.ToInt32(Msg7_10));
            //-Buffer-Msg8--------------------------------------------------------
            Buf_MSG8[0] = 0x03;
            Buf_MSG8[1] = 0xA8;
            Buf_MSG8[2] = 0x08;
            Buf_MSG8[3] = Convert.ToByte(Msg8_20, 16);
            BigToSmall(4, 4, Buf_MSG8, Convert.ToInt32(Msg8_1, 16));
            Buf_MSG8[8] = Convert.ToByte(Msg8_2, 16);
            Buf_MSG8[9] = Convert.ToByte(Msg8_3, 16);
            Buf_MSG8[10] = Convert.ToByte(Msg8_4, 16);
            Buf_MSG8[11] = Convert.ToByte(Msg8_5, 16);
            Buf_MSG8[12] = Convert.ToByte(Msg8_6, 16);
            Buf_MSG8[13] = Convert.ToByte(Msg8_7, 16);
            Buf_MSG8[14] = Convert.ToByte(Msg8_8, 16);
            Buf_MSG8[15] = Convert.ToByte(Msg8_9, 16);

						if (int.Parse(Msg8_10) > 255)
						{
							Buf_MSG8[16] = Convert.ToByte("255");
						}
						else
						{
							Buf_MSG8[16] = Convert.ToByte(Msg8_10);
						}
            Buf_MSG8[17] = Convert.ToByte(Msg8_11, 16);

            Buf_MSG8[18] = Convert.ToByte(Msg8_12, 16);
            Buf_MSG8[19] = Convert.ToByte(Msg8_13, 16);
            Buf_MSG8[20] = Convert.ToByte(Msg8_14, 16);
            Buf_MSG8[21] = Convert.ToByte(Msg8_15, 16);
            Buf_MSG8[22] = Convert.ToByte(Msg8_16, 16);
            Buf_MSG8[23] = Convert.ToByte(Msg8_17, 16);
            Buf_MSG8[24] = Convert.ToByte(Msg8_18, 16);
            Buf_MSG8[25] = Convert.ToByte(Msg8_19, 16);

						BigToSmall(26, 2, Buf_MSG8, Convert.ToInt32(Msg8_10));

            int i = 0;
            //-Selected Send Message-----------------------------------------------------------
            switch (Convert.ToInt16(comboBox1.SelectedItem))
            {
                case 1:
                    progressBar1.Maximum = Convert.ToInt16(comboBox1.SelectedItem);
                    progressBar1.Value = i;
                    v_usb.HID_SetFeature(Handless, BufferSystem, BufferSystem.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG1, Buf_MSG1.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    MessageBox.Show("Successfully Load", "", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
                    break;
                case 2:
                    progressBar1.Maximum = Convert.ToInt16(comboBox1.SelectedItem);
                    progressBar1.Value = i;
                    v_usb.HID_SetFeature(Handless, BufferSystem, BufferSystem.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG1, Buf_MSG1.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG2, Buf_MSG2.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    MessageBox.Show("Successfully Load", "", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
                    break;
                case 3:
                    progressBar1.Maximum = Convert.ToInt16(comboBox1.SelectedItem);
                    progressBar1.Value = i;
                    v_usb.HID_SetFeature(Handless, BufferSystem, BufferSystem.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG1, Buf_MSG1.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG2, Buf_MSG2.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG3, Buf_MSG3.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    MessageBox.Show("Successfully Load", "", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
                    break;
                case 4:
                    progressBar1.Maximum = Convert.ToInt16(comboBox1.SelectedItem);
                    progressBar1.Value = i;
                    v_usb.HID_SetFeature(Handless, BufferSystem, BufferSystem.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG1, Buf_MSG1.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG2, Buf_MSG2.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG3, Buf_MSG3.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG4, Buf_MSG4.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    MessageBox.Show("Successfully Load", "", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
                    break;
                case 5:
                    progressBar1.Maximum = Convert.ToInt16(comboBox1.SelectedItem);
                    progressBar1.Value = i;
                    v_usb.HID_SetFeature(Handless, BufferSystem, BufferSystem.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG1, Buf_MSG1.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG2, Buf_MSG2.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG3, Buf_MSG3.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG4, Buf_MSG4.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG5, Buf_MSG5.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    MessageBox.Show("Successfully Load", "", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
                    break;
                case 6:
                    progressBar1.Maximum = Convert.ToInt16(comboBox1.SelectedItem);
                    progressBar1.Value = i;
                    v_usb.HID_SetFeature(Handless, BufferSystem, BufferSystem.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG1, Buf_MSG1.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG2, Buf_MSG2.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG3, Buf_MSG3.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG4, Buf_MSG4.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG5, Buf_MSG5.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG6, Buf_MSG6.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    MessageBox.Show("Successfully Load", "", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
                    break;
                case 7:
                    progressBar1.Maximum = Convert.ToInt16(comboBox1.SelectedItem);
                    progressBar1.Value = i;
                    v_usb.HID_SetFeature(Handless, BufferSystem, BufferSystem.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG1, Buf_MSG1.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG2, Buf_MSG2.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG3, Buf_MSG3.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG4, Buf_MSG4.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG5, Buf_MSG5.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG6, Buf_MSG6.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG7, Buf_MSG7.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    MessageBox.Show("Successfully Load", "", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
                    break;
                case 8:
                    progressBar1.Maximum = Convert.ToInt16(comboBox1.SelectedItem);
                    progressBar1.Value = i;
                    v_usb.HID_SetFeature(Handless, BufferSystem, BufferSystem.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG1, Buf_MSG1.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG2, Buf_MSG2.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG3, Buf_MSG3.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG4, Buf_MSG4.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG5, Buf_MSG5.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG6, Buf_MSG6.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG7, Buf_MSG7.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    v_usb.HID_SetFeature(Handless, Buf_MSG8, Buf_MSG8.Length); // Отправка данных методом Set_Future
                    progressBar1.Value = i++;
                    Thread.Sleep(100);
                    MessageBox.Show("Successfully Load", "", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
                    break;


            }

            checkBox4.Checked = false;
            // v_usb.HID_SetFeature(Handless, Buffer1, Buffer1.Length); // Отправка данных методом Set_Future
            checkBox2.Checked = true;
        }

        private void button14_Click(object sender, EventArgs e)
        {
            Form10 f = new Form10();
            f.Owner = this;
            f.ShowDialog();
        }

        private void button15_Click(object sender, EventArgs e)
        {
            Buf_Erase[0] = 0x01;
            Buf_Erase[1] = 0x01;
            Buf_Erase[2] = 0x06;
            Buf_Erase[3] = 0x01;
            Buf_Erase[4] = 0x00;
            Buf_Erase[5] = 0x01;
            Buf_Erase[6] = 0x02;
            Buf_Erase[7] = 0x03;
            Buf_Erase[8] = 0x04;
            Buf_Erase[9] = 0x05;
            Buf_Erase[10] = 0x55;
            
            progressBar1.Maximum = 1;
            progressBar1.Value = 0;
            
            v_usb.HID_SetFeature(Handless,Buf_Erase, 12); // Отправка данных методом Set_Future
           
        }

        private void BigToSmall(int StartPosition, int QTY, byte[] MassData, Int32 Big) // Conver Bit (long) to Byte (0xFF)
        {
            int i = 0;
            for (i = 0; i < QTY; i++)
            {
                MassData[StartPosition + i] = (byte)((Big & (0x000000FF << 8 * i)) >> 8 * i);
            }

        }

        /*******************************************************************************
        * Function Name : SmallToBig.
        * Description   : .
        * Input         : None.
        * Output        : None.
        * Return value  : The state value.
         * 
        *******************************************************************************/
        private UInt32 smallToBig(int StartPosition, int QTY, byte[] MassData)
        {
            int i = 0;
            UInt32 Big = 0x00;
            for (i = 0; i < QTY; i++)
            {
                Big = (UInt32)(Big | ((MassData[StartPosition + i]) << 8 * i));
            }
            return Big;
        }

        private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar <= 47 || e.KeyChar >= 58) && e.KeyChar != 8)
                e.Handled = true;
        }

        private void comboBox3_SelectedIndexChanged(object sender, EventArgs e)
        {
            label13.Text = Convert.ToString(comboBox3.SelectedIndex);
        }

        private void checkBox5_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox5.Checked == true) 
            {
                this.Width = 737;
            }
            else
                this.Width = 275;
        }

        private void button16_Click(object sender, EventArgs e)
        {
            maskedTextBox1.Text = DateTime.Now.ToShortDateString();
        }

        /*
        * Шифровка - дешифровка текстовых данных
        */
        public string XorCrypt(string text, int key)
        {
            string newText = "";
            for (int i = 0; i < text.Length; i++)
            {
                int charValue = Convert.ToInt32(text[i]);       // Преобразовываем в сиволы ASCII
                charValue ^= key;                               // XOR'им
                newText += char.ConvertFromUtf32(charValue);    // Преобразовываем обратно в string
            }
            return newText;
        }
        
        private void button17_Click(object sender, EventArgs e)
        {
            label15.Text = "= " + Convert.ToString(3600 / (Convert.ToInt32((textBox7.Text))))+" km/h";
        }

        private void textBox7_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar <= 47 || e.KeyChar >= 58) && e.KeyChar != 8)
                e.Handled = true;
        }

				private void pictureBox1_Click(object sender, EventArgs e)
				{
					Process.Start("http://simplecan.16mb.com");
				}

				private void button18_Click(object sender, EventArgs e)
				{
					if (windowsState == 0)
					{
						this.Height = 482;
						windowsState = 1;
						groupBox2.Visible = true;
					}
					else
					{
						groupBox2.Visible = false;
						this.Height = 419;
						windowsState = 0;
					}
				}


    }
}
