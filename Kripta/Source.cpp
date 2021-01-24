#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>

enum FileReadMod
{
	Display,
	NotDisplay,
	Statystics,
};

enum Mod
{
	Encoding,
	Decoding
};

enum Shift
{
	Up,
	Down,
	Left,
	Right,
};

enum ShiftMod
{
	NewKey,
	Key,
};

void ArrayShift(Shift shift, ShiftMod mod);
void ArrayDisplay(char Array[5][6]);
void ArrayDisplay(char ArrayChar[5][6], int ArrayInt[5][6]);
void FileEncoding(LPCTSTR toRead, LPCTSTR toWrite, Mod mod);
char MostCommonWord(char ArrayChar[5][6], int ArrayInt[5][6]);
BOOL FileRead(LPCTSTR toRead, FileReadMod Mod);
BOOL FileWrite(LPCTSTR toWrite, char buffer);

char WordArray[5][6] = { 'А', 'Б', 'В', 'Г', 'Д', 'Е', 
						'Ж', 'З', 'И', 'К', 'Л', 'М', 
						'Н', 'О', 'П', 'Р', 'С', 'Т', 
						'У', 'Ф', 'Х', 'Ц', 'Ч', 'Ш', 
						'Щ', 'Ы', 'Ь', 'Э', 'Ю', 'Я'};

char KeyArray[5][6];
char DecodingArray[5][6];
int CounterArray[5][6];

void WordCount(char word)
{
	int word_code = (int)word;

	if ((word_code < -64 || word_code >  -33) && word_code != -88) 
		return;

	if (word_code >= -64 && word_code <= -33) word_code += 32;
	else if (word_code == -88) word_code += 16;
	word_code += 33;

	if (word_code >= 10) word_code--;
	if (word_code >= 27) word_code--;
	else if (word_code == 26) word_code++;

	if (word_code == -39) word_code = 6;

	int ArrayHeight = 0;
	int ArrayWidth = 0;

	if (word_code != 6)
		ArrayHeight = word_code / 6;
	else
		ArrayHeight = word_code % 6;

	if (word_code != 6)
		ArrayWidth = word_code % 6 - 1;
	else
		ArrayWidth = word_code - 1;

	CounterArray[ArrayHeight][ArrayWidth] += 1;
}

