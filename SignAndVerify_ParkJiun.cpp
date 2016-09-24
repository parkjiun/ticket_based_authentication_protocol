//Date: 2016.09.24
//Author: Park Jiun
#include"stdafx.h"
#include<iostream>
#include<string>
#using <System.dll>

using namespace System;
using namespace System::Security::Cryptography;
using namespace System::Text;

int main()
{
	try
	{
		UnicodeEncoding^ ByteConverter = gcnew UnicodeEncoding;
		RSACryptoServiceProvider^ RSA = gcnew RSACryptoServiceProvider;

		String^ publicOnly = "<RSAKeyValue><Modulus>wDnf8RnU+k3BrOEw9JxzFv0Gejy1TTo1DGF7ipFj7rqGhGWcaU/S1pPukz0rV7J9rprwjCHhp5d34EkzwBYTDfQSXDSJqFiO2ao05STD1kLTTbQSs1z+mpxvtTKBinRaaU6xonYDGKbIOt0MbF4XHt8CCi4wQWI7XciX4dRN9CU=</Modulus><Exponent>AQAB</Exponent></RSAKeyValue>";
		String^ PublicPrivate = "<RSAKeyValue><Modulus>wDnf8RnU+k3BrOEw9JxzFv0Gejy1TTo1DGF7ipFj7rqGhGWcaU/S1pPukz0rV7J9rprwjCHhp5d34EkzwBYTDfQSXDSJqFiO2ao05STD1kLTTbQSs1z+mpxvtTKBinRaaU6xonYDGKbIOt0MbF4XHt8CCi4wQWI7XciX4dRN9CU=</Modulus><Exponent>AQAB</Exponent><P>6AS1ILY+GkUrV+dem8tyikjNp7MOeA8h5Jiccjoske0h2gzOfv0E0hNgVRxy+stisHUNp7CaumxujBF2Ot81fQ==</P><Q>1Bg/cpvESxJw+jt21dEGl9s+0sPM5UxeI7yFBNB6s9DQd8n9e+BGzrXUrWP47SblYfYJRRx52uIGgFGTB27ZyQ==</Q><DP>SRFKdW3PKvjDiKBdpBSzEqeQ1JJIKTkixFnnUvXNGXujYIcN9OH7xajCeqtF7oNkpguG7FtqrvD883GAWVP4BQ==</DP><DQ>Hx0HgbqUCydDZ5H9ltQ5EWHaT3Tlw+V2Eev/33rt5R8G1evNwbRe7sgB0QXPaIrCL6K2LWtF/PQXXA+bcAW08Q==</DQ><InverseQ>kVo9bXKqwSat85JmWeTYKWrHxkOpljWtsmUATgKlVUCSEzkeXfcd7StXSt21fe3n5MwgFytWa0N3+a7q+NXudw==</InverseQ><D>En7PEQnw/9dw8eMl/Hc8LKNSVvsV37UgywzrH+FO2fa5AC6trsVXLj3EGAcr7y91n9H5IKaW6XLtvhcVA1+sXAHbWyn8Knu9Hiol7LxKZo/BRReXquAGL8W9y+ae8Qt4UwuPu9DUCYbQ652EWHwFneRIBuZM9k/OYLNRK2Ba3Ik=</D></RSAKeyValue>";
		RSA->FromXmlString(PublicPrivate);

		//convert C++ standard string to System String
		std::string in;
		std::cin >> in;
		String^ input = gcnew String(in.c_str()); 
		array<Byte>^ Plain = ByteConverter->GetBytes(input); //convert System String to array<Byte>
	
		//hash algorithm: SHA256 among SHA-2
		Object^ asd = gcnew SHA256Managed; 

		//1. Prototype: array<Byte>^ SignData(array<Byte>^ buffer, System::Object^ hash)
		//2. parameter: (signature target, hash algorithm)
		//3. return: result of sign
		array<Byte>^Sign = RSA->SignData(Plain, asd);
		
		//1. Prototype: bool VerifyData(array<Byte>^ buffer, System::Object^ hash, array<Byte>^ Signature)
		//2. parameter: (comparison target, hash algorithm used when signing, result of SignData())
		//3. return
		//		true: match between "result of applying hash algotirhm to comparison target" and "result of SignData()"(3rd parameter)
		//		false: mismatch between "result of applying hash algotirhm to comparison target" and "result of SignData()"(3rd parameter)
		bool verify = RSA->VerifyData(ByteConverter->GetBytes("SIGK"), asd, Sign);
		
		if (verify) printf("일치\n");
		else printf("불일치\n");

	}
	catch (CryptographicException^ e)
	{

		//Catch and display a CryptographicException  
		//to the console.
		Console::WriteLine(e->Message);
	}
}