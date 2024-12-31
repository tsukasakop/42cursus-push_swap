# test

- 3 permitations

```python
eval $(python -c '
import itertools
for i in itertools.permutations(["0", "1", "2"]):
    print(f"echo \"{i}\";./a.out {" ".join(i)};echo;")
')
```

- random 500 val

```sh
./push_swap $(shuf -i 1-1000000 -n 500) | wc -l
```

- leaks check

```sh
valgrind --leak-check=full ./push_swap $(shuf -i 1-1000000 -n 500)
```

- dl checker

```sh
wget https://cdn.intra.42.fr/document/document/28355/checker_linux
chmod +x checker_linux
```

- install tester

```sh
git clone git@github.com:nafuka11/push_swap_tester.git
mv checker_linux checker
cd push_swap_tester
```

```sh
python3 push_swap_tester.py -l 500 -c 100
```
