Public Class Form1
   Private Sub button1_Click(sender As Object, e As EventArgs) Handles button1.Click
      openFileDialog1.ShowDialog()
      AxPDFiumControl1.Document = openFileDialog1.FileName
   End Sub
End Class
