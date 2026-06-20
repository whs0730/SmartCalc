#include "utils/NumberFormat.h"
#include "utils/StringUtil.h"
#include "utils/TimeUtil.h"

#include <cassert>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void testStringTrimAndCase() {
    assert(StringUtil::ltrim("  abc  ") == "abc  ");
    assert(StringUtil::rtrim("  abc  ") == "  abc");
    assert(StringUtil::trim("  abc  ") == "abc");
    assert(StringUtil::removeSpaces(" a b\tc\n") == "abc");
    assert(StringUtil::toLower("Sin(X)") == "sin(x)");
    assert(StringUtil::toUpper("sin(x)") == "SIN(X)");
}

void testStringSplitJoinReplace() {
    vector<string> parts = StringUtil::split("a,b,,c", ',');

    assert(parts.size() == 4);
    assert(parts[0] == "a");
    assert(parts[2] == "");
    assert(parts[3] == "c");
    assert(StringUtil::join(parts, "|") == "a|b||c");
    assert(StringUtil::replaceAll("1+2+3", "+", " plus ") == "1 plus 2 plus 3");
}

void testStringCheck() {
    assert(StringUtil::startsWith("SmartCalc", "Smart"));
    assert(StringUtil::endsWith("SmartCalc", "Calc"));
    assert(StringUtil::contains("SmartCalc", "art"));
    assert(StringUtil::isInteger(" -123 "));
    assert(!StringUtil::isInteger("12.3"));
    assert(StringUtil::isNumber("3.14"));
    assert(StringUtil::isNumber("-1e-3"));
    assert(!StringUtil::isNumber("1e"));
}

void testNumberFormat() {
    assert(NumberFormat::formatDouble(3.140000, 6) == "3.14");
    assert(NumberFormat::formatDouble(2.0, 6) == "2");
    assert(NumberFormat::formatFixed(3.1, 3) == "3.100");
    assert(NumberFormat::formatPercent(0.125, 2) == "12.5%");
    assert(NumberFormat::removeTrailingZeros("10.5000") == "10.5");
    assert(NumberFormat::roundTo(3.14159, 2) == 3.14);
    assert(NumberFormat::isClose(0.1 + 0.2, 0.3, 0.000001));
}

void testTimeUtil() {
    time_t sample = 0;

    string date = TimeUtil::formatTimestamp(sample, "%Y-%m-%d");
    string safe = TimeUtil::getFileSafeTime();

    assert(date.size() == 10);
    assert(TimeUtil::getCurrentTime().size() == 19);
    assert(TimeUtil::getCurrentDate().size() == 10);
    assert(TimeUtil::getCurrentTimeOnly().size() == 8);
    assert(safe.find(':') == string::npos);
    assert(TimeUtil::getUnixTimestamp() > 0);
}

int main() {
    testStringTrimAndCase();
    testStringSplitJoinReplace();
    testStringCheck();
    testNumberFormat();
    testTimeUtil();

    cout << "Utils tests passed!" << endl;
    return 0;
}