#include <iostream>	
#include <tuple>
using namespace std;
namespace test {
	//template<typename... Types>
	//void f(Types... args);

	//template<typename... Bases>
	//class X : public Bases... {
	//public:
	//	X(const Bases&... b) : Bases(b)...{}
	//};

	//X<> x0;
	//X<int> x1(1);
	//X<int, int> x2(2, 3);

	template<typename F, typename... T>
	void call(F&& f, T&&... t) {
		f(forward<T>(t)...);
	}

	template<size_t N>
	struct print_tuple {
		template<typename... T>
		typename enable_if<(N<sizeof...(T))>::type 
		print(ostream& os, const tuple<T...>& t) const {
			os << "," << get<N>(t);
			print_tuple<N + 1>().print(os, t);
		}
		template<typename... T>
		typename enable_if<!(N<sizeof...(T))>::type
		print(ostream&, const tuple<T...>&) const {}
	};

	ostream& operator<< (ostream& os, const tuple<>&) {
		return os << "{}";
	}
	template<typename... T>
	ostream& operator<< (ostream& os, const tuple<T...>& t) {
		os << "{" << get<0>(t);
		print_tuple<1>().print(os, t);
		return os << "}"; 
	}

	void user() {
		cout << make_tuple() << endl;
		cout << make_tuple<int, int, int>(1, 2, 3) << endl;
		cout << make_tuple<int, int, int, int, int, int, int, int, int, int, int, int, int, int, int>(1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) << endl;
	}
}
