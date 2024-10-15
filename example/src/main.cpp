#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()

#include "hare-clark.hpp"

int main() {
  int number_of_vacancies;
  cout << "Enter the number of vacancies: ";
  cin >> number_of_vacancies;
  
  int number_of_votes;
  cout << "Enter the number of votes: ";
  cin >> number_of_votes;
  
  int number_of_candidates;
  cout << "Enter the number of candidates: ";
  cin >> number_of_candidates;
  
  cout << "Enter the names of the candidates (space-separated): ";
  vector<string> candidates(number_of_candidates);
  for (int i = 0; i < number_of_candidates; ++i) cin >> candidates[i];
  
  cout << "Enter the ballots (space-/line-separated): ";
  vector<vector<int>> ballots(number_of_votes, vector<int>(number_of_candidates));
  for (int i = 0; i < number_of_votes; ++i) for (int j = 0; j < number_of_candidates; ++j) cin >> ballots[i][j];
  
  vector<vector<int>> sorted_ballots(number_of_votes, vector<int> (number_of_candidates));
  for (int i = 0; i < number_of_votes; ++i) {
    iota(all(sorted_ballots[i]), 0);
    sort(all(sorted_ballots[i]), [&](int a, int b) { return ballots[i][a] != -1 && (ballots[i][b] == -1 || ballots[i][a] < ballots[i][b]); });
    while (sorted_ballots[i].size() && ballots[i][sorted_ballots[i].back()] == -1) sorted_ballots[i].pop_back();
  }
  
  HareClark hc(number_of_vacancies);
  
  hc.add_candidates(candidates);
  hc.add_ballots(sorted_ballots);
  
  vector<string> elected_candidates = hc.run();
  
  cout << endl << endl << "Elected candidates: ";
  for (const string& candidate : elected_candidates) cout << candidate << " ";
  cout << endl;
  
  return 0;
}
