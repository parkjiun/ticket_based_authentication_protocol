#include"stdafx.h"
#include<stdio.h>
#include<string>
#include<iostream>
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

		RSAParameters privateKey = RSA->ExportParameters(true); //인자로 ture 넘기면 private key 받아옴/false면 public key
		RSAParameters publicKey;


		/*
			public:
				virtual String^ ToXmlString(
					bool includePrivateParameters
				) override
			
			매개 변수
				includePrivateParameters
				Type: System::Boolean
				공개 및 개인 RSA 키를 포함하는 경우 true이고, 공개 키만 포함하는 경우는 false입니다.
			
			반환 값
				Type: System::String^
				현재 RSA 개체의 키가 들어 있는 XML 문자열입니다.
		*/
		String^ publicKeyText = RSA->ToXmlString(false);
		//ToXmlString 함수에 인자를 false로 전달해 RSA에 저장된 public Key를 받아옴
		printf("<Public Key1>\n%s\n\n", publicKeyText);

		String^ privateKeyText = RSA->ToXmlString(true);
		//ToXmlString 함수에 인자를 true로 전달해 RSA에 저장된 private Key를 받아옴
		printf("<Private Key>\n%s\n\n", privateKeyText);

		array<Byte>^ Plain = ByteConverter->GetBytes("PLAIN TEXT");


		/*
		FromXmlString 함수
		RSA 개체의 key 값을 XML string으에 저장돼 있는 정보로 초기화해줌

			public:
				virtual void FromXmlString(
					String^ xmlString
				) override

			매개 변수
			xmlString
				Type: System::String
				The XML string containing RSA key information.
			
			예외
			예외 조건
				ArgumentNullException
					The xmlString parameter is nullptr.
				CryptographicException
					The format of the xmlString parameter is not valid.
		*/

		//아래의 식과 같이 public key 등을 이미 받아놓은 key string으로 사용할 수 있다.
		//publicKeyText = "<RSAKeyValue><Modulus>tjver1f5lrmPgK3jyclHartZrHfO6brZWS9gM6lcDNexph8sOJ+mxW5sCT5Gd0wkcpSn0udruSJY60O3+GF3efURLDHWOC3/UQ8/1IyS0E6Vm1Wuur+/FAt9U/NgHKf4mWobHDb7Ee7T26/oF/uq71Vw+kCg+BsnrdwuzWjR9wU=</Modulus><Exponent>AQAB</Exponent></RSAKeyValue>";
		RSA->FromXmlString(publicKeyText);
		array<Byte>^Cipher = RSA->Encrypt(Plain, false);
		/*
			Encrypt는 Public Key를, Decrypt는 Private Key를 사용해야하며,
			서명을 위한 Private Key로의 Encrypt는 SignData 함수를 사용하고
			검증을 위한 Public key로의 Decrypt는 VeryfyData 함수를 사용함/
		*/


		//privateKeyText = "<RSAKeyValue><Modulus>tjver1f5lrmPgK3jyclHartZrHfO6brZWS9gM6lcDNexph8sOJ+mxW5sCT5Gd0wkcpSn0udruSJY60O3+GF3efURLDHWOC3/UQ8/1IyS0E6Vm1Wuur+/FAt9U/NgHKf4mWobHDb7Ee7T26/oF/uq71Vw+kCg+BsnrdwuzWjR9wU=</Modulus><Exponent>AQAB</Exponent><P>uDYPRf5AF+/JZQ9yKq/EF05qwIHv3VK6TkCStUD8X3dTVQeaIcrpQYBSeq2cjiF0JwdfZ9SYKIJO590FN/Lhaw==</P><Q>/UCLE3SY8B3UA0fnOv7ZyR/jnHPoJZqoAHzzg61jbte03gqXhID5XdlhFjPC6eazo14wecWovmsrznYwCyn1Tw==</Q><DP>G09IbGQJNINEJEtp7ZIpTBtAEFIzMWi2XiuMlHqR78VNAWojG6dtdVyE3dMnRpsHEVIyfr4x4K+Q6ycFQworCQ==</DP><DQ>Aj++fG++o/M/3L+YuBdnS7fyx4Ln/t1+vHJfnz288lEMFCS3779Nd53klNPk2TrpQXwmpg4xT2+YNf8qsg6vVQ==</DQ><InverseQ>K7Hbu82g5snHp/5qK9rD2lm+l6qopkkeY9qoAVI3fQWmsnAOIkzqwSYP3Y06sFTTjSmaJLpB16JoHLd458c/2w==</InverseQ><D>J5eJUYIlFUSac2QUNc53qC4tFOXwu+Ie/5vl5EN63sVr8MIcCu9Qvds4OKfhimCuGIDIl280/cODGxYa3albWfJDpEUljdICGbx9DOiNspExE62ECarpShrOdyV3OYb2qriQxNmLXhV/3kCjZqoezwicAc/Ed0AvFta2R2+F0w8=</D></RSAKeyValue>";
		RSA->FromXmlString(privateKeyText);
		printf("%s\n\n", RSA->Decrypt(Cipher, false));

		SHA1CryptoServiceProvider^ SHA1 = gcnew SHA1CryptoServiceProvider;
		array<Byte>^hashed_val = SHA1->ComputeHash(Plain);
		printf("%s\n",hashed_val);
	
		array<Byte>^temp = RSA->SignData(hashed_val, SHA1);
		RSA->FromXmlString(publicKeyText);
		bool result = RSA->VerifyData(hashed_val, SHA1, temp);
	}
	catch (CryptographicException^ e)
	{

		//Catch and display a CryptographicException  
		//to the console.
		Console::WriteLine(e->Message);
	}

}
