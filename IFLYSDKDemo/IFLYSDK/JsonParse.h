#pragma once
#include "util.h"

class JsonParse
{
public:
	JsonParse(void);
	~JsonParse(void);
	//����json�������
	static AiuiResult* parse(const std::string& aiuiJson);
	//������������ص�url��ַ
	static mvsResult* parseMvsResult(const std::string &data);
};

