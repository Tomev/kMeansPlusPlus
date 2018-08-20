#include "kMeans.h"

kMeans::kMeans(int meansInitializationMethod) {
  switch(meansInitializationMethod){
    case KPLUSPLUS:
      break;
    case FORGY:
    default:
      break;
  }
}


/** Main method of the cluster. From vector of objects (placed inside separate clusters) the method creates a clustering
 *  structure using BIMSEC algorithm.
 *
 *  @brief Returns clusters of objects given in singular clusters.
 *
 *  @param Vector of objects inside respective clusters
 *  @return Clustered objects.
 */
std::vector<i_cluster> kMeans::groupObjects(std::vector<i_cluster> objects)
{
  std::vector<i_cluster> groupedObjects;

  selectInitialMeans();

  return groupedObjects;
}

