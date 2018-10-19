#ifndef KMEANS_KPLUSPLUSINITIALIZATIONALGORITHM_H
#define KMEANS_KPLUSPLUSINITIALIZATIONALGORITHM_H

#include "i_meansInitializationAlgorithm.h"

class kPlusPlusInitializationAlgorithm : public i_meansInitializationAlgorithm{
  public:
    kPlusPlusInitializationAlgorithm();

    std::vector<clusterPtr> selectInitialMeans(unsigned int k, std::vector<clusterPtr> clusters) override;
  protected:
};

#endif //KMEANS_KPLUSPLUSINITIALIZATIONALGORITHM_H
