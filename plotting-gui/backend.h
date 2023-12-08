#pragma once
#include <vector>
//functions:
//getting current time in utc
double GetCurrentUTCTimeSeconds(); 
//converting utc time in seconds. from seconds to date and time (receives utc time in seconds and spits a const char.
const char* UtcTimeInSecondsToDateTime(double time);
//write a function to convert utc time form second form to normal format (D/M/Y  Hour:minute:second)


//classes:
class DataStreamBack {
private:
	const char* Name;
public:
	std::vector<double> DataBuffer;
	std::vector<double> TimeBuffer;
	DataStreamBack(const char* _Name);
	void LoadDataPoint();  // it loads a data point with it's measurement time in the end of both DataBuffer and TimeBuffer
	void SaveDataStream(const char * Name);  // this method saves the DataBuffer and the TimeBuffer into a csv file with Name as its name carrying the name of the Datastream if the csv doesn"t exist it creates it. if not it records into the existing one by adding the rest of data and keeping what was inside before
	void ClearBuffers();  // this method deletes everything that is inside the data stream the buffers are cleared when this method is called.

	                     
};
