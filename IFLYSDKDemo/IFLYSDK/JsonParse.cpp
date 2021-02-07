#include "StdAfx.h"
#include "JsonParse.h"
#include "picojson.h"

JsonParse::JsonParse(void)
{
}


JsonParse::~JsonParse(void)
{
}


/**
* @brief httpclient::parse  解析aiuiresult结果
* @param aiuiJson   aiui结果
* @return
*/
AiuiResult* JsonParse::parse(const std::string& aiuiJson)
{
	if (aiuiJson.empty()){
		return nullptr;
	}
	picojson::value v;
	std::string err = picojson::parse(v, aiuiJson);
	if (!err.empty()){
		cout << err << endl;
		return nullptr;
	}

	if (!v.is<picojson::object>()){
		return nullptr;
	}

	AiuiResult *aiuiresult = new AiuiResult;
	aiuiresult->Rc = v.get("rc").get<string>();
	aiuiresult->Msg = v.get("msg").get<string>();
	aiuiresult->Offset = v.get("offset").get<string>();
	aiuiresult->Limit = v.get("limit").get<string>();
	aiuiresult->Sid = v.get("sid").get<string>();
	aiuiresult->Total = v.get("total").get<string>();

	if (aiuiresult->Rc == "0") {
		auto _result = v.get("result");
		if (_result.is<picojson::array>()) {
			picojson::array list = _result.get<picojson::array>();
			for (picojson::array::iterator iter = list.begin(); iter != list.end(); ++iter) {
				Result cres;
				if ((*iter).contains("songname"))
					cres.Songname = (*iter).get("songname").get<string>();

				if ((*iter).contains("audiopath"))
					cres.Audiopath = (*iter).get("audiopath").get<string>();
				if ((*iter).contains("singernames")) {
					if ((*iter).get("singernames").is<picojson::array>()){
						picojson::array singers = (*iter).get("singernames").get<picojson::array>();
						for (picojson::array::iterator siter = singers.begin(); siter != singers.end(); ++siter) {
							string sing;
							sing = (*siter).get<string>();
							cres.Singernames.push_back(sing);
						}
					}
				}
				aiuiresult->result.push_back(cres);
			}
		}
	}
	return aiuiresult;
}


mvsResult* JsonParse::parseMvsResult(const std::string &data)
{
	mvsResult *mvsr = new mvsResult ;
	picojson::value v;
	std::string err = picojson::parse(v,data);
	if (!err.empty()){
		return nullptr;
	}

	if (!v.is<picojson::object>()){
		return nullptr;
	}

	mvsr->sid = v.get("sid").get<std::string>();
	mvsr->code = v.get("code").get<double>();
	picojson::value::object _data = v.get("data").get<picojson::object>();

	if (_data.find("rtmpUrl") != _data.end())
		mvsr->d.rtmpUrl = _data["rtmpUrl"].get<std::string>();
	if (_data.find("httpUrl") != _data.end())
		mvsr->d.httpUrl = _data["httpUrl"].get<std::string>();
	if (_data.find("rtcUrl") != _data.end())
		mvsr->d.rtcUrl = _data["rtcUrl"].get<std::string>();
	if (_data.find("httpsUrl") != _data.end())
		mvsr->d.httpsUrl = _data["httpsUrl"].get<std::string>();
	if (_data.find("rtcsUrl") != _data.end())
		mvsr->d.rtcsUrl = _data["rtcsUrl"].get<std::string>();
	return mvsr;
}