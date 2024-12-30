#!/bin/bash

echo $1
num=${1-3}
src="
import itertools
for i in itertools.permutations(map(str, range($num))):
    p = ' '.join(i)
    print(f'echo -n \'{p}:\'; ./push_swap {p} 2>/dev/null | wc -l;')
"
eval $(python -c "$src")
