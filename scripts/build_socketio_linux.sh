#!/usr/bin/env bash
# Rebuilds libs/socket.io-client/lib/linux64 (x86_64) and linuxaarch64 (64-bit
# ARM: Raspberry Pi OS 64-bit, ARM servers) in Docker: static, -fPIC (apps link
# as PIE, the default on current distros), without TLS like the other platforms.
#
#   scripts/build_socketio_linux.sh            # both
#   scripts/build_socketio_linux.sh arm64      # or amd64
#
# socket.io-client-cpp at 36059f1 (2016-01-29), the version of the headers in
# libs/socket.io-client/include, with the Boost libraries it needs. Built on
# Ubuntu 18.04 (glibc 2.27, Boost 1.65: this websocketpp predates Boost 1.70),
# so the libraries link on any newer distro.
set -euo pipefail

SIO_COMMIT=36059f1
ADDON=$(cd "$(dirname "$0")/.." && pwd)

for arch in ${*:-amd64 arm64}; do
	case $arch in
		amd64) dir=linux64 ;;
		arm64) dir=linuxaarch64 ;;
		*) echo "unknown arch: $arch (amd64 or arm64)" >&2; exit 1 ;;
	esac
	echo "socket.io-client-cpp $SIO_COMMIT, linux/$arch -> libs/socket.io-client/lib/$dir"
	docker run --rm --platform "linux/$arch" -v "$ADDON:/addon" ubuntu:18.04 bash -euo pipefail -c "
		export DEBIAN_FRONTEND=noninteractive
		apt-get -o Acquire::Retries=5 update -qq && apt-get -o Acquire::Retries=5 install -y -qq git cmake g++ make \
			libboost-system-dev libboost-date-time-dev libboost-random-dev > /dev/null
		cd /tmp && git clone -q https://github.com/socketio/socket.io-client-cpp sio
		cd sio && git checkout -q $SIO_COMMIT && git submodule update -q --init
		mkdir build && cd build
		cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_POSITION_INDEPENDENT_CODE=ON > /dev/null
		make -j\$(nproc) sioclient > /dev/null
		cd ..
		out=/addon/libs/socket.io-client/lib/$dir
		mkdir -p \$out
		cp build/libsioclient.a \$out/
		for b in system date_time random; do cp /usr/lib/\$(gcc -dumpmachine)/libboost_\$b.a \$out/; done
		chown -R \$(stat -c %u:%g /addon) \$out
		ls -la \$out
	"
done
