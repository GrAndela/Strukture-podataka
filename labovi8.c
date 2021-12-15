#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


struct _tree;
typedef struct _tree* treeP;
typedef struct _tree {
	int element;
	treeP left;
	treeP right;
} tree;

treeP InsertElement(int element, treeP root);
treeP CreateNewElement(int element);
int InorderPrint(treeP root);
int PreorderPrint(treeP root);
int PostorderPrint(treeP root);
treeP FindElement(int element, treeP root);
treeP FindMinElement(treeP root);
treeP DeleteElement(int element, treeP root);

int main()
{
	treeP root = NULL;
	treeP temp = NULL;

	int choice = 0;
	int element = 0;

	do {
		printf("\n*************************************\n");
		printf("Choose: \n");
		printf("1 - Adding new element to the tree\n");
		printf("2 - Print tree(inorder)\n");
		printf("3 - Print tree(preorder)\n");
		printf("4 - Print tree(postorder)\n");
		printf("5 - Find element in tree\n");
		printf("6 - Delete element from tree\n");
		printf("0 - Exit\n");
		printf("\n*************************************\n");

		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			printf("Write element you want add: \n");
			scanf("%d", &element);
			root = InsertElement(element, root);
			break;
		case 2:
			InorderPrint(root);
			break;
		case 3:
			PreorderPrint(root);
			break;
		case 4:
			PostorderPrint(root);
			break;
		case 5:
			printf("Write element you want to find in the tree: \n");
			scanf("%d", &element);
			temp = FindElement(element, root);
			if (temp != NULL) {
				printf("Element %d is found in the tree\n", temp->element);
			}
			else {
				printf("Element %d is not in the tree\n", element);
			}
			break;
		case 6:
			printf("Write element you want to delete from tree: \n");
			scanf("%d", &element);
			root = DeleteElement(element, root);
		case 0:
			break;
		default:
			printf("Error while writing!\n");
		}

	} while (choice != 0);

	return 0;
} 

treeP InsertElement(int element, treeP root)
{
	treeP current = root;
	treeP newElement = NULL;

	if (current == NULL) {
		newElement = CreateNewElement(element);
		return newElement;
	}
	else if (element < current->element) {
		current->left = InsertElement(element, current->left);
	}
	else if (element > current->element) {
		current->right = InsertElement(element, current->right);
	}

	return current;

} 

treeP CreateNewElement(int element)
{
	treeP newElement = NULL;

	newElement = (treeP)malloc(sizeof(tree));
	if (newElement == NULL)	{
		printf("Can't allocate memory!\n");
		return NULL;
	}
	newElement->element = element;
	newElement->left = NULL;
	newElement->right = NULL;

	return newElement;
}

int InorderPrint(treeP root)
{
	treeP current = root;

	if (current != NULL) {
		InorderPrint(current->left);
		printf("%d ", current->element);
		InorderPrint(current->right);
	}

	return 0;
}

int PreorderPrint(treeP root)
{
	treeP current = root;

	if (current != NULL) {
		printf("%d ", current->element);
		PreorderPrint(current->left);
		PreorderPrint(current->right);
	}

	return 0;
}

int PostorderPrint(treeP root)
{
	treeP current = root;

	if (current != NULL) {
		PostorderPrint(current->left);
		PostorderPrint(current->right);
		printf("%d ", current->element);
	}

	return 0;
}

treeP FindElement(int element, treeP root)
{
	treeP current = root;

	if (current == NULL) {
		return NULL;
	}
	else if (element < current->element) {
		return FindElement(element, current->left);
	}
	else if (element > current->element) {
		return FindElement(element, current->right);
	}
	else {
		return current;
	}
}

treeP FindMinElement(treeP root)
{

	treeP current = root;

	while (current->left != NULL) {
		current = current->left;
	}

	return current;
}

treeP DeleteElement(int element, treeP root)
{
	treeP current = root;
	treeP temp = NULL;

	if (current == NULL) {
		printf("There is not element in the tree you want to delete!\n");
		return current;
	}
	else if (element < current->element) {
		current->left = DeleteElement(element, current->left);
	}
	else if (element > current->element) {
		current->right = DeleteElement(element, current->right);
	}
	else if (current->left != NULL && current->right != NULL) {
		temp = FindMinElement(current->right);
		current->element = temp->element;
		current->right = DeleteElement(current->element, current->right);
	}
	else {
		temp = current;
		if (current->left == NULL) {
			current = current->right;
		}
		else {
			current = current->left;
		}
		free(temp);
	}

	return current;
}