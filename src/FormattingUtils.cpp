#include "pch.h"
#include "FormattingUtils.h"

namespace kx::Utils {

    // --- Function Implementations ---

    std::string FormatTimestamp(const std::chrono::system_clock::time_point& tp) {
        // Convert to time_t for HH:MM:SS
        std::time_t time = std::chrono::system_clock::to_time_t(tp);
        std::tm local_tm;
        localtime_s(&local_tm, &time); // Use safe version

        // Get milliseconds
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch()) % 1000;

        std::stringstream ss;
        // Format HH:MM:SS
        ss << std::put_time(&local_tm, "%H:%M:%S");
        // Append milliseconds, padded with zeros
        ss << '.' << std::setfill('0') << std::setw(3) << ms.count();

        return ss.str();
    }

    std::string FormatBytesToHex(const std::vector<uint8_t>& data, int maxBytes) {
        std::stringstream ss;
        int count = 0;
        bool truncated = false; // Flag to check if truncation happened

        for (const auto& byte : data) {
            // Apply maxBytes limit (only if positive)
            if (maxBytes > 0 && count >= maxBytes) {
                ss << "...";
                truncated = true;
                break; // Stop processing bytes
            }

            if (count > 0) ss << " "; // Add space before the next byte (if not the first)

            ss << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
            count++;
        }

        // Handle edge cases for display string
        if (data.empty()) {
            return "(empty)";
        }
        // If maxBytes forced truncation and no bytes were printed (e.g., maxBytes=0)
        if (count == 0 && maxBytes == 0 && !data.empty()) {
            return "...";
        }
        // If data exists, but limit was 0 or negative, and nothing printed (shouldn't happen with loop fix)
        if (ss.str().empty() && !data.empty() && !truncated) {
            // This case might indicate an issue, but return something sensible.
            // If maxBytes <= 0, it should have printed everything.
            return "(Error Formatting Hex?)"; // Or return empty string ""
        }


        return ss.str();
    }

    std::string FormatDisplayLogEntryString(const PacketInfo& packet, int maxHexBytes) {
        std::string timestampStr = FormatTimestamp(packet.timestamp);
        const char* directionStr = (packet.direction == PacketDirection::Sent) ? "[S]" : "[R]";
        int displaySize = static_cast<int>(packet.data.size());

        std::string dataHexStr = FormatBytesToHex(packet.data, maxHexBytes);

        std::stringstream ss;
        ss << timestampStr << " "         // Timestamp (HH:MM:SS.mmm)
            << directionStr << " "         // Direction ([S] or [R])
            << packet.name << " "          // Resolved Name
            << "Op:0x" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << packet.rawHeaderId << std::dec // Opcode (Op:0xABCD)
            << " | Sz:" << displaySize     // Size (Sz:N)
            << " | " << dataHexStr;        // Hex Data (potentially truncated)

        return ss.str();
    }

    std::string FormatFullLogEntryString(const PacketInfo& packet) {
        std::string timestampStr = FormatTimestamp(packet.timestamp);
        const char* directionStr = (packet.direction == PacketDirection::Sent) ? "[S]" : "[R]";
        int displaySize = static_cast<int>(packet.data.size());

        std::string dataHexStr = FormatBytesToHex(packet.data, -1); // Format full hex data

        std::stringstream ss;
        ss << timestampStr << " "         // Timestamp (HH:MM:SS.mmm)
            << directionStr << " "         // Direction ([S] or [R])
            << packet.name << " "          // Resolved Name
            << "Op:0x" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << packet.rawHeaderId << std::dec // Opcode (Op:0xABCD)
            << " | Sz:" << displaySize     // Size (Sz:N)
            << " | " << dataHexStr;        // Hex Data (full)

        return ss.str();
    }

} // namespace kx::Utils