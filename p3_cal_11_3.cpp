// =====================================================
// this part set in vimrc
// created by Chen Xu
// email: chenxu@mail.ustc.edu.cn
// copyright cx
// Darwin newas.local 17.6.0 Darwin Kernel Version 17.6.0: Tue May  8 15:22:16 PDT 2018; root:xnu-4570.61.1~1/RELEASE_X86_64 x86_64
// Last modify:
// 2018年 6月16日 星期六 07时40分16秒 CST
// =====================================================

#include <string>
#include <iostream>
#include <cmath>
using namespace std;

int f1(int n, char abyte, int c) { 
	for (int ibit = 0; ibit < 8; ibit++) {
		int bit = (abyte >> ibit) & 1;
		if (bit + ((n - bit) & ~1) == n) {
			n = (n - bit) >> 1;
		} else {
			n = ((c - bit) ^ n) >> 1;
		}
	}
	return n;
}

string genPassword(string str) {
	int hash = 0xA439;
	for (int  ibyte = str.size() - 1; ibyte >= 0; ibyte--) {
		hash = f1(hash, str[ibyte], 0x105C3);
	}

	int n1 = 0;
	while (f1(f1(hash, n1 & 0xFF, 0x105C3), n1 >> 8, 0x105C3) != 0xA5B6) {
		if (++n1 >= 0xFFFF) {
			return "Error";
		}
	}

	n1 = floor(((n1 + 0x72FA) & 0xFFFF) * 99999.0 / 0xFFFF);
	string n1strtmp = (string("0000") + to_string(n1));
	string n1str = n1strtmp.substr(n1strtmp.size()-5, 5);

	int temp = stoi(
			n1str.substr(0,n1str.size()-3)
			+ n1str.substr(n1str.size()-2, 2) 
			+ n1str.substr(n1str.size()-3, 1));
	temp = ceil((temp / 99999.0) * 0xFFFF);
	temp = f1(f1(0, temp & 0xFF, 0x1064B), temp >> 8, 0x1064B);

	for (int ibyte = str.size() - 1; ibyte >= 0; ibyte--) {
		temp = f1(temp, str[ibyte], 0x1064B);
	}

	int n2 = 0;
	while (f1(f1(temp, n2 & 0xFF, 0x1064B), n2 >> 8, 0x1064B) != 0xA5B6) {
		if (++n2 >= 0xFFFF) {
			return "Error";
		}
	}

	n2 = floor((n2 & 0xFFFF) * 99999.0 / 0xFFFF);
	string n2strtmp = (string("0000") + to_string(n2));
	string n2str = n2strtmp.substr(n2strtmp.size()-5, 5);

	string password;
	password.push_back(n2str[3]);
	password.push_back(n1str[3]);
	password.push_back(n1str[1]);
	password.push_back(n1str[0]);
	password.push_back('-');
	password.push_back(n2str[4]);
	password.push_back(n1str[2]);
	password.push_back(n2str[0]);
	password.push_back('-');
	password.push_back(n2str[2]);
	password.push_back(n1str[4]);
	password.push_back(n2str[1]);
	password.append("::1");
	return password;
}

string genFromMathId(string mathId, string activationKey) {
	string password = genPassword(mathId + "$1&" + activationKey);
	return password;
}

//6469-027-086::1
void p3_cal_11_3(string mathId="", string activationKey="")
{
	cout<<genFromMathId(mathId, activationKey)<<endl;
}

int main()
{
	p3_cal_11_3();
}
