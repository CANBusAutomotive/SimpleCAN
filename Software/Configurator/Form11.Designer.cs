namespace USB_termo_2
{
    partial class Form11
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
					this.label1 = new System.Windows.Forms.Label();
					this.label2 = new System.Windows.Forms.Label();
					this.label3 = new System.Windows.Forms.Label();
					this.label4 = new System.Windows.Forms.Label();
					this.label5 = new System.Windows.Forms.Label();
					this.label6 = new System.Windows.Forms.Label();
					this.textBox1 = new System.Windows.Forms.TextBox();
					this.SuspendLayout();
					// 
					// label1
					// 
					this.label1.AutoSize = true;
					this.label1.Font = new System.Drawing.Font("Consolas", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
					this.label1.ForeColor = System.Drawing.Color.Blue;
					this.label1.Location = new System.Drawing.Point(125, 13);
					this.label1.Name = "label1";
					this.label1.Size = new System.Drawing.Size(20, 22);
					this.label1.TabIndex = 0;
					this.label1.Text = "0";
					// 
					// label2
					// 
					this.label2.AutoSize = true;
					this.label2.Font = new System.Drawing.Font("Consolas", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
					this.label2.ForeColor = System.Drawing.Color.Blue;
					this.label2.Location = new System.Drawing.Point(126, 40);
					this.label2.Name = "label2";
					this.label2.Size = new System.Drawing.Size(20, 22);
					this.label2.TabIndex = 1;
					this.label2.Text = "0";
					// 
					// label3
					// 
					this.label3.AutoSize = true;
					this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
					this.label3.Location = new System.Drawing.Point(101, 40);
					this.label3.Name = "label3";
					this.label3.Size = new System.Drawing.Size(19, 20);
					this.label3.TabIndex = 2;
					this.label3.Text = "--";
					// 
					// label4
					// 
					this.label4.AutoSize = true;
					this.label4.Font = new System.Drawing.Font("Consolas", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
					this.label4.Location = new System.Drawing.Point(13, 40);
					this.label4.Name = "label4";
					this.label4.Size = new System.Drawing.Size(50, 22);
					this.label4.TabIndex = 3;
					this.label4.Text = "Date";
					// 
					// label5
					// 
					this.label5.AutoSize = true;
					this.label5.Font = new System.Drawing.Font("Consolas", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
					this.label5.Location = new System.Drawing.Point(12, 9);
					this.label5.Name = "label5";
					this.label5.Size = new System.Drawing.Size(80, 22);
					this.label5.TabIndex = 4;
					this.label5.Text = "Mileage";
					// 
					// label6
					// 
					this.label6.AutoSize = true;
					this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
					this.label6.Location = new System.Drawing.Point(100, 13);
					this.label6.Name = "label6";
					this.label6.Size = new System.Drawing.Size(19, 20);
					this.label6.TabIndex = 5;
					this.label6.Text = "--";
					// 
					// textBox1
					// 
					this.textBox1.BackColor = System.Drawing.Color.Cyan;
					this.textBox1.BorderStyle = System.Windows.Forms.BorderStyle.None;
					this.textBox1.Dock = System.Windows.Forms.DockStyle.Bottom;
					this.textBox1.Enabled = false;
					this.textBox1.Location = new System.Drawing.Point(0, 92);
					this.textBox1.Name = "textBox1";
					this.textBox1.Size = new System.Drawing.Size(238, 13);
					this.textBox1.TabIndex = 6;
					this.textBox1.Text = "v 3.1.0";
					this.textBox1.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
					// 
					// Form11
					// 
					this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
					this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
					this.ClientSize = new System.Drawing.Size(238, 105);
					this.Controls.Add(this.textBox1);
					this.Controls.Add(this.label6);
					this.Controls.Add(this.label5);
					this.Controls.Add(this.label4);
					this.Controls.Add(this.label3);
					this.Controls.Add(this.label2);
					this.Controls.Add(this.label1);
					this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
					this.Name = "Form11";
					this.ShowIcon = false;
					this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
					this.Text = "Device Data";
					this.Load += new System.EventHandler(this.Form11_Load);
					this.ResumeLayout(false);
					this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        public System.Windows.Forms.Label label1;
        public System.Windows.Forms.Label label2;
				private System.Windows.Forms.TextBox textBox1;

    }
}