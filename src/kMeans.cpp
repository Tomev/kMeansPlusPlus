#include "kMeans.h"
#include <limits>
#include <cmath>

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

  while (!hasEveryMeanAnObject(means))
  {
    means = _meansInitializationAlgorithm->selectInitialMeans(_k, objects);
    assignObjectsToMeans(objects, &means);
  }

  recountClusteringIndicator(means);

  while (didClusteringIndicatorChange())
  {
    updateMeans(&means);
    assignObjectsToMeans(objects, &means);
    recountClusteringIndicator(means);
  }

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
  clusterablePtr currentObject;
  double currentMinimalDistanceValue = 0.0, currentDistanceValue = 0.0;

  for(clusterPtr object : objects) {

    currentObject = object->getObject();
    currentMinimalDistanceValue = std::numeric_limits<double>::max();

    for(clusterPtr mean : *means) {
      currentDistanceValue = _objectDistanceMeasure->getObjectsDistance(mean->getMean(), currentObject);

      if(currentDistanceValue < currentMinimalDistanceValue) {
        currentMinimalDistanceValue = currentDistanceValue;
        closestMean = mean;
      }
    }

    closestMean->addSubcluster(object);
  }
}

/** Updates clustering indicators. Current clustering indicator becomes old one, and new one is count
 *  in its place.
 *
 *  @param Current means.
 */
void kMeans::recountClusteringIndicator(std::vector<clusterPtr> means) {
  _oldClusteringIndicator = _clusteringIndicator;
  _clusteringIndicator = 0;

  std::vector<clusterPtr> currentMeanSubclusters;
  clusterablePtr currentMean;

  for(clusterPtr mean : means) {
    currentMeanSubclusters = mean->getSubclusters();
    currentMean = mean->getMean();
    for(clusterPtr subcluster : currentMeanSubclusters) {
      _clusteringIndicator +=
          pow(_objectDistanceMeasure->getObjectsDistance(currentMean, subcluster->getObject()), 2);
    }
  }
}

/** Checks if clustering indicator values changed after last recount.
 *
 *  @return The result of the check.
 */
bool kMeans::didClusteringIndicatorChange() {
  return fabs(_oldClusteringIndicator - _clusteringIndicator) < 1e-5;
}

/** Updates each mean form means set according to current subclusters and clears subclusters set.
 *
 *  @param means - current means.
 */
void kMeans::updateMeans(std::vector<clusterPtr> *means) {
  for(clusterPtr mean : *means)
  {
    mean->updateMean();
    mean->clearSubclusters();
  }
}
