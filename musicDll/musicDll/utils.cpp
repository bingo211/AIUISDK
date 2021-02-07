#include "utils.h"
#include <windows.h>
#include "picojson.h"

std::string generateParams(const std::string &height, const std::string &width) {
     picojson::value json;
     json.set<picojson::object>(picojson::object());
     json.get<picojson::object>()["video_height"] = picojson::value(height);
     json.get<picojson::object>()["video_width"] = picojson::value(width);
     std::string cjson = json.serialize();
     std::string params = base64::encode(cjson);
     return params;
}

/*
mvsResult* parseMvsResult(const std::string &data){
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
*/

std::vector<newResult> parseNewsResult(const std::string &cjson)
{
  std::vector<newResult> rest;
  picojson::value v;
  std::string err = picojson::parse(v,cjson);
  if (!err.empty()){
    return rest;
  }

  if (!v.is<picojson::object>()) {
     return rest;
  }

  picojson::value _result = v.get("result");

  if (_result.is<picojson::array>()) {
     picojson::array list = _result.get<picojson::array>();
     for (picojson::array::iterator iter = list.begin() ; iter != list.end() ; ++iter){
        newResult nr;
#if 0
        if ((*iter).contains("publishTime"))
            nr.publishTime = (*iter).get("publishTime").get<std::string>();
        if ((*iter).contains("img"))
            nr.img = (*iter).get("img").get<std::string>();
        if ((*iter).contains("author"))
            nr.author = (*iter).get("author").get<std::string>();
        if ((*iter).contains("description"))
            nr.description = (*iter).get("description").get<std::string>();
        if ((*iter).contains("publishSource"))
            nr.publishSource = (*iter).get("publishSource").get<std::string>();
        if ((*iter).contains("source"))
            nr.source = (*iter).get("source").get<std::string>();
        if ((*iter).contains("type"))
            nr.type = (*iter).get("type").get<std::string>();
        if ((*iter).contains("hot"))
            nr.hot = (*iter).get("hot").get<std::string>();
#endif

        if ((*iter).contains("content"))
            nr.content = (*iter).get("content").get<std::string>();
        if ((*iter).contains("url"))
            nr.url = (*iter).get("url").get<std::string>();
#if 0
        if ((*iter).contains("tags"))
            nr.tags = (*iter).get("tags").get<std::string>();
        if ((*iter).contains("actor"))
            nr.actor = (*iter).get("actor").get<std::string>();
        if ((*iter).contains("name"))
            nr.name = (*iter).get("name").get<std::string>();
        if ((*iter).contains("category"))
            nr.category = (*iter).get("category").get<std::string>();
#endif
        rest.push_back(nr);

     }
  }
  return rest;
}

