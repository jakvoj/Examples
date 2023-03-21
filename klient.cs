using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using MySql.Data.MySqlClient;
namespace klient
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        MySql.Data.MySqlClient.MySqlConnection conn;
        MySqlDataReader nacteni = null;
        private void prihlaseni()
        {
            try
            {
                string myConnectionString = "server=" + textBox3.Text + "; uid=" + textBox2.Text + "; pwd=" + textBox1.Text + "; database=" + "slovnik" + ";";
                conn = new MySql.Data.MySqlClient.MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();
                conn.Close();
                panel1.Visible = false;
                panel2.Visible = true;

            }
            catch
            {
                MessageBox.Show("Přihlášení selhalo, zkuste to znovu");
            }
           
        }
        private void cteni()
        {
            try
            {
                conn.Open();
                MySqlCommand cmd = new MySqlCommand(@"select slova.slovo_id, slova.cesky, slova.anglicky, slova.poznamka from slova", conn);
                nacteni = cmd.ExecuteReader();
                textBox4.Text = "id: česky:   anglicky:   poznámka: " + Environment.NewLine;
                while (nacteni.Read() == true)
                {
                    textBox4.Text += nacteni["slovo_id"].ToString() + "   " + nacteni["cesky"].ToString() + "   " + nacteni["anglicky"].ToString() + "   " + nacteni["poznamka"].ToString() + Environment.NewLine;

                }
                conn.Close();
            }
            catch
            {
                MessageBox.Show("Došlo k chybě komunikace s databází");
                conn.Close();
            }
        }
        private void vyhledavani()
        {
            conn.Open();
            MySqlCommand cmd = new MySqlCommand(@"select slova.slovo_id, slova.cesky, slova.anglicky, slova.poznamka from slova where slova.cesky = '" + textBox5.Text + "' or slova.anglicky = '" + textBox6.Text + "'; ", conn);
            nacteni = cmd.ExecuteReader();
            textBox4.Text = "id: česky:   anglicky:   poznámka: " + Environment.NewLine;
            if (textBox7.Text != "")
            {
                textBox7.BackColor = System.Drawing.Color.Red;
                label7.Visible = true;
                timer1.Enabled = true;
            }
            while (nacteni.Read() == true)
            {
                textBox4.Text += nacteni["slovo_id"].ToString() + "   " + nacteni["cesky"].ToString() + "   " + nacteni["anglicky"].ToString() + "   " + nacteni["poznamka"].ToString() + Environment.NewLine;

            }
            conn.Close();
            textBox5.Text = null;
            textBox6.Text = null;
            textBox7.Text = null;
        }
        private void mazani()
        {
            conn.Open();
            MySqlCommand cmd = new MySqlCommand(@"delete from slova where slova.slovo_id = " + textBox8.Text, conn);
            nacteni = cmd.ExecuteReader();
            conn.Close();
        }
        private void zaznamenani()
        {
            conn.Open();
            MySqlCommand cmd = new MySqlCommand(@"insert into slova(cesky, anglicky, poznamka) values ('" + textBox5.Text + "', '" + textBox6.Text + "', '" + textBox7.Text + "'); ", conn);
            nacteni = cmd.ExecuteReader();
            conn.Close();
        }
        private void aktualizace()
        {
            if(textBox5.Text != "")
            {
            conn.Open();
            MySqlCommand cmd = new MySqlCommand(@"update slova set cesky = '" + textBox5.Text + "' where slovo_id = " + textBox8.Text, conn);
            nacteni = cmd.ExecuteReader();
             
            }
            if(textBox6.Text != "")
            {
            MySqlCommand cmd1 = new MySqlCommand(@"update slova set anglicky = '" + textBox6.Text + "' where slovo_id = " + textBox8.Text, conn);
            nacteni = cmd1.ExecuteReader();
            }
            if (textBox7.Text != "")
            {
                MySqlCommand cmd2 = new MySqlCommand(@"update slova set poznamka = '" + textBox7.Text + "' where slovo_id = " + textBox8.Text, conn);
                nacteni = cmd2.ExecuteReader();
            }
        }
        private void button1_Click(object sender, EventArgs e)
        {
            this.prihlaseni();
            textBox4.Visible = true;
            this.cteni();
        }
        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            textBox1.PasswordChar = '*';
        }

        private void button5_Click(object sender, EventArgs e)
        {
            this.vyhledavani();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            textBox7.BackColor = System.Drawing.Color.White;
            label7.Visible = false;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            this.mazani();
            this.cteni();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.zaznamenani();
            this.cteni();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            this.aktualizace();
            this.cteni();
        }
    }
}
