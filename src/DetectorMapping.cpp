// -*- C++ -*-

#include <iostream>
#include <yaml-cpp/yaml.h>

namespace dmap
{

//_____________________________________________________________________________
int
get_detector()
{
  return 0;
}

void
display_yaml_tree(const YAML::Node& node, int depth = 0)
{
  for (const auto& it : node) {
    for (int i = 0; i < depth; ++i) {
      std::cout << "  ";  // Indentation for better visualization
    }

    if (it.second.IsMap() || it.second.IsSequence()) {
      std::cout << it.first << ": " << std::endl;
      // Recursive call for nested nodes
      display_yaml_tree(it.second, depth + 1);
    } else {
      std::cout << it.first << ": " << it.second << std::endl;
    }
  }
}

//_____________________________________________________________________________
void
print()
{
  try {
    YAML::Node config = YAML::LoadFile("test.yml");
    display_yaml_tree(config);
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return;
  }
}

}
