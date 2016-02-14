#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  isConnected = false;
  address = "http://127.0.0.1:8888";
  status = "not connected";

  socketIO.setup(address);
  ofAddListener(socketIO.notifyEvent, this, &ofApp::gotEvent);

  ofAddListener(socketIO.connectionEvent, this, &ofApp::onConnection);
}

void ofApp::onConnection () {
  isConnected = true;
  bindEvents();
}

void ofApp::bindEvents () {
  std::string serverEventName = "server-event";
  socketIO.bindEvent(serverEvent, serverEventName);
  ofAddListener(serverEvent, this, &ofApp::onServerEvent);

  std::string pingEventName = "ping";
  socketIO.bindEvent(pingEvent, pingEventName);
  ofAddListener(pingEvent, this, &ofApp::onPingEvent);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  ofDrawBitmapStringHighlight(ofApp::status, 20, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::gotEvent(string& name) {
  status = name;
}

//--------------------------------------------------------------
void ofApp::onServerEvent (ofxSocketIOData& data) {
  ofLogNotice("ofxSocketIO", data.getStringValue("stringData"));
  ofLogNotice("ofxSocketIO", ofToString(data.getIntValue("intData")));
  ofLogNotice("ofxSocketIO", ofToString(data.getFloatValue("floatData")));
  ofLogNotice("ofxSocketIO", ofToString(data.getBoolValue("boolData")));
}

void ofApp::onPingEvent (ofxSocketIOData& data) {
  ofLogNotice("ofxSocketIO", "ping");
  std::string pong = "pong";
  std::string param = "foo";
  socketIO.emit(pong, param);
}
