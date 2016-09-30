#include"stdafx.h"
#include<stdio.h>
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
		
		array<Byte>^PublicKey = { 214,46,220,83,160,73,40,39,201,155,19,202,3,11,191,178,56,74,90,36,248,103,18,144,170,163,145,87,54,61,34,220,222,207,137,149,173,14,92,120,206,222,158,28,40,24,30,16,175,108,128,35,230,118,40,121,113,125,216,130,11,24,90,48,194,240,105,44,76,34,57,249,228,125,80,38,9,136,29,117,207,139,168,181,85,137,126,10,126,242,120,247,121,8,100,12,201,171,38,226,193,180,190,117,177,87,143,242,213,11,44,180,113,93,106,99,179,68,175,211,164,116,64,148,226,254,172,147 };
		array<Byte>^Exponent = { 1,0,1 };

		//Values to store encrypted symmetric keys.
		array<Byte>^Plain = ByteConverter->GetBytes("PLAIN TEXT");
		array<Byte>^Cipher;
		array<Byte>^Dec;

		//Create a new instance of RSACryptoServiceProvider.
		RSACryptoServiceProvider^ RSA = gcnew RSACryptoServiceProvider;

		//Create a new instance of RSAParameters.
		RSAParameters RSAKeyInfo;

		//Set RSAKeyInfo to the public key values. 
		RSAKeyInfo.Modulus = PublicKey;
		RSAKeyInfo.Exponent = Exponent;

		//Import key parameters into RSA.
		RSA->ImportParameters(RSAKeyInfo);

		Cipher = RSA->Encrypt(Plain, false);
		Dec = RSA->Encrypt(Plain, false);

		Console::WriteLine("Encrypted plaintext: {0}", ByteConverter->GetString(Plain));

		Console::WriteLine("Encrypted plaintext: {0}", ByteConverter->GetString(Cipher));

		Console::WriteLine("Decrypted plaintext: {0}", ByteConverter->GetString(Dec));
	

		RSAParameters privateKey = RSA->ExportParameters(true); //인자로 ture 넘기면 private key 받아옴/false면 public key
		RSAParameters publicKey;
		publicKey.Modulus = privateKey.Modulus; //public key로 예상
		publicKey.Exponent = privateKey.Exponent; //private key로 예상
		RSA->ImportParameters(publicKey);

		String^ publicKeyText = RSA->ToXmlString(false);
		printf("<Public Key1>\n%s\n", publicKeyText);

		RSA->ImportParameters(privateKey);
		String^ privateKeyText = RSA->ToXmlString(true);
		printf("<Private Key>\n%s\n", privateKeyText);
		

	}
	catch (CryptographicException^ e)
	{

		//Catch and display a CryptographicException  
		//to the console.
		Console::WriteLine(e->Message);
	}

}
