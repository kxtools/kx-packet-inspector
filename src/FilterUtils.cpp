#include "pch.h"
#include "FilterUtils.h"

namespace kx::Filtering {

    // Helper function (implementation of the check)
    bool ShouldDisplayPacket(const kx::PacketInfo& packet) {
        // 1. Apply direction filter
        if (kx::g_packetDirectionFilterMode == kx::DirectionFilterMode::ShowSentOnly && packet.direction != kx::PacketDirection::Sent) {
            return false;
        }
        if (kx::g_packetDirectionFilterMode == kx::DirectionFilterMode::ShowReceivedOnly && packet.direction != kx::PacketDirection::Received) {
            return false;
        }

        // 2. Apply header/type include/exclude filter (only if mode is not ShowAll)
        if (kx::g_packetFilterMode != kx::FilterMode::ShowAll) {
            bool isChecked = false;
            bool foundInFilters = false;

            // Check against header filters if it's a normal/unknown header packet
            if (packet.specialType == kx::InternalPacketType::NORMAL) {
                // Construct the key used in the global map
                auto key = std::make_pair(packet.direction, packet.rawHeaderId);
                auto it = kx::g_packetHeaderFilterSelection.find(key);
                if (it != kx::g_packetHeaderFilterSelection.end()) {
                    isChecked = it->second; // Get the boolean value (checked state)
                    foundInFilters = true;
                }
            }
            // Check against special type filters otherwise
            else {
                auto it = kx::g_specialPacketFilterSelection.find(packet.specialType);
                if (it != kx::g_specialPacketFilterSelection.end()) {
                    isChecked = it->second;
                    foundInFilters = true;
                }
            }

            // Apply Include/Exclude logic
            if (kx::g_packetFilterMode == kx::FilterMode::IncludeOnly) {
                // Must be found in the filter list AND be checked to be included
                if (!foundInFilters || !isChecked) {
                    return false;
                }
            }
            else { // Exclude mode (kx::g_packetFilterMode == kx::FilterMode::Exclude)
                // Must NOT be (found in the list AND checked) to be included (i.e., exclude if found and checked)
                if (foundInFilters && isChecked) {
                    return false;
                }
            }
        }

        // If all checks passed, display the packet
        return true;
    }


    std::vector<int> GetFilteredPacketIndices(const std::deque<kx::PacketInfo>& fullLog) {
        std::vector<int> filteredIndices;
        // Reserve likely size? Maybe not necessary if filtering is aggressive.
        // filteredIndices.reserve(fullLog.size() / 2); // Example guess

        for (int i = 0; i < fullLog.size(); ++i) {
            if (ShouldDisplayPacket(fullLog[i])) {
                filteredIndices.push_back(i);
            }
        }
        return filteredIndices;
    }

} // namespace kx::Filtering