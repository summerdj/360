#include <stdio.h>
#include <stdlib.h>
#include "qh_string.h"
#include <assert.h>
#include <string.h>
#include <iostream>
void test1()
{
	char t[] = "nice";
	char t2[] = "hello";
	char t3[] = "xxxxxxxx";
	qh::string s;
	qh::string s1(t);
	qh::string s2("hello");
	qh::string s3('x',8);
	
	assert(s.size() == 0);
	assert(s.data() == NULL);
	assert(strcmp(t , s1.data()) == 0);
	assert(strcmp(t2 , s2.data()) == 0);
	assert(strcmp(t3 , s3.data()) == 0);

	//test sting and \0
	//std::string x = "r";
	//if(x[1] == '\0') std::cout<<"yes";
}
void test2()
{
	char a[] = "hello world";
	qh::string s(a);
	assert(s.size() == strlen(a));
	assert(strcmp(s.data(),a) == 0 );
	for(size_t i = 0; i< s.size(); i++)
	{
		assert(s[i] == a[i]);
	}
}

void test3()
{
	char a[] = "nice meet";
	qh::string s(a);
	qh::string s2;
	assert(s2.c_str() == NULL );
	assert(strcmp(s.c_str(),s.data()) == 0);
	assert(strcmp(s.c_str(),a) == 0);
	assert(strcmp(s.data(),a) == 0);
}
int main(int argc, char* argv[])
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好
    //TODO 单元测试写法请参考INIParser那个项目，不要写一堆printf，要用assert进行断言判断。
	test1();
	test2();
	test3();
#ifdef WIN32
    system("pause");
#endif

	return 0;
}

