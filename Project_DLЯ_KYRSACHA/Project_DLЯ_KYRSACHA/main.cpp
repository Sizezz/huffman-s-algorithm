#include "Huffman_tree.h"
#define encode_output "output_encode.txt"
#define decode_output "output_decode.txt"
#define filename_input "input.txt"
#define debug_mode false
#define show_data false
using namespace std;

/* ��������� ������ �� ����� � string text */
/* "�����������" ���������� (���� ����������)*/
string get_data(const string& filename)
{
	string text;
	fstream input;
	setlocale(LC_ALL, "RU");
	input.open(filename, ios::in);
	while (!input.eof())
	{
		string temp;
		getline(input, temp);
		if (!input.eof())
		{
			temp += '\n';
		}
		text += temp;
	}
	input.close();
	return text;
}

/* �������� �������� */
string get_repeat(string text)
{
	string abc;
	bool exit_flag = 0;
	abc.push_back(text[0]);
	for (int i = 1; i < text.size(); i++)
	{
		exit_flag = 0;
		for (int j = 0; j < abc.size(); j++)
		{
			if (abc[j] == text[i])						//���� � ����� �������� ��� ���� ����� �����
			{
				exit_flag = 1;							//�������, ���� ����� ����� �����
				break;
			}
		}
		if (exit_flag == 1)								//���� �� �������� ����� �����
		{
			continue;									//��������� �� ��������� �������� ��� ����. �����
		}
		else											//���� ����� ������� �� ����
		{
			abc.push_back(text[i]);
			continue;
		}
	}
	return abc;
}

/* ��������� ������� ������� ������������� �������� */
void get_frequency(string text, int* frequencies, string abc)
{
	for (int i = 0; i < abc.size(); i++)
	{
		frequencies[i] = 0;
	}
	for (int j = 0; j < abc.size(); j++)
	{
		for (int i = 0; i < text.size(); i++)
		{
			if (abc[j] == text[i])
			{
				frequencies[j]++;
			}
		}
	}
}

/* ���� ������� ������ � ���������� */
string get_input()
{
	setlocale(LC_ALL, "RU");
	string text;
	cout << "Enter the text: ";
	getline(std::cin, text);
	cout << endl;
	return text;
}

void WriteGreetings()
{
	cout << "Tsurkan Vladimir Sergeevich" << endl
		<< "group 423" << endl
		<< "Course project" << endl;
}

int main()
{
	WriteGreetings();


	/* ����� ���� ����� */
	string choose;
	cout << "press (1) to enter text from the keyboard: " << endl
		<< "press (2) to enter text from the file:" << endl;
	getline(cin, choose);
	cout << endl;
	string text;
	if (choose[0] == '1')
	{
		text = get_input();									//���� � ����������
	}
	else if (choose[0] == '2')
	{
		text = get_data(filename_input);					//���� �� �����
	}
	else
	{
		cout << "incorrect input" << endl;
		exit(1);
	}

	/* �������� ������ ������ */
	string abc = get_repeat(text);
	int* frequencies = new int[abc.size()];
	get_frequency(text, frequencies, abc);

	if (show_data)
	{
		cout << "Text is: " << text << endl;
	}

	if (debug_mode)
	{
		cout << "Alphabet: " << abc << endl;
		cout << "Size of alphabet: " << abc.size() << endl;
		cout << "Frequencies: " << endl;
		for (int i = 0; i < abc.size(); i++)
		{
			cout << abc[i] << " - " << frequencies[i] << endl;
		}
		cout << endl;
	}

	/* ��������� ����������: ���� ������ */
	bool flag_ex = 0;
	if (abc.size() < 2)
	{
		flag_ex = !flag_ex;
	}

	/* ����������� */
	huffman_coding encoding;
	cout << endl << "Character: Code-word" << endl;
	encoding.HuffmanCodes(abc, frequencies, flag_ex);
	encoding.encode_text(text);

	string temp = encoding.get_encode();
	if (show_data)
	{
		cout << endl << "Code-string: " << temp;
	}
	encoding.output_file(encode_output, true);

	/* �������������� */
	temp = encoding.decode_text(temp, flag_ex);
	if (show_data)
	{
		cout << endl << "Decode-string: " << temp << endl;
	}
	encoding.output_file(decode_output, false);
	return 0;
}