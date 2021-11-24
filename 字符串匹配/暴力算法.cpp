#include <iostream>
#include <string>
using namespace std;

char* strStr(const char* str, const char* target)
{
	if (!*target)	return (char*)str;
	char* p1 = (char*)str;
	while (*p1)
	{
		char* p1begin = p1;
		char* p2 = (char*)target;
		while (*p1 && *p2 && *p1 == *p2)
		{
			p1++;
			p2++;
		}
		if (!*p2)
			return p1begin;
		p1 = p1begin + 1;
	}
	return NULL;
}