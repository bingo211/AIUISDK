#pragma once
#include "util.h"

class JsonParse
{
public:
	JsonParse(void);
	~JsonParse(void);
	//音乐json结果解析
	static AiuiResult* parse(const std::string& aiuiJson);
	//解析虚拟形象回调url地址
	static mvsResult* parseMvsResult(const std::string &data);
};