BOOL FileWrite(LPCTSTR toWrite, char buffer)
{
	HANDLE hFile;
	DWORD pdw;

	if ((hFile = CreateFile(toWrite, GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
	{
		std::cout << "\nsFile creation failed with error " << GetLastError() << std::endl;
	}

	SetFilePointer(hFile, NULL, NULL, FILE_END);
	WriteFile(hFile, (char*)&buffer, sizeof(char), &pdw, NULL);

	CloseHandle(hFile);

	return true;
}

BOOL FileWipe(LPCTSTR toWrite)
{
	HANDLE hFile;

	if ((hFile = CreateFile(toWrite, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
	{
		std::cout << "\nsFile creation failed with error " << GetLastError() << std::endl;
	}
	CloseHandle(hFile);
	return true;
}



BOOL FileRead(LPCTSTR toRead, FileReadMod Mod)
{
	char buffer;
	HANDLE hFile;
	DWORD pdw = NULL;
	BOOL not_empty = false;

	if ((hFile = CreateFile(toRead, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
	{
		std::cout << "\nFile creation failed with error " << GetLastError() << std::endl;
	}

	do
	{
		ReadFile(hFile, (char*)&buffer, sizeof(buffer), &pdw, NULL);
		if (pdw == 0)
		{
			break;
		}
		if (!not_empty) not_empty = true;
		if (Mod == Display) std::cout << buffer;
		else if (Mod == Statystics) WordCount(buffer);
	} while (pdw != 0);

	CloseHandle(hFile);
	return not_empty;
}

char WordShift(char buffer, Mod mod)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (mod == Encoding)
			{
				if (buffer == WordArray[i][j])
				{
					buffer = KeyArray[i][j];
					return buffer;
				}
				
			}
			else if (mod == Decoding)
			{
				if (buffer == KeyArray[i][j])
				{
					buffer = WordArray[i][j];
					return buffer;
				}
			}
			
		}
	}
	return buffer;
}

void ArrayDecoding(char buffer_1)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			KeyArray[i][j] = WordArray[i][j];
		}
	}

	int buffer_1_x;
	int buffer_1_y;

	char buffer_2 = MostCommonWord(KeyArray, CounterArray);
	int buffer_2_x;
	int buffer_2_y;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (buffer_1 == WordArray[i][j])
			{
				buffer_1_x = j;
				buffer_1_y = i;
			}
			if (buffer_2 == WordArray[i][j])
			{
				buffer_2_x = j;
				buffer_2_y = i;
			}
		}
	}


	int shift_x = buffer_1_x - buffer_2_x;
	if (shift_x > 0)
	{
		while (shift_x > 0)
		{
			ArrayShift(Right, Key);
			shift_x--;
		}
	}
	if (shift_x < 0)
	{
		while (shift_x < 0)
		{
			ArrayShift(Left, Key);
			shift_x++;
		}
	}

	int shift_y = buffer_1_y - buffer_2_y;
	if (shift_y > 0)
	{
		while (shift_y > 0)
		{
			ArrayShift(Down, Key);
			shift_y--;
		}
	}
	if (shift_y < 0)
	{
		while (shift_y < 0)
		{
			ArrayShift(Up, Key);
			shift_y++;
		}
	}

	FileEncoding("D:\\_C0D3D_IN.txt", "D:\\_C0D3D_OUT.TXT", Decoding);
}

void FileEncoding(LPCTSTR toRead, LPCTSTR toWrite, Mod mod)
{
	char buffer;
	HANDLE hFile;
	DWORD pdw = NULL;

	FileWipe(toWrite);

	if ((hFile = CreateFile(toRead, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
	{
		std::cout << "\nFile creation failed with error " << GetLastError() << std::endl;
	}

	do
	{
		ReadFile(hFile, (char*)&buffer, sizeof(buffer), &pdw, NULL);
		if (pdw == 0)
		{
			break;
		}
		buffer = WordShift(buffer, mod);
		FileWrite(toWrite, buffer);

	} while (pdw != 0);
	CloseHandle(hFile);
}

void ArrayDisplay(char Array[5][6])
{
	std::cout << std::endl;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			std::cout << Array[i][j] << " ";
		}
		std::cout << std::endl;
	}

	return;
}

void ArrayDisplay(char ArrayChar[5][6], int ArrayInt[5][6])
{
	std::cout << std::endl;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			std::cout << ArrayChar[i][j] << " - " << ArrayInt[i][j] << " ";
		}
		std::cout << std::endl;
	}

	return;
}

char MostCommonWord(char ArrayChar[5][6], int ArrayInt[5][6])
{
	int maxInt = 0;
	char maxChar = 0;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (ArrayInt[i][j] > maxInt)
			{
				maxInt = ArrayInt[i][j];
				maxChar = ArrayChar[i][j];
			}
		}
	}
	std::cout << "\nСамая распространённая буква: " << maxChar << " - " << maxInt << std::endl;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			CounterArray[i][j] = 0;
		}
	}

 	return maxChar;
}



