#include "ofxSocketIOData.h"

ofxSocketIOData::ofxSocketIOData () {}

void ofxSocketIOData::setData(sio::message::ptr const& data) {
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
  return (float) _data->get_map()[key]->get_double();
}

double ofxSocketIOData::getDoubleValue(std::string key) {
  return _data->get_map()[key]->get_double();
}

bool ofxSocketIOData::getBoolValue(std::string key) {
  return _data->get_map()[key]->get_bool();
}
