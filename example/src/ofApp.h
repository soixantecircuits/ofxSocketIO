#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#include "ofxSocketIO.h"


class ofApp : public ofBaseApp{
public:
  void setup();
  void update();
  void draw();

  void keyPressed(int key);
  void keyReleased(int key);

  void gotEvent(string& name);
  void onServerEvent(string& name);

  ofxSocketIO socketIO;

  bool isConnected;
  void onConnection();
  void bindEvents();
  ofEvent<string> serverEvent;

  string address;
  string status;
};
