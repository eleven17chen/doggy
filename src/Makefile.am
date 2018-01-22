
cpp_programs=private_inherit diff_returntype

system_programs= volatile

dna_programs=dna33_01 dna34_01 dna35_01 dna35_02 dna35_03 dna36_01 dna36_02

af_programs=af171101_01 af171110_01 af171113_01 # af171114_01

myalgo_programs=lockfree_queue spinlock BinaryTree AVLTree bubble_sort quick_sort my_quick_sort eight_queen

noinst_PROGRAMS=doggy Hello_C $(dna_programs) $(af_programs) $(myalgo_programs) $(system_programs) $(cpp_programs)

doggy_SOURCES=hello2.cpp

Hello_C_SOURCES=computer/hello.c

dna33_01_SOURCES=level0/datastructure_and_algo/33/dna33_01.cpp
dna34_01_SOURCES=level0/datastructure_and_algo/34/dna34_01.cpp
dna35_01_SOURCES=level0/datastructure_and_algo/35/dna35_01.cpp
dna35_02_SOURCES=level0/datastructure_and_algo/35/dna35_02.cpp
dna35_03_SOURCES=level0/datastructure_and_algo/35/dna35_03.cpp
dna36_01_SOURCES=level0/datastructure_and_algo/36/dna36_01.cpp
dna36_02_SOURCES=level0/datastructure_and_algo/36/dna36_02.cpp

af171101_01_SOURCES=level0/algorithm_fan/20171101/af171101_01.cpp
af171110_01_SOURCES=level0/algorithm_fan/20171110/af171110_01.cpp
af171113_01_SOURCES=level0/algorithm_fan/20171113/af171113_01.cpp
# af171114_01_SOURCES=level0/algorithm_fan/20171114/af171114_01.cpp

lockfree_queue_SOURCES=level0/myalgo/queue/lockfree_queue.cpp
lockfree_queue_LDFLAGS= -pthread

spinlock_SOURCES=level0/myalgo/lock/spinlock.cpp
spinlock_LDFLAGS= -pthread

volatile_SOURCES=level0/system/volatile.cpp

private_inherit_SOURCES=level0/cpp/private_inherit.cpp
diff_returntype_SOURCES=level0/cpp/diff_returntype.cpp

BinaryTree_SOURCES=level0/myalgo/tree/BinaryTree.cpp
AVLTree_SOURCES=level0/myalgo/tree/AVLTree.cpp
TwoThreeTree_SOURCES=level0/myalgo/tree/TwoThreeTree.cpp
bubble_sort_SOURCES=level0/myalgo/sort/bubble_sort.cpp
quick_sort_SOURCES=level0/myalgo/sort/quick_sort.cpp
my_quick_sort_SOURCES=level0/myalgo/sort/quick_sort.cpp
eight_queen_SOURCES=level0/myalgo/nqueen/eight_queen.cpp
