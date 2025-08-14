#include "pch.h"
#include "PacketData.h"

namespace kx {

std::deque<PacketInfo> g_packetLog;
std::mutex g_packetLogMutex;
}