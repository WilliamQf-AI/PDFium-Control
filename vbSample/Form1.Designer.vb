<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
   Inherits System.Windows.Forms.Form

   'Form overrides dispose to clean up the component list.
   <System.Diagnostics.DebuggerNonUserCode()> _
   Protected Overrides Sub Dispose(ByVal disposing As Boolean)
      Try
         If disposing AndAlso components IsNot Nothing Then
            components.Dispose()
         End If
      Finally
         MyBase.Dispose(disposing)
      End Try
   End Sub

   'Required by the Windows Form Designer
   Private components As System.ComponentModel.IContainer

   'NOTE: The following procedure is required by the Windows Form Designer
   'It can be modified using the Windows Form Designer.  
   'Do not modify it using the code editor.
   <System.Diagnostics.DebuggerStepThrough()> _
   Private Sub InitializeComponent()
      Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Form1))
      Me.textBox1 = New System.Windows.Forms.TextBox()
      Me.AxPDFiumControl1 = New AxPDFiumControl.AxPDFiumControl()
      Me.label1 = New System.Windows.Forms.Label()
      Me.button1 = New System.Windows.Forms.Button()
      Me.openFileDialog1 = New System.Windows.Forms.OpenFileDialog()
      CType(Me.AxPDFiumControl1, System.ComponentModel.ISupportInitialize).BeginInit()
      Me.SuspendLayout()
      '
      'textBox1
      '
      Me.textBox1.Enabled = False
      Me.textBox1.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
      Me.textBox1.Location = New System.Drawing.Point(12, 12)
      Me.textBox1.Multiline = True
      Me.textBox1.Name = "textBox1"
      Me.textBox1.ReadOnly = True
      Me.textBox1.Size = New System.Drawing.Size(892, 146)
      Me.textBox1.TabIndex = 101
      Me.textBox1.Text = resources.GetString("textBox1.Text")
      '
      'AxPDFiumControl1
      '
      Me.AxPDFiumControl1.Enabled = True
      Me.AxPDFiumControl1.Location = New System.Drawing.Point(13, 221)
      Me.AxPDFiumControl1.Name = "AxPDFiumControl1"
      Me.AxPDFiumControl1.OcxState = CType(resources.GetObject("AxPDFiumControl1.OcxState"), System.Windows.Forms.AxHost.State)
      Me.AxPDFiumControl1.Size = New System.Drawing.Size(891, 824)
      Me.AxPDFiumControl1.TabIndex = 102
      '
      'label1
      '
      Me.label1.AutoSize = True
      Me.label1.Location = New System.Drawing.Point(13, 181)
      Me.label1.Name = "label1"
      Me.label1.Size = New System.Drawing.Size(165, 13)
      Me.label1.TabIndex = 104
      Me.label1.Text = "Select a PDF or HTML document"
      '
      'button1
      '
      Me.button1.Location = New System.Drawing.Point(184, 176)
      Me.button1.Name = "button1"
      Me.button1.Size = New System.Drawing.Size(46, 23)
      Me.button1.TabIndex = 103
      Me.button1.Text = "..."
      Me.button1.UseVisualStyleBackColor = True
      '
      'openFileDialog1
      '
      Me.openFileDialog1.FileName = "openFileDialog1"
      '
      'Form1
      '
      Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
      Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
      Me.ClientSize = New System.Drawing.Size(944, 1070)
      Me.Controls.Add(Me.AxPDFiumControl1)
      Me.Controls.Add(Me.label1)
      Me.Controls.Add(Me.button1)
      Me.Controls.Add(Me.textBox1)
      Me.Name = "Form1"
      Me.Text = "Form1"
      CType(Me.AxPDFiumControl1, System.ComponentModel.ISupportInitialize).EndInit()
      Me.ResumeLayout(False)
      Me.PerformLayout()

   End Sub

   Private WithEvents textBox1 As TextBox
   Friend WithEvents AxPDFiumControl1 As AxPDFiumControl.AxPDFiumControl
   Private WithEvents label1 As Label
   Private WithEvents button1 As Button
   Private WithEvents openFileDialog1 As OpenFileDialog
End Class
