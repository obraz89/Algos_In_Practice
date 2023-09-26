#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "snowflakes.h"

#define NVERTS 6

struct SnowFlake {

	int operator[](int ind) const { return vals[ind]; }
	int& operator[](int ind) { return vals[ind]; }

	void read_vals() {
		for (int i = 0; i < NVERTS; i++) {
			scanf("%d", &vals[i]);
		}
	}

	void init(int base) {
		read_vals();
		code = calc_code(base);
	}

	int calc_code(int base) {
		int sum = 0;
		for (auto e : vals) {
			sum += e;
		}
		return sum % base;
	}

	void print() const {
		for (int i=0; i<NVERTS; i++)
			printf("F_%d[%d]=%d; ", code, i, vals[i]);
		printf("\n");
	}

	static bool compare(const SnowFlake& f1, const SnowFlake& f2) {
		for (int k = 0; k < 2; k++) {
			for (int offset = 0; offset < NVERTS; offset++) {
				bool equal = true;
				for (int i = 0; i < NVERTS; i++) {
					// k = 0 - clockwise variants 012345 and rotations
					// k = 1 - counter-clock variants 543210 and rotations
					int j = (k == 0) ? offset + i : offset + (NVERTS - 1 - i);
					if (j >= NVERTS) j -= NVERTS;

					if (f1[i] != f2[j]) {
						equal = false;
						break;
					}
				}
				if (equal) return true;
			}
		}
		return false;
	}

	int vals[NVERTS];
	int code;

};

struct SnowFlakeListNode {
	SnowFlake* flake;
	SnowFlakeListNode* next;
	SnowFlakeListNode() : flake(nullptr), next(nullptr) {};
	SnowFlakeListNode(SnowFlake* relem) :flake(relem), next(NULL) {};
};

// snow flakes grouped by code
struct SnowFlakesGrouped {

	SnowFlakeListNode** cont;
	int _size;
	SnowFlakesGrouped(int size) : _size(size) {
		cont = new SnowFlakeListNode * [size];
		for (int i = 0; i < size; i++) cont[i] = nullptr;
	}
	~SnowFlakesGrouped() {
		SnowFlakeListNode* node, *node_to_delete;
		for (int i = 0; i < _size; i++) {
			node = cont[i];
			while (node) {
				node_to_delete = node;
				node = node->next;
				delete node_to_delete;
			}
		}
		delete[] cont;
	}

	void add_node(SnowFlake& flake) {
		SnowFlakeListNode* node = new SnowFlakeListNode(&flake);
		SnowFlakeListNode* old_root = cont[flake.code];
		cont[flake.code] = node;
		cont[flake.code]->next = old_root;
	}

	void find_identical_flakes() {
		SnowFlakeListNode* node1, *node2;
		for (int i = 0; i < _size; i++) {
			node1 = cont[i];
			while (node1) {
				node2 = node1->next;
				while (node2) {
					if (SnowFlake::compare(*node1->flake, *node2->flake)) {
						printf("Identical flakes found:\n");
						node1->flake->print();
						node2->flake->print();
					}
					node2 = node2->next;
				}
				node1 = node1->next;
			}
		}
	}
};

int flakes_main() {

	printf("number of vertices in snowflake:%d\n", NVERTS);
	SnowFlake f1, f2;
	printf("Enter values for the first flake\n");
	for (int i = 0; i < NVERTS; i++) {
		scanf("%d", &f1[i]);
		printf("f1[%d]=%d; ", i, f1[i]);
	}
	printf("\n");
	printf("Enter values for the second flake\n");

	printf("\n");

	if (SnowFlake::compare(f1, f2)) {
		printf("Flakes equal\n");
	}
	else {
		printf("Flakes different\n");
	}

	const int NFLAKES = 10;

	SnowFlake* sarr = new SnowFlake[NFLAKES];
	SnowFlakesGrouped slist(NFLAKES);

	for (int i = 0; i < NFLAKES; i++) {
		SnowFlake& f = sarr[i];
		f.init(NFLAKES);
		//sstorage[i].print();
	}

	// group every code in a list
	for (int i = 0; i < NFLAKES; i++) {
		SnowFlake& flake = sarr[i];
		slist.add_node(flake);
	}

	slist.find_identical_flakes();

	delete[] sarr;

	return 0;
}