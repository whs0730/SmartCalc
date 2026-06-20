#pragma once

#include <string>
#include <vector>

using namespace std;

// 字符串工具类，集中放置常用的文本处理函数。
class StringUtil {
public:
    // 空白字符处理。
    static string ltrim(const string& text);
    static string rtrim(const string& text);
    static string trim(const string& text);
    static string removeSpaces(const string& text);

    // 大小写转换。
    static string toLower(const string& text);
    static string toUpper(const string& text);

    // 字符串拆分、拼接和替换。
    static vector<string> split(const string& text, char delimiter);
    static string join(const vector<string>& parts, const string& delimiter);
    static string replaceAll(const string& text, const string& oldText, const string& newText);

    // 简单匹配判断。
    static bool startsWith(const string& text, const string& prefix);
    static bool endsWith(const string& text, const string& suffix);
    static bool contains(const string& text, const string& keyword);

    // 数字字符串判断。
    static bool isInteger(const string& text);
    static bool isNumber(const string& text);
};
