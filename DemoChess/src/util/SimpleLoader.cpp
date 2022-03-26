#include <tchar.h>

#include <fstream>

#include "SimpleLoader.h"


SimpleLoader::SimpleLoader()
	:fileData(0), fileDataLen(0), datamap{}
{

}

SimpleLoader::~SimpleLoader()
{
	unload();
}

SimpleLoader::SimpleLoader(const std::wstring& fileName)
	:SimpleLoader()
{
	load(fileName);
}

void SimpleLoader::load(const std::wstring& fileName)
{
	if (fileData)
		unload();
	// Table: https://docs.moodle.org/dev/Table_of_locales
	/*
	* Usually a locale identifier consists of at least a language identifier and a region identifier.
	* The general syntax for locales is:
		language[_region][.charset]
	*/
	std::locale::global(std::locale(""));
	std::wifstream fs(fileName);
	fs.imbue(std::locale("zh_CN.UTF-8"));
	if (!fs.is_open())
		return;
	/*
	* streampos count 2 for \n\r, maybe more for Chinese Char
	* but wifstream.read, wifstream.get translate \n\r to \n and bytes to Char with locale
	* Don't use seekg-tellg to get size
	*/
	wchar_t _tS = 0;
	std::wstring temp;
	while (!fs.eof()) {
		fs.get(_tS);
		temp += _tS;
	}
	temp.pop_back();
	fileDataLen = temp.size() + 1;
	fileData = new wchar_t[fileDataLen];
	rsize_t n = (fileDataLen - 1) * sizeof(wchar_t);
	memcpy_s(fileData, n, temp.c_str(), n);
	fileData[fileDataLen - 1] = 0;
	fs.close();
	parse();
}

void SimpleLoader::unload()
{
	if (fileData) {
		delete[] fileData;
		fileData = 0;
		datamap.clear();
	}
	fileDataLen = 0;
}

void SimpleLoader::parse()
{
	if (!fileData)
		return;
	const wchar_t _b1 = _T(' ');
	const wchar_t _b2 = _T('\t');
	const wchar_t _newline = _T('\n');
	const wchar_t _eq = _T('=');
	const wchar_t _comm = _T('#');
	const wchar_t _0 = 0;
	const size_t _justend = fileDataLen - 1;
	wchar_t* p = &fileData[0];
	enum class What { KeyB = 1, KeyE, ValB, ValE, NextKey, EOS };
	What findwhat = What::KeyB;
	std::wstring key;
	for (size_t i = 0; i < fileDataLen; ++i) {
		const wchar_t& cur = fileData[i];
		switch (findwhat)
		{
			//find key begin
		case What::KeyB:
			if (cur != _b1 && cur != _b2 && cur != _newline) {
				p = &fileData[i];
				if (cur == _comm) {
					findwhat = What::EOS;
				}
				else if (cur == _0) {
					i = _justend;
				}
				else {
					findwhat = What::KeyE;
				}
			}
			break;
			//find key end
		case What::KeyE:
			if (cur == _b1 || cur == _b2 || cur == _eq) {
				key = std::move(std::wstring(p, &cur - p));
				findwhat = What::ValB;
			}
			break;
			//find end of skipping
		case What::EOS:
			if (cur == _newline) {
				while (fileData[i] == _b1 || fileData[i] == _b2 || fileData[i] == _newline)
					++i;
				--i;
				findwhat = What::KeyB;
			}
			break;
			//find value begin
		case What::ValB:
			if (cur != _eq && cur != _b1 && cur != _b2) {
				p = &fileData[i];
				findwhat = What::ValE;
			}
			break;
			//find value end
		case What::ValE:
			if (cur == _b1 || cur == _b2 || cur == _newline || cur == _0) {
				datamap[key] = { p, &fileData[i] };
				findwhat = What::NextKey;
			}
			break;
			//find next key
		case What::NextKey:
			if (cur != _b1 && cur != _b2 && cur != _newline) {
				if (cur == _comm) {
					findwhat = What::EOS;
				}
				else {
					findwhat = What::KeyB;
				}
				--i;
			}
			break;
		default:
			break;
		}
		if (i == _justend && findwhat == What::ValE) {
			datamap[key] = { p, &fileData[i] + 1 };
		}
	}
}
