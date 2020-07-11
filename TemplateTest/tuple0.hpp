template<typename... Types>
class Tuple;

//recursive case 
template<typename Head,typename... Tail>
class Tuple<Head, Tail...> {
private: 
	Head head;
	Tuple<Tail...> tail;
public:
	Tuple() {}
	Tuple(Head const& head, Tuple<Tail...> const& tail) : head(head), tail(tail) {}

	Head& getHead() { return head; }
	Head const& getHead() const { return head; }
	Tuple<Tail...>& getTail() { return tail; }
	Tuple<Tail...> const& getTail() { return tail; }
};

//basis case
template<>
class Tuple<> {};