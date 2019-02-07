#include <assimp/Importer.hpp>   // C++ importer interface
#include <assimp/scene.h>        // Output data structure
#include <assimp/postprocess.h>  // Post processing flags
#include <iostream>              //TODO: Replace with logging

#include "mesh_importers.h"

std::shared_ptr<aiScene> mesh_utils::loadMeshToAssimpScene(const std::string& path)
{
  Assimp::Importer importer;

  // TODO: Explore the postprocessing steps (http://assimp.sourceforge.net/lib_html/postprocess_8h.html) in particular:
  // aiProcess_FixInfacingNormals , aiProcess_GenNormals , aiProcess_GenSmoothNormals,
  // aiProcess_FindDegenerates(particulary about removing lines)
  const aiScene* scene_temp = importer.ReadFile(path,
                                                aiProcess_CalcTangentSpace | aiProcess_Triangulate |
                                                    aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

  // If the import failed
  if (!scene_temp)
  {
    std::cout << "aiScene Import Failed!\n";
    return std::shared_ptr<aiScene>(nullptr);
  }
  // Creates a shared_ptr to the scene and releases ownership of the scene from the Importer
  std::shared_ptr<aiScene> output(importer.GetOrphanedScene());

  // We're done. Everything will be cleaned up by the importer destructor
  return output;
}

bool mesh_utils::loadMeshToAssimpMesh(const std::string& path, std::vector<aiMesh>& meshes)
{
  std::shared_ptr<aiScene> scene = mesh_utils::loadMeshToAssimpScene(path);

  if (!scene)
  {
    std::cout << "aiMesh Import Failed!\n";
    return false;
  }
  const unsigned int num_meshes = scene->mNumMeshes;
  if (num_meshes == 0)
  {
    std::cout << "File contained no meshes!\n";
    return false;
  }

  // Loop over all meshes. In many cases, there will be only one
  unsigned int nface = 0;
  unsigned int nvert = 0;
  for (unsigned int ind = 0; ind < num_meshes; ind++)
  {
    // Copy the meshes into the vector
    aiMesh* mesh = scene->mMeshes[ind];
    meshes.push_back(*mesh);

    // Keep running total of number of faces/vertices
    nface += mesh->mNumFaces;
    nvert += mesh->mNumVertices;
  }

  // Check that the meshes weren't all empty
  if (nface == 0)
  {
    std::cout << "File contained no valid faces!\n";
    return false;
  }
  if (nvert == 0)
  {
    std::cout << "File contained no valid vertices!\n";
    return false;
  }

  return true;
}

bool mesh_utils::loadMeshToAssimpMesh(const std::string& path, aiMesh& mesh)
{
  std::cout << "Combining the meshes is currently unimplemented";
  return false;
}
