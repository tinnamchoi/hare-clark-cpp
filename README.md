# hare-clark-cpp

## Usage

### Build

```sh
make build
```

### Input

* The first line contains a single integer $v$ &mdash; the number of vacancies.
* The second line contains a single integer $b$ &mdash; the number of ballots.
* The third line contains a single integer $c$ &mdash; the number of candidates.
* The fourth line contains $c$ space-separated strings &mdash; the names of the candidates
* The remaining $b$ lines each contain $c$ space-separated integers &mdash; the ballots

#### Ballots

The numbers on each ballot correspond to the names of the candidates, i.e. a candidate list such as:

```
JadenWall InayahTrevino ClarkMitchell AmeeraFerrell
```

and a ballot such as:

```
4 1 3 2
```

will indicate that the voter has `InayahTrevino` as the first preference, `AmeeraFerrell` as the second preference, `ClarkMitchell` as the third preference, and `JadenWall` as the fourth preference.

The numbers are only relative to each other within the ballot, meaning the following 2 ballots are identical:

```
1 2 3 4
1 3 10 11
```

This allows for a relatively easy removal of candidate(s).

### Running it

For an interactive experience, do

```sh
make run
```

which will prompt you for the necessary information and print the results in the terminal as well.

#### Example

```sh
[user@host hare-clark-cpp]$ make run
./a.out
Enter the number of vacancies: 2
Enter the number of votes: 8
Quota: 3.66667
Enter the number of candidates: 8
Enter the names of the candidates (space-separated): JadenWall InayahTrevino ClarkMitchell AmeeraFerrell AntonyMorrow JoseBishop VanessaPacheco TraciFrye
Enter the votes (space-/line-separated): 
2 8 5 6 1 4 3 7
8 1 7 5 2 4 3 6
5 4 1 8 2 6 7 3
1 8 6 2 3 7 5 4
3 7 8 4 5 1 6 2
4 2 1 6 3 5 8 7
1 8 4 7 3 5 2 6
6 8 1 5 2 4 3 7


== RESULTS ==
Loser: AmeeraFerrell (0.000000)
Loser: VanessaPacheco (0.000000)
Loser: TraciFrye (0.000000)
Loser: InayahTrevino (1.000000)
Loser: JoseBishop (1.000000)
Loser: AntonyMorrow (2.000000)
Winner: JadenWall (4.000000)
Winner: ClarkMitchell (4.333333)
```

Alternatively, you can put the same inputs in `in.txt` and run

```sh
make test
```

which will store the results in `out.txt`.

`in.txt` and `out.txt` are both pre-filled with an example, feel free to replace / remove them.

## Miscellaneous

Names from the examples were generated with https://www.name-generator.org.uk/quick/

Ballots were generated with the following script, which, with a time complexity of $O(rc^2)$, is so slow that I don't think it deserves a file on its own:

```python
import random

row = input("Enter the number of rows: ")
col = input("Enter the number of columns: ")

for i in range(int(row)):
    st = set(range(1, int(col)+1))
    while (len(st) > 0):
        rn = random.choice(list(st))
        st.remove(rn)
        print(rn, end=" ")
    print()
```
