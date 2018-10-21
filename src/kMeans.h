#ifndef KMEANS_KMEANS_H
#define KMEANS_KMEANS_H

#include "lib/interfaces/clusterRelated/clusteringAlgorithms/i_distanceBasedClusteringAlgorithm.h"
#include "lib/interfaces/clusterRelated/i_clusterDistanceMeasure.h"
#include "meansInitializationAlgorithms/i_meansInitializationAlgorithm.h"

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
    kMeans(meansInitializationAlgorithmPtr meansInitializationAlgorithm,
           unsigned int k);

    std::vector<clusterPtr> groupObjects(std::vector<clusterPtr> objects);

  protected:
    meansInitializationAlgorithmPtr _meansInitializationAlgorithm;
    unsigned int _k;

    clusterDistanceMeasurePtr _clusterDistanceMeasure;
    objectDistanceMeasurePtr _objectDistanceMeasure;

    double _clusteringIndicator = 0.0, _oldClusteringIndicator = 0.0;

    bool hasEveryMeanAnObject(std::vector<clusterPtr> means);
    void assignObjectsToMeans(std::vector<clusterPtr> objects, std::vector<clusterPtr> *means);
    void recountClusteringIndicator(std::vector<clusterPtr> means);
    bool didClusteringIndicatorChange();
    void updateMeans(std::vector<clusterPtr> *means);


};




#endif //KMEANS_KMEANS_H
