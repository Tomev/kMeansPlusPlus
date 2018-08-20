#ifndef KMEANS_I_MEANSINITIALIZATIONALGORITHM_H
#define KMEANS_I_MEANSINITIALIZATIONALGORITHM_H

#include "../lib/interfaces/clusterRelated/i_cluster.h"

/** @brief Interface class for means initialization algorithm.
 *
 */
class i_meansInitializationAlgorithm {
  public:
    /** Main method of the algorithm. It returns vector of k means from given objects vector.
     *
     *  @param Vector of objects to selects initial means from and number of means k.
     *  @return Vector of initial means.
     */
    virtual std::vector<i_cluster> selectInitialMeans(unsigned int k, std::vector<i_cluster> objects) = 0;
};

#endif //KMEANS_I_MEANSINITIALIZATIONALGORITHM_H
