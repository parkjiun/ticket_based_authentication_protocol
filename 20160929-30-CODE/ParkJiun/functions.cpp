//Date: 2016.09.24
//Author: Park Jiun
#include"stdafx.h"

using namespace System;
using namespace System::Security::Cryptography;
using namespace System::Text;

//Verify2는 test 목적으로 Verify함수에서 인자 타입을 변경한 함수
bool Verify2(array<Byte>^ M, array<Byte>^ hMCA)
{
	try
	{
		freopen("CA_RSA_Key.txt", "r", stdin);
		UnicodeEncoding^ ByteConverter = gcnew UnicodeEncoding;
		RSACryptoServiceProvider^ RSA = gcnew RSACryptoServiceProvider;

		//CA's RAS Key
		std::string in1, in2;
		std::cin >> in1 >> in2;
		String^ publicOnly = gcnew String(in1.c_str()); //convert C++ standard string to System String
		String^ PublicPrivate = gcnew String(in2.c_str()); //convert System String to array<Byte>
		RSA->FromXmlString(PublicPrivate);

		//hash algorithm: SHA256 among SHA-2
		Object^ hash = gcnew SHA256Managed;

		//1. Prototype: array<Byte>^ SignData(array<Byte>^ buffer, System::Object^ hash)
		//2. parameter: (signature target, hash algorithm)
		//3. return: result of sign
		//array<Byte>^Sign = RSA->SignData(Plain, hash);

		
		//1. Prototype: bool VerifyData(array<Byte>^ buffer, System::Object^ hash, array<Byte>^ Signature)
		//2. parameter: (comparison target, hash algorithm used when signing, verification target)
		//3. return
		//		true: match between "result of applying hash algotirhm to comparison target" and "verification target"(3rd parameter)
		//		false: mismatch between "result of applying hash algotirhm to comparison target" and "verification target"(3rd parameter)
		bool verify = RSA->VerifyData(M, hash, hMCA);
		return verify;
	}
	catch (CryptographicException^ e)
	{
		//Catch and display a CryptographicException  
		//to the console.
		Console::WriteLine(e->Message);
	}
}

bool Verify(char **parameter)
{	
	//M = (h(Client's name), Client's Public Key);
	//parameter[0] : h("Client's name)
	//parameter[1] : Client's Public Key
	std::string SsignToHashM = parameter[2]; //[h(M)]CA
	std::string Smessage = parameter[0];
	Smessage += parameter[1];

	try
	{
		freopen("CA_RSA_Key.txt", "r", stdin);
		UnicodeEncoding^ ByteConverter = gcnew UnicodeEncoding;
		RSACryptoServiceProvider^ RSA = gcnew RSACryptoServiceProvider;

		//CA's RAS Key
		std::string in1, in2;
		std::cin >> in1 >> in2;
		String^ publicOnly = gcnew String(in1.c_str()); //convert C++ standard string to System String
		String^ PublicPrivate = gcnew String(in2.c_str()); //convert System String to array<Byte>
		RSA->FromXmlString(PublicPrivate);
		
		String^ tmp;
		tmp = gcnew String(Smessage.c_str());
		array<Byte>^ message = ByteConverter->GetBytes(tmp); 

		tmp = gcnew String(SsignToHashM.c_str());
		array<Byte>^ signToHashMessage = ByteConverter->GetBytes(tmp);

		//hash algorithm: SHA256 among SHA-2
		Object^ hash = gcnew SHA256Managed;

		//1. Prototype: array<Byte>^ SignData(array<Byte>^ buffer, System::Object^ hash)
		//2. parameter: (signature target, hash algorithm)
		//3. return: result of sign
		//array<Byte>^Sign = RSA->SignData(Plain, hash);


		//1. Prototype: bool VerifyData(array<Byte>^ buffer, System::Object^ hash, array<Byte>^ Signature)
		//2. parameter: (comparison target, hash algorithm used when signing, verification target)
		//3. return
		//		true: match between "result of applying hash algotirhm to comparison target" and "verification target"(3rd parameter)
		//		false: mismatch between "result of applying hash algotirhm to comparison target" and "verification target"(3rd parameter)
		bool verify = RSA->VerifyData(message, hash, signToHashMessage);
		return verify;
	}
	catch (CryptographicException^ e)
	{
		//Catch and display a CryptographicException  
		//to the console.
		Console::WriteLine(e->Message);
	}
}

array<Byte>^ SignMessage(array<Byte>^ M) {
	freopen("CA_RSA_Key.txt", "r", stdin);
	UnicodeEncoding^ ByteConverter = gcnew UnicodeEncoding;
	RSACryptoServiceProvider^ RSA = gcnew RSACryptoServiceProvider;

	//CA's RAS Key
	std::string in1, in2;
	std::cin >> in1 >> in2;
	String^ publicOnly = gcnew String(in1.c_str()); //convert C++ standard string to System String
	String^ PublicPrivate = gcnew String(in2.c_str()); //convert System String to array<Byte>
	RSA->FromXmlString(PublicPrivate);

	//hash algorithm: SHA256 among SHA-2
	Object^ hash = gcnew SHA256Managed;

	return RSA->SignData(M, hash);
}

void CovertStringTostring(String ^ s, std::string& os) {
	using namespace Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

void CovertByteArrayTostring(array<Byte>^ arr, std::string& os) {
	UnicodeEncoding^ ByteConverter = gcnew UnicodeEncoding;
	String^ s = ByteConverter->GetString(arr);

	using namespace Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

array<Byte>^ makeM(){
	std::string clientPublicKey = "<RSAKeyValue><Modulus>2yrsvBqkmsAPF7T36KvOs++ss0HL/nRF2fPBXSaGIfOevxT2qTBowznfn+79jZTiL6//h7RWy5yuHpEzvijO0hYJcYUgn4Ya53yTgfLiS8yoKy/dkJWDeJlWLZ22dZYs//rtQFwDN0KW7UukOk5jY1sbvhLxEqIg7iiv4deN2g0=</Modulus><Exponent>AQAB</Exponent></RSAKeyValue>";
	
	UnicodeEncoding^ ByteConverter = gcnew UnicodeEncoding;
	SHA256Managed^ hash = gcnew SHA256Managed;


	array<Byte>^ name = ByteConverter->GetBytes("Jiun");
	array<Byte>^ hashed_text = hash->ComputeHash(name);
	
	std::string Message;
	CovertByteArrayTostring(hashed_text, Message);

	Message += clientPublicKey;

	String^ tmp = gcnew String(Message.c_str());
	array<Byte>^ ret = ByteConverter->GetBytes(tmp);

	return ret;
}