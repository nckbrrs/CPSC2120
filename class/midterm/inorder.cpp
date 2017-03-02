#include <iostream>
#include <cstdlib>
#include <assert.h>
using namespace std;

// A node in a linked list
struct ListNode {
  int val;
  ListNode *next;
  ListNode (int v, ListNode *n) { val = v; next = n; }
  ListNode () { val = 0; next = NULL; }
};

// A node in a binary tree.  This tree will encode an arbitrary sequence
// so its inorder traversal may not be in sorted order
struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode (int v, TreeNode *l, TreeNode *r) { val = v; left = l; right = r; }
  TreeNode (int v) { val = v; left = right = NULL; }
  TreeNode () { val = 0; left = right = NULL; }
};

// return a randomly-built (therefore balanced) binary tree of size N, for testing
TreeNode *build_tree(int N)
{
  if (N == 0) return NULL;
  if (N == 1) return new TreeNode(rand() % 1000000);
  int k = rand() % (N-1);
  return new TreeNode(rand() % 1000000, build_tree(k), build_tree(N-1-k));
}

void print_inorder(TreeNode *T)
{
  if (T == NULL) return;
  print_inorder(T->left);
  cout << T->val << "\n";
  print_inorder(T->right);
}

void print_list(ListNode *L)
{
  while (L != NULL) {
    cout << L->val << "\n";
    L = L->next;
  }
}

// MY FUNCTION (WHICH DIDN'T WORK)
ListNode *bst_to_list (TreeNode *T, ListNode *L) {

	if (T==NULL) {
		cout << "T is null \n";
		return L;
	}

	bst_to_list (T->left, L);
	L = new ListNode(T->val, L);
	bst_to_list (T->right, L);

	return L;
}

// PROFESSOR'S ANSWER 
ListNode *inorder (TreeNode *T, ListNode *L) {
	return T==NULL ? sofar : 
		inorder(T->left, new ListNode(T->val, inorder(T->right, sofar)));
}

int main(void)
{
	TreeNode *T = build_tree(20);

	cout << "In-order contents of test tree:\n";
	print_inorder(T);

	ListNode *L = NULL; 
	// TBD... add code here (and possibly other functions above) to
	// store the inorder traversal of T in a linked list pointed to by L.
	inorder(T, L);

	cout<<"after bst_to_list... \n";

	cout<<"In-order traversal in a linked list (hopefully the same as above):\n";
	print_list(L);

	return 0;
}
