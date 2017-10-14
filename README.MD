# InnoVisioNate PDFium Control

---
The PDFium Control object is an incredibly easy way to display __both__ PDF files AND HTML (or any file that Internet Explorer can display) in your windows application.

This control uses the MSHTML control internally - yet in this case ALL the complexity of hosting that control (which is significant) is done for you behind the scenes because it is built in to the PDFium Control.

For PDF documents, the control uses the google pdfium project to create bitmaps for each page, then it creates the appropriate HTML document for display.

Now - displaying documents could not be easier. Check out the vb and C# samples to see how, with one line of code - you can display any document (PDF or anything internet explorer can display) very easily.

This control is written with RAW COM - it is a perfect example of how easy it is to implement RAW COM, as opposed to using something like ATL or MFC. 

There are a large number of classes and source files here - however note carefully that these are mostly "boiler plate" - you can take these sources and turn just about anything into a real COM object very simply.

What this project demonstrates is what ATL and MFC are essentially doing for you behind the scenes - but more importantly, what this project shows is how easy it is to bypass the over-complexity of BOTH ATL and MFC - and put the incredible power of ALL of COM directly at your fingertips. This also means that you can integrate COM into existing software without needing to change any object model, AND that you can create your object model how you see fit, it does not have to be built on top of any framework.

### NOTE: To use this repository - please clone this one, AND the Common Repository at the root of some drive (so you will have a C:\Common and C:\PDFium-Control directory)

At some point, I may create an environment variable to "home" these projects, but for now, the project inter-relations among them rely on "\Common" visibility (note the drive letter does not matter).

All projects produce binary artifacts into "\Common\Artifacts\<configuration>\<platform>" 

---

Also, please navigate to the pdfium\lib\Debug\x64 (or similar location based on configuration and platform) directory, and unzip the pdfium.lib file in pdfium.zip to that location, It's a big lib file. At some point I will investigate removing components in it that aren't required for this project.

---
