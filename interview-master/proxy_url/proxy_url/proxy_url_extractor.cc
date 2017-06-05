#include "proxy_url_extractor.h"
#include <fstream>
#include <vector>
#include "tokener.h"
#include <iostream>
using std::cout;
using std::endl;
namespace qh
{

    namespace {

        template< class _StringVector, 
        class StringType,
        class _DelimType> 
            inline void StringSplit(  
            const StringType& str, 
            const _DelimType& delims, 
            unsigned int maxSplits, 
            _StringVector& ret)
        {
            unsigned int numSplits = 0;

            // Use STL methods
            size_t start, pos;
            start = 0;

            do
            {
                pos = str.find_first_of( delims, start );

                if ( pos == start )
                {
                    ret.push_back(StringType());
                    start = pos + 1;
                }
                else if ( pos == StringType::npos || ( maxSplits && numSplits + 1== maxSplits ) )
                {
                    // Copy the rest of the string
                    ret.push_back(StringType());
                    *(ret.rbegin()) = StringType(str.data() + start, str.size() - start);
                    break;
                }
                else
                {
                    // Copy up to delimiter
                    //ret.push_back( str.substr( start, pos - start ) );
                    ret.push_back(StringType());
                    *(ret.rbegin()) = StringType(str.data() + start, pos - start);
                    start = pos + 1;
                }

                ++numSplits;

            }
            while ( pos != StringType::npos );
        }
    }

    ProxyURLExtractor::ProxyURLExtractor()
    {
    }

    bool ProxyURLExtractor::Initialize( const std::string& param_keys_path )
    {
        std::ifstream ifs;
        ifs.open(param_keys_path.data(), std::fstream::in);
        typedef std::vector<std::string> stringvector;
        stringvector keysvect;
        
        while (!ifs.eof()) {
            std::string line;
            getline(ifs, line);
            if (ifs.fail() && !ifs.eof()) {
                fprintf(stderr, "SubUrlExtractor::LoadParamKeysFile readfile_error=[%s] error!!", param_keys_path.data());
                ifs.close();
                return false;
            }
            if (line.empty()) continue;

            keysvect.clear();
            StringSplit(line, ",", static_cast<unsigned int>(-1), keysvect);
            assert(keysvect.size() >= 1);
            keys_set_.insert(keysvect.begin(), keysvect.end());
            keys_set_.erase("");
        }

        ifs.close();

        return true;
    }

    std::string ProxyURLExtractor::Extract( const std::string& raw_url )
    {
        std::string sub_url;
        ProxyURLExtractor::Extract(keys_set_, raw_url, sub_url);
        return sub_url;
    }

    void ProxyURLExtractor::Extract( const KeyItems& keys, const std::string& raw_url, std::string& sub_url )
    {
//#if 1
        //TODO ÇëÃæÊÔÕßÔÚÕâÀïÌí¼Ó×Ô¼ºµÄ´úÂëÊµÏÖÒÔÍê³ÉËùÐè¹¦ÄÜ
//#else
        //ÕâÊÇÒ»·Ý²Î¿¼ÊµÏÖ£¬µ«ÔÚÌØÊâÇé¿öÏÂ¹¤×÷²»ÄÜ·ûºÏÔ¤ÆÚ
        Tokener token(raw_url);
        token.skipTo('?');
        token.next(); //skip one char : '?' 
        std::string key;
		std::string temp;
		while(token.current() == '&') //¿¿¿¿¿¿¿¿¿¿¿¿
		{
			token.next();
		}
		while (!token.isEnd()) {
        	temp = token.nextString('&');
	    	if(temp.size()!=0)
	    		token.back(temp.size() + 1);  	 //temp ¿¿¿¿¿¿¿¿¿ & ¿¿¿¿¿
			//token.next();
			key = token.nextString('=');  //key ¿¿¿¿¿= ¿¿¿
			//cout << key.size() <<" "<<temp.size()<<" "<<endl;
			//cout<<key << " "<< temp<<endl;
			if(key.size() > temp.size() && temp.size() != 0)  // &axxx&url=asdfg
			{
			//	cout<< "2"<<key<<endl;
				token.skipBackTo('&');
				//token.next();			
				continue;
			}
            if (keys.find(key) != keys.end()) {
                const char* curpos = token.getCurReadPos();
                int nreadable = token.getReadableSize();
		//cout<<"jjjj"<<endl;
                /**
                * case 1: 
                *  raw_url="http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&a=http://hnujug.com/&xx=yy"
                *  sub_url="http://hnujug.com/"
                */
				bool flag = true;
				if(token.current() == '&')  // "&query=&url=xxxxxxx" "&query=http://xxxxxxxxx/"judge
				{
					flag = false;
            	}
				sub_url = token.nextString('&');
				//cout<<"bbbbbbb   "<<sub_url<<"bbbb"<<token.current()<<endl;
            	if (sub_url.empty() && nreadable > 0 && flag ) {
                    /**
                    * case 2: 
                    * raw_url="http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&a=http://hnujug.com/"
                    * sub_url="http://hnujug.com/"
                    */
			
                    assert(curpos);
                    sub_url.assign(curpos, nreadable);
		    //cout<<"kkkkk   "<<sub_url<<endl;
                }
            }
            token.skipTo('&');
            token.next();//skip one char : '&'
        }
//#endif
    }

    std::string ProxyURLExtractor::Extract( const KeyItems& keys, const std::string& raw_url )
    {
        std::string sub_url;
        ProxyURLExtractor::Extract(keys, raw_url, sub_url);
        return sub_url;
    }
}

