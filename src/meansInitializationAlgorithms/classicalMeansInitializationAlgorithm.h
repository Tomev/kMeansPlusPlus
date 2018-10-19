#ifndef KMEANS_CLASSICALMEANSINITIALIZATIONALGORITHM_H
#define KMEANS_CLASSICALMEANSINITIALIZATIONALGORITHM_H

#include "i_meansInitializationAlgorithm.h"

class classicalMeansInitializationAlgorithm : public i_meansInitializationAlgorithm {
  public:
    std::vector<clusterPtr> selectInitialMeans(unsigned int k, std::vector<clusterPtr> clusters) override;
};

#endif //KMEANS_CLASSICALMEANSINITIALIZATIONALGORITHM_H
