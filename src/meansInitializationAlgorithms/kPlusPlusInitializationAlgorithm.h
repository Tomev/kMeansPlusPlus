#ifndef KMEANS_KPLUSPLUSINITIALIZATIONALGORITHM_H
#define KMEANS_KPLUSPLUSINITIALIZATIONALGORITHM_H

#include "i_meansInitializationAlgorithm.h"
#include "../lib/interfaces/clusterRelated/i_clusterDistanceMeasure.h"

class kPlusPlusInitializationAlgorithm : public i_meansInitializationAlgorithm{
  public:
    kPlusPlusInitializationAlgorithm(clusterDistanceMeasurePtr clusterDistanceMeasure);

    std::vector<clusterPtr> selectInitialMeans(unsigned int k, std::vector<clusterPtr> clusters) override;

  protected:
    clusterDistanceMeasurePtr _clusterDistanceMeasure;

    std::vector<double> countClustersDistanceFromMeans(std::vector<clusterPtr> means, std::vector<clusterPtr> clusters);
    std::vector<double> countClustersSelectionProbabilities(std::vector<double> distances);
    unsigned int findNewMeanIndexAccordingToSelectionProbabilities(std::vector<double> selectionProbabilities);

};

#endif //KMEANS_KPLUSPLUSINITIALIZATIONALGORITHM_H
