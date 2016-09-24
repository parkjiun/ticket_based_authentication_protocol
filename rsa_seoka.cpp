#include"stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string>

using namespace System;
using namespace System::Security::Cryptography;
using namespace System::Text;

int main()
{
	freopen("output.txt", "w", stdout);

	// 1. seoka 해쉬-> signdata -> 반대과정
	// 2. seoka 해쉬
	// 1-2 비교

	RSACryptoServiceProvider^ RSA = gcnew RSACryptoServiceProvider;
	UnicodeEncoding^ ByteConverter = gcnew UnicodeEncoding;

	String^ privateKeyText = "<RSAKeyValue><Modulus>xb2pB0WkbgL0/3UxAYLs5B4ekUYaKBiYmKAlTNylzcefzeJPiJlPkob4aPjlU6fZBU/9NiCsthO4DPtazSXk+wB4Q1JtLf2rKLqboxNLZxvV286Gfl24XEB9RswVmhgPDk60VQ1QAI495qoc9paEhmSjcShdCZL7D/r17M6YEkM=</Modulus><Exponent>AQAB</Exponent><P>5kO8JY9g2bBgNZ0eCaLJGknrGDMk2cmm13RUbRv6auas0sjRxZQP0vg6OAPy43l4JKIJte375kl8LFwpU93lYw==</P><Q>29ddmOPFm8JfRLN6mCxTt3w9bizweniMiXpwzXVgq/yrKMoEsT1zj+35jSZ32E6u0u9ZBmo+Ur7dQb10j6aloQ==</Q><DP>jChAlpAuQHL2LMwk43KdfA3wNnuy+4mdr1lUplE4XOdp3Kd14BCejSigr0XgCwv90DZ9OKrSADtMhOfYE/9lxw==</DP><DQ>F13+7t9XA8VXRwAkycP8agZkqS9RqFLj7UD8eHo/ekhzEPTYJta3T9clrWEnX/CNGJKkTdBBK55p+jDfEN3PwQ==</DQ><InverseQ>M/IbkooBDo4QSon30995lG6/A+O8WYtYPohNGmb/sHDoIJ/Kry94uBwHSMi4K08H5jrCDlNOtrn3zaKzlrz+yA==</InverseQ><D>ujJoClfyiECykCW62pB9HiSaZfMbyCu47ObHmMOgQM+7U3PJrnembPQ4zyenUYmYmh8C8Mf9uYmB4n+AtfH71RJ7SR507ki/zaPjxVatUYrBk/DZckidgclYd/sdCvLARXOr83Ykbxqz/tkE5to2TKj4uqnOMa2iFXE4Nfu3LME=</D></RSAKeyValue>";
	String^ publicKeyText = "<RSAKeyValue><Modulus>xb2pB0WkbgL0/3UxAYLs5B4ekUYaKBiYmKAlTNylzcefzeJPiJlPkob4aPjlU6fZBU/9NiCsthO4DPtazSXk+wB4Q1JtLf2rKLqboxNLZxvV286Gfl24XEB9RswVmhgPDk60VQ1QAI495qoc9paEhmSjcShdCZL7D/r17M6YEkM=</Modulus><Exponent>AQAB</Exponent></RSAKeyValue>";

	// Keyword
	array<Byte>^dataToEncrypt = ByteConverter->GetBytes("keyword");
	
	// RSA의 key setting
	RSA->FromXmlString(privateKeyText);

	// Hash Service 개체
	Object^ hash_algo = gcnew SHA1CryptoServiceProvider;

	// dataToEncrypt를 
	// hash하고
	// 셋팅된 key로 암호화
	array<Byte>^result = RSA->SignData(dataToEncrypt, hash_algo); //
	printf("sign data : %s\n", result);

	// dataToEncrypt를 hash 하고 셋팅된 key로 암호화하여
	// result와 비교한다
	// 같다면 return true;
	bool success = RSA->VerifyData(dataToEncrypt, hash_algo, result);
	if (success) printf("Success\n");
	else printf("Fail. \n");

	delete RSA;		
	
	return 0;
}

