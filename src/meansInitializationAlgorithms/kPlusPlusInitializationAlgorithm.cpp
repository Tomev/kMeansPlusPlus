#include "kPlusPlusInitializationAlgorithm.h"
#include <cstdlib>
#include <cmath>

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
  unsigned int newMeanIndex = 0;
  newMeanIndex = rand() % clusters.size();

  // Add it to the means and remove from set of considered clusters
  means.push_back(clusters[newMeanIndex]);
  clusters.erase(clusters.begin() + newMeanIndex);

  std::vector<double> clustersDistancesFromMeans;
  std::vector<double> clustersSelectionProbabilities;

  // Repeat until desired number of means is achieved
  while(means.size() < k) {
    clustersDistancesFromMeans = countClustersDistanceFromMeans(means, clusters);
    clustersSelectionProbabilities = countClustersSelectionProbabilities(clustersDistancesFromMeans);
    newMeanIndex = findNewMeanIndexAccordingToSelectionProbabilities(clustersSelectionProbabilities);
    means.push_back(clusters[newMeanIndex]);
    clusters.erase(clusters.begin() + newMeanIndex);
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

/** Counts vector of cluster selection probabilities according to k++ algorithm.
 *
 *  @param distances - clusters distances from means set
 *  @return cluster selection probabilities
 */
std::vector<double> kPlusPlusInitializationAlgorithm::countClustersSelectionProbabilities(
    std::vector<double> distances) {
  std::vector<double> clustersSelectionProbabilities;
  double squaredDistancesSum = 0, squaredDistance = 0;


  for(double distance : distances)
  {
    squaredDistance = pow(distance, 2);
    squaredDistancesSum += squaredDistance;
    clustersSelectionProbabilities.push_back(squaredDistance);
  }

  for(double selectionProbability : clustersSelectionProbabilities)
    selectionProbability /= squaredDistancesSum;

  return clustersSelectionProbabilities;
}

/** Selects new mean according to given probabilities vector.
 *
 *  @param selectionProbabilities - probability of each cluster to be selected as new mean
 *  @return New mean index.
 */
unsigned int kPlusPlusInitializationAlgorithm::findNewMeanIndexAccordingToSelectionProbabilities(
    std::vector<double> selectionProbabilities) {
  unsigned int newMeanIndex = 0;
  double workingProbabilitiesSum = selectionProbabilities[newMeanIndex];
  double randomPercent = (double) rand() / RAND_MAX;

  while(randomPercent > workingProbabilitiesSum)
    workingProbabilitiesSum += selectionProbabilities[++newMeanIndex];

  return newMeanIndex;
}

