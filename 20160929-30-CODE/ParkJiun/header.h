//Date: 2016.09.29
//Author: Park Jiun
#pragma once
#include"stdafx.h"

using namespace System;
using namespace System::Security::Cryptography;
using namespace System::Text;


bool Verify2(array<Byte>^, array<Byte>^);
bool Verify(char **);
void first_request();
array<Byte>^ SignMessage(array<Byte>^ );
array<Byte>^ makeM();
void CovertByteArrayTostring(array<Byte>^, std::string&);
void CovertStringTostring(String ^, std::string&);