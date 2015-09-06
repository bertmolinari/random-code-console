// random-code-console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MyLinkedListElement.h"

#include <cstdlib>

MyLinkedListElement* BuildLinkedList(int size);
MyLinkedListElement* RemoveLinkedListElement(MyLinkedListElement* head, int value);
MyLinkedListElement* PartitionLinkedList(MyLinkedListElement* head, int value);
int GetRandomElementValue(MyLinkedListElement* head);

void PrintLinkedList(MyLinkedListElement* head);

const int c_listSize = 30;

int main()
{
	MyLinkedListElement* head = BuildLinkedList(c_listSize);
	::printf("---Initial list.\n");
	PrintLinkedList(head);

	int value = ::GetRandomElementValue(head);
	::printf("---Selected value: %d.\n", value);

	MyLinkedListElement* newHead = RemoveLinkedListElement(head, value);
	::printf("---List after removal.\n");
	PrintLinkedList(newHead);

	value = ::GetRandomElementValue(head);
	::printf("---Selected value: %d.\n", value);
	newHead = PartitionLinkedList(head, value);
	::printf("---List after partitioning.\n");
	PrintLinkedList(newHead);

	return 0;
}

// Creates a linked list of size N with each element storing it's position in the list as it's value.
MyLinkedListElement* BuildLinkedList(int size)
{
	MyLinkedListElement* head = nullptr;
	MyLinkedListElement* prev = nullptr;

	if (size == 0)
		return nullptr;

	// create the linked list.
	for (int i = 0; i < size; ++i)
	{
		MyLinkedListElement* element = new MyLinkedListElement();
		int value = ::rand() % 1000;

		element->SetValue(value);
		if (prev)
		{
			prev->AddNext(element);
			prev = element;
		}
		else
		{
			head = element;
			prev = head;
		}
	}



	return head;
}

MyLinkedListElement* RemoveLinkedListElement(MyLinkedListElement* element, int value)
{
	MyLinkedListElement* prev = element;
	MyLinkedListElement* next;

	if (prev->GetValue() == value)
	{
		return prev->GetNext();
	}

	bool done = false;
	while (!done)
	{
		next = prev->GetNext();
		if (next != nullptr && next->GetValue() == value)
		{
			prev->AddNext(next->GetNext());
			delete next;
			done = true;
		}
		else
		{
			prev = prev->GetNext();
		}

		if (prev == nullptr)
		{
			done = true;
		}
	}

	return element;
}

void PrintLinkedList(MyLinkedListElement* head)
{
	// walk the linked list and print out the values at each element.
	MyLinkedListElement* current = head;
	while (current != nullptr)
	{
		::printf("%d\n", current->GetValue());
		current = current->GetNext();
	}
}

int GetRandomElementValue(MyLinkedListElement* head)
{
	int position = ::rand() % c_listSize;
	MyLinkedListElement* current = head;

	while (position--)
	{
		current = current->GetNext();
	}

	return current->GetValue();
}

MyLinkedListElement* PartitionLinkedList(MyLinkedListElement* head, int value)
{
	MyLinkedListElement* lessThanListHead = nullptr;
	MyLinkedListElement* lessThanListTail = nullptr;
	MyLinkedListElement* greaterThanOrEqualListHead = nullptr;
	MyLinkedListElement* greaterThanOrEqualListTail = nullptr;
	MyLinkedListElement* current = head;
	MyLinkedListElement* currentNext = head->GetNext();

	// iterate over the incoming list and create the two sub lists (one for all values less than,
	// and the other with all values greater than or equal
	while (current != nullptr)
	{
		if (current->GetValue() < value)
		{
			if (lessThanListTail == nullptr)
			{
				lessThanListHead = lessThanListTail = current;
			}
			else
			{
				lessThanListTail->AddNext(current);
			}
			current->AddNext(nullptr);
			lessThanListTail = current;
		}
		else
		{
			if (current->GetValue() == value)
			{
				current->AddNext(greaterThanOrEqualListHead);
				greaterThanOrEqualListHead = current;
			}
			else
			{
				if (greaterThanOrEqualListTail == nullptr)
				{
					greaterThanOrEqualListHead = greaterThanOrEqualListTail = current;
				}
				else
				{
					greaterThanOrEqualListTail->AddNext(current);
				}
				current->AddNext(nullptr);
				greaterThanOrEqualListTail = current;
			}
		}
		current = currentNext;
		currentNext = (current) ? current->GetNext() : nullptr;
	}

	lessThanListTail->AddNext(greaterThanOrEqualListHead);
	return lessThanListHead;
}
