#ifndef  MYVECTOR_H
#define  MYVECTOR_H

namespace my_vector {
	template <class T>
	class vector {
	public:
		typedef T value_type;
		typedef value_type* pointer;
		typedef value_type* iterator;
		typedef value_type& reference;
		typedef size_t size_type;
		typedef ptrdiff_t differece_type;


	};
}

#endif // ! MYVECTOR_H