std::vector<weatherResult> parseWeatherResult(const std::string &cjson)
{
    std::vector<weatherResult> rest;
    picojson::value v;
    std::string err = picojson::parse(v,cjson);
    if (!err.empty()){
      return rest;
    }

    if (!v.is<picojson::object>()) {
       return rest;
    }

    picojson::value _result = v.get("result");

    if (_result.is<picojson::array>()) {
       picojson::array list = _result.get<picojson::array>();
       for (picojson::array::iterator iter = list.begin() ; iter != list.end() ; ++iter){
              weatherResult nr;
              if ((*iter).contains("date"))
                  nr.date = (*iter).get("date").get<std::string>();
              if ((*iter).contains("tempLow"))
                  nr.tempLow = (*iter).get("tempLow").get<std::string>();
              if ((*iter).contains("weatherType"))
                  nr.weatherType = (*iter).get("weatherType").get<double>();
              if ((*iter).contains("img"))
                  nr.img = (*iter).get("img").get<std::string>();
              if ((*iter).contains("week"))
                  nr.week = (*iter).get("week").get<std::string>();
              if ((*iter).contains("airData"))
                  nr.airData = (*iter).get("airData").get<double>();
              if ((*iter).contains("windLevel"))
                  nr.windLevel = (*iter).get("windLevel").get<double>();
              if ((*iter).contains("city"))
                  nr.city = (*iter).get("city").get<std::string>();
              if ((*iter).contains("date_for_voice"))
                  nr.date_for_voice = (*iter).get("date_for_voice").get<std::string>();
              if ((*iter).contains("weather"))
                  nr.weather = (*iter).get("weather").get<std::string>();
              if ((*iter).contains("humidity"))
                  nr.humidity = (*iter).get("humidity").get<std::string>();
              if ((*iter).contains("warning"))
                  nr.warning = (*iter).get("warning").get<std::string>();
              if ((*iter).contains("dateLong"))
                  nr.dateLong = (*iter).get("dateLong").get<double>();
              if ((*iter).contains("airQuality"))
                  nr.airQuality = (*iter).get("airQuality").get<std::string>();
              if ((*iter).contains("temp"))
                  nr.temp = (*iter).get("temp").get<double>();
              if ((*iter).contains("weatherDescription"))
                  nr.weatherDescription = (*iter).get("weatherDescription").get<std::string>();
              if ((*iter).contains("weatherDescription3"))
                  nr.weatherDescription3 = (*iter).get("weatherDescription3").get<std::string>();
              if ((*iter).contains("pm25"))
                  nr.pm25 = (*iter).get("pm25").get<std::string>();
              if ((*iter).contains("weatherDescription7"))
                  nr.weatherDescription7 = (*iter).get("weatherDescription7").get<std::string>();
              if ((*iter).contains("tempRange"))
                  nr.tempRange = (*iter).get("tempRange").get<std::string>();
              if ((*iter).contains("tempHigh"))
                  nr.tempHigh = (*iter).get("tempHigh").get<std::string>();
              if ((*iter).contains("lastUpdateTime"))
                  nr.lastUpdateTime = (*iter).get("lastUpdateTime").get<std::string>();
              if ((*iter).contains("wind"))
                  nr.wind = (*iter).get("wind").get<std::string>();

              //
              if ((*iter).contains("exp")){
                picojson::value::object _exp = (*iter).get("exp").get<picojson::object>();
                //ct
                if (_exp.find("ct") != _exp.end()){
                    picojson::value::object _ct = _exp["ct"].get<picojson::object>();
                    if (_ct.find("expName") != _ct.end()){
                        nr.exp.ct.expName = _ct["expName"].get<std::string>();
                    }
                    if (_ct.find("level") != _ct.end()){
                        nr.exp.ct.level = _ct["level"].get<std::string>();
                    }
                    if (_ct.find("prompt") != _ct.end()){
                        nr.exp.ct.prompt = _ct["prompt"].get<std::string>();
                    }
                }

                //dy
                if (_exp.find("dy") != _exp.end()){
                    picojson::value::object _dy = _exp["dy"].get<picojson::object>();
                    if (_dy.find("expName") != _dy.end()){
                        nr.exp.dy.expName = _dy["expName"].get<std::string>();
                    }
                    if (_dy.find("level") != _dy.end()){
                        nr.exp.dy.level = _dy["level"].get<std::string>();
                    }
                    if (_dy.find("prompt") != _dy.end()){
                        nr.exp.dy.prompt = _dy["prompt"].get<std::string>();
                    }
                }


                //gm
                if (_exp.find("gm") != _exp.end()){
                    picojson::value::object _dy = _exp["gm"].get<picojson::object>();
                    if (_dy.find("expName") != _dy.end()){
                        nr.exp.gm.expName = _dy["expName"].get<std::string>();
                    }
                    if (_dy.find("level") != _dy.end()){
                        nr.exp.gm.level = _dy["level"].get<std::string>();
                    }
                    if (_dy.find("prompt") != _dy.end()){
                        nr.exp.gm.prompt = _dy["prompt"].get<std::string>();
                    }
                }


                //jt
                if (_exp.find("jt") != _exp.end()){
                    picojson::value::object _dy = _exp["jt"].get<picojson::object>();
                    if (_dy.find("expName") != _dy.end()){
                        nr.exp.jt.expName = _dy["expName"].get<std::string>();
                    }
                    if (_dy.find("level") != _dy.end()){
                        nr.exp.jt.level = _dy["level"].get<std::string>();
                    }
                    if (_dy.find("prompt") != _dy.end()){
                        nr.exp.jt.prompt = _dy["prompt"].get<std::string>();
                    }
                }


                //tr
                if (_exp.find("tr") != _exp.end()){
                    picojson::value::object _dy = _exp["tr"].get<picojson::object>();
                    if (_dy.find("expName") != _dy.end()){
                        nr.exp.tr.expName = _dy["expName"].get<std::string>();
                    }
                    if (_dy.find("level") != _dy.end()){
                        nr.exp.tr.level = _dy["level"].get<std::string>();
                    }
                    if (_dy.find("prompt") != _dy.end()){
                        nr.exp.tr.prompt = _dy["prompt"].get<std::string>();
                    }
                }


                //uv
                if (_exp.find("uv") != _exp.end()){
                    picojson::value::object _dy = _exp["uv"].get<picojson::object>();
                    if (_dy.find("expName") != _dy.end()){
                        nr.exp.uv.expName = _dy["expName"].get<std::string>();
                    }
                    if (_dy.find("level") != _dy.end()){
                        nr.exp.uv.level = _dy["level"].get<std::string>();
                    }
                    if (_dy.find("prompt") != _dy.end()){
                        nr.exp.uv.prompt = _dy["prompt"].get<std::string>();
                    }
                }


                //xc
                if (_exp.find("xc") != _exp.end()){
                    picojson::value::object _dy = _exp["xc"].get<picojson::object>();
                    if (_dy.find("expName") != _dy.end()){
                        nr.exp.xc.expName = _dy["expName"].get<std::string>();
                    }
                    if (_dy.find("level") != _dy.end()){
                        nr.exp.xc.level = _dy["level"].get<std::string>();
                    }
                    if (_dy.find("prompt") != _dy.end()){
                        nr.exp.xc.prompt = _dy["prompt"].get<std::string>();
                    }
                }


                //yd
                if (_exp.find("yd") != _exp.end()){
                    picojson::value::object _dy = _exp["yd"].get<picojson::object>();
                    if (_dy.find("expName") != _dy.end()){
                        nr.exp.yd.expName = _dy["expName"].get<std::string>();
                    }
                    if (_dy.find("level") != _dy.end()){
                        nr.exp.yd.level = _dy["level"].get<std::string>();
                    }
                    if (_dy.find("prompt") != _dy.end()){
                        nr.exp.yd.prompt = _dy["prompt"].get<std::string>();
                    }
                }

              }

              rest.push_back(nr);
          }
       }
    return rest;
}
