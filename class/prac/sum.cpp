#include <iostream>

using namespace std;

struct LNode {
	int val;
	LNode *next;
	LNode (int v, LNode *n) { val = v; next = n; }
};

int compute_sum(LNode *L)
{
	int sum = 0;
	if (L == NULL) return 0;
	sum = compute_sum(L->next);
	return sum + L->val;
	
}

int main (void)
{
	LNode *list = new LNode(1, NULL);
	for (int i=2; i<11; i++) list = new LNode (i, list);

	LNode *temp = list;
	while (temp) { cout << temp->val << endl; temp = temp->next; }

	cout << "list->val is "<<  list->val << endl;
	cout << "sum is: " << compute_sum(list) << endl;
	
}
