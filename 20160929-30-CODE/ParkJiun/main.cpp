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
	if (verify) printf("��ġ\n");
	else printf("����ġ\n");
	
	UnicodeEncoding^ ByteConverter = gcnew UnicodeEncoding;
	String^ corruptedM = "sdaskas;lak;ejpd";//M�� ���۵ưų� �Ѽյ� ��� test
	verify = Verify2(ByteConverter->GetBytes(corruptedM), clients.gethMCA());
	if (verify) printf("��ġ\n");
	else printf("����ġ\n");
}