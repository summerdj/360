#include <stdlib.h>
#include "qh_vector.h"
#include <iostream>

int main(int argc, char* argv[])
{
    //TODO ��������ӵ�Ԫ���ԣ�Խ��Խ�ã�����·��������ԽȫԽ��
    //TODO ��Ԫ����д����ο�INIParser�Ǹ���Ŀ����Ҫдһ��printf��Ҫ��assert���ж����жϡ�

    qh::vector<int> num_vect;
    std::cout<<"-----------------------test init function�size()�capacity()------------------------"<< std::endl;
	std::cout<<" vector<int> v : "<<std::endl;
	std::cout<<"vector init size "<< num_vect.size() <<"   vector init capacity "<< num_vect.capacity()<< std::endl;
	qh::vector<int> v(3,6);
	std::cout<<" vector<int> v(3,6) : "<<std::endl;
	std::cout<<"vector init size "<< v.size() <<"   vector init capacity "<< v.capacity()<< std::endl;
	int *a = &v[0];
	for(size_t  i = 0; i < v.size(); i++){
		std::cout<< " content " << *(a + i) << " ";
	}		
	std::cout<<std::endl;
	std::cout<<"-----------------------test [] operator------------------------"<< std::endl;
	std::cout<<" use [] get items "<<std::endl;
	for(size_t i = 0; i < v.size(); i++){
		std::cout<< v[i] << " ";
	}
	std::cout<<std::endl;
	std::cout<<"-----------------------test =  operator------------------------"<< std::endl;	
	num_vect = v;
	for(size_t i = 0; i< num_vect.size(); i++){
		std::cout<< num_vect[i]<< " ";
	}	
	std::cout<<std::endl;
	num_vect = num_vect;
	std::cout<<"-----------------------test push_back() pop_back() ------------------------"<< std::endl;
		std::cout<<" use [] get items "<<std::endl;
	num_vect.push_back(1);
	num_vect.push_back(2);
	std::cout<<" size : "<< num_vect.size() << std::endl;
	for(size_t i = 0; i< num_vect.size(); i++){
    	 std::cout<< num_vect[i]<< " ";
    }
    std::cout<<std::endl;
 	num_vect.pop_back();
	std::cout<<" size : "<< num_vect.size() << std::endl;
    for(size_t i = 0; i< num_vect.size(); i++){
    	std::cout<< num_vect[i]<< " ";
	}    
    std::cout<<std::endl;
	std::cout<<"-----------------------test resize(size_t n)------------------------"<< std::endl;
	num_vect.resize(2);
	for(size_t i = 0; i< num_vect.size(); i++){
        std::cout<< num_vect[i]<< " ";
    }
    std::cout<<std::endl;
	std::cout<<"-----------------------test resize(size_t n, T &m)------------------------"<< std::endl;
	num_vect.resize(8,8);
	for(size_t i = 0; i< num_vect.size(); i++){
        std::cout<< num_vect[i]<< " ";
    }
    std::cout<<std::endl;
    std::cout<<"-----------------------test reserve()------------------------"<< std::endl;
	num_vect.reserve(20);
	std::cout<<" size : "<< num_vect.size() <<"    capacity : "<< num_vect.capacity()<< std::endl;
	num_vect.reserve(2);
 	std::cout<<" size : "<< num_vect.size() <<"    capacity : "<< num_vect.capacity()<< std::endl;
	std::cout<<"-----------------------test clear() and  empty()------------------------"<< std::endl;
	if(num_vect.empty()) 
		std::cout<< " true,empty "<<std::endl;
	else
		std::cout<< " false,not empty "<<std::endl;
	num_vect.clear();
	if(num_vect.empty()) 
		std::cout<< " true,empty "<<std::endl;
    else
        std::cout<< " false,not empty "<<std::endl;


	//std::cout<<num_vect[0]<<std::endl;
	//std::cout<<num_vect[1]<<std::endl;
	//std::cout<<num_vect.size()<<std::endl;	
 
/* ������
	int *x = new int[1];
	std::cout<<x[0]<<std::endl;
	x[1] = 2;
	std::cout<<x[1]<<std::endl;
*/
#ifdef WIN32
    system("pause");
#endif

	return 0;
}

