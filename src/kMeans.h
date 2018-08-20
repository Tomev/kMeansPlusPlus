#ifndef KMEANS_KMEANS_H
#define KMEANS_KMEANS_H

#include "lib/interfaces/clusterRelated/clusteringAlgorithms/i_distanceBasedClusteringAlgorithm.h"


enum meansInitializationMethods {
  CLASSICAL = 0,
  FORGY = 1,
  KPLUSPLUS = 2,
};

/**
 *  Implementation of classic k-means (BIMSEC) algorithm.
 */
class kMeans : protected i_distanceBasedClusteringAlgorithm {
  public:
    kMeans(int meansInitializationMethod);

    std::vector<i_cluster> groupObjects(std::vector<i_cluster> objects);
  protected:

};




#endif //KMEANS_KMEANS_H
