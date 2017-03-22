//
//  ofxSocketIO.h
//
//  Created by hugohil on 05/02/16.
//
//
#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#if defined(_MSC_VER) || defined(_WIN32) || defined(WIN32) || defined(__MINGW32__)
  // Windows stuff
#else
  // Linux and OSX here
  #include <sio_client.h>
#endif
#include "ofxSocketIOData.h"

class ofxSocketIO : protected ofThread {
private :
  sio::client client;

  void onConnect();
  void onClose(sio::client::close_reason const& reason);
  void onFail();
  void onTryReconnect();

public :
  std::string currentStatus = "close";

  void setup(std::string& address);
  void setup(std::string& address, std::map<std::string,std::string>& query);

  void bindEvent(ofEvent<ofxSocketIOData&>& event, std::string eventName, std::string nsp="");

  ofEvent<void> connectionEvent;
  ofEvent<std::string> notifyEvent;

  void emit(std::string& eventName);
  void emit(std::string& eventName, std::string& data, std::string nsp="");
  void emitBinary(std::string& eventName, shared_ptr<string> const& bStr, std::string nsp="");

  void closeConnection();
  void openConnection(std::string& address);
};
