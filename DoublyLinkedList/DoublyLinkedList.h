#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST
#include <iostream>

template<typename T>
class DoublyLinkedList
{
private:

	struct Node 
	{
		T item; 
		Node* next; 
		Node* prev; 
	};

	int m_nrOfElements; 
	Node* m_head; 
	bool m_isEmpty; 

public:

	DoublyLinkedList()
	{
		m_nrOfElements = 0;
		m_head = nullptr;
		m_isEmpty = true;
	}

	~DoublyLinkedList()
	{
		Node* walker = m_head; 
		Node* deleteNode = m_head; 

		while (walker != nullptr)
		{
			walker = walker->next; 

			delete deleteNode->item; 
			delete deleteNode;

			deleteNode = walker; 
		}
	}

	template<typename T>
	void InsertFirst(T data)
	{
		Node* nodeInsert;
		nodeInsert = new Node{ data, nullptr, nullptr };

		if (m_isEmpty)
		{
			m_head = nodeInsert;
			m_head->prev = nullptr;
			m_head->next = nullptr;
			m_isEmpty = false;
		}
		else
		{
			m_head->prev = nodeInsert;
			nodeInsert->next = m_head;
			m_head = m_head->prev;
		}
		m_nrOfElements++;
	}

	template<typename T>
	void InsertLast(T data)
	{
		Node* nodeInsert;
		Node* temp; 
		nodeInsert = new Node { data, nullptr, nullptr };
		
		Node* walker = m_head;

		while (walker->next != nullptr)
		{
			walker = walker->next;
		}
		
		walker->next = nodeInsert;
		temp = walker;
		walker = walker->next;
		walker->prev = temp;
		walker->next = nullptr;
		m_nrOfElements++;
	}

	void DeleteFirst()
	{
		if (m_nrOfElements == 1)
		{
			delete m_head->item; 
			delete m_head;
			m_head = nullptr;
		}
		else
		{
			m_head = m_head->next;
			delete m_head->prev->item; 
			delete m_head->prev;
			m_head->prev = nullptr;
		}
		m_nrOfElements--;

		if (m_nrOfElements == 0)
			m_isEmpty = true;
	}

	void DeleteLast()
	{
		Node* walker = m_head;

		while (walker->next != nullptr)
			walker = walker->next;

		delete walker->item; 
		walker->prev->next = nullptr; 
		delete walker;
		walker = nullptr;

		m_nrOfElements--;

		if (m_nrOfElements == 0)
			m_isEmpty = true;
	}

	template<typename T>
	void InsertAfter(T data, int index)
	{
		if (index >= (m_nrOfElements - 1))
			InsertLast(data);
		else if (m_isEmpty)
			InsertFirst(data);
		else
		{
			Node* walker = m_head;
			Node* insertNode = new Node { data, nullptr, nullptr }; 

			for (int i = 0; i < index; i++)
			{
				walker = walker->next;
			}
			walker->next->prev = insertNode;
			insertNode->next = walker->next;
			walker->next = insertNode;
			insertNode->prev = walker;
			m_nrOfElements++; 
		}
	}

	void DeleteAt(int index)
	{
		if (index >= (m_nrOfElements - 1))
			DeleteLast();
		else if (index <= 0)
			DeleteFirst(); 
		else if (m_isEmpty)
			std::cout << "List is empty!" << std::endl;
		else
		{
			Node* walker = m_head;
			for (int i = 0; i < index; i++)
			{
				walker = walker->next;
			}

			if (walker->prev != nullptr)
			{
				walker->prev->next = walker->next;
				walker->next->prev = walker->prev;
			}
			else
			{
				m_head = walker->next; 
			}

			delete walker->item; 
			delete walker;
			walker = nullptr;

			m_nrOfElements--; 
		}
	}

	void DisplayForward()
	{
		Node* walker = m_head;

		while (walker != nullptr)
		{
 			std::cout << *walker->item << std::endl;
			walker = walker->next;
		}
	}

	void DisplayBackwards()
	{
		Node* walker = GetAt(m_nrOfElements - 1);

		while (walker != nullptr)
		{
			std::cout << *walker->item << std::endl;
			walker = walker->prev;
		}
	}

	Node* GetAt(int index)
	{
		Node* walker = m_head;

		for (int i = 0; i < index; i++)
		{
			walker = walker->next;
		}
		return walker;
	}

	Node* GetFirst()
	{
		return m_head;
	}
};

#endif
