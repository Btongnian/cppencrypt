/*
* �ļ���:Source.cpp
* ��;:���ܽ����ַ���
* ʱ��:2023��3��26��
* Github:https://github.com/Btongnian/cppencrypt
* Gitee:https://gitee.com/kao_shan_yao/cppencrypt
* ��----------------------------------------------------------------------------------------------------------��
* |          _____                      _____                      _____                      _____          |
* |         /\    \                    /\    \                    /\    \                    /\    \         |
* |        /||\    \                  /||\    \                  /||\____\                  /||\    \        |
* |       /||||\    \                /||||\    \                /|||||   |                 /||||\    \       |
* |      /||||||\    \              /||||||\    \              /||||||   |                /||||||\    \      |
* |     /|||/\|||\    \            /|||/\|||\    \            /|||||||   |               /|||/\|||\    \     |
* |    /|||/__\|||\    \          /|||/  \|||\    \          /|||/||||   |              /|||/  \|||\    \    |
* |    \|||\   \|||\    \        /|||/    \|||\    \        /|||/ ||||   |             /|||/    \|||\    \   |
* |  ___\|||\   \|||\    \      /|||/    / \|||\    \      /|||/  ||||___|______      /|||/    / \|||\    \  |
* | /\   \|||\   \|||\    \    /|||/    /   \|||\    \    /|||/   |||||||||\    \    /|||/    /   \|||\ ___\ |
* |/||\   \|||\   \|||\____\  /|||/____/     \|||\____\  /|||/    ||||||||||\____\  /|||/____/     \||||   | |
* |\|||\   \|||\   \||/    /  \|||\    \      \||/    /  \||/    / -----/|||/    /  \|||\    \     /||||___| |
* | \|||\   \|||\   \/____/    \|||\    \      \/____/    \/____/      /|||/    /    \|||\    \   /|||/    / |
* |  \|||\   \|||\    \         \|||\    \                            /|||/    /      \|||\    \ /|||/    /  |
* |   \|||\   \|||\____\         \|||\    \                          /|||/    /        \|||\    /|||/    /   |
* |    \|||\  /|||/    /          \|||\    \                        /|||/    /          \|||\  /|||/    /    |
* |     \|||\/|||/    /            \|||\    \                      /|||/    /            \|||\/|||/    /     |
* |      \||||||/    /              \|||\    \                    /|||/    /              \||||||/    /      |
* |       \||||/    /                \|||\____\                  /|||/    /                \||||/    /       |
* |        \||/    /                  \||/    /                  \||/    /                  \||/    /        |
* |         \/____/                    \/____/                    \/____/                    \/____/         |
* ��----------------------------------------------------------------------------------------------------------��
*/
#include <fstream>//��ȡ�ļ�������
#include <iostream>//����ַ�������
#include <string>//�ַ���������
#include <codecvt>//IO UTF-8�ļ�
#include <comutil.h>//IO UTF-8�ļ�
#pragma comment(lib, "comsuppw.lib")//IO UTF-8�ļ��ľ�̬��

using namespace std;//ȫ�������ռ�

//���ܺ���:��Ҫ���ܵ��ַ��� ��Կ
wstring encrypt(const wstring& plaintext, const wstring& key)
{
	wstring ciphertext = plaintext;
	for (int i = 0; i < plaintext.size(); ++i)
	{
		ciphertext[i] = plaintext[i] ^ key[i % key.size()];
	}
	return ciphertext;
}
//���ܺ���:��Ҫ���ܵ��ַ��� ��Կ
wstring decrypt(const wstring& ciphertext, const wstring& key) {
	wstring plaintext = ciphertext;
	for (int i = 0; i < ciphertext.size(); ++i) {
		plaintext[i] = ciphertext[i] ^ key[i % key.size()];
	}
	return plaintext;
}

//����ļ�:�ļ��� �ַ���
void woutput(const string& filename, const wstring& outstr)
{
	wofstream out;
	out.imbue(std::locale(out.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::little_endian>));
	out.open(filename);
	if (!out.is_open())
	{
		cout << "δ��\n";
		system("pause");
		exit(1);
	}
	out << outstr;
	out.close();
}
//�����ļ�:�ļ��� ����:�ַ���
wstring winput(const string& filename)
{
	wifstream in;
	in.imbue(std::locale(in.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::little_endian>));
	in.open(filename);
	if (!in.is_open())
	{
		cout << "δ��\n";
		system("pause");
		exit(1);
	}
	wstring temp, add;
	while (getline(in, temp))
	{
		add += temp;
		add += '\n';
	}
	add.pop_back();
	in.close();
	return add;
}


int main()
{
	string infilename("δ����.txt");//δ�����ļ���
	string outfilename("�Ѽ���.data");//�Ѽ����ļ���
	wstring key = L"1234567890";//��Կ ����ʹ������

	//��ȡδ���ܵ�UTF-8�ļ�������������µ��ļ�
	woutput(outfilename, encrypt(winput(infilename), key));

	//����wcout���wstring
	std::locale loc("chs");
	std::wcout.imbue(loc);

	//��ȡ�Ѽ��ܵ�UTF-8�ļ����ܲ����
	wcout << decrypt(winput(outfilename), key);
	return 0;
}