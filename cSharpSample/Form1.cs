using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace cSharpSample {
   public partial class Form1:Form {
      public Form1() {
      InitializeComponent();
      }

      private void button1_Click(object sender,EventArgs e) {

          DialogResult rc = openFileDialog1.ShowDialog();

          if ( DialogResult.OK == rc )
            axPDFiumControl1.Document = openFileDialog1.FileName;
      }
   }
}
