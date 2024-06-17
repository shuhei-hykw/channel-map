// -*- C++ -*-

#include <cstdint>
#include <functional>
#include <iostream>
#include <unordered_map>

namespace cmap
{
enum EChannelMap {
  kDetectorID,
  kGroupID,
  kLayerID,
  kUpDown,
  kSegment,
  kFeNodeID,
  kFeBoardID,
  kFeChannel,
  kNChannelMap
};

struct DetectorParam
{
  uint32_t detectorID;
  uint32_t groupID;
  uint32_t layerID;
  uint32_t upDown;
  uint32_t segment;

  bool operator ==(const DetectorParam& rhs) const
  {
    bool ret=(detectorID == rhs.detectorID &&
            groupID == rhs.groupID &&
            layerID == rhs.layerID &&
            upDown == rhs.upDown &&
            segment == rhs.segment);
    if(ret){
      std::cout << "Duplicated Key ("
                << detectorID << ", "
                << groupID << ", "
                << layerID << ", "
                << upDown << ", "
                << segment << ")"
                << std::endl;
    }
    return ret;
  }
};

struct FeParam
{
  uint32_t feNodeID;
  uint32_t feBoardID;
  uint32_t feChannel;

  bool operator ==(const FeParam& rhs) const
  {
    return (feNodeID == rhs.feNodeID &&
            feBoardID == rhs.feBoardID &&
            feChannel == rhs.feChannel);
  }
};

void print();
}

namespace std
{
template<>
struct std::hash<cmap::DetectorParam> {
  std::size_t operator()(const cmap::DetectorParam& k) const {
    auto h0 = std::hash<uint32_t>()(k.detectorID);
    auto h1 = std::hash<uint32_t>()(k.groupID);
    auto h2 = std::hash<uint32_t>()(k.layerID);
    auto h3 = std::hash<uint32_t>()(k.upDown);
    auto h4 = std::hash<uint32_t>()(k.segment);
    return h0 ^ (h1<<1) ^ (h2<<2) ^ (h3<<3) ^ (h4<<4);
    // return (k.detectorID << 60) &&
    //   (k.groupID << 50) &&
    //   (k.layerID << 40) &&
    //   (k.upDown << 30) &&
    //   (k.upDown << 20) &&
    //   k.segment;
  }
};
}
