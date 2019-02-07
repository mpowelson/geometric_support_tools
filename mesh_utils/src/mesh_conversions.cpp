#include "mesh_conversions.h"
#include <pcl/point_cloud.h>
#include <pcl/PolygonMesh.h>
#include <pcl/point_types.h>
#include <pcl/conversions.h>

bool mesh_utils::AssimpMeshToPCL(aiMeshConstPtr assimp_mesh, pcl::PolygonMeshPtr pcl_mesh)
{
  unsigned int nface = assimp_mesh->mNumFaces;
  unsigned int nvert = assimp_mesh->mNumVertices;

  // Because we have xyz points, we will fill out a PointCloud and convert it to PointCloud2
  pcl::PointCloud<pcl::PointXYZ> point_cloud;
  point_cloud.is_dense = true;

  // Loop over vertices - adding them to the point cloud
  for (unsigned int ind = 0; ind < nvert; ++ind)
  {
    // Convert Assimp pt to PCL pt
    auto pt_assimp = assimp_mesh->mVertices[ind];
    pcl::PointXYZ pt(pt_assimp.x, pt_assimp.y, pt_assimp.z);
    // Add it to PointCloud
    point_cloud.push_back(pt);
  }

  // Convert PointCloud to PointCloud2
  pcl::PCLPointCloud2 point_cloud_2;
  pcl::toPCLPointCloud2(point_cloud, point_cloud_2);
  pcl_mesh->cloud = point_cloud_2;

  // Loop over faces, adding them to polygon list
  for (unsigned int ind = 0; ind < nface; ++ind)
  {
    unsigned int num_vertices_in_face = assimp_mesh->mFaces[ind].mNumIndices;

    pcl::Vertices pcl_face;

    // Add all vertices in the Assimp face to the PCL face
    for (unsigned int ind2 = 0; ind2 < num_vertices_in_face; ++ind2)
    {
      pcl_face.vertices.push_back(assimp_mesh->mFaces[ind].mIndices[ind2]);
    }
    pcl_mesh->polygons.push_back(pcl_face);
  }
  return true;
}

// Not super confident this isn't going to have runtime issues with the assimp arrays
bool mesh_utils::PCLMeshToAssimp(pcl::PolygonMeshConstPtr pcl_mesh, aiMeshPtr assimp_mesh)
{
  // Convert to PointCloud for easier interface with assimp
  pcl::PointCloud<pcl::PointXYZ> point_cloud;
  pcl::fromPCLPointCloud2(pcl_mesh->cloud, point_cloud);

  unsigned int nface = static_cast<unsigned int>(pcl_mesh->polygons.size());
  unsigned int nvert = static_cast<unsigned int>(point_cloud.points.size());

  // Loop over vertices - adding them to the point cloud
  for (unsigned int ind = 0; ind < nvert; ++ind)
  {
    // Assimp mesh vertices are stored in an array preallocated to 0x7fffffff
    assimp_mesh->mVertices[ind].x = point_cloud.points[ind]._PointXYZ::x;
    assimp_mesh->mVertices[ind].y = point_cloud.points[ind]._PointXYZ::y;
    assimp_mesh->mVertices[ind].z = point_cloud.points[ind]._PointXYZ::z;
  }

  // Loop over faces, adding them to polygon list
  for (unsigned int ind = 0; ind < nface; ++ind)
  {
    unsigned int num_vertices_in_face = static_cast<unsigned int>(pcl_mesh->polygons[ind].vertices.size());

    // Add all vertices in the Assimp face to the PCL face
    for (unsigned int ind2 = 0; ind2 < num_vertices_in_face; ++ind2)
    {
      assimp_mesh->mFaces[ind].mIndices[ind2] = pcl_mesh->polygons[ind].vertices[ind2];
    }
  }
  return true;
}
