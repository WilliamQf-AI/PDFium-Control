Public Class Form1
   Public Sub New()

      ' This call is required by the designer.
      InitializeComponent()

      AxPDFiumControl2.Document = "http://google.com"

   End Sub

   Private Sub button1_Click(sender As Object, e As EventArgs) Handles button1.Click
      openFileDialog1.ShowDialog()
      '      AxPDFiumControl2.Document = openFileDialog1.FileName
      AxPDFiumControl2.Document = "http://google.com"

   End Sub

   Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
      AxPDFiumControl2.Document = "http://google.com"

   End Sub
End Class
