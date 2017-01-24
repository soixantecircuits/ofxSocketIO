//
//  ofxSocketIO.cpp
//
//  Created by hugohil on 05/02/16.
//
//
#include "ofxSocketIO.h"

void ofxSocketIO::setup (std::string &address) {
  std::map<std::string,std::string> query;
  setup(address, query);
}

void ofxSocketIO::setup (std::string &address, std::map<std::string,std::string> &query) {
  currentStatus = "not connected";

  client.set_open_listener(std::bind(&ofxSocketIO::onConnect, this));
  client.set_close_listener(std::bind(&ofxSocketIO::onClose, this, std::placeholders::_1));
  client.set_fail_listener(std::bind(&ofxSocketIO::onFail, this));
  client.set_reconnect_listener(std::bind(&ofxSocketIO::onTryReconnect, this));

  client.connect(address, query);
}

void ofxSocketIO::onConnect () {
  currentStatus = "connected";
  ofNotifyEvent(notifyEvent, currentStatus);
  ofNotifyEvent(connectionEvent);
}

void ofxSocketIO::onClose (sio::client::close_reason const& reason) {
  currentStatus = "close";
  ofNotifyEvent(notifyEvent, currentStatus);
}

void ofxSocketIO::onFail () {
  currentStatus = "error";
  ofNotifyEvent(notifyEvent, currentStatus);
}

void ofxSocketIO::onTryReconnect () {
  currentStatus = "trying to reconnect";
  ofNotifyEvent(notifyEvent, currentStatus);
}

void ofxSocketIO::bindEvent (ofEvent<ofxSocketIOData&>& event, string eventName) {
  socket->on(eventName, sio::socket::event_listener_aux([&] (string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp) {
    ofxSocketIOData ofxData;
    if (data) {
      ofxData.setData(data);
    } else {
      ofxData.setNullData();
    }
    ofNotifyEvent(event, ofxData, this);
  }));
}

void ofxSocketIO::emit (std::string& eventName, std::string& data, string nsp) {
  if (client.opened()) {
    client.socket(nsp)->emit(eventName, data);
  } else {
    ofLogWarning("ofxSocketIO", "socket is not available.");
  }
}

void ofxSocketIO::emitBinary (std::string& eventName, shared_ptr<string> const& bStr, string nsp) {
  if (client.opened()) {
    client.socket(nsp)->emit(eventName, bStr);
  } else {
    ofLogWarning("ofxSocketIO", "socket is not available.");
  }
}

void ofxSocketIO::closeConnection () {
  client.sync_close();
}

void ofxSocketIO::openConnection (std::string &address) {
    client.connect(address);
}
