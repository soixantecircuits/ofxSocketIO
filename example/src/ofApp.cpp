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
  string eventName = "server-event";
  socketIO.bindEvent(serverEvent, eventName);
  ofAddListener(serverEvent, this, &ofApp::gotEvent);
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
void ofApp::onServerEvent (string& name) {
  ofLogNotice("ofApp - onServerEvent", name);
//  status = name;
}