#pragma once
class MyBinaryTreeNode
{
public:
	MyBinaryTreeNode() : m_left(nullptr), m_right(nullptr), m_value(-1) {}
	~MyBinaryTreeNode();

	void AddLeft(MyBinaryTreeNode* left) { m_left = left; }
	MyBinaryTreeNode* GetLeft() { return m_left; }

	void AddRight(MyBinaryTreeNode* right) { m_right = right; }
	MyBinaryTreeNode* GetRight() { return m_right; }

	void SetValue(int value) { m_value = value; }
	int GetValue(void) { return m_value; }

private:
	MyBinaryTreeNode* m_left;
	MyBinaryTreeNode* m_right;
	int m_value;
};

