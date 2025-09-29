#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdint>
#include <Windows.h>

void Print(const std::string& str = "");
void Print(const char* str);

// 文字列を変換する関数
std::wstring ConvertString(const std::string& str);
std::string ConvertString(const std::wstring& str);
