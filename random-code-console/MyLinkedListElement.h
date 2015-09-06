#pragma once
class MyLinkedListElement
{
public:
	MyLinkedListElement() : m_next(nullptr), m_value(-1) {}
	~MyLinkedListElement();

	void AddNext(MyLinkedListElement* next) { m_next = next;  }
	MyLinkedListElement* GetNext() { return m_next;  }

	void SetValue(int value) { m_value = value; }
	int GetValue(void) { return m_value; }

private:
	MyLinkedListElement* m_next;
	int m_value;
};

