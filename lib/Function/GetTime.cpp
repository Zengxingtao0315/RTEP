/*****************************************************************************
* | File      	:   GetTime.cpp
* | Author      :   xingtao Zeng
* | Function    :   Get local time
* | Info        :
******************************************************************************/

#include "GetTime.hpp"

/*******************************************************************************
function:
            Get local time
*******************************************************************************/
PAINT_TIME Time::getLocalTime() {
    PAINT_TIME time;
	std::time_t now;
    std::tm *local;

    std::time(&now);
    local = std::localtime(&now);

    // 提取需要的时间信息
    time.Hour = local->tm_hour;
    time.Min = local->tm_min;
	time.Sec = local->tm_sec;
	return time;
}



float SunlightDurationRecorder::getSunlightDurationInHours(bool digitalValue) {
	auto now = std::chrono::system_clock::now();
	if (!initialized_) {
		// 第一次调用函数，初始化记录信息
		start_time_ = now;
		duration_0_ = std::chrono::duration<int, std::ratio<1, 1>>(0);
		last_reset_time_ = now;
		initialized_ = true;
	} else {
		// 检查是否到达新的一天，如果是则重置时长记录
		auto time_since_last_reset = now - last_reset_time_;
		if (time_since_last_reset >= std::chrono::hours(24)) {
			duration_0_ = std::chrono::duration<int, std::ratio<1, 1>>{0};
			last_reset_time_ = now;
		}
	}

	// 根据 digital 记录时长
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - start_time_);
	if (digitalValue == 0) {
		duration_0_ += duration;
	} 
	if (digitalValue == 1) {
        start_time_ = now;
    }
	
	int light_duration = duration_0_.count();
	std::chrono::seconds Drt{light_duration};  // 
    float hours = std::chrono::duration_cast<std::chrono::hours>(Drt).count();
    std::cout << hours << " hours" << std::endl;
	return hours;
	
}

