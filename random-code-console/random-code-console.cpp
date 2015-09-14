// random-code-console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MyLinkedListElement.h"
#include "MyBinaryTreeNode.h"

#include <cstdlib>

// Linked list functions
MyLinkedListElement* BuildLinkedList(int size);
MyLinkedListElement* RemoveLinkedListElement(MyLinkedListElement* head, int value);
MyLinkedListElement* PartitionLinkedList(MyLinkedListElement* head, int value);
int GetRandomElementValue(MyLinkedListElement* head);


// Binary tree functions
MyBinaryTreeNode* BuildBinaryTree(int size, int start = 0);
void InOrderTraversal(MyBinaryTreeNode* node);
void PreOrderTraversal(MyBinaryTreeNode* node);
void PostOrderTraversal(MyBinaryTreeNode* node);
bool IsTreeBalanced(MyBinaryTreeNode* node, int balanceDelta);
int MeasureTreeDepth(MyBinaryTreeNode* node, int depth);

void PrintLinkedList(MyLinkedListElement* head);

const int c_listSize = 30;

int main()
{
	// linked list code
	MyLinkedListElement* head = ::BuildLinkedList(c_listSize);
	::printf("---Initial list.\n");
	PrintLinkedList(head);

	int value = ::GetRandomElementValue(head);
	::printf("---Selected value: %d.\n", value);

	MyLinkedListElement* newHead = ::RemoveLinkedListElement(head, value);
	::printf("---List after removal.\n");
	::PrintLinkedList(newHead);

	value = ::GetRandomElementValue(head);
	::printf("---Selected value: %d.\n", value);
	newHead = ::PartitionLinkedList(head, value);
	::printf("---List after partitioning.\n");
	::PrintLinkedList(newHead);

	// binary tree code
	::printf("---Initialize tree.\n");
	MyBinaryTreeNode* treeNode = ::BuildBinaryTree(7);

	::printf("---In order traversal.\n");
	::InOrderTraversal(treeNode);

	::printf("---Pre order traversal.\n");
	::PreOrderTraversal(treeNode);

	::printf("---Post order traversal.\n");
	::PostOrderTraversal(treeNode);

	::printf("---Checking balance.\n");
	bool isBalanced = ::IsTreeBalanced(treeNode, 1);
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


//// Binary tree functions
//MyBinaryTreeNode* BuildBinaryTree(int size, int start)
//{
//	// compute the value that we're going to assign to the root of this tree.  
//	// we compute it as the middle value between the start and the end of the array of #'s (which we assume to be contiguous)
//	int rootValue = (size / 2) + start;
//	// compute the size of the tree that will come underneath this element.  
//	//int subTreeSize = rootValue - start;
//	int subTreeSize = size - start - 1;
//
//	MyBinaryTreeNode* node = new MyBinaryTreeNode();
//
//	node->SetValue(rootValue);
//	if( size > 1)
//	{ 
//		node->AddLeft(::BuildBinaryTree(subTreeSize, start));
//		//if( start + size - 1 > rootValue)
//		if(subTreeSize > 2)
//		{
//			// if the size is odd, then we need to have an imbalanced tree, we'll put more nodes on the right
//			if (size % 2 != 0)
//			{
//				subTreeSize += 1;
//			}
//			node->AddRight(::BuildBinaryTree(subTreeSize, rootValue + 1));
//		}
//	}
//
//	return node;
//}

// Binary tree functions
MyBinaryTreeNode* BuildBinaryTree(int size, int start)
{
	// compute the value that we're going to assign to the root of this tree.  
	// we compute it as the middle value between the start and the end of the array of #'s (which we assume to be contiguous)
	int rootValue = (size % 2) ? (((size - 1) / 2) + start) : ((size / 2 ) + start);
	// compute the size of the tree that will come underneath this element.  
	//int subTreeSize = rootValue - start;
	int leftSubTreeSize = rootValue - start;
	int rightSubTreeSize = size - 1 - leftSubTreeSize;

	MyBinaryTreeNode* node = new MyBinaryTreeNode();

	node->SetValue(rootValue);
	if( size > 1)
	{ 
		if (leftSubTreeSize > 0)
		{
			node->AddLeft(::BuildBinaryTree(leftSubTreeSize, start));
		}

		if(rightSubTreeSize > 0)
		{
			node->AddRight(::BuildBinaryTree(rightSubTreeSize, rootValue + 1));
		}
	}

	return node;
}

void InOrderTraversal(MyBinaryTreeNode* node)
{
	if (node == nullptr)
	{
		return;
	}

	::InOrderTraversal(node->GetLeft());
	::printf("%d ", node->GetValue());
	::InOrderTraversal(node->GetRight());
}

void PreOrderTraversal(MyBinaryTreeNode* node)
{
	if (node == nullptr)
	{
		return;
	}

	::printf("%d ", node->GetValue());
	::PreOrderTraversal(node->GetLeft());
	::PreOrderTraversal(node->GetRight());
}

void PostOrderTraversal(MyBinaryTreeNode* node)
{
	if (node == nullptr)
	{
		return;
	}

	::PostOrderTraversal(node->GetLeft());
	::PostOrderTraversal(node->GetRight());
	::printf("%d ", node->GetValue());
}

bool IsTreeBalanced(MyBinaryTreeNode* node, int balanceDelta)
{
	int leftDepth = ::MeasureTreeDepth(node->GetLeft(), 1);
	int rightDepth = ::MeasureTreeDepth(node->GetRight(), 1 );

	if (::abs(leftDepth - rightDepth) > balanceDelta)
	{
		return false;
	}

	return true;
}

int MeasureTreeDepth(MyBinaryTreeNode* node, int currentDepth)
{
	if (node == nullptr)
	{
		return currentDepth;
	}

	currentDepth++;
	int leftDepth = ::MeasureTreeDepth(node->GetLeft(), currentDepth);
	int rightDepth = ::MeasureTreeDepth(node->GetRight(), currentDepth);

	if (leftDepth > rightDepth)
	{
		return leftDepth;
	}
	
	return rightDepth;
}