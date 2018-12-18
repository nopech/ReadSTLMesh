#include <cstdlib>
#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>

#include <unistd.h>                         // for unlink
#include <stk_io/StkMeshIoBroker.hpp>       // for StkMeshIoBroker
#include <stk_mesh/base/GetEntities.hpp>    // for count_entities
#include <stk_mesh/base/MetaData.hpp>       // for MetaData
#include <stk_mesh/base/Selector.hpp>       // for Selector
#include <stk_topology/topology.hpp>        // for topology, etc
#include <string>                           // for string
#include <vector>                           // for vector
#include "stk_io/DatabasePurpose.hpp"       // for DatabasePurpose::READ_MESH


int main(int argc, char** argv) {
    std::string inputFileName = "input.i";
    std::string name;
    std::string inputDBName;
    unsigned spatialDimension;
    size_t inputMeshIdx;

    // Check input file
    std::ifstream fin(inputFileName);
    if (!fin.good()) {
        std::cerr << "Input file is not specified or does not exist: user specified (or default) name= " << inputFileName << std::endl;
        return 0;
    } else {
        std::cout << "Valid input file, continue with reading" << std::endl;
    }
    
    // Read input file
    YAML::Node input = YAML::LoadFile(inputFileName); // load the input file
    const YAML::Node realms = input["realms"]; // get all realms specified in the input file
    const YAML::Node realm = realms[0]; // get first realm specified in the input file
    name = realm["name"].as<std::string>(); // read realm name
    inputDBName = realm["mesh"].as<std::string>(); // read mesh file name
    std::cout << "Name of the mesh is " << inputDBName << std::endl;
    
    // Read mesh
//    stk::mesh::MetaData meta;
    
    
    return 0;
}

