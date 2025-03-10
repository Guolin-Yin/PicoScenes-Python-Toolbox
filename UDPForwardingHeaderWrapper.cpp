#include <optional>
#include "UDPForwardingHeader.hxx"  // The original header
#include <cstdint>

extern "C" {

// Define a simple, unpacked struct for Cython
struct MySimpleUDPForwardingHeader {
    uint32_t magicNumber;
    uint16_t version;
    uint16_t diagramTaskId;
    uint16_t diagramId;
    uint16_t numDiagrams;
    uint32_t currentDiagramLength;
    uint32_t totalDiagramLength;
    bool has_value;  // indicates success/failure
};

// A wrapper function that calls the original fromBuffer()
MySimpleUDPForwardingHeader parseUDPForwardingHeader(const uint8_t *buf) {
    MySimpleUDPForwardingHeader out;
    out.has_value = false; // default

    // Attempt to parse using original code
    if (auto optHeader = PicoScenesFrameUDPForwardingDiagramHeader::fromBuffer(buf)) {
        out.magicNumber        = optHeader->magicNumber;
        out.version            = optHeader->version;
        out.diagramTaskId      = optHeader->diagramTaskId;
        out.diagramId          = optHeader->diagramId;
        out.numDiagrams        = optHeader->numDiagrams;
        out.currentDiagramLength = optHeader->currentDiagramLength;
        out.totalDiagramLength = optHeader->totalDiagramLength;
        out.has_value          = true;
    }
    return out;
}

} // extern "C"
