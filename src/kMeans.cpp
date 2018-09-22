#include "kMeans.h"
#include <limits>

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
  std::vector<clusterPtr> means;

  while (hasEveryMeanAnObject(means));
  {
    means = _meansInitializationAlgorithm->selectInitialMeans(_k, objects);
    assignObjectsToMeans(objects, &means);
  }

  recountClusteringIndicator();
  // assignObjectToMeans;
  // recountClusteringIndicator;
  //


  return groupedObjects;
}

/** Checks if every mean has at least one cluster.
 *
 *  @brief Checks if every mean has at least one cluster.
 *
 *  @param means - vector of means
 *  @return A decision if every mean has at least one cluster appointed.
 */
bool kMeans::hasEveryMeanAnObject(std::vector<clusterPtr> means) {
  if (means.size() == 0) return false;

  for (clusterPtr mean : means)  if(mean->getCount() == 0) return false;

  return true;
}

/** Assigns objects to means. Note that means should be empty, as this method doesn't clean them.
 *
 *  @brief Assigns objects to means.
 *
 *  @param objects - vector of objects to cluster (given as clusters)
 *  @param means - vector of current means
 */
void kMeans::assignObjectsToMeans(std::vector<clusterPtr> objects, std::vector<clusterPtr> *means) {
  clusterPtr closestMean;
  double currentMinimalDistanceValue = 0.0, currentDistanceValue = 0.0;

  for(clusterPtr object : objects) {

    currentMinimalDistanceValue = std::numeric_limits<double>::max();

    for(clusterPtr mean : *means) {
      currentDistanceValue = _clusterDistanceMeasure->getClustersDistance(mean, object);

      if(currentDistanceValue < currentMinimalDistanceValue) {
        currentMinimalDistanceValue = currentDistanceValue;
        closestMean = mean;
      }
    }

    closestMean->addSubcluster(object);
  }
}

void kMeans::recountClusteringIndicator(std::vector<clusterPtr> means) {

}
