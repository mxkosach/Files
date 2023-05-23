#include "myfunctions.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

void myopen(ifstream& fin, const char* fname, const int mode = ios::in);
void myopen(ofstream& fout, const char* fname,
	const int mode = ios::trunc | ios::out);
void file2scn(ifstream& fin, const char* fname, const int maxlen = 128);

struct student
{
	char fio[32];
	int group;
	float val;
	char dat[12];
	char tel[14];
};

int main()
{
	setlocale(LC_ALL, "RUS");

	{
		title(2);
		ifstream fin;
		const char* fname1 = "14.2.txt";
		fin.open(fname1);
		if (fin.is_open())
			cout << "Файл " << fname1 << " открыт" << endl;
		else
			cout << "Ошибка открытия файла " << fname1 << endl;
		fin.close();

		const char* fname2 = "abc.txt";
		fin.open(fname2);
		if (fin.is_open())
			cout << "Файл " << fname2 << " открыт" << endl;
		else
			cout << "Ошибка открытия файла " << fname2 << endl;
		fin.close();
	}

	{
		title(3);
		ofstream fout;
		const char* fname = "14.3.txt";
		fout.open(fname);
		if (!fout.is_open())
			cout << "Ошибка открытия файла " << fname << endl;
		cout << "Посимвольная запись в файл первой строки.\n";
		char s[32] = "1) Моя певая запись в файл.";
		for (char* p = s; *p; p++)
			fout.put(*p);
		fout.put('\n');
		fout.close();

		fout.open(fname, ios_base::app);
		if (!fout.is_open())
			cout << "Ошибка открытия файла " << fname << endl;
		cout << "Посимвольная запись в файл первой строки.\n";
		char d[32] = "2) Это вторая строка файла.";
		for (char* p = d; *p; p++)
			fout.put(*p);
		fout.put('\n');
		fout.close();

		ifstream fin;
		fin.open(fname);
		if (!fin.is_open())
			cout << "Ошибка открытия файла " << fname << endl;
		cout << "\nПосимвольное чтение файла:\n";
		while (!fin.eof())
		{
			char ch;
			fin.get(ch);
			cout << ch;
		}
		fin.close();
	}

	{
		title(4);
		ofstream fout;
		const char* fname = "14.4.txt";
		/*fout.open(fname);
		if (!fout.is_open())
			cout << "Ошибка открытия файла " << fname << endl;*/
		myopen(fout, fname);
		fout << "===================\n";
		int m = 12345;
		float x = acos(-1);
		fout << fixed << setprecision(2)
			<< "m  =" << setw(7) << m << '\n'
			<< "x  =" << setw(7) << x << '\n';
		fout << "===================\n";
		fout.close();

		ifstream fin;
		/*fin.open(fname);
		if (!fin.is_open())
			cout << "Ошибка открытия файла " << fname << endl;*/
		myopen(fin, fname);
		const int maxlen = 20;
		char s[maxlen], t[maxlen];
		int n; float y;
		fin >> s;  cout << s << endl;
		fin >> s >> t >> n;
		cout << s << " " << t << " " << n << endl;
		fin >> s >> t >> y;
		cout << s << " " << t << " " << y << endl;
		fin >> s;  cout << s << endl;
		fin.close();

		/*fin.open(fname);
		if (!fin.is_open())
			cout << "Ошибка открытия файла " << fname << endl;*/
		myopen(fin, fname);
		fin.getline(s, maxlen);
		fin.getline(s, maxlen);
		char* p = str2int(s, 2);
		n = atoi(p);
		fin.getline(s, maxlen);
		setlocale(LC_NUMERIC, "C");
		p = str2int(s, 2);
		y = atof(p);
		setlocale(LC_NUMERIC, "RUS");
		fin.close();
		cout << "\nЧисловые значения в файле задания: " << n << " " << y << endl;
	}

	{
		title(6);
		ifstream fin;
		file2scn(fin, "14.4.txt");
	}

	{
		title(7);
		const int maxlen = 128, nval = 4, ngr = 3;
		char s[maxlen];
		int val[nval];
		const char* fname[ngr] = {
			"Группа 1.txt", "Группа 2.txt","Группа 3.txt",
		};
		ifstream fin; ofstream fout;
		myopen(fout, "Отличники.txt");


		char io[5];
		int nstud = 0;
		for (int i = 0; i < ngr; i++)
		{
			myopen(fin, fname[i]);
			while (!fin.eof())
			{
				fin >> s >> io;
				for (int j = 0; j < nval; j++)
					fin >> val[j];
				if (val[mymin(val, nval)] > 8)
				{
					mycat(s, " "); mycat(s, io);
					fout << left << setw(20) << s << " группа " << i + 1 << endl;
					nstud++;
				}
			}
			fin.close();
		}
		fout.close();

		file2scn(fin, "Отличники.txt");
	}

	{
		title(8);
		char* s = new char[128];
		int nstud = myinput(s, "Отличники.txt");
		char** srt = new char* [nstud];
		char* p = s;
		for (int i = 0; i < nstud; i++)
		{
			srt[i] = p;
			p += mylen(p) + 1;
		}
		mysrt(srt, nstud, true);

		ofstream fout;
		myopen(fout, "Отличники.txt");
		for (int i = 0; i < nstud; i++)
			fout << srt[i] << endl;
		fout.close();
		ifstream fin;
		file2scn(fin, "Отличники.txt");
		delete[]srt; delete[]s;
	}

	{
		//Задание 9
		ofstream fout;
		myopen(fout, "14.9.bin", ios_base::binary);
		int m = 100;
		fout.write((char*)&m, sizeof(m));
		double a = 173.904;
		fout.write((char*)&a, sizeof(a));

		int X[] = { 1,2,3,5,7,11,13,17,19 };
		int nx = sizeof(X) / sizeof(X[0]);
		fout.write((char*)&nx, sizeof(nx));
		fout.write((char*)&X, nx * sizeof(X[0]));

		const char* s = "************************";
		int ns = mylen(s) + 1;
		fout.write((char*)&ns, sizeof(ns));
		fout.write(s, ns);

		student st1 = { "Липницкий А.Н.",5,7.25,"2000.04.17","29-361-90-14" };
		fout.write((char*)&st1, sizeof(st1));
		fout.close();
	}

	{
		title(10);
		ifstream fin;
		myopen(fin, "14.9.bin", ios_base::binary);
		int m;  fin.read((char*)&m, sizeof(m));
		double a;   fin.read((char*)&a, sizeof(a));
		cout << m << " " << a << endl;

		int nx; fin.read((char*)&nx, sizeof(nx));
		int* X = new int[nx];   fin.read((char*)X, nx * sizeof(X[0]));
		myout(X, nx, nx, 3);

		int ns; fin.read((char*)&ns, sizeof(ns));
		char* s = new char[ns]; fin.read(s, ns);
		cout << s << endl;

		student st1;
		fin.read((char*)&st1, sizeof(st1));
		cout << st1.fio << " " << st1.group << " " << st1.val << " "
			<< st1.dat << " " << st1.tel << endl;
		fin.close();
		delete[]X;  delete[]s;
	}


	cout << endl; system("pause");
	return 0;
}

void myopen(ifstream& fin, const char* fname, const int mode)
{
	fin.open(fname, mode);
	if (!fin.is_open())
		cout << "\nОшибка открытия файла " << fname << endl;
}

void myopen(ofstream& fout, const char* fname, const int mode)
{
	fout.open(fname, mode);
	if (!fout.is_open())
		cout << "\nОшибка открытия файла " << fname << endl;
}

//выводит на экран содержимое текстового файла fname
void file2scn(ifstream& fin, const char* fname, const int maxlen)
{
	char* s = new char[maxlen];
	myopen(fin, fname);
	while (!fin.eof())
	{
		fin.getline(s, maxlen);
		cout << s << endl;
	}
	fin.close();
	delete[]s;
}
