#include <iostream>

using namespace std;

template <class T>
class AVLTree {
	private:
		struct vertex_t {
			T data;
			int height;
			vertex_t *left, *right;
		};
		
		// The root of the AVL Tree
		vertex_t* root;

		int max(int num1, int num2) {
			return (num1 > num2) ? num1 : num2;
		}

		vertex_t* rotateLeft(vertex_t *vtx) {
			// The rotation
			vertex_t *rightchild = vtx->right;
			vtx->right = rightchild->left;
			rightchild->left = vtx;

			// Update the heights
			vtx->height = calculateHeight(vtx);
			rightchild->height = calculateHeight(rightchild);

			return rightchild;
		}

		vertex_t* rotateRight(vertex_t *vtx) {
			vertex_t *leftchild = vtx->left;
			vtx->left = leftchild->right;
			leftchild->right = vtx;
			vtx->height = calculateHeight(vtx);
			leftchild->height = calculateHeight(leftchild);
			return leftchild;
		}

		int getHeight(vertex_t *vtx) {
			if (vtx == NULL) {
				return -1;
			}
			return vtx->height;
		}

		int calculateHeight(vertex_t *vtx) {
			if (vtx == NULL) {
				return -1;
			}
			return 1 + max(getHeight(vtx->left), getHeight(vtx->right));
		}

		int getBalanceFactor(vertex_t *vtx) {
			if (vtx == NULL) {
				return 0;
			}
			return getHeight(vtx->left) - getHeight(vtx->right);
		}

		vertex_t* getPredecessor(vertex_t *vtx) {
			for (vtx = vtx->left; vtx->right != NULL; vtx = vtx->right);
			return vtx;
		}

		vertex_t* insertElement(vertex_t *vtx, T &data) {
			if (vtx == NULL) {
				vtx = new vertex_t();
				vtx->data = data;
				vtx->left = vtx->right = NULL;
				vtx->height = 0;
				return vtx;
			}
			if (data < vtx->data) {
				vtx->left = insertElement(vtx->left, data);
			} else if (data > vtx->data) {
				vtx->right = insertElement(vtx->right, data);
			} else {
				return vtx;
			}
			vtx->height = calculateHeight(vtx);
			int bf = getBalanceFactor(vtx);
			if (bf > 1) {
				if (getBalanceFactor(vtx->left) < 0) {
					vtx->left = rotateLeft(vtx->left);
				}
				return rotateRight(vtx);
			}
			if (bf < -1) {
				if (getBalanceFactor(vtx->right) > 0) {
					vtx->right = rotateRight(vtx->right);
				}
				return rotateLeft(vtx);
			}
			return vtx;
		}

		vertex_t* removeElement(vertex_t *vtx, T &data) {
			if (vtx == NULL) {
				return NULL;
			}
			if (data < vtx->data) {
				vtx->left = removeElement(vtx->left, data);
			} else if (data > vtx->data) {
				vtx->right = removeElement(vtx->right, data);
			} else if (vtx->left != NULL && vtx->right != NULL) {
				vertex_t *predecessor = getPredecessor(vtx);
				vtx->data = predecessor->data;
				vtx->left = removeElement(vtx->left, vtx->data);
			} else if (vtx->left != NULL) {
				vertex_t *toDelete = vtx;
				vtx = vtx->left;
				delete(toDelete);
			} else if (vtx->right != NULL) {
				vertex_t *toDelete = vtx;
				vtx = vtx->right;
				delete(toDelete);
			} else {
				delete(vtx);
				return NULL;
			}
			vtx->height = calculateHeight(vtx);
			int bf = getBalanceFactor(vtx);
			if (bf > 1) {
				if (getBalanceFactor(vtx->left) < 0) {
					vtx->left = rotateLeft(vtx->left);
				}
				return rotateRight(vtx);
			} else if (bf < -1) {
				if (getBalanceFactor(vtx->right) > 0) {
					vtx->right = rotateRight(vtx->right);
				}
				return rotateLeft(vtx);
			}
			return vtx;
		}

		void printInOrder(vertex_t *vtx) {
			if (vtx == NULL) {
				return;
			}
			printInOrder(vtx->left);
			cout << vtx->data << " ";
			printInOrder(vtx->right);
		}

		void printPreOrder(vertex_t *vtx) {
			if (vtx == NULL) {
				return;
			}
			cout << vtx->data << " ";
			printPreOrder(vtx->left);
			printPreOrder(vtx->right);
		}

		void printPostOrder(vertex_t *vtx) {
			if (vtx == NULL) {
				return;
			}
			printPostOrder(vtx->left);
			printPostOrder(vtx->right);
			cout << vtx->data << " ";
		}

		void deleteInPostOrder(vertex_t *vtx) {
			if (vtx == NULL) {
				return;
			}
			deleteInPostOrder(vtx->left);
			deleteInPostOrder(vtx->right);
			delete(vtx);
		}
	public:
		AVLTree<T>() {
			root = NULL;
		}
		
		~AVLTree<T>() {
			deleteInPostOrder(root);
		}
		void insert(T &data) {
			root = insertElement(root, data);
		}

		void remove(T &data) {
			root = removeElement(root, data);
		}

		bool contains(T &data) {
			vertex_t *vtx = root;
			while (vtx != NULL) {
				if (data < vtx->data) {
					vtx = vtx->left;
				} else if (data > vtx->data) {
					vtx = vtx->right;
				} else {
					return true;
				}
			}
			return false;
		}

		void printTree() {
			cout << "Inorder: ";
			printInOrder(root);
			cout << endl << "Postorder: ";
			printPostOrder(root);
			cout << endl << "Preorder: ";
			printPreOrder(root);
			cout << endl;
		}
};
