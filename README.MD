# InnoVisioNate PDFium Control

## NOTE: To use this repository - please ALSO clone the Common Repository and put it somewhere where it is a sibling of where you put this one.

### For example, if you clone this repository to C:\PDFium-Control, then clone Common to C:\Common. When you do this, the PDFium-Control should build cleanly the very first time.
---
The PDFium Control object is an incredibly easy way to display __both__ PDF files AND HTML (or any file that Internet Explorer can display) in your windows application.

This control uses the MSHTML control internally - yet in this case ALL the complexity of hosting that control (which is significant) is done for you behind the scenes because it is built in to the PDFium Control.

For PDF documents, the control uses the google pdfium project to create bitmaps for each page, then it creates the appropriate HTML document for display.

Now - displaying documents could not be easier. Check out the vb and C# samples to see how, with one line of code - you can display any document (PDF or anything internet explorer can display) very easily.

This control is written with RAW COM - it is a perfect example of how easy it is to implement RAW COM, as opposed to using something like ATL or MFC. 

There are a large number of classes and source files here - however note carefully that these are mostly "boiler plate" - you can take these sources and turn just about anything into a real COM object very simply.

What this project demonstrates is what ATL and MFC are essentially doing for you behind the scenes - but more importantly, what this project shows is how easy it is to toss out the over-complexity of BOTH ATL and MFC - and put the incredible power of ALL of COM directly at your fingertips.
