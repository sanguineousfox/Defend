#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

//Возвращает N-ый бит 1-байтового числа A, начиная с начала
bool GetBit(unsigned char A, int N)
{
	return (A >> 8 - N - 1) & 1u;
}

//Вставляет в значение A указанный бит Bit в позицию N (с начала)
void ChangeBit(unsigned char& A, bool Bit, int N)
{
	if (Bit == 0) A &= ~(1 << 8 - N - 1);
	if (Bit == 1) A |= (1 << 8 - N - 1);
}

//Определяет количество символов в тексте
int LengthFile(string FileName)
{
	ifstream file(FileName, ios::binary | ios::ate);
	int Length = file.tellg();
	file.close();
	return Length;
}

vector<unsigned char> readText(const string& filename) {

	ifstream fin(filename, ios::binary);
	vector<unsigned char> text((istreambuf_iterator<char>(fin)),
		istreambuf_iterator<char>());
	fin.close();

	return text;
}

void writeText(vector <unsigned char> Text, string FileName)
{
	ofstream File(FileName);
	for (int i = 0; i < Text.size(); i++)
		File << Text[i];
	File.close();

}
//Помещает секретное сообщение из файла SecretText (txt) в файл PictureFileName (bmp)
void PutCryptMessage(string SecretText, LPTSTR PictureFileName)
{	int Size = LengthFile(SecretText);
	vector <unsigned char> Crypt = readText(SecretText);
	//Объявим нужные структуры
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	unsigned char Palette[1024];
	unsigned long RW;
	//Откроем файл для чтения
	HANDLE InputFile = CreateFile(PictureFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (InputFile == INVALID_HANDLE_VALUE)
		return;
	//Загрузим заголовки и палитру
	ReadFile(InputFile, &bfh, sizeof(bfh), &RW, NULL);
	ReadFile(InputFile, &bih, sizeof(bih), &RW, NULL);
	ReadFile(InputFile, Palette, sizeof(Palette), &RW, NULL);
	int Height = bih.biHeight;
	int Width = bih.biWidth;
	//Объявим растр как одномерный массив точек
	vector <RGBTRIPLE> Points(Height * Width);
	//Загрузим растр в массив
	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			ReadFile(InputFile, &Points[Height * i + j], sizeof(Points[Height * i + j]), &RW, NULL);
		}
		//Обеспечим выравнивание строки
		ReadFile(InputFile, Palette, (sizeof(RGBTRIPLE) * Width) % 4, &RW, NULL);
	}
	//Закроем дескриптор
	CloseHandle(InputFile);
	//Заменим последние биты оттенка голубого в растре
	for (int i = 0; i < Crypt.size(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			ChangeBit(Points[4 * i + j].rgbtBlue, GetBit(Crypt[i], 2 * j), 6);
			ChangeBit(Points[4 * i + j].rgbtBlue, GetBit(Crypt[i], 2 * j + 1), 7);
		}
	}
	//Откроем данный файл для записи
	HANDLE OutputFile = CreateFile(PictureFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
	if (OutputFile == INVALID_HANDLE_VALUE)
		return;
	//Запишем заголовки и палитру в файл-вывода
	WriteFile(OutputFile, &bfh, sizeof(bfh), &RW, NULL);
	WriteFile(OutputFile, &bih, sizeof(bih), &RW, NULL);
	WriteFile(OutputFile, Palette, sizeof(Palette), &RW, NULL);
	//Загрузим растр в файл вывода
	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			WriteFile(OutputFile, &Points[Height * i + j], sizeof(Points[Height * i + j]), &RW, NULL);
			//WriteFile(OutputFile, &Points[Height * i + j], sizeof(Points), &RW, NULL);
		}
		//Обеспечим выравнивание строки
		WriteFile(OutputFile, Palette, (sizeof(RGBTRIPLE) * Width) % 4, &RW, NULL);
	}
	//Закроем дескриптор
	CloseHandle(OutputFile);
	cout << "Секретное содержимое было успешно помещено.\n";
}

//"Достает" секретное сообщение и возвращает его

void TakeCryptMessage(LPTSTR InputFileName, string Output)
{
	//Объявим нужные структуры
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	unsigned char Palette[1024];
	unsigned long RW;
	//Откроем файл для чтения
	HANDLE InputFile = CreateFile(InputFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (InputFile == INVALID_HANDLE_VALUE)
		return;
	//Загрузим заголовки и палитру
	ReadFile(InputFile, &bfh, sizeof(bfh), &RW, NULL);
	ReadFile(InputFile, &bih, sizeof(bih), &RW, NULL);
	ReadFile(InputFile, Palette, sizeof(Palette), &RW, NULL);
	int Height = bih.biHeight;
	int Width = bih.biWidth;
	//Объявим растр как одномерный массив точек
	vector <RGBTRIPLE> Points(Height * Width);
	//Загрузим растр в массив
	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			ReadFile(InputFile, &Points[Height * i + j], sizeof(Points[Height * i + j]), &RW, NULL);
		}
		// Обеспечим выравнивание строки
		ReadFile(InputFile, Palette, (sizeof(RGBTRIPLE) * Width) % 4, &RW, NULL);
	}
	//Закроем дескриптор
	CloseHandle(InputFile);
	vector <unsigned char> Text(Height * Width / 4);
	//Заменим последние биты оттенка голубого в растре
	for (int i = 0; i < Height * Width / 4; i++)
		for (int j = 0; j < 4; j++)
		{
			ChangeBit(Text[i], GetBit(Points[4 * i + j].rgbtBlue, 6), 2 * j);
			ChangeBit(Text[i], GetBit(Points[4 * i + j].rgbtBlue, 7), 2 * j + 1);
		}
	writeText(Text, Output);
	cout << "Секретное содержимое было успешно извлечено.\n";
}

void CheckCryptMessage(string Input, string Output)
{
	int input_lenght = LengthFile(Input);
	int output_lenght = LengthFile(Output);

	vector <unsigned char> input_vector = readText(Input);
	vector <unsigned char> output_vector = readText(Output);

	BOOL flag = TRUE;

	if (input_lenght > output_lenght) flag = FALSE;
	else
		for (int i = 0; i < input_lenght; i++)
		{
			if (!(input_vector[i] == output_vector[i]))
				flag = FALSE;
		}
	
	if (flag)
		std::cout << "Совпадение обнаружено" << std::endl;
	else if(!flag)
		std::cout << "Совпадений не найдено." << std::endl;
}

int _tmain(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	/*

	* argv[0] - Расположение программы

	* argv[1] - Тип операции (-embed (внедрение), -retrieve (извлечение), -check (проверка))

	* argv[2] - Первый файл

	* argv[3] - Второй файл

	*/

	//argv[2] - "Secret.txt", argv[3] - "Picture.bmp".
	if (string(argv[1]) == "-embed")
		PutCryptMessage(argv[2], argv[3]);
	//argv[2] - "Picture.bmp", argv[3] - "Secret.txt".
	if (string(argv[1]) == "-retrieve")
		TakeCryptMessage(argv[2], argv[3]);
	if (string(argv[1]) == "-check")
		CheckCryptMessage(argv[2], argv[3]);
	system("pause");
	return 0;
}