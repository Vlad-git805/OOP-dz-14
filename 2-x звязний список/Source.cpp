
#include <iostream>
using namespace std;

template<class T>
class List
{
private:
	struct Node
	{
		T value;	
		Node* next;	
		Node* prev;	
	};

	Node* head;	
	Node* tail; 

	int size;	

public:
	List() : head(nullptr), tail(nullptr), size(0) { }

	List(const List& other)
	{
		Node* current = other.head;
		while (current != nullptr)
		{
			AddToTail(current->value);
			current = current->next;
		}
	}

	List(List&& other)
	{
		this->head = other.head;
		this->size = other.size;
		other.head = nullptr;
		other.size = 0;
	}

	List& operator=(const List& other)
	{
		if (this == &other)
			return *this;

		if (this != nullptr)
		{
			while (!IsEmpty())
			{
				DeleteHead();
			}
		}
		Node* current = other.head;
		while (current != nullptr)
		{
			AddToTail(current->value);
			current = current->next;
		}
		return *this;
	}

	List& operator=(List&& other)
	{
		if (this == &other)
			return *this;

		if (this != nullptr)
		{
			while (!IsEmpty())
			{
				DeleteHead();
			}
		}
		
		this->head = other.head;
		this->size = other.size;
		other.head = nullptr;
		other.size = 0;
		return *this;
	}

	List operator-()
	{
		List new_list;

		for (Node* current = tail; current != nullptr; current = current->prev)
		{
			new_list.AddToTail(current->value);
		}
		
		return new_list;
	}

	List operator+(const List& other)
	{
		List new_list;

		Node* current = this->head;
		for (int i = 0; i < this->size; i++)
		{
			new_list.AddToTail(current->value);
			current = current->next;
		}

		Node* current2 = other.head;
		for (int i = 0; i < other.size; i++)
		{
			new_list.AddToTail(current2->value);
			current2 = current2->next;
		}

		return new_list;
	}

	List operator*(const List&other)
	{
		List new_list;

		Node* current = this->head;
		//for (Node* current = head; current != nullptr; current = current->next)
		for (int i = 0; i < this->size; i++)
		{
			Node* current2 = other.head;
			for (int i = 0; i < other.size; i++)
			{
				if (current->value == current2->value)
				{
					new_list.AddToTail(current2->value);
					break;
				}											 
															
				current2 = current2->next;
			}
			current = current->next;
		}
		
		return new_list;
	}

	~List()
	{
		DeleteAll();
	}

	bool IsEmpty() const
	{
		return size == 0;
	}
	int GetCount() const
	{
		return size;
	}

	void AddToHead(T value)
	{
		Node* newElem = new Node;
		newElem->value = value;
		newElem->next = head;
		newElem->prev = nullptr;

		if (IsEmpty())
		{
			head = tail = newElem;
		}
		else
		{
			head->prev = newElem;
			head = newElem;
		}
		++size;
	}

	void AddToTail(T value)
	{
		Node* newElem = new Node;
		newElem->value = value;
		newElem->next = nullptr;
		newElem->prev = tail;

		if (IsEmpty())
		{
			head = tail = newElem;
		}
		else
		{
			tail->next = newElem;
			tail = newElem;
		}
		++size; 
	}

	void DeleteHead()
	{
		if (IsEmpty()) return;

		Node* temp = head->next;
		delete head;

		if (temp == nullptr)
		{
			head = tail = nullptr;
		}
		else
		{
			temp->prev = nullptr;
			head = temp;
		}
		--size; 
	}

	void DeleteTail()
	{
		if (IsEmpty()) return;

		if (head->next == nullptr)
		{
			delete head;
			head = tail = nullptr;
		}
		else
		{
			Node* temp = tail->prev;

			delete temp->next;
			temp->next = nullptr;
			tail = temp;
		}
		--size; 
	}