void ArrayShift(Shift shift, ShiftMod mod)
{
	if(mod==NewKey)
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
			KeyArray[i][j] = WordArray[i][j];
	}

	switch (shift)
	{

	case Left:
	{
		char First = KeyArray[0][0];

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 6; j++)
				KeyArray[i][j] = KeyArray[i][j+1];
		}

		KeyArray[5-1][6-1] = First;
		break;
	}
		

	case Right:
	{
		char Last = KeyArray[5-1][6-1];

		for (int i = 5-1; i >= 0; i--)
		{
			for (int j = 6-1; j >= 0; j--)
				KeyArray[i][j] = KeyArray[i][j - 1];
		}
		KeyArray[0][0] = Last;
		break;
	}
		

	case Up:
	{
		char Buffer[6];

		for (int i = 0; i < 6; i++) Buffer[i] = KeyArray[0][i];

		for (int i = 0; i < 5 - 1; i++)
		{
			for (int j = 0; j < 6; j++)
				KeyArray[i][j] = KeyArray[i+1][j];
		}

		for (int i = 0; i < 6; i++) KeyArray[4][i] = Buffer[i];

		break;
	}

	case Down:
	{
		char Buffer[6];

		for (int i = 0; i < 6; i++) Buffer[i] = KeyArray[4][i];

		for (int i = 5 - 1; i > 0; i--)
		{
			for (int j = 6 - 1; j >= 0; j--)
				KeyArray[i][j] = KeyArray[i-1][j];
		}

		for (int i = 0; i < 6; i++) KeyArray[0][i] = Buffer[i];

		break;
	}	

	}
}

BOOL ShiftEncription(BOOL first_iteration)
{
	system("cls");

	ShiftMod mod;
	if (first_iteration) mod = NewKey;
	else mod = Key;

	std::cout << "[Начата процедура зашифровки файла методом смещения]" << std::endl;
	std::cout << "\nВ каком направлении необходимо задать смещение?" << std::endl;

	std::cout << "Влево(1)" << std::endl;
	std::cout << "Вправо(2)" << std::endl;
	std::cout << "Вверх(3)" << std::endl;
	std::cout << "Вниз(4)" << std::endl;

	switch (_getch())
	{
	case '1':
		ArrayShift(Left, mod);
		break;
	case '2':
		ArrayShift(Right, mod);
		break;
	case '3':
		ArrayShift(Up, mod);
		break;
	case '4':
		ArrayShift(Down, mod);
		break;
	}
	FileEncoding("D:\\_C0D3D.txt", "D:\\_C0D3D_IN.txt", Encoding);

	std::cout << "\nФайл успешно зашифрован. Для продолжения нажмите любую клавишу."<<std::endl;
	_getch();

	return true;
}

void ShiftDecription()
{
	char vowel[7] = {'О', 'Е', 'А', 'И', 'У', 'Я', 'Ы'};
	for (int i = 0; i < 7; i++)
	{	
		system("cls");
		std::cout << "[Начата процедура расшифровки файла методом смещения]" << std::endl;

		FileRead("D:\\_C0D3D_IN.txt", Statystics);
		ArrayDecoding(vowel[i]);
		FileRead("D:\\_C0D3D_OUT.txt", Display);
		std::cout << "\n\nЕсли результат дешифровки корректен, нажмите 1. В обратном случае - 2";
		switch (_getch())
		{
		case '1':
			return;

		case '2':
			break;
		}
	}
	system("cls");
	std::cout << "Тады хз =(" << std::endl;
	system("pause");
}

BOOL StatusCheck(LPCTSTR file)
{
	if (FileRead(file, NotDisplay)) return true;
	else return false;
}

void Menu()
{
	BOOL first_iteration = true;

	while (1)
	{
		system("cls");
		if (StatusCheck("D:\\_C0D3D.txt")) std::cout << "Статус[Файл готов к работе]" << std::endl;
		else std::cout << "Статус[Файл не готов к работе]" << std::endl;
		std::cout << "\nВыберите пункт меню:" << std::endl;
		std::cout << "Шифрование данных в файле(1)" << std::endl;
		std::cout << "Расшифровка данных в файле(2)" << std::endl;
		std::cout << "Завершить работу(3)" << std::endl;
		switch (_getch())
		{
		case '1':
			if (StatusCheck("D:\\_C0D3D.txt"))
			if (ShiftEncription(first_iteration)) first_iteration = false;
			break;
		case '2':
			if (StatusCheck("D:\\_C0D3D_IN.txt"))
			ShiftDecription();
			break;
		case '3':
			return;
			break;			
		}
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	Menu();

	return 0;
}