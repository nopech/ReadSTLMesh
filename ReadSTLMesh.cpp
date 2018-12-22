#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ostream>
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

//namespace sierra {
int main(int argc, char** argv) 
{
    bool pippo=false;
    while(pippo){}
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
    MPI_Init(&argc, &argv);
    // Read mesh (Code from Sierra Toolkit documentation)
    MPI_Comm communicator = MPI_COMM_WORLD;
    if(stk::parallel_machine_size(communicator) == 1) {
        stk::mesh::MetaData meta;
        stk::mesh::BulkData bulk(meta, communicator);

        stk::io::StkMeshIoBroker meshReader;
        meshReader.set_bulk_data(bulk);
        meshReader.add_mesh_database(inputDBName, stk::io::READ_MESH);
        meshReader.create_input_mesh();
        meshReader.add_all_mesh_fields_as_input_fields();
        meshReader.populate_bulk_data();

        unsigned numElems = stk::mesh::count_selected_entities(meta.universal_part(), bulk.buckets(stk::topology::ELEM_RANK));
        std::cout << "numElems = " << numElems << std::endl;
    }
    
    return 0;
}
//} // namespace sierra