	void Add(T value, int pos)
	{
		if (pos <= 0 || pos > size + 1) return;

		if (pos == 1)
		{
			AddToHead(value);
			return;
		}
		if (pos == size + 1)
		{
			AddToTail(value);
			return;
		}

		int count = size / 2;

		Node* newElem = new Node;
		newElem->value = value;

		Node* current = head;

		if (count > pos)
		{
			for (int i = 0; i < pos - 1; ++i)
			{
				current = current->next;
			}
		}
		else if (count <= pos)
		{
			for (int i = size; i > (size - pos) + 1; --i)
			{
				current = current->next;
			}
		}

		newElem->prev = current->prev;
		current->prev->next = newElem;

		current->prev = newElem;
		newElem->next = current;

		++size; 
	}

	int Find(T data)
	{
		Node* current = head;

		for (int i = 0; i < size; i++)
		{
			if (current->value == data)
			{
				return i;
			}
			current = current->next;
		}
		return 0;
	}

	int Peplace(T oldValue, T newValue)
	{
		Node* current = head;
		int count = 0;
		for (int i = 0; i < size; i++)
		{
			if (current->value == oldValue)
			{
				current->value = newValue;
				++count;
			}
			current = current->next;
		}
		return count;
	}

	void Delete(int pos)
	{
		if (pos <= 0 || pos > size) return;

		if (pos == 1)
		{
			DeleteHead();
			return;
		}
		if (pos == size)
		{
			DeleteTail();
			return;
		}

		int count = size / 2;

		Node* current = head;

		if (count > pos)
		{
			for (int i = 0; i < pos - 1; ++i)
			{
				current = current->next;
			}
		}
		else if (count <= pos)
		{
			for (int i = size; i > (size - pos) + 1; --i)
			{
				current = current->next;
			}
		}

		current->prev->next = current->next;
		current->next->prev = current->prev;
		delete current;

		--size; 
	}

	void Print() const
	{
		for (Node* current = head; current != nullptr; current = current->next)
		{
			cout << current->value << ", ";
		}
	}

	void DeleteAll()
	{
		//DelAll();
		while (!IsEmpty())
		{
			DeleteHead();
		}
	}
};

int main()
{
	/*List ls;

	ls.AddToHead(10);
	ls.AddToHead(15);
	ls.AddToHead(5);
	ls.AddToHead(20);

	ls.Print(); cout << endl;

	ls.DeleteHead();
	ls.AddToTail(777);*/

	////////////////////

	/*ls.Print(); cout << endl;

	ls.DeleteTail();
	ls.DeleteTail();

	ls.Print(); cout << endl;

	ls.AddToHead(10);
	ls.AddToHead(15);
	ls.AddToHead(5);
	ls.AddToHead(20);

	ls.Print(); cout << endl;

	ls.DeleteHead();
	ls.AddToTail(777);

	ls.Print(); cout << endl;

	ls.DeleteTail();
	ls.DeleteTail();

	ls.Print(); cout << endl;

	ls.AddToHead(55);
	ls.AddToHead(33);

	ls.AddToTail(990);
	ls.AddToTail(676);

	ls.Print(); cout << endl;

	ls.Add(3, 3);
	ls.Add(7, 7);

	ls.Print(); cout << endl;

	ls.Delete(3);
	ls.Print(); cout << endl;

	ls.Delete(7);
	ls.Print(); cout << endl;*/

	List<int> ls;

	ls.AddToHead(15);
	ls.AddToHead(10);
	ls.AddToHead(10);
	ls.AddToHead(20);
	ls.Print(); cout << endl;

	/*ls.AddToHead(10);
	ls.AddToHead(123);
	ls.AddToHead(321);
	ls.AddToHead(40);
	ls.AddToHead(105);
	ls.AddToHead(78);

	ls.Print(); cout << endl;
	ls.Add(100, 8);
	ls.Print(); cout << endl;
	ls.Add(125, 9);
	ls.Print(); cout << endl;
	ls.Delete(8);
	ls.Print(); cout << endl;
	ls.Delete(2);
	ls.Print(); cout << endl;*/

	List<int> ls2;

	ls2.AddToHead(15);
	ls2.AddToHead(15);
	ls2.AddToHead(40);
	ls2.AddToHead(105);
	ls2.Print(); cout << endl;

	List<int> ls3;

	//ls3 = -ls2;
	//ls3 = ls * ls2;
	ls3 = ls + ls2;

	ls3.Print();
	system("pause");
	return 0;
}