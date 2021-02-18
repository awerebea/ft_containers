# ft_containers
21-School (Ecole42) 'ft_containers' project.

My own C ++ implementation of data structures such as list, vector, map, queue, stack and set with C98 member functions only.

# Usage:
In this project used [googletest](https://github.com/google/googletest.git) framework, so repo should be cloned with `--recurse-submodules` option:
```
git --recurse-submodules clone git@github.com:awerebea/ft_containers.git
```

To use a container in your code, its header file must be included accordingly :
```cpp
#include "List.hpp"
#include "Vector.hpp"
#include "Map.hpp"
#include "Queue.hpp"
#include "Stack.hpp"
#include "Set.hpp"
```

The container can then be used as usual instead of the STL version:
```cpp
int main() {
	ft::List<int> my_list;

	my_list.push_back(5);
	my_list.push_front(21);
	my_list.insert(my_list.begin(), 42);
	// etc.

	std::cout << "my_list contains:";
	for (ft::List<int>::iterator it = my_list.begin(); it != my_list.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
}
```

Output:
```
my_list contains: 42 21 5
```


### More info about C++ containers and allowed methods can be found at the links below:
[https://www.cplusplus.com/reference/list/list/](https://www.cplusplus.com/reference/list/list/)

[https://www.cplusplus.com/reference/vector/vector/](https://www.cplusplus.com/reference/vector/vector/)

[https://www.cplusplus.com/reference/map/map/](https://www.cplusplus.com/reference/map/map/)

[https://www.cplusplus.com/reference/queue/queue/](https://www.cplusplus.com/reference/queue/queue/)

[https://www.cplusplus.com/reference/stack/stack/](https://www.cplusplus.com/reference/stack/stack/)

[https://www.cplusplus.com/reference/set/set/](https://www.cplusplus.com/reference/set/set/)

## Known issues:
Googletest framework is not compiled on school Mac with included Makefile (on Linux it works fine), maybe it can be fixed somehow.
