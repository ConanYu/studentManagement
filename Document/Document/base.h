#pragma once
#include <fstream>
#include <codecvt>
#include <cstring>
using namespace std;
constexpr int MAXIMUM = 10000;
class list {
private:
	int * OOP;
	int * MAT;
	list(){
		OOP = new int[MAXIMUM];
		MAT = new int[MAXIMUM];
		memset(OOP, 0, sizeof(int) * MAXIMUM);
		memset(MAT, 0, sizeof(int) * MAXIMUM);
	}
	friend class Management;
	friend class CChildView;
};

// 文件为utf8编码，用csv的逗号分隔符的格式读入
class Management {
private:
	int sz;
	list data;
public:
	Management() {
		sz = 0;
		data = list();
	}
	// 文件 => 内存
	void set(const wchar_t * fileString) {
		sz = 0;
		data = list();

		// utf8
		locale utf8(locale(""), new codecvt_utf8<wchar_t, 0x10ffff, little_endian>);
		wifstream ifs(fileString);
		ifs.imbue(utf8);

		//不存在文件
		if (!ifs.is_open()) {
			return;
		}

		// curString 即 buffer
		wchar_t * curString = new wchar_t[2048];
		int * idx = new int[128];
		while (!ifs.eof()) {
			ifs.getline(curString, 2048);
			int p = 0;
			const int len = wcslen(curString);
			for (int i = 0; i < len; i++) {
				if (curString[i] == L',') {
					curString[i] = L'\0';
					idx[p++] = i + 1;
				}
			}
			if (len <= 0) {
				break;
			}
			int gradeOOP = 0, gradeMath = 0;
			swscanf(curString + idx[1], L"%d", &gradeOOP);
			swscanf(curString + idx[2], L"%d", &gradeMath);
			data.OOP[sz] = gradeOOP;
			data.MAT[sz] = gradeMath;
			sz++;
		}
		delete[] idx;
		delete[] curString;
		ifs.close();
	}
	friend class CChildView;
};
