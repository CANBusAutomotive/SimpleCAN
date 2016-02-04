using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace USB_termo_2
{
    public partial class Form10 : Form
    {
        public Form10()
        {
            InitializeComponent();
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            comboBox2.Items.Clear();
            switch (comboBox1.Text)
            {
                case "Audi":
                    object[] items1 = { "A4", "A6", "A8", "Q7", "Allroad" };
                    comboBox2.Items.AddRange(items1);
                    break;
                case "BMW":
                    object[] items2 = { "3-E90", "3-E91", "5-E60", "5-E61", "5-F10", "7-E65", "7-E66", "7-E67", "7-F01", "X5-E70", "X5-E71", };
                    comboBox2.Items.AddRange(items2);
                    break;
                case "Citroen":
                    object[] items3 = { "Boxer", "C4", "C5", "Berlingo", "Jumper", "Jumpy", "Nemo" };
                    comboBox2.Items.AddRange(items3);
                    break;
                case "Chrysler":
                    object[] items4 = { "C300" };
                    comboBox2.Items.AddRange(items4);
                    break;
                case "Chevrolet":
                    object[] items5 = { "Captiva", "Cruze", "Epica", "Aveo" };
                    comboBox2.Items.AddRange(items5);
                    break;
                case "Ford":
										object[] items6 = { "C-MAx", "Focus", "Fiesta", "Fusion", "Galaxy", "Kuga", "Mondeo", "S-Max", "Scorpi", "Transit", "Tourneo" };
                    comboBox2.Items.AddRange(items6);
                    break;
                case "Hyundai":
                    object[] items7 = { "Genesis", "SantaFe", "Sonata", "Tucson" };
                    comboBox2.Items.AddRange(items7);
                    break;
                case "KIA":
                    object[] items8 = { "Cerato", "Sorento", "Sportage" };
                    comboBox2.Items.AddRange(items8);
                    break;
                case "LandRover":
                    object[] items9 = { "Discovery3" };
                    comboBox2.Items.AddRange(items9);
                    break;
                case "Lexus":
                    object[] items10 = { "LS460", "LX570", "RX350", "GX460" };
                    comboBox2.Items.AddRange(items10);
                    break;
                case "Mazda":
                    object[] items11 = { "2", "3", "6", "CX-7" };
                    comboBox2.Items.AddRange(items11);
                    break;
                case "Mitsubishi":
                    object[] items12 = { "Outlander-XL", "Lancer-X" };
                    comboBox2.Items.AddRange(items12);
                    break;
                case "Mercedes":
                    object[] items13 = { "164", "203", "204", "211", "220", "221", "251", "Vito", "Viano", "Sprinter", "ML", "GL", "G550" };
                    comboBox2.Items.AddRange(items13);
                    break;
                case "Nissan":
                    object[] items14 = { "Pathfinder", "X-Trail", "Primera", "Teana", "Murano", "Qashqai", "Patrol", "Navara" };
                    comboBox2.Items.AddRange(items14);
                    break;
                case "Opel":
                    object[] items15 = { "Astra-J", "Astra-H", "Antara", "Insgnia", "Vectra-C", "Zafira-B", "Combo" };
                    comboBox2.Items.AddRange(items15);
                    break;
                case "Peugeot":
                    object[] items16 = { "301","308", "407","408", "Boxer", "Partner", "Expert" };
                    comboBox2.Items.AddRange(items16);
                    break;
                case "Renault":
                    object[] items17 = { "Scenic-2", "Megan-2", "Megan-3", "Kangoo-2", "Lodgy", "Fluence", "Traffic" };
                    comboBox2.Items.AddRange(items17);
                    break;
                case "Skoda":
                    object[] items18 = { "Octavia-3","Roomster", "Superb", "Yeti" };
                    comboBox2.Items.AddRange(items18);
                    break;
                case "Toyota":
                    object[] items19 = { "Avensis", "Auris", "Camry", "Corolla", "HighLander", "LandCruiser-200", "LandCruiser-Prado", "Tundra", "Prado","Prius", "RAV-4", "Verso" };
                    comboBox2.Items.AddRange(items19);
                    break;
                case "Volvo":
                    object[] items20 = { "S80", "S90", "S60", "S70", "XC70", "XC90" };
                    comboBox2.Items.AddRange(items20);
                    break;
                case "VW":
                    object[] items21 = { "Passat-B6", "Passat-B7", "Golf-5", "Golf-7", "Jetta", "Caddy", "Polo", "T5", "Touareg", "Tiguan", "Touran", "Caravelle", "Crafter", "Multivan", };
                    comboBox2.Items.AddRange(items21);
                    break;
                case "Suzuki":
                    object[] items22 = { "GrandVitara", "Swift", "SX4" };
                    comboBox2.Items.AddRange(items22);
                    break;
                case "Gazel":
                    object[] items23 = { "New", "Next", "Buisnes"};
                    comboBox2.Items.AddRange(items23);
                    break;
                case "SsangYong":
                    object[] items24 = { "Action", "Rexton"};
                    comboBox2.Items.AddRange(items24);
                    break;
                case "Cadillac":
                    object[] items25 = { "Escalade" };
                    comboBox2.Items.AddRange(items25);
                    break;
                case "Chery":
                    object[] items26 = { "Tiggo" };
                    comboBox2.Items.AddRange(items26);
                    break;
                
            }
        }// Марки и модели в ComboBOX

        private void button1_Click(object sender, EventArgs e)
        {
            Close();
        }//Кнопка отмена

        private void button2_Click(object sender, EventArgs e)
        {
            Form1 main = this.Owner as Form1; // применяем новые значения для первой формы (Form1) из полей
            if (main != null)
            {
                SaveFileDialog saveFileDialog = new SaveFileDialog();
                if (checkBox1.Checked == false) // проверяем состояние чекбокса
                {
                    saveFileDialog.FileName = comboBox1.Text + "-" + comboBox2.Text + "-" + numericUpDown1.Value + "г" + "-" + comboBox3.Text + "-" + textBox2.Text + "km_h" + "-[3_1_1]";
                    saveFileDialog.Filter = "Configuration file (*.can)|*.can|Все файлы (*.*)|*.*";

                }
                else
                {
                    saveFileDialog.FileName = textBox3.Text;
                    saveFileDialog.Filter = "Configuration file (*.can)|*.can|Все файлы (*.*)|*.*";

                }

                if (saveFileDialog.ShowDialog() == DialogResult.OK)
                {
                    StreamWriter streamWriter = new StreamWriter(saveFileDialog.FileName);

                   // streamWriter.WriteLine((string)(main.comboBox1.SelectedItem), "\r\n");
                    streamWriter.WriteLine((string)(main.XorCrypt((string)main.comboBox1.SelectedItem, main.KEY)), "\r\n");
                    streamWriter.WriteLine((string)(main.XorCrypt((string)main.comboBox2.SelectedItem, main.KEY)), "\r\n");
                    streamWriter.WriteLine((string)(main.XorCrypt((string)main.comboBox3.SelectedItem, main.KEY)), "\r\n");
                    streamWriter.WriteLine((string)(main.XorCrypt((string)main.comboBox4.SelectedItem, main.KEY)), "\r\n");
                    streamWriter.WriteLine((string)(main.XorCrypt((string)main.comboBox5.SelectedItem, main.KEY)), "\r\n");
                    streamWriter.WriteLine((string)(main.XorCrypt((string)main.comboBox6.SelectedItem, main.KEY)), "\r\n");
                    streamWriter.WriteLine((string)(main.XorCrypt((string)main.comboBox7.SelectedItem, main.KEY)), "\r\n");
                    streamWriter.WriteLine((string)(main.XorCrypt((string)main.comboBox8.SelectedItem, main.KEY)), "\r\n");
                    streamWriter.WriteLine((string)(main.XorCrypt((string)main.comboBox9.SelectedItem, main.KEY)), "\r\n");
                    streamWriter.WriteLine((string)(main.XorCrypt((string)main.comboBox10.SelectedItem, main.KEY)), "\r\n");
                    streamWriter.WriteLine((string)(main.XorCrypt((string)main.comboBox11.SelectedItem, main.KEY)), "\r\n");

                    streamWriter.WriteLine(main.textBox1.Text, "\r\n");
                    streamWriter.WriteLine(main.maskedTextBox1.Text, "\r\n");
                    // Записываем 1-ое сообщение
                    streamWriter.WriteLine(main.XorCrypt(main.Msg1_1,main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg1_2, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg1_3, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg1_4, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg1_5, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg1_6, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg1_7, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg1_8, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg1_9, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg1_10, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg1_11, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg1_12, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg1_13, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg1_14, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg1_15, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg1_16, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg1_17, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg1_18, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg1_19, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg1_20, main.KEY), "\r\n");
                    // Записываем 2-ое сообщение
                    streamWriter.WriteLine(main.XorCrypt(main.Msg2_1, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg2_2, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg2_3, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg2_4, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg2_5, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg2_6, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg2_7, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg2_8, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg2_9, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg2_10, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg2_11, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg2_12, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg2_13, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg2_14, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg2_15, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg2_16, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg2_17, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg2_18, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg2_19, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg2_20, main.KEY), "\r\n");
                    // Записываем 3 сообщение
                    streamWriter.WriteLine(main.XorCrypt(main.Msg3_1, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg3_2, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg3_3, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg3_4, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg3_5, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg3_6, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg3_7, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg3_8, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg3_9, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg3_10, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg3_11, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg3_12, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg3_13, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg3_14, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg3_15, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg3_16, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg3_17, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg3_18, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg3_19, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg3_20, main.KEY), "\r\n");
                    // Записываем 4 сообщение
                    streamWriter.WriteLine(main.XorCrypt(main.Msg4_1, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg4_2, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg4_3, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg4_4, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg4_5, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg4_6, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg4_7, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg4_8, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg4_9, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg4_10, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg4_11, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg4_12, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg4_13, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg4_14, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg4_15, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg4_16, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg4_17, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg4_18, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg4_19, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg4_20, main.KEY), "\r\n");
                    // Записываем 5 сообщение
                    streamWriter.WriteLine(main.XorCrypt(main.Msg5_1, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg5_2, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg5_3, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg5_4, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg5_5, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg5_6, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg5_7, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg5_8, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg5_9, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg5_10, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg5_11, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg5_12, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg5_13, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg5_14, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg5_15, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg5_16, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg5_17, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg5_18, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg5_19, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg5_20, main.KEY), "\r\n");
                    // Записываем 6 сообщение
                    streamWriter.WriteLine(main.XorCrypt(main.Msg6_1, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg6_2, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg6_3, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg6_4, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg6_5, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg6_6, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg6_7, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg6_8, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg6_9, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg6_10, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg6_11, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg6_12, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg6_13, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg6_14, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg6_15, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg6_16, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg6_17, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg6_18, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg6_19, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg6_20, main.KEY), "\r\n");
                    // Записываем 7 сообщение
                    streamWriter.WriteLine(main.XorCrypt(main.Msg7_1, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg7_2, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg7_3, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg7_4, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg7_5, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg7_6, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg7_7, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg7_8, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg7_9, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg7_10, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg7_11, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg7_12, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg7_13, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg7_14, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg7_15, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg7_16, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg7_17, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg7_18, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg7_19, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg7_20, main.KEY), "\r\n");
                    // Записываем 8 сообщение
                    streamWriter.WriteLine(main.XorCrypt(main.Msg8_1, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg8_2, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg8_3, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg8_4, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg8_5, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg8_6, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg8_7, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg8_8, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg8_9, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg8_10, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg8_11, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg8_12, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg8_13, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg8_14, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg8_15, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg8_16, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg8_17, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg8_18, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg8_19, main.KEY), "\r\n");
                    streamWriter.WriteLine(main.XorCrypt(main.Msg8_20, main.KEY), "\r\n");

										streamWriter.WriteLine(main.XorCrypt(main.OneThreadcheckBox.Checked.ToString(), main.KEY), "\r\n");


                    streamWriter.Close();
                    Close();
                }
            }
        }//Кнопка сохранения

        private void Form10_Load(object sender, EventArgs e)
        {
            if (checkBox1.Checked == false)  // проверяем состояние чекбокса
            {
                comboBox1.Enabled = true;
                comboBox2.Enabled = true;
                comboBox3.Enabled = true;
                numericUpDown1.Enabled = true;
                textBox2.Enabled = true;
                textBox3.Enabled = false;
            }
            else if (checkBox1.Checked == true)
            {
                comboBox1.Enabled = false;
                comboBox2.Enabled = false;
                comboBox3.Enabled = false;
                numericUpDown1.Enabled = false;
                textBox2.Enabled = false;
                textBox3.Enabled = true;
            }
        }//загрузка формы

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox1.Checked == false) // проверяем состояние чекбокса
            {
                comboBox1.Enabled = true;
                comboBox2.Enabled = true;
                comboBox3.Enabled = true;
                numericUpDown1.Enabled = true;
                textBox2.Enabled = true;
                textBox3.Enabled = false;
            }
            else if (checkBox1.Checked == true)
            {
                comboBox1.Enabled = false;
                comboBox2.Enabled = false;
                comboBox3.Enabled = false;
                numericUpDown1.Enabled = false;
                textBox2.Enabled = false;
                textBox3.Enabled = true;
            }
        }

        private void textBox2_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar <= 47 || e.KeyChar >= 58) && e.KeyChar != 8)
                e.Handled = true;
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }//состояние чекбокса
    }
}
