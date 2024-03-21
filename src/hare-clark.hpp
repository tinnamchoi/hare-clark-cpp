#pragma once

#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

class HareClark {
 private:
  int number_of_vacancies;
  std::vector<std::string> candidates;
  std::vector<std::vector<int>> ballots;
  
  /**
   * @brief Process a candidate by redistributing their votes
   * 
   * @param candidate Candidate to be processed
   * @param unavailable_candidates Set of candidates that are unavailable
   * @param ballots_with_weights Ballots with their weights
   * @param votes Current value of votes for each candidate
   * @param transfer_value Value by which the votes should be transferred, defaulted to 1
   */
  void process_candidate(int candidate, std::unordered_set<int>& unavailable_candidates, std::vector<std::pair<std::vector<int>, double>>& ballots_with_weights, std::vector<double>& votes, double transfer_value = 1) {
    unavailable_candidates.insert(candidate);
    votes[candidate] = -1;
    for (auto& [ballot, weight] : ballots_with_weights) if (ballot.back() == candidate) {
      weight *= transfer_value;
      while (ballot.size() > 1 && unavailable_candidates.count(ballot.back())) ballot.pop_back();
      if (ballot.size()) votes[ballot.back()] += weight;
    }
  }

 public:
  /**
   * @brief Construct a new Hare Clark object
   *
   * @param number_of_vacancies Number of vacancies, defaulted to 1
   */
  HareClark(int number_of_vacancies = 1) : number_of_vacancies(number_of_vacancies) {}

  /**
   * @brief Add to the list of candidates
   *
   * @param candidates List of candidates to be added
   */
  void add_candidates(std::vector<std::string> candidates) {
    for (const std::string& candidate : candidates) this->candidates.push_back(candidate);
  }

  /**
   * @brief Add to the list of ballots
   *
   * @param ballots List of ballots to be added
   * @details Each ballot is a list of integers, where each integer represents the index of the candidate in the list of candidates.
   * @details e.g. with a candidate list of `{"A", "B", "C"}`, a ballot of `{2, 0, 1}` would represent a ballot with "C" as the first preference, "A" as the second preference, and "B" as the third preference.
   */
  void add_ballots(std::vector<std::vector<int>> ballots) {
    for (std::vector<int>& ballot : ballots) std::reverse(ballot.begin(), ballot.end());
    this->ballots.insert(this->ballots.end(), ballots.begin(), ballots.end());
  }
  
  /**
   * @brief Run the Hare-Clark process
   * 
   * @return elected_candidates List of elected candidates
   */
  std::vector<std::string> run() {
    std::vector<std::string> elected_candidates; // List of elected candidates
    std::unordered_set<int> unavailable_candidates; // Set of candidates that are either elected or eliminated
    const double quota = (double)ballots.size() / (number_of_vacancies + 1) + 1; // Droop quota

    std::vector<std::pair<std::vector<int>, double>> ballots_with_weights; // Ballots and their current weights
    for (const std::vector<int>& ballot : ballots) ballots_with_weights.push_back({ballot, 1});
    
    std::vector<double> votes(candidates.size()); // Current value of votes for each candidate
    for (const auto& [ballot, weight] : ballots_with_weights) votes[ballot.back()] += weight;
    
    while (number_of_vacancies < candidates.size() - unavailable_candidates.size()) {
      int winner = -1;
      int loser = -1;
      for (int i = 0; i < candidates.size(); ++i) {
        if (unavailable_candidates.count(i)) continue;
        if (winner == -1 || votes[i] > votes[winner]) winner = i;
        if (loser == -1 || votes[i] < votes[loser]) loser = i;
      }
      // If the winner has more votes than the quota, they are elected
      if (votes[winner] > quota) {
        double surplus = votes[winner] - quota;
        double transfer_value = surplus / votes[winner];
        process_candidate(winner, unavailable_candidates, ballots_with_weights, votes, transfer_value);
        elected_candidates.push_back(candidates[winner]);
        votes[winner] = -2;
        --number_of_vacancies;
      // Otherwise, the loser is eliminated
      } else {
        process_candidate(loser, unavailable_candidates, ballots_with_weights, votes);
        votes[loser] = -1;
      }
    }
    if (number_of_vacancies) {
      for (int i = 0; i < candidates.size(); ++i) if (!unavailable_candidates.count(i)) elected_candidates.push_back(candidates[i]);
    }
    return elected_candidates;
  }
};
