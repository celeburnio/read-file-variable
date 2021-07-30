#include <string>
#include <syslog.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

bool readVariable(std::string var, std::string &value)
{
	std::ifstream fileBoxInfo;
	std::stringstream buffer;
	std::string fileName("/boxinfo/");
	bool ret = false;
	fileName.append(var);
	fileBoxInfo.open(fileName); //open the input file
	if (fileBoxInfo.is_open()) 
	{
		buffer << fileBoxInfo.rdbuf();
		fileBoxInfo.close();
		value = buffer.str();
        syslog(LOG_INFO, "readVariable: value=%s", value.c_str());
		ret = true;
	}
	return ret;
}

void retryReadVariable(std::string var, std::string &value, int32_t retries = 5, uint32_t millisecs= 100)
{
	int max_retries = retries;
	do
	{
		readVariable(var, value);
		syslog(LOG_INFO, "Reading %s = %s", var.c_str(), value.c_str());
		if (value.length()==0) usleep(millisecs*1000);
	}
	while((0 == value.length()) && --max_retries);
}


int main() {
    std::string countryCode;
	std::stringstream ss;
    
	retryReadVariable("CountryCode", countryCode);

    syslog(LOG_INFO, "CountryCode readed: %s", countryCode.c_str());

	std::transform(countryCode.begin(), countryCode.end(), countryCode.begin(), [](unsigned char c){ return std::tolower(c); });
    syslog(LOG_INFO, "CountryCode after transform: %s", countryCode.c_str());
    return 0;
}