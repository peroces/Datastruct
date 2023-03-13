#include <fstream>
#include <iostream>
#include <string>

using namespace std;

string instruction[14]; //instruction ����� string �迭
string code[14]; //code ����� string �迭
string temp;
string LOC[12];
string label[12]; //label ����� string �迭
string opcode[12]; //opcode ����� string �迭
string oprend[12]; //oprend ����� string �迭


string search_code(string instruct) { //code ��ȯ�� searchh �Լ�
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

string search_LOC(string oprend) { //LOCCTR ��ȯ�� search �Լ�
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
	if (ifs.fail()) //���� �Է� ���� �� ���� ó��
	{
		cout << "optab open error!" << endl;
		return -1;
	}

	while (!ifs.eof()) { //���⸦ �������� �ۼ��Ǿ������Ƿ� >>�� ���� �Է¹���
		for (int i = 0; i < 14; i++) {
			ifs >> instruction[i];
			ifs >> code[i];
		}
	}

	ifstream SRCFILE("INTLIST");

	if (SRCFILE.fail()) //���� �Է� ���� �� ���� ó��
	{
		cout << "file open error!" << endl;
		return -1;
	}


	int j = 0; //���� �� �ε���
	int k = 0; //string �迭�� ���� �� �ε���
	char tmp[40] = { '\0' }; //������ 1�پ� �б����� tmp
	char t[20] = { '\0' }; //1�پ� �о�� tmp�� ���� ������ t
	while (!SRCFILE.eof()) {
		SRCFILE.getline(tmp, 40); //1�پ� �о�� tmp�� ����

		j = 0;

		for (int i = 0; i < 4; i++) { //LOC�������� �ݺ�
			if (tmp[i] == ' ') //���� �� �� break
				break;
			t[j] = tmp[i]; //tmp�� t�� ����
			j++; //t�� �ε��� ����
			LOC[k] = t; //������ t�� LOC�� ����
		}

		for (int l = 0; l < 20; l++) //t�ʱ�ȭ
			t[l] = { '\0' };

		j = 0;
		for (int i = 8; i < 19; i++) { //label�������� �ݺ�
			if (tmp[i] == ' ')
				break;
			t[j] = tmp[i];
			j++;
			label[k] = t;
		}

		for (int l = 0; l < 20; l++) //t�ʱ�ȭ
			t[l] = { '\0' };

		for (int l = 20; l < 31; l++) { //opcode�������� �ݺ�
			if (tmp[l] == ' ')
				break;
			t[j] = tmp[l];
			j++;
			opcode[k] = t;
		}

		j = 0;
		for (int i = 32; i < 40; i++) { //oprend�������� �ݺ�
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
		if (opcode[i] == "resw" || opcode[i] == "resb") //resb�� ��� ���ڸ� �ƽ�Ű�ڵ�ȭ�Ͽ� ����

			break;
		if (opcode[i] == "word") {
			for (int j = oprend[i].length(); i < 8; i++) //word�� ��� ���� �״�� ����
				OBJCODE[i] += " ";
			OBJCODE[i] += oprend[i];
		}
		if (opcode[i] == "byte") {
			char* charr = new char[oprend[i].size() + 1]; //���ڿ� �����Ҵ��� ���� ����
			copy(oprend[i].begin(), oprend[i].end(), charr);
			charr[oprend[i].size()] = '\0';
			for (int j = 3; j < oprend[i].length(); j++) {
				OBJCODE[i] += charr[j - 1];
			}
			delete[] charr;
		}
		temp1 = search_code(opcode[i]); //����ڵ忡 ���Ե� ����� ���þ �ش��ϴ� �ڵ�
		temp2 = search_LOC(oprend[i]); //����ڵ忡 ���Ե� LOCCTR
		OBJCODE[i] = temp1 + temp2; //temp1�� temp2 ���ļ� ����ڵ�
		cout << LOC[i] << "  ";
		if (temp1 == "error" || temp2 == "error") { //���� �ϳ��� ���� ������ ���� ó��
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
		cout << OBJCODE[i] << "  " << label[i]; //OBJCODE ���
		for (int j = label[i].length(); j < 10; j++)
			cout << " ";
		cout << opcode[i];
		for (int j = opcode[i].length(); j < 10; j++) //opcode ���
			cout << " ";
		cout << oprend[i];
			
	}

	return 0;
}