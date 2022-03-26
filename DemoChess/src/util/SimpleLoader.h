#pragma once

#include <string>
#include <map>

// For TrVSnk, only float and wstring is needed.
class SimpleLoader
{
private:
	template<typename T>
	struct RestrictType {
		typedef void rtype;
	};
	template<>
	struct RestrictType<int> {
		typedef int rtype;
	};
	template<>
	struct RestrictType<float> {
		typedef float rtype;
	};
	template<>
	struct RestrictType<std::wstring> {
		typedef std::wstring rtype;
	};
public:
	SimpleLoader();
	~SimpleLoader();
	SimpleLoader(const std::wstring& fileName);
public:
	void load(const std::wstring& fileName);
	void unload();
public:
	template<typename T>
	typename RestrictType<T>::rtype get(const std::wstring& key) const
	{
		return;
	}
	template<>
	typename RestrictType<int>::rtype get<int>(const std::wstring& key) const
	{
		auto search = datamap.find(key);
		if (search != datamap.end()) {
			std::wstring s(search->second.start, search->second.end - search->second.start);
			return std::stoi(s);
		}
		throw;
	}
	template<>
	typename RestrictType<float>::rtype get<float>(const std::wstring& key) const
	{
		auto search = datamap.find(key);
		if (search != datamap.end()) {
			std::wstring s(search->second.start, search->second.end - search->second.start);
			return std::stof(s);
		}
		throw;
	}
	template<>
	typename RestrictType<std::wstring>::rtype get<std::wstring>(const std::wstring& key) const
	{
		auto search = datamap.find(key);
		if (search != datamap.end()) {
			return std::wstring(search->second.start, search->second.end - search->second.start);
		}
		throw;
	}
private:
	void parse();
private:
	struct Valtype { wchar_t* start; wchar_t* end; };
	std::map<std::wstring, Valtype> datamap;
	wchar_t* fileData;
	size_t fileDataLen;
};
