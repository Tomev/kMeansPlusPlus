#include "kPlusPlusInitializationAlgorithm.h"
#include <cstdlib>

kPlusPlusInitializationAlgorithm::kPlusPlusInitializationAlgorithm(clusterDistanceMeasurePtr clusterDistanceMeasure)
: _clusterDistanceMeasure(clusterDistanceMeasure) {}


/** Main method for selecting k means from given set of clusters according to k++ algorithm.
 *
 *  @param k - desired number of means
 *  @param clusters - initial set of clusters
 *  @return
 */
std::vector<clusterPtr> kPlusPlusInitializationAlgorithm::selectInitialMeans(unsigned int k,
                                                                             std::vector<clusterPtr> clusters) {
  std::vector<clusterPtr> means;

  // Randomly select first mean
  int newMeanIndex = 0;
  newMeanIndex = rand() % clusters.size();

  // Add it to the means and remove from set of considered clusters
  means.push_back(clusters[newMeanIndex]);
  clusters.erase(clusters.begin() + newMeanIndex);

  std::vector<double> clustersDistanceFromMeans;

  // Repeat until desired number of means is achieved
  while(means.size() < k) {
    clustersDistanceFromMeans = countClustersDistanceFromMeans(means, clusters);

  }




  return means;
}

/** A method that counts distances of each cluster from clusters set from means set. It should be noted that distances
 *  indexes corresponds to cluster indexes.
 *
 *  @brief A method that counts distances of each cluster from clusters set from means set.
 *
 *  @param means - current means
 *  @param clusters  - other clusters
 *  @return distances of each clusters from means set
 */
std::vector<double> kPlusPlusInitializationAlgorithm::countClustersDistanceFromMeans(std::vector<clusterPtr> means,
                                                                                     std::vector<clusterPtr> clusters) {
  std::vector<double> distances;

  double minClusterMeanDistance = 0, currentDistance = 0;

  for(clusterPtr cluster : clusters)
  {
    minClusterMeanDistance = 0;

    for(int i = 0; i < means.size(); ++i)
    {
      currentDistance = _clusterDistanceMeasure->getClustersDistance(cluster, means[i]);
      minClusterMeanDistance = currentDistance < minClusterMeanDistance ? currentDistance : minClusterMeanDistance;
    }

    distances.push_back(minClusterMeanDistance);
  }

  return distances;
}

