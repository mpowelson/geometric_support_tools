#include <assimp/mesh.h>
#include <pcl/PolygonMesh.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

namespace mesh_utils
{
typedef std::shared_ptr<aiMesh> aiMeshPtr;
typedef const std::shared_ptr<aiMesh> aiMeshConstPtr;

// Note: Header has not been filled
bool AssimpMeshToPCL(aiMeshConstPtr assimp_mesh, pcl::PolygonMeshPtr pcl_mesh);

bool PCLMeshToAssimp(pcl::PolygonMeshConstPtr, aiMeshPtr assimp_mesh);

bool AssimpMeshToVTK(aiMeshConstPtr assimp_mesh, vtkSmartPointer<vtkPolyData> vtk_mesh);

bool VTKMeshToAssimp(const vtkSmartPointer<vtkPolyData> vtk_mesh, aiMeshPtr assimp_mesh);

}  // namespace mesh_utils
