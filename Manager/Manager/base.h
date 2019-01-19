#pragma once
#include <fstream>
#include <codecvt>
using namespace std;
class Student {
private:
	CString name;
	CString number;
	int gradeOOP;
	int gradeMath;
public:
	Student(){}
	void set(CString _name, CString _number, const int & _gradeOOP = 0, const int & _gradeMath = 0)
	{
		name = _name;
		number = _number;
		gradeOOP = _gradeOOP;
		gradeMath = _gradeMath;
	}
	Student(CString _name, CString _number, const int & _gradeOOP = 0, const int & _gradeMath = 0) {
		this->set(_name, _number, _gradeOOP, _gradeMath);
	}
	CString getName() const {
		return name;
	}
	CString getNumber() const {
		return number;
	}
	const int getGradeOOP() const {
		return gradeOOP;
	}
	const int getGradeMath() const {
		return gradeMath;
	}
	friend class Management;
};

// 假线性表
template<typename T>
class myVector
{
private:
	T * p;
	unsigned __sz;
public:
	myVector()
	{
		p = new T[10000];
		__sz = 0;
	}
	void push(const T & newObj)
	{
		p[__sz] = newObj;
		__sz++;
	}
	T& operator[] (const unsigned & idx) const
	{
		return p[idx];
	}
	unsigned size() const
	{
		return this->__sz;
	}
	void erase(int n) {
		const int sz = __sz - 1;
		for (int i = n; i < sz; i++) {
			p[i] = p[i + 1];
		}
		__sz--;
	}
};


// 文件为utf8编码，用csv的逗号分隔符的格式读入
class Management {
	myVector<Student> v;
public:
	Management() {
		v = myVector<Student>();
	}
	
	// 文件 => 内存
	Management(const wchar_t * fileString) {
		v = myVector<Student>();
		
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

			CString name, number;
			int gradeOOP = 0, gradeMath = 0;
			name = curString;
			number = curString + idx[0];
			swscanf(curString + idx[1], L"%d", &gradeOOP);
			swscanf(curString + idx[2], L"%d", &gradeMath);
			add(Student(name, number, gradeOOP, gradeMath));
		}
		delete[] idx;
		delete[] curString;
		ifs.close();
	}

	
	void add(const Student & obj)
	{
		CString s = obj.number;
		if (find(s) == -1) {
			v.push(obj);
		}
		else {
			throw bad_exception();
		}
	}

	// 遍历寻找 找到返回下标 找不到返回-1
	unsigned find(CString s)
	{
		const int len = v.size();
		for (int i = 0; i < len; i++)
		{
			if (s == v[i].number)
			{
				return i;
			}
		}
		return -1;
	}

private:
	static bool cmp0(const Student & a, const Student & b) {
		return a.number < b.number;
	}

	static bool cmp1(const Student & a, const Student & b) {
		return a.name < b.name;
	}

	static bool cmp2(const Student & a, const Student & b) {
		return a.gradeOOP < b.gradeOOP;
	}

	static bool cmp3(const Student & a, const Student & b) {
		return a.gradeMath < b.gradeMath;
	}

public:
	int sort(const int index = 0, const bool reverse = 0) {
		const int n = v.size();
		bool(*p)(const Student &, const Student &) = cmp0;
		switch (index) {
		//number
		case 0: p = cmp0; break;
		//name
		case 1: p = cmp1; break;
		//gradeOOP
		case 2: p = cmp2; break;
		//gradeMath
		case 3: p = cmp3; break;
		}
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				if (p(v[j], v[i]) ^ reverse) {
					Student tmp = v[i];
					v[i] = v[j];
					v[j] = tmp;
				}
			}
		}
		return index * 2 + (int)reverse;
	}

	// 内存 => 文件
	void output(const wchar_t * fileString) {
		locale utf8(locale(""), new codecvt_utf8<wchar_t, 0x10ffff, little_endian>);
		wofstream ofs(fileString);
		ofs.imbue(utf8);
		const int len = v.size();
		for (int i = 0; i < len; i++)
		{
			const wchar_t * name = v[i].name;
			const wchar_t * number = v[i].number;
			ofs << name << L',' << number << L',' << v[i].gradeOOP << L',' << v[i].gradeMath << endl;
		}
		ofs.close();
	}

	void erase(int n) {
		v.erase(n);
	}

	friend class CManagerDlg;
	friend class CChgDlg;
};
