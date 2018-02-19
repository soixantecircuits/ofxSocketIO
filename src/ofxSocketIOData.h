#pragma once

#include "ofMain.h"
#if defined(_MSC_VER) || defined(_WIN32) || defined(WIN32) || defined(__MINGW32__)
  // Windows stuff
#else
  // Linux and OSX here
  #include <sio_client.h>
#endif

class ofxSocketIOData : public ofEventArgs {
private :
  sio::message::ptr _data;

public :
  ofxSocketIOData();

  void setData(sio::message::ptr const&);
  void setNullData();

  std::string getStringValue(std::string key);
  int getIntValue(std::string key);
  float getFloatValue(std::string key);
  double getDoubleValue(std::string key);
  bool getBoolValue(std::string key);
  ofxSocketIOData getNestedValue(std::string key);

  std::vector<std::shared_ptr<sio::message>>& getVector();
};
