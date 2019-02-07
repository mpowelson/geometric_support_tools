#include <assimp/scene.h>
#include <memory>

namespace mesh_utils
{
/**
 * @brief Loads file at path specified into an aiScene object and returns the shared_ptr
 * @param path Path to the file
 * @return Returns a shared_ptr to the scene
 */
std::shared_ptr<aiScene> loadMeshToAssimpScene(const std::string& path);

/**
 * @brief Loads file at path specified into a vector of aiMesh objects
 * @param path Path to the file
 * @param meshes Vector to which the meshes will be appended (if vector already contains meshes, they will not be
 * overwritten)
 * @return Returns true if succesful
 */
bool loadMeshToAssimpMesh(const std::string& path, std::vector<aiMesh>& meshes);

// TODO: Add overload that combines all meshes into one aiMesh
bool loadMeshToAssimpMesh(const std::string& path, aiMesh& mesh);

// Loads to assimp and converts to PCL
bool loadMeshToPCL(const std::string& path);

// Loads to assimp and converts
bool loadMeshToVTK(const std::string& path, /* vtk polydata */ bool encode_normals);

}  // namespace mesh_utils
