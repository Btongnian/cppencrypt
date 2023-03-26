/*
* 文件名:Source.cpp
* 用途:加密解密字符串
* 时间:2023年3月26日
* Github:https://github.com/Btongnian/cppencrypt
* Gitee:https://gitee.com/kao_shan_yao/cppencrypt
* █----------------------------------------------------------------------------------------------------------█
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
* █----------------------------------------------------------------------------------------------------------█
*/
#include <fstream>//读取文件包含库
#include <iostream>//输出字符包含库
#include <string>//字符串包含库
#include <codecvt>//IO UTF-8文件
#include <comutil.h>//IO UTF-8文件
#pragma comment(lib, "comsuppw.lib")//IO UTF-8文件的静态库

using namespace std;//全局命名空间

//加密函数:需要加密的字符串 秘钥
wstring encrypt(const wstring& plaintext, const wstring& key)
{
	wstring ciphertext = plaintext;
	for (int i = 0; i < plaintext.size(); ++i)
	{
		ciphertext[i] = plaintext[i] ^ key[i % key.size()];
	}
	return ciphertext;
}
//解密函数:需要解密的字符串 秘钥
wstring decrypt(const wstring& ciphertext, const wstring& key) {
	wstring plaintext = ciphertext;
	for (int i = 0; i < ciphertext.size(); ++i) {
		plaintext[i] = ciphertext[i] ^ key[i % key.size()];
	}
	return plaintext;
}

//输出文件:文件名 字符串
void woutput(const string& filename, const wstring& outstr)
{
	wofstream out;
	out.imbue(std::locale(out.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::little_endian>));
	out.open(filename);
	if (!out.is_open())
	{
		cout << "未打开\n";
		system("pause");
		exit(1);
	}
	out << outstr;
	out.close();
}
//输入文件:文件名 返回:字符串
wstring winput(const string& filename)
{
	wifstream in;
	in.imbue(std::locale(in.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::little_endian>));
	in.open(filename);
	if (!in.is_open())
	{
		cout << "未打开\n";
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
	string infilename("未加密.txt");//未加密文件名
	string outfilename("已加密.data");//已加密文件名
	wstring key = L"0";//秘钥 尽量使用较小数字

	//读取未加密的UTF-8文件并加密输出到新的文件
	woutput(outfilename, encrypt(winput(infilename), key));

	//设置wcout输出wstring
	std::locale loc("chs");
	std::wcout.imbue(loc);

	//读取已加密的UTF-8文件解密并输出
	wcout << decrypt(winput(outfilename), key);
	return 0;
}
