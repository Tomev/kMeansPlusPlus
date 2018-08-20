#ifndef KMEANS_CLASSICALMEANSINITIALIZATIONALGORITHM_H
#define KMEANS_CLASSICALMEANSINITIALIZATIONALGORITHM_H

#include "i_meansInitializationAlgorithm.h"

class classicalMeansInitializationAlgorithm : public i_meansInitializationAlgorithm {
  public:
    std::vector<i_cluster> selectInitialMeans(unsigned int k, std::vector<i_cluster> objects) override;
};

#endif //KMEANS_CLASSICALMEANSINITIALIZATIONALGORITHM_H
