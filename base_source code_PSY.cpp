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

		RSAParameters privateKey = RSA->ExportParameters(true); //���ڷ� ture �ѱ�� private key �޾ƿ�/false�� public key
		RSAParameters publicKey;


		/*
			public:
				virtual String^ ToXmlString(
					bool includePrivateParameters
				) override
			
			�Ű� ����
				includePrivateParameters
				Type: System::Boolean
				���� �� ���� RSA Ű�� �����ϴ� ��� true�̰�, ���� Ű�� �����ϴ� ���� false�Դϴ�.
			
			��ȯ ��
				Type: System::String^
				���� RSA ��ü�� Ű�� ��� �ִ� XML ���ڿ��Դϴ�.
		*/
		String^ publicKeyText = RSA->ToXmlString(false);
		//ToXmlString �Լ��� ���ڸ� false�� ������ RSA�� ����� public Key�� �޾ƿ�
		printf("<Public Key1>\n%s\n\n", publicKeyText);

		String^ privateKeyText = RSA->ToXmlString(true);
		//ToXmlString �Լ��� ���ڸ� true�� ������ RSA�� ����� private Key�� �޾ƿ�
		printf("<Private Key>\n%s\n\n", privateKeyText);

		array<Byte>^ Plain = ByteConverter->GetBytes("PLAIN TEXT");


		/*
		FromXmlString �Լ�
		RSA ��ü�� key ���� XML string���� ����� �ִ� ������ �ʱ�ȭ����

			public:
				virtual void FromXmlString(
					String^ xmlString
				) override

			�Ű� ����
			xmlString
				Type: System::String
				The XML string containing RSA key information.
			
			����
			���� ����
				ArgumentNullException
					The xmlString parameter is nullptr.
				CryptographicException
					The format of the xmlString parameter is not valid.
		*/

		//�Ʒ��� �İ� ���� public key ���� �̹� �޾Ƴ��� key string���� ����� �� �ִ�.
		//publicKeyText = "<RSAKeyValue><Modulus>tjver1f5lrmPgK3jyclHartZrHfO6brZWS9gM6lcDNexph8sOJ+mxW5sCT5Gd0wkcpSn0udruSJY60O3+GF3efURLDHWOC3/UQ8/1IyS0E6Vm1Wuur+/FAt9U/NgHKf4mWobHDb7Ee7T26/oF/uq71Vw+kCg+BsnrdwuzWjR9wU=</Modulus><Exponent>AQAB</Exponent></RSAKeyValue>";
		RSA->FromXmlString(publicKeyText);
		array<Byte>^Cipher = RSA->Encrypt(Plain, false);
		/*
			Encrypt�� Public Key��, Decrypt�� Private Key�� ����ؾ��ϸ�,
			������ ���� Private Key���� Encrypt�� SignData �Լ��� ����ϰ�
			������ ���� Public key���� Decrypt�� VeryfyData �Լ��� �����/
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