#include "avl_tree.h"

typedef struct Node {
  int key;
  int height;
  Node *left;
  Node *right;
} Node;

// a utility function to get height of the tree
static int Height(Node *node) {
  if (node == NULL)
    return 0;
  return node->height;
}

// a utility function to get maximum of two integers
static int Max(int a, int b) {
  return (a > b) ? a : b;
}

// get Balance factor of node
static int GetBalance(Node *node) {
  if (node == NULL)
    return 0;
  return Height(node->left) - Height(node->right);
}

/* given a non-empty BST, return the
 node with minimum key value found in that tree.*/
static Node *MinValueNode(Node *node) {
  Node *current = node;

  /* loop down to find the leftmost leaf */
  while (current->left != NULL)
    current = current->left;

  return current;
}

/* helper function that allocates a new node with the given key and
 NULL left and right pointers. */
static Node *NewNode(int key) {
  Node* node = (Node*) malloc(sizeof(Node));
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;  // new node is initially added at leaf
  return (node);
}

// a utility function to right rotate subtree rooted with y
static Node *RightRotate(Node *y) {
  Node *x = y->left;
  Node *T2 = x->right;

  // perform rotation
  x->right = y;
  y->left = T2;

  // update heights
  y->height = Max(Height(y->left), Height(y->right)) + 1;
  x->height = Max(Height(x->left), Height(x->right)) + 1;

  // return new root
  return x;
}

// a utility function to left rotate subtree rooted with x
static Node *LeftRotate(Node *x) {
  Node *y = x->right;
  Node *T2 = y->left;

  // perform rotation
  y->left = x;
  x->right = T2;

  // update heights
  x->height = Max(Height(x->left), Height(x->right)) + 1;
  y->height = Max(Height(y->left), Height(y->right)) + 1;

  // return new root
  return y;
}

// recursive function to insert key in subtree rooted
Node *Insert(Node *node, int key) {
  // perform the normal BST insertion
  if (node == NULL)
    return (NewNode(key));

  if (key < node->key)
    node->left = Insert(node->left, key);
  else if (key > node->key)
    node->right = Insert(node->right, key);
  else
    // Equal keys are not allowed in BST
    return node;

  // update height of this ancestor node
  node->height = 1 + Max(Height(node->left), Height(node->right));

  /* get the balance factor of this ancestor
   node to check whether this node became
   unbalanced */
  int balance = GetBalance(node);

  /* if this node becomes unbalanced, then
   there are 4 cases */

  // Left Left Case
  if (balance > 1 && key < node->left->key)
    return RightRotate(node);

  // Right Right Case
  if (balance < -1 && key > node->right->key)
    return LeftRotate(node);

  // Left Right Case
  if (balance > 1 && key > node->left->key) {
    node->left = LeftRotate(node->left);
    return RightRotate(node);
  }

  // Right Left Case
  if (balance < -1 && key < node->right->key) {
    node->right = RightRotate(node->right);
    return LeftRotate(node);
  }

  /* return the unchanged node pointer */
  return node;
}

/* recursive function to delete a node with given key
 from subtree with given root. It returns root of
 the modified subtree */
Node *DeleteNode(Node *root, int key) {
  // STEP 1: PERFORM STANDARD BST DELETE
  if (root == NULL)
    return root;

  /* if the key to be deleted is smaller than the
   root's key, then it lies in left subtree */
  if (key < root->key)
    root->left = DeleteNode(root->left, key);

  /* if the key to be deleted is greater than the
   root's key, then it lies in right subtree */
  else if (key > root->key)
    root->right = DeleteNode(root->right, key);

  /* if key is same as root's key, then This is
   the node to be deleted */
  else {
    // node with only one child or no child
    if ((root->left == NULL) || (root->right == NULL)) {
      Node *temp = root->left ? root->left : root->right;

      // no child case
      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        // one child case
        *root = *temp;  // copy the contents of
                        // the non-empty child
      free(temp);
    } else {
      /* node with two children: Get the inorder
       successor (smallest in the right subtree) */
      Node* temp = MinValueNode(root->right);

      // copy the inorder successor's data to this node
      root->key = temp->key;

      // delete the inorder successor
      root->right = DeleteNode(root->right, temp->key);
    }
  }

  // if the tree had only one node then return
  if (root == NULL)
    return root;

  // update height of the current node
  root->height = 1 + Max(Height(root->left), Height(root->right));

  // check the balance
  int balance = GetBalance(root);

  // If this node becomes unbalanced, then there are 4 cases

  // Left Left Case
  if (balance > 1 && GetBalance(root->left) >= 0)
    return RightRotate(root);

  // Left Right Case
  if (balance > 1 && GetBalance(root->left) < 0) {
    root->left = LeftRotate(root->left);
    return RightRotate(root);
  }

  // Right Right Case
  if (balance < -1 && GetBalance(root->right) <= 0)
    return LeftRotate(root);

  // Right Left Case
  if (balance < -1 && GetBalance(root->right) > 0) {
    root->right = RightRotate(root->right);
    return LeftRotate(root);
  }

  return root;
}

void DeleteTree(Node *root) {
  if (root != NULL) {
    DeleteTree(root->left);
    DeleteTree(root->right);
    free(root);
  }
}

void Find(Node *root, int key) {
  if (root == NULL) {
    puts("No such element\n");
    return;
  }
  if (key < root->key)
    Find(root->left, key);
  else if (key > root->key)
    Find(root->right, key);
  else
    PrintNode(root);
}

void PrintNode(Node *root) {
  printf("Key: %d", root->key);
}

void PrintInOrder(Node *root) {
  if (root != NULL) {
    printf("%d ", root->key);
    PrintInOrder(root->left);
    PrintInOrder(root->right);
  }
}
