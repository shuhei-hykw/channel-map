// -*- C++ -*-

#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>

#include <yaml-cpp/yaml.h>
#include <json/json.h>

#include "DetectorMapping.h"

namespace cmap
{

std::unordered_map<DetectorParam, FeParam> detToFe;
// std::unordered_map<FeParam, DetectorParam, FeParam::Hash> feToDet;

//_____________________________________________________________________________
void
print()
{
  try {
    std::string line_buf;
    std::string csv_buf;
    std::string input_path("channel_map.csv");

    std::ifstream ifs(input_path);
    while(std::getline(ifs, line_buf)){
      std::replace(line_buf.begin(), line_buf.end(), ',', ' ');
      std::istringstream iss(line_buf);
      // std::string detectorName, feName;
      uint32_t detectorID, groupID, layerID, upDown, segment,
        feNodeID, feBoardID, feChannel;

      iss >> feNodeID >> feBoardID >> feChannel
          >> detectorID >> groupID >> layerID >> upDown >> segment;
        // FeParam feParam(feNodeID, feBoardID, feChannel);
        // DetectorParam detParam(detectorID, groupID, layerID, upDown, segment);
      detToFe[DetectorParam{detectorID, groupID, layerID, upDown, segment}] = FeParam{feNodeID, feBoardID, feChannel};
        //      feToDet[feParam];// = {detectorID, groupID, layerID, upDown, segment};
      // while(std::getline(iss, csv_buf, ',')){
      //   std::cout << csv_buf << "\t";
      // }
      // static uint32_t i = 0;
      // std::cout << ++i << std::endl;
      // std::cout << line_buf << std::endl;
      // std::cout << "Key ("
      //           << detectorID << ", "
      //           << groupID << ", "
      //           << layerID << ", "
      //           << upDown << ", "
      //           << segment << "), Value ("
      //           << feNodeID << ", "
      //           << feBoardID << ", "
      //           << feChannel << ")"
      //           << std::endl;
    }

#if 1
    for(const auto& pair: detToFe){
      static uint32_t i = 0;
      std::cout << ++i << std::endl;
      std::cout << "Key ("
                << pair.first.detectorID << ", "
                << pair.first.groupID << ", "
                << pair.first.layerID << ", "
                << pair.first.upDown << ", "
                << pair.first.segment << "), Value ("
                << pair.second.feNodeID << ", "
                << pair.second.feBoardID << ", "
                << pair.second.feChannel << ")"
                << std::endl;
    }
#endif
    // YAML::Node yamlNode = YAML::LoadFile("test.yml");
    // // Convert YAML to JSON
    // std::string csvData = convertYamlToCsv(yamlNode);
    // std::cout << csvData << std::endl;

    // Json::StreamWriterBuilder writerBuilder;
    // std::string jsonString = Json::writeString(writerBuilder, config);
    // Display the JSON
    // std::cout << "JSON representation:" << std::endl;
    // std::cout << jsonString << std::endl;
    // display_yaml_tree(config);
  }catch(const std::exception& e){
    std::cerr << "Error: " << e.what() << std::endl;
    return;
  }
}


//_____________________________________________________________________________
std::string
convertYamlToCsv(const YAML::Node& node, const std::string& prefix = "")
{
  std::string csvString;
  if (node.IsMap()){
    for(const auto& entry : node){
      const std::string key = entry.first.as<std::string>();
      const YAML::Node& value = entry.second;

      std::string fullKey = prefix.empty() ? key : prefix + "." + key;
      csvString += convertYamlToCsv(value, fullKey);
    }
  } else if (node.IsSequence()){
    int index = 0;
    for(const auto& element : node){
      std::string fullKey = prefix + "[" + std::to_string(index) + "]";
      csvString += convertYamlToCsv(element, fullKey);
      index++;
    }
  } else {
    csvString += prefix + "," + node.as<std::string>() + "\n";
  }
  return csvString;
}

//_____________________________________________________________________________
int
get_detector()
{
  return 0;
}

void
display_yaml_tree(const YAML::Node& node, int depth = 0)
{
  for(const auto& it : node){
    for(int i = 0; i < depth; ++i){
      std::cout << "  ";  // Indentation forbetter visualization
    }

    if (it.second.IsMap() || it.second.IsSequence()){
      std::cout << it.first << ": " << std::endl;
      // Recursive call fornested nodes
      display_yaml_tree(it.second, depth + 1);
    } else {
      std::cout << it.first << ": " << it.second << std::endl;
    }
  }
}


}
