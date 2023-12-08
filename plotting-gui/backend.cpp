#pragma once
#include "backend.h"
#include "DATA_generator.h"
#include <iostream>
#include <ctime>
#include <string>
#include <iomanip>
#include <chrono>
#include <time.h>
#include <stdio.h>
#include <fstream>
#include <iomanip>
#include <sstream>
//temporary
#include <limits>
//end temporary
//functions 
// In the entire program. unix timestamp is used for it's practical and easy usage. (time is manipulated as the total number of seconds elapsed from the start f
// this function gives time in unix timestamp ( a way to tore time as the total number of seconds from 1970 utc time, quite efficient for doing quick operations)
double GetCurrentUTCTimeSeconds() {              //!!! this is microsecond precision, you might want to modify later for sub micro precision.
	// Get the current system time with microsecond precision
	auto now = std::chrono::system_clock::now();

	// Convert the time_point to a duration representing microseconds
	auto us = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch());

	// Extract the microseconds part from the duration
	auto microseconds = us.count() % 1000000;

	// Convert the time_t object to UTC time represented by struct tm
	std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

	// Format the time in UTC with microsecond precision
	std::tm utcTime;
	gmtime_s(&utcTime, &currentTime); // For Windows
	// Alternatively, you can use gmtime(&currentTime); for non-Windows systems.

	// Calculate the fractional seconds including microseconds
	double fractionalSeconds = static_cast<long double>(microseconds) / 1000000.0;

	// Calculate the total UTC time in seconds with microsecond precision
	double utcTimeSeconds = static_cast<long double>(currentTime) + fractionalSeconds;

	return utcTimeSeconds;
}
//next function converts unix time (double storing the number of seconds from 1970 january 1) to human readable utc time using iso800something. it resturns a const char*
const char* UtcTimeInSecondsToDateTime(double unix_time) {
	time_t unix_seconds = (time_t)unix_time;
	int microseconds = (int)((unix_time - (double)unix_seconds) * 1000000); // by changin the number 10^6 to something else u set the precision of display.(microseconds milliseconds etc...)

	// Calculate the number of days since January 1, 1970 (Unix epoch)
	long days = unix_seconds / 86400;

	// Calculate the seconds within the current day
	int seconds = unix_seconds % 86400;

	// Convert to struct tm
	struct tm timeinfo;
	gmtime_s(&timeinfo, &unix_seconds);

	// Format the result as a string
	static char result[30]; // Adjust the size as needed
	strftime(result, sizeof(result), "%Y-%m-%d %H:%M:%S", &timeinfo); 

	// Append milliseconds to the result
	snprintf(result + 19, sizeof(result) - 19, ".%03d", microseconds);

	return result;
}
//class DataStreamBack
DataStreamBack::DataStreamBack(const char* _Name) {
	Name = _Name;
} 
//temporary definition for testing
void DataStreamBack::LoadDataPoint() {
	std::vector<double> var = generate_data_point(3);
	TimeBuffer.push_back(var[0]);
	DataBuffer.push_back(var[1]);

}
// the name needs to be somthing.csv
void DataStreamBack::SaveDataStream(const char* name) {
	std::ofstream file;
	file.open(name);
	file << "Time, Data" << std::endl;
	for (int i = 0; i<TimeBuffer.size(); i++) {
		long double a = 81726.123456789123;
		file << TimeBuffer[i] <<","<<DataBuffer[i]<<","<<a<< std::endl;

	}
	file.close();
}

