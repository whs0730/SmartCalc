#include "utils/TimeUtil.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

std::string TimeUtil::getCurrentTime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm localTime;

#ifdef _WIN32
    localtime_s(&localTime, &currentTime);
#else
    localTime_r(&currentTime,&localTime);

#endif

    std::ostringstream output;
    output<<std::put_time(&localTime,"%Y-%m-%d %H:%M:%S");
    return output.str();

}
