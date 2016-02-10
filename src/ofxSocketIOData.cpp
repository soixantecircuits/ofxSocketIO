#include "ofxSocketIOData.h"

void ofxSocketIOData::setData(sio::message::ptr data) {
  _data = data;
}

/*
 * Would be awesome to use templates here
 */
std::string ofxSocketIOData::getStringValue(std::string key) {
  return _data->get_map()[key]->get_string();
}

int ofxSocketIOData::getIntValue(std::string key) {
  return _data->get_map()[key]->get_int();
}

float ofxSocketIOData::getFloatValue(std::string key) {
  return _data->get_map()[key]->get_int();
}

double ofxSocketIOData::getDoubleValue(std::string key) {
  return _data->get_map()[key]->get_int();
}

bool ofxSocketIOData::getBoolValue(std::string key) {
  return _data->get_map()[key]->get_int();
}