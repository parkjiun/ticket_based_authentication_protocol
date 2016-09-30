#include "stdafx.h"

ref class Certificate {
private:
	array<Byte>^ M;
	array<Byte>^ hMCA;
public:
	Certificate(){
		M = makeM();
		hMCA = SignMessage(M);
	}
	array<Byte>^ getM() { return M; }
	array<Byte>^ gethMCA() { return hMCA; }
};

int main() {
	Certificate clients;
	bool verify = Verify2(clients.getM(), clients.gethMCA());
	if (verify) printf("일치\n");
	else printf("불일치\n");
	
	UnicodeEncoding^ ByteConverter = gcnew UnicodeEncoding;
	String^ corruptedM = "sdaskas;lak;ejpd";//M이 조작됐거나 훼손된 경우 test
	verify = Verify2(ByteConverter->GetBytes(corruptedM), clients.gethMCA());
	if (verify) printf("일치\n");
	else printf("불일치\n");
}