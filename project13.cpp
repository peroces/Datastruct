#include <fstream>
#include <iostream>
#include <string>

using namespace std;

string instruction[14]; //instruction 저장용 string 배열
string code[14]; //code 저장용 string 배열
string temp;
string LOC[12];
string label[12]; //label 저장용 string 배열
string opcode[12]; //opcode 저장용 string 배열
string oprend[12]; //oprend 저장용 string 배열


string search_code(string instruct) { //code 반환용 searchh 함수
	int i;
	for (i = 0; i < 14; i++) {
		if (instruct == instruction[i]) {
			return code[i];
			break;
		}
		if (i == 14)
			return"error";
	}
}

string search_LOC(string oprend) { //LOCCTR 반환용 search 함수
	int i;
	for (i = 0; i < 12; i++) {
		if (oprend == label[i]) {
			return LOC[i];
			break;
		}
		if (i == 12)
			return "error";
	}
}


int main() {
	ifstream ifs("optab.txt");
	if (ifs.fail()) //파일 입력 실패 시 예외 처리
	{
		cout << "optab open error!" << endl;
		return -1;
	}

	while (!ifs.eof()) { //띄어쓰기를 기준으로 작성되어있으므로 >>를 통해 입력받음
		for (int i = 0; i < 14; i++) {
			ifs >> instruction[i];
			ifs >> code[i];
		}
	}

	ifstream SRCFILE("INTLIST");

	if (SRCFILE.fail()) //파일 입력 실패 시 예외 처리
	{
		cout << "file open error!" << endl;
		return -1;
	}


	int j = 0; //복사 시 인덱스
	int k = 0; //string 배열로 복사 시 인덱스
	char tmp[40] = { '\0' }; //파일을 1줄씩 읽기위한 tmp
	char t[20] = { '\0' }; //1줄씩 읽어온 tmp를 나눠 저장할 t
	while (!SRCFILE.eof()) {
		SRCFILE.getline(tmp, 40); //1줄씩 읽어와 tmp에 저장

		j = 0;

		for (int i = 0; i < 4; i++) { //LOC영역에서 반복
			if (tmp[i] == ' ') //공백 일 시 break
				break;
			t[j] = tmp[i]; //tmp를 t로 복사
			j++; //t의 인덱스 조정
			LOC[k] = t; //조정된 t를 LOC로 복사
		}

		for (int l = 0; l < 20; l++) //t초기화
			t[l] = { '\0' };

		j = 0;
		for (int i = 8; i < 19; i++) { //label영역에서 반복
			if (tmp[i] == ' ')
				break;
			t[j] = tmp[i];
			j++;
			label[k] = t;
		}

		for (int l = 0; l < 20; l++) //t초기화
			t[l] = { '\0' };

		for (int l = 20; l < 31; l++) { //opcode영역에서 반복
			if (tmp[l] == ' ')
				break;
			t[j] = tmp[l];
			j++;
			opcode[k] = t;
		}

		j = 0;
		for (int i = 32; i < 40; i++) { //oprend영역에서 반복
			t[j] = tmp[i];
			j++;
			oprend[k] = t;
		}

		for (int l = 0; l < 20; l++)
			t[l] = { '\0' };
		k++;
	}

	string OBJCODE[12];
	string temp1, temp2;
	for (int i = 1; i < 12; i++) {
		if (opcode[i] == "resw" || opcode[i] == "resb") //resb인 경우 문자를 아스키코드화하여 저장

			break;
		if (opcode[i] == "word") {
			for (int j = oprend[i].length(); i < 8; i++) //word인 경우 숫자 그대로 저장
				OBJCODE[i] += " ";
			OBJCODE[i] += oprend[i];
		}
		if (opcode[i] == "byte") {
			char* charr = new char[oprend[i].size() + 1]; //문자열 동적할당을 통해 복사
			copy(oprend[i].begin(), oprend[i].end(), charr);
			charr[oprend[i].size()] = '\0';
			for (int j = 3; j < oprend[i].length(); j++) {
				OBJCODE[i] += charr[j - 1];
			}
			delete[] charr;
		}
		temp1 = search_code(opcode[i]); //기계코드에 포함될 어셈블리 지시어에 해당하는 코드
		temp2 = search_LOC(oprend[i]); //기계코드에 포함될 LOCCTR
		OBJCODE[i] = temp1 + temp2; //temp1과 temp2 합쳐서 기계코드
		cout << LOC[i] << "  ";
		if (temp1 == "error" || temp2 == "error") { //둘중 하나라도 에러 있을시 예외 처리
			cout << "        " << label[i];
			for (int j = label[i].length(); j < 10; j++)
				cout << " ";
			cout << opcode[i];
			for (int j = opcode[i].length(); j < 10; j++)
				cout << " ";
			cout << oprend[i];
			cout << "\n error!\n";
			break;
		}
		cout << OBJCODE[i] << "  " << label[i]; //OBJCODE 출력
		for (int j = label[i].length(); j < 10; j++)
			cout << " ";
		cout << opcode[i];
		for (int j = opcode[i].length(); j < 10; j++) //opcode 출력
			cout << " ";
		cout << oprend[i];
			
	}

	return 0;
}