#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "tree_candy.h"

struct Node {
	int candy;
	Node* left;
	Node* right;
	Node(int c) : candy(c), left(nullptr), right(nullptr) {}
};

Node* read_tree_helper(char* line, int* pos) {
	Node* tree;
	tree = new Node(0);
	if (tree == NULL) {
		fprintf(stderr, "malloc error\n");
		exit(1);
	}
	if (line[*pos] == '(') {
		(*pos)++;
		tree->left = read_tree_helper(line, pos);
		(*pos)++;
		tree->right = read_tree_helper(line, pos);
		(*pos)++;
		return tree;
	}
	else {
		tree->left = NULL;
		tree->right = NULL;
		tree->candy = line[*pos] - '0';
		(*pos)++;
		if (line[*pos] != ')' && line[*pos] != ' ' &&
			line[*pos] != '\0') {
			tree->candy = tree->candy * 10 + line[*pos] - '0';
			(*pos)++;
		}
		return tree;
	}
}

Node* read_tree(char* line) {
	int pos = 0;
	return read_tree_helper(line, &pos);
}

int count_candy(Node* node) {
	if (!node->left && !node->right) {
		return node->candy;
	}
	else {
		return count_candy(node->left) + count_candy(node->right);
	}
}

#define SIZE 255

int tree_candy_main() {
	int i;
	char line[SIZE + 1];
	Node* tree;
	gets_s(line);
	tree = read_tree(line);
	printf("Candy:%d", count_candy(tree));
	//tree_solve(tree);
	return 0;
}

