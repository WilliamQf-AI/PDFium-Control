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
      Me.AxPDFiumControl2 = New AxPDFiumControl.AxPDFiumControl()
      CType(Me.AxPDFiumControl2, System.ComponentModel.ISupportInitialize).BeginInit()
      Me.SuspendLayout()
      '
      'AxPDFiumControl2
      '
      Me.AxPDFiumControl2.Enabled = True
      Me.AxPDFiumControl2.Location = New System.Drawing.Point(51, 40)
      Me.AxPDFiumControl2.Name = "AxPDFiumControl2"
      Me.AxPDFiumControl2.OcxState = CType(resources.GetObject("AxPDFiumControl2.OcxState"), System.Windows.Forms.AxHost.State)
      Me.AxPDFiumControl2.Size = New System.Drawing.Size(1184, 858)
      Me.AxPDFiumControl2.TabIndex = 0
      '
      'Form1
      '
      Me.ClientSize = New System.Drawing.Size(1268, 944)
      Me.Controls.Add(Me.AxPDFiumControl2)
      Me.Name = "Form1"
      CType(Me.AxPDFiumControl2, System.ComponentModel.ISupportInitialize).EndInit()
      Me.ResumeLayout(False)

   End Sub

   Private WithEvents textBox1 As TextBox
   Private WithEvents label1 As Label
   Private WithEvents button1 As Button
   Private WithEvents openFileDialog1 As OpenFileDialog
   Friend WithEvents AxPDFiumControl2 As AxPDFiumControl.AxPDFiumControl
End Class
