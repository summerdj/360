#include "qh_string.h"
//#include <exception>
#include <string.h>
namespace qh
{
    // TODO 将在这里写实现代码

    string::string()
        : data_(NULL), len_(0)
    {
    }

    string::string( const char* s )
    {
    	if(s == NULL) 
			return ;
		len_ = strlen(s);
		data_ = new char[len_ + 1];
		strcpy(data_,s);
	}

    string::string( const char s, const size_t len )
    {
		len_ = len;
		data_ = new char[len_ + 1];
		*(data_ + len_) = '\0';
		for(size_t i = 0; i < len_; i++)
			data_[i] =  s;
		//strset(data_ ,s);
    }

    string::string( const string& rhs )
    {
		len_ = rhs.len_;
		data_ = new char[len_ + 1];
		strcpy(data_,rhs.data_);
    }

    string& string::operator=( const string& rhs )
    {
    	if(this != &rhs)
		{
			if(len_ < rhs.len_)
			{
				delete[] data_;
				data_ = new char[rhs.len_ + 1];
			}
			len_ = rhs.len_;
			strcpy(data_ , rhs.data_);
		}	 
		return *this;
    }
	bool operator==(const string& a, const string& b)
	{
		return strcmp(a.data_,b.data_) == 0;
	}
    string::~string()
    {
		delete[] data_;
    }

    size_t string::size() const
    { 
		return len_;
    }

    const char* string::data() const
    {
        return data_;
    }

    const char* string::c_str() const
    {
    /*    if(data_[len_] != '\0')
		{
			len_ = len_ + 1;
			char* tmp = data_;
			data_ = new char[len_];
			strcmp(data_,tmp;
		    data_[len_] = '\0';
			delete[] tmp;
		}
		*/
		if(len_ == 0)
			return NULL;
		//terminate();
		return data_;
    }

    char& string::operator[]( const size_t index )
    {
     	if(index > 0 && index < len_);   
			return data_[index];
    }
}
