
template<typename T>
struct Node {
	T item;
	Node* next;
	Node(T _item, Node* _next = nullptr) : item(_item), next(_next) {}
};

template<typename T>
class Stack {
public:
	bool isEmpty() {
		return first == nullptr;
	}
	void push(T item) {
		Node<T>* node = new Node<T>(item);
		node->next = first;
		first = node;
	}
	T pop() {
		auto item = first->item;
		first = first->next;
		return item;
	}
private:
	Node<T>* first = nullptr;
};