using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace USB_termo_2
{
    public partial class Form11 : Form
    {
        public Form11()
        {
            InitializeComponent();
        }

        private void Form11_Load(object sender, EventArgs e)
        {

            Form1 main = this.Owner as Form1; // применяем стандартные значения из первой формы (Form1) для полей
            if (main != null)
            {
                label1.Text = main.label11.Text + " km";
                // label2.Text = main.label12.Text;
                char[] date = main.label12.Text.ToCharArray();
                /*
                 * Проверяем сколько элементов в массиве на тот случай если дат на чинается на "0" прим.: 01-02-2015
                */
								if (date.Length <= 7)
								{
									label2.Text = "0" + date[0].ToString() + "-" + date[1].ToString() + date[2].ToString() + "-" + date[3].ToString() + date[4].ToString() + date[5].ToString() + date[6].ToString();
								}
								else
								{
									label2.Text = date[0].ToString() + date[1].ToString() + "-" + date[2].ToString() + date[3].ToString() + "-" + date[4].ToString() + date[5].ToString() + date[6].ToString() + date[7].ToString();
								}
								
            }
        }
    }
}
