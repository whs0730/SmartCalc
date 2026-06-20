#include "utils/TimeUtil.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

namespace {
    tm toLocalTime(time_t timestamp) {
        tm localTime;

#ifdef _WIN32
        // Windows 和其他系统的本地时间转换函数不同，这里统一封装。
        localtime_s(&localTime, &timestamp);
#else
        localtime_r(&timestamp, &localTime);
#endif

        return localTime;
    }
}

string TimeUtil::getCurrentTime() {
    return formatCurrentTime("%Y-%m-%d %H:%M:%S");
}

string TimeUtil::getCurrentDate() {
    return formatCurrentTime("%Y-%m-%d");
}

string TimeUtil::getCurrentTimeOnly() {
    return formatCurrentTime("%H:%M:%S");
}

string TimeUtil::getFileSafeTime() {
    // 文件名中不能安全使用冒号，所以这里用横线分隔时分秒。
    return formatCurrentTime("%Y-%m-%d_%H-%M-%S");
}

long long TimeUtil::getUnixTimestamp() {
    auto now = chrono::system_clock::now();
    return static_cast<long long>(chrono::system_clock::to_time_t(now));
}

string TimeUtil::formatCurrentTime(const string& format) {
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    return formatTimestamp(currentTime, format);
}

string TimeUtil::formatTimestamp(time_t timestamp, const string& format) {
    tm localTime = toLocalTime(timestamp);
    ostringstream output;
    output << put_time(&localTime, format.c_str());
    return output.str();
}
