### Build Code

Build code

```sh
g++ -o main main.cpp SelfOrganizingList.cpp 
```

Run executable
```sh
./main
```


### About the Project

Linked lists are a fundamental data structure used commonly in many ADT implementations. For instance, linked lists can be found in implementations of stacks and ques, graphs, etc. The power of linked lists is in their ability to quickly insert and delete data. With a wort case time complexity of O(1) for both insertion and deletion. Although an area of improvement for linked lists is its search operation. The worst time complexity for searching a linked list is O(n). Which can raise speed issues if the application of the structure requires a high volume of accessing. This problem can be addressed through organizing the list by how often each element is accessed, namely Self Organizing lists (Count Approach).

Self Organizing lists aim to optimize linear search time by placing the most commonly accessed items at the front of the list. The best-case time complexity for search is O(1). Although it is key to note, Self Organizing lists do not guarantee that the search time will be faster than a linked list, however it will decrease the probability of the worst case from occurring. The worst case for search will still match linked lists with a time complexity of O(n). So, the idea is that self organizing lists will have a better average case than linked lists. 

The count approach addresses this issue by storing a data member that accumulates the number of times that element was accessed. There are other approaches such as the Transpose approach and Move-To-Front approach, which all have the same means but different methods. 

A few applications of Self Organizing lists are used in neural networks to cluster meaningful and similar data. They can also be seen in caching algorithms to optimize access time by sorting relevant and frequently locations in memory.
