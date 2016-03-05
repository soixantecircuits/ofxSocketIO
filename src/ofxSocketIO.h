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
  sio::socket::ptr socket;

  std::string currentStatus;

  void onConnect();
  void onClose(sio::client::close_reason const& reason);
  void onFail();
  void onTryReconnect();

public :
  void setup(std::string& address);

  void bindEvent(ofEvent<ofxSocketIOData&>& event, std::string eventName);

  ofEvent<void> connectionEvent;
  ofEvent<std::string> notifyEvent;

  void emit(std::string& eventName, std::string& data);
  void emitBinary(std::string& eventName, shared_ptr<string> const& bStr);

  void closeConnection();
  void openConnection(std::string& address);
};
