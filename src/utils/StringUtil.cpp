#include "utils/StringUtil.h"

#include <cctype>

using namespace std;

string StringUtil::ltrim(const string& text) {
    int start = 0;

    // 从左侧跳过所有空白字符。
    while (start < static_cast<int>(text.size())
        && isspace(static_cast<unsigned char>(text[start]))) {
        start++;
    }

    return text.substr(start);
}

string StringUtil::rtrim(const string& text) {
    int end = static_cast<int>(text.size()) - 1;

    // 从右侧向前找到最后一个非空白字符。
    while (end >= 0 && isspace(static_cast<unsigned char>(text[end]))) {
        end--;
    }

    return text.substr(0, end + 1);
}

string StringUtil::trim(const string& text) {
    return rtrim(ltrim(text));
}

string StringUtil::removeSpaces(const string& text) {
    string result;

    for (int i = 0; i < static_cast<int>(text.size()); i++) {
        if (!isspace(static_cast<unsigned char>(text[i]))) {
            result += text[i];
        }
    }

    return result;
}

string StringUtil::toLower(const string& text) {
    string result = text;

    for (int i = 0; i < static_cast<int>(result.size()); i++) {
        result[i] = static_cast<char>(tolower(static_cast<unsigned char>(result[i])));
    }

    return result;
}

string StringUtil::toUpper(const string& text) {
    string result = text;

    for (int i = 0; i < static_cast<int>(result.size()); i++) {
        result[i] = static_cast<char>(toupper(static_cast<unsigned char>(result[i])));
    }

    return result;
}

vector<string> StringUtil::split(const string& text, char delimiter) {
    vector<string> parts;
    string current;

    // 保留空片段，例如 "a,,b" 会得到三个部分。
    for (int i = 0; i < static_cast<int>(text.size()); i++) {
        if (text[i] == delimiter) {
            parts.push_back(current);
            current.clear();
        }
        else {
            current += text[i];
        }
    }

    parts.push_back(current);
    return parts;
}

string StringUtil::join(const vector<string>& parts, const string& delimiter) {
    string result;

    for (int i = 0; i < static_cast<int>(parts.size()); i++) {
        if (i > 0) {
            result += delimiter;
        }
        result += parts[i];
    }

    return result;
}

string StringUtil::replaceAll(const string& text, const string& oldText, const string& newText) {
    if (oldText.empty()) {
        return text;
    }

    string result;
    int pos = 0;
    int oldLength = static_cast<int>(oldText.size());

    // 手动向后扫描，避免替换后的内容再次参与匹配。
    while (pos < static_cast<int>(text.size())) {
        if (text.compare(pos, oldLength, oldText) == 0) {
            result += newText;
            pos += oldLength;
        }
        else {
            result += text[pos];
            pos++;
        }
    }

    return result;
}

bool StringUtil::startsWith(const string& text, const string& prefix) {
    if (prefix.size() > text.size()) {
        return false;
    }

    return text.compare(0, prefix.size(), prefix) == 0;
}

bool StringUtil::endsWith(const string& text, const string& suffix) {
    if (suffix.size() > text.size()) {
        return false;
    }

    return text.compare(text.size() - suffix.size(), suffix.size(), suffix) == 0;
}

bool StringUtil::contains(const string& text, const string& keyword) {
    return text.find(keyword) != string::npos;
}

bool StringUtil::isInteger(const string& text) {
    string value = trim(text);
    if (value.empty()) {
        return false;
    }

    int start = 0;
    if (value[0] == '+' || value[0] == '-') {
        start = 1;
    }

    if (start == static_cast<int>(value.size())) {
        return false;
    }

    for (int i = start; i < static_cast<int>(value.size()); i++) {
        if (!isdigit(static_cast<unsigned char>(value[i]))) {
            return false;
        }
    }

    return true;
}

bool StringUtil::isNumber(const string& text) {
    string value = trim(text);
    if (value.empty()) {
        return false;
    }

    int i = 0;
    bool hasDigit = false;
    bool hasDot = false;
    bool hasExponent = false;

    if (value[i] == '+' || value[i] == '-') {
        i++;
    }

    // 支持普通小数和科学计数法，例如 3.14、-1e-3。
    while (i < static_cast<int>(value.size())) {
        char ch = value[i];

        if (isdigit(static_cast<unsigned char>(ch))) {
            hasDigit = true;
            i++;
        }
        else if (ch == '.' && !hasDot && !hasExponent) {
            hasDot = true;
            i++;
        }
        else if ((ch == 'e' || ch == 'E') && !hasExponent && hasDigit) {
            hasExponent = true;
            i++;

            if (i < static_cast<int>(value.size()) && (value[i] == '+' || value[i] == '-')) {
                i++;
            }

            bool exponentHasDigit = false;
            while (i < static_cast<int>(value.size())
                && isdigit(static_cast<unsigned char>(value[i]))) {
                exponentHasDigit = true;
                i++;
            }

            if (!exponentHasDigit) {
                return false;
            }
        }
        else {
            return false;
        }
    }

    return hasDigit;
}
