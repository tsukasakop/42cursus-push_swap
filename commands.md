# test

- 3 permitations

```python
eval $(python -c '
import itertools
for i in itertools.permutations(["0", "1", "2"]):
    print(f"echo \"{i}\";./a.out {" ".join(i)};echo;")
')
```
