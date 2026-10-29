meta:
	ADDON_NAME = ofxSocketIO
	ADDON_DESCRIPTION = openFrameworks wrapper for socket.io-client-cpp
	ADDON_AUTHOR = soixantecircuits
	ADDON_TAGS = "socket.io" "websocket" "network"
	ADDON_URL = https://github.com/soixantecircuits/ofxSocketIO

common:

# Static libraries are linked in order on Linux: socket.io-client before the
# Boost libraries it uses. Without these lists the order would be whatever
# order the files are found in.
linux64:
	ADDON_LIBS = libs/socket.io-client/lib/linux64/libsioclient.a
	ADDON_LIBS += libs/socket.io-client/lib/linux64/libboost_date_time.a
	ADDON_LIBS += libs/socket.io-client/lib/linux64/libboost_random.a
	ADDON_LIBS += libs/socket.io-client/lib/linux64/libboost_system.a

linuxaarch64:
	ADDON_LIBS = libs/socket.io-client/lib/linuxaarch64/libsioclient.a
	ADDON_LIBS += libs/socket.io-client/lib/linuxaarch64/libboost_date_time.a
	ADDON_LIBS += libs/socket.io-client/lib/linuxaarch64/libboost_random.a
	ADDON_LIBS += libs/socket.io-client/lib/linuxaarch64/libboost_system.a

linuxarmv6l:
	ADDON_LIBS = libs/socket.io-client/lib/linuxarmv6l/libsioclient.a
	ADDON_LIBS += libs/socket.io-client/lib/linuxarmv6l/libboost_date_time.a
	ADDON_LIBS += libs/socket.io-client/lib/linuxarmv6l/libboost_random.a
	ADDON_LIBS += libs/socket.io-client/lib/linuxarmv6l/libboost_system.a
