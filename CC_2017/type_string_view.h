#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include <string_view>
#include <fstream>
#include <filesystem>
#include <experimental\filesystem>

namespace type_string_view
{
	/*
		���ڿ��� ���� �������� �ʴ� ���۷���
		�ٸ� ��򰡿��� �����ϰ� �ִ� ���ڿ��� ���縦 ���ϱ� ����
		���ڿ� ��ܿ� �߻�ȭ�� �����ϴµ� �����ϰ� ��� (ex:�Ľ�)

		constexpr void remove_prefix(size_type n);	���λ� ����
		constexpr void remove_suffix(size_type n);  ���̻� ����
	*/
	using namespace std::experimental::filesystem::v1;
	using byte = unsigned char;

	void println(const string& str)
	{
		cout << str << endl;
	}

	void println_overloading(const char* str)
	{
		cout << str << endl;
	}

	void opt_println(const string_view& str)
	{
		cout << str << endl;
	}

	bool GetFiles(vector<path>& v, const path& Dir, bool bSearchSubDirectories = true)
	{
		if (!is_directory(Dir)) return false;
	
		for (const auto& entry : directory_iterator{ Dir })
		{
			if (is_regular_file(entry.status()))
				v.push_back(entry.path());

			else if (is_directory(entry.status()))
				GetFiles(v, entry.path(), bSearchSubDirectories);
		}
	
		return true;
	}

	void FilePathRead(vector<wstring>& out, const std::wstring path)
	{
		WIN32_FIND_DATA fd;
		std::wstring start_path = path + std::wstring(TEXT("*.*"));
		HANDLE hFindHande = FindFirstFile(start_path.c_str(), &fd);

		//������ ��
		//if (hFindHande != INVALID_HANDLE_VALUE) return;

		while (FindNextFile(hFindHande, &fd))
		{
			auto index = start_path.find(TEXT("*"));

			std::wstring new_path;
			new_path.reserve(start_path.size());

			auto count = 0;
			auto size = (start_path.size() - 3);
			for (auto i = 0U; i < size; ++i)
			{
				if (index == i) count += 3;
				new_path.push_back(start_path[i + count]);
			}

			std::wstring save_path = new_path + std::wstring(fd.cFileName);

			auto attribute = fd.dwFileAttributes;

			if (attribute | FILE_ATTRIBUTE_DIRECTORY)
			{
				if (fd.cFileName[0] == '.')continue;
				out.push_back(save_path);
			}

			//if (attribute | FILE_ATTRIBUTE_ARCHIVE)
			//	out.push_back(save_path);

		}

		FindClose(hFindHande);
	}


	void getFileName(string_view str)
	{
		str.remove_suffix(4);
		cout << str << endl;
	}

	void getFileName(wstring_view str)
	{
		str.remove_suffix(4);
		if (str[str.size() - 1] == '.')
			wcout << L"--> error : " << str << endl;
		else
			wcout << str << endl;
	}

	void start()
	{
		string str{ "hellow world" };

		println(str);			 // ���� ����
		println("hellow world"); // const char* -> string -> string.c_str()

		// 1��
		println_overloading("hellow world");
		println_overloading(str.c_str());


		// upgarade
		opt_println(str);			 // ���� ����
		opt_println("hellow world"); // �����


		// cout			
		getFileName("dnf.exe");

		vector<wstring> vPath;
		FilePathRead(vPath, L"..\\font\\");

		// for (auto str : vPath)
		// {
		// 	cout << str << "\t Name";
		// 	getFileName(str);
		// 	cout << endl;
		// }

		vector<path> v;
		GetFiles(v, "..\\font\\");
		
		for (auto p : v)
		{
			cout << p << "\t Name";
			getFileName(p.c_str());
		}
	}

}