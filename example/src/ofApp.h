#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#include "ofxSocketIO.h"
#include "ofxSocketIOData.h"

class ofApp : public ofBaseApp{
public:
  void setup();
  void update();
  void draw();

  void keyPressed(int key);
  void keyReleased(int key);

  void gotEvent(std::string& name);
  void onServerEvent(ofxSocketIOData& data);
  void onPingEvent(ofxSocketIOData& data);

  ofxSocketIO socketIO;

  bool isConnected;
  void onConnection();
  void bindEvents();
  ofEvent<ofxSocketIOData&> serverEvent;
  ofEvent<ofxSocketIOData&> pingEvent;

  std::string address;
  std::string status;
};
