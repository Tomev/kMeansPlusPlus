#include "kMeans.h"

kMeans::kMeans(meansInitializationAlgorithmPtr meansInitializationAlgorithm, unsigned int k) {
  _meansInitializationAlgorithm = meansInitializationAlgorithm;
  _k = k;
}

/** Main method of the cluster. From vector of objects (placed inside separate clusters) the method creates a clustering
 *  structure using BIMSEC algorithm.
 *
 *  @brief Returns clusters of objects given in singular clusters.
 *
 *  @param Vector of objects inside respective clusters
 *  @return Clustered objects.
 */
std::vector<clusterPtr> kMeans::groupObjects(std::vector<clusterPtr> objects)
{
  std::vector<clusterPtr> groupedObjects;
  std::vector<clusterPtr> means =
    _meansInitializationAlgorithm->selectInitialMeans(_k, objects);

  


  return groupedObjects;
}

