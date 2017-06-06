#include "ini_parser.h"


namespace qh
{ 
	void INIParser::Split(const std::string& str, std::vector<std::string>& results, const std::string& line_seperator)
	{
		size_t pos = 0, lastpos = 0, length = str.length();
		while(lastpos < length + 1)
		{
			pos = str.find_first_of(line_seperator,lastpos);
			if(pos == std::string::npos)
			{
				pos = length;
			}	
			if(pos != lastpos)
			{
				results.push_back(std::string(str.data() + lastpos, pos - lastpos));
			}
			lastpos = pos + 1;
		}
	}
	//line_seperator  \n    key_value_seperaotr   =    data_  map<string ,string>
	bool INIParser::Parse(const char* ini_data, size_t ini_data_len, const std::string& line_seperator, const std::string& key_value_seperator)
	{
 		if( NULL == ini_data) 
		{
			std::cout<<"Error : ini_data is null"<<std::endl;
			return false;
		}
		if( "" == line_seperator) 
		{
			std::cout<<"Error : line_seperator is null"<<std::endl;
			return false;
		}
		if( "" == key_value_seperator) 
		{
			std::cout<<"Error : key_value_seperator is null" <<std::endl;
			return false;
		}
		
		std::vector<std::string> lines;
		Split(std::string(ini_data, ini_data_len), lines, line_seperator);
//		for(size_t i = 0;i< lines.size();i++)
//			std::cout<<lines[i]<<std::endl;
		std::vector<std::string> key_values;
		for(size_t i = 0; i < lines.size(); i++)
		{
			key_values.clear();
			Split(lines[i], key_values, key_value_seperator);
//			for(size_t j = 0;j < key_values.size(); j++)
//				std::cout<<key_values[j]<<"  "<<std::endl;
			if(key_values.size() == 2)
			{
				data_[key_values[0]] = key_values[1];
//				std::cout<< "data_ value:"<<data_[key_values[0]]<<std::endl;
			}
			else
			{
				std::cout<<" Error : not key value format" <<std::endl;
			}

		}
		return true;
	}
	const std::string& INIParser::Get(const std::string& key, bool* found )
	{
		bool t = true;
		bool f = false;
//		std::cout<<"key :"<<key <<std::endl;
		std::map<std::string,std::string>::iterator it = data_.begin();
		while(it != data_.end()){
//			std::cout<<"key "<<it->first <<" value"<<it->second <<std::endl;
			it++;
		}
		if(data_.find(key) != data_.end())
		{
			found = &t;
//			std::cout<<"data_[key]"<<data_[key]<<std::endl;
			return data_[key];		
		}
		found = &f;
		std::string a("");
		std::string &temp = a;
		return temp;	
	}
}
