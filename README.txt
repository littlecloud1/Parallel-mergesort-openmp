Author: Lai Man Tang, Yuan Qin
Last modified Date: 2/4/2018
email: laimt@uci.edu, yqin@uci.edu
----------------------------------

file: parallel-mergesort.cc mergesort.o36440988

parallel-mergesort.cc:
It implements the parallel-mergesort in OpenMP. The function will first get the thread numbers. each merge function will divided depth by 2. If depth is less than one, which means spawn reach logn, it will stop spawning and run the sequential merge sort in the std <algorithm>.

mergesort.o36440988:
This result is comparing the sequential mergesort(same algorithm without using OpenMP and std <algorithm>) and the parallel-mergesort.

The parallel-mergesort can reach approximately 14X speedup.