#pragma once

#include <ctime>
#include <string>

using namespace std;

// 时间工具类，供历史记录和文件命名使用。
class TimeUtil {
public:
    static string getCurrentTime();
    static string getCurrentDate();
    static string getCurrentTimeOnly();
    static string getFileSafeTime();
    static long long getUnixTimestamp();

    static string formatCurrentTime(const string& format);
    static string formatTimestamp(time_t timestamp, const string& format);
};
