# hare-clark-cpp

Hare-Clark is an electoral system used in Tasmania and the Australian Capital Territory. To read more on how the preferential votes are distributed, please refer to [the Wikipedia article](https://en.wikipedia.org/wiki/Hare%E2%80%93Clark_electoral_system), which is what this implementation is mostly based off of.

Additional sources:
* https://www.tec.tas.gov.au/info/Publications/HareClark.html
* https://www.aec.gov.au/learn/files/poster-count-senate-pref-voting.pdf
* https://www.aec.gov.au/learn/files/poster-counting-hor-pref-voting.pdf
* https://facultycouncil.utexas.edu/hare-clark-preferential-voting-system

## Usage

This is a single-header library. To use this, simply download the `src/hare-clark.hpp` file into your project and `#include "hare-clark.hpp"`.

However, it is recommended that you add this repository as a submodule using `git submodule add https://github.com/tinnamchoi/hare-clark-cpp` to make updating the library easier. Read more on Git submodules [here](https://git-scm.com/book/en/v2/Git-Tools-Submodules).

### Functions

#### `HareClark(int number_of_vacancies = 1)`

Construct a new Hare Clark object

| Parameters            | Description                         |
| --------------------- | ----------------------------------- |
| `number_of_vacancies` | Number of vacancies, defaulted to 1 |

#### `void add_candidates(std::vector<std::string> candidates)`

Add to the list of candidates

| Parameters   | Description                    |
| ------------ | ------------------------------ |
| `candidates` | List of candidates to be added |

#### `void add_ballots(std::vector<std::vector<int>> ballots)`

Add to the list of ballots

| Parameters | Description                 |
| ---------- | --------------------------- |
| `ballots`  | List of ballots to be added |

Each ballot is a list of integers, where each integer represents the index of the candidate in the list of candidates.

e.g. with a candidate list of `{"A", "B", "C"}`, a ballot of `{2, 0, 1}` would represent a ballot with "C" as the first preference, "A" as the second preference, and "B" as the third preference.

#### `std::vector<std::string> run()`

Run the Hare-Clark process

| Returns              | Description                |
| -------------------- | -------------------------- |
| `elected_candidates` | List of elected candidates |

## Examples

For a practical example of the library being applied, see [example/README.md](example/README.md)
