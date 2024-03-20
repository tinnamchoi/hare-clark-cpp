#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()

int main() {
  int vacancies;
  cout << "Enter the number of vacancies: ";
  cin >> vacancies;
  
  int votes_n;
  cout << "Enter the number of votes: ";
  cin >> votes_n;
  
  double quota = (double)votes_n / (vacancies + 1) + 1;
  cout << "Quota: " << quota << endl;
  
  int candidates_n;
  cout << "Enter the number of candidates: ";
  cin >> candidates_n;
  
  cout << "Enter the names of the candidates (space-separated): ";
  vector<string> candidates(candidates_n);
  for (int i = 0; i < candidates_n; ++i) cin >> candidates[i];
  
  // for (int i = 0; i < candidates_n; ++i) cout << i + 1 << ". " << candidates[i] << endl;
  
  cout << "Enter the votes (space-/line-separated): ";
  vector<vector<int>> votes(votes_n, vector<int>(candidates_n));
  for (int i = 0; i < votes_n; ++i) for (int j = 0; j < candidates_n; ++j) cin >> votes[i][j];
  
  vector<pair<double, vector<int>>> sorted_votes(votes_n, {1, vector<int> (candidates_n)});
  for (int i = 0; i < votes_n; ++i) {
    iota(all(sorted_votes[i].second), 0);
    sort(all(sorted_votes[i].second), [&](int a, int b) { return votes[i][b] < votes[i][a]; });
    // cout << "Sorted: ";
    // for (int a : sorted_votes[i]) cout << a << " "; cout << endl;
  }
  
  unordered_set<int> used;
  
  cout << endl << endl;
  
  vector<double> candidate_votes(candidates_n);
  for (auto & v : sorted_votes) {
    candidate_votes[v.second.back()] += 1;
  }
  
  vector<string> log;
  
  while (vacancies) {
    int winner = -1;
    int loser = -1;
    for (int i = 0; i < candidates_n; ++i) {
      // cout << candidates[i] << ": " << candidate_votes[i] << endl;
      if (used.count(i)) continue;
      if (winner == -1 || candidate_votes[i] > candidate_votes[winner]) winner = i;
      if (loser == -1 || candidate_votes[i] < candidate_votes[loser]) loser = i;
    }
    if (candidate_votes[winner] > quota) {
      // cout << "Winner: " << candidates[winner] << endl;
      log.push_back("Winner: " + candidates[winner] + " (" + to_string(candidate_votes[winner]) + ")");
      used.insert(winner);
      --vacancies;
      double surplus = candidate_votes[winner] - quota;
      double transfer = surplus / candidate_votes[winner];
      // cout << "Transfer: " << transfer << endl;
      for (auto & v : sorted_votes) if (v.second.size() && used.count(v.second.back())) {
        // cout << v.first << ": ";
        // for (auto a : v.second) cout << a << " "; cout << endl;
        while (v.second.size() && used.count(v.second.back())) v.second.pop_back();
        v.first *= transfer;
        if (v.second.size()) candidate_votes[v.second.back()] += v.first;
      }
      candidate_votes[winner] = -2;
    } else {
      // cout << "Loser: " << candidates[loser] << endl;
      log.push_back("Loser: " + candidates[loser] + " (" + to_string(candidate_votes[loser]) + ")");
      used.insert(loser);
      for (auto & v : sorted_votes) if (v.second.size() && used.count(v.second.back())) {
        // for (auto a : v.second) cout << a << " "; cout << endl;
        while (v.second.size() && used.count(v.second.back())) v.second.pop_back();
        if (v.second.size()) candidate_votes[v.second.back()] += v.first;
      }
      candidate_votes[loser] = -1;
    }
    // cout << endl;
    // for (double & a : candidate_votes) a = ceil(a);
  }
  
  cout << "== RESULTS ==" << endl;
  for (auto & a : log) cout << a << endl;
}
