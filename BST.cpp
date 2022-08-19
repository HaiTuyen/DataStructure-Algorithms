#include <iostream>
#include <queue>
using namespace std;

struct NODE{
    int key;
    NODE* left;
    NODE* right;
};

//1. Initialize a NODE from a given value:
NODE* createNode(int data) 
{
    NODE* p = new NODE;
    if (p == NULL) 
    {
        return NULL;
    }
    p->key = data;
    p->left = NULL;
    p->right = NULL;
    return p;
}

//2. Add a NODE with given value into a given Binary Search Tree:
void Insert(NODE* &pRoot, int x)
{
    if (pRoot == NULL) 
    {
        pRoot = createNode(x);
        return;
    }
    if (pRoot->key < x)
    {
        Insert(pRoot->right, x);
    }
    else 
    {
        Insert(pRoot->left, x);
    }
}

//3. Pre-order Traversal:
void NLR(NODE* pRoot)
{
    if (pRoot == NULL)
    {
        return;
    }
    cout << pRoot->key << " ";
    NLR(pRoot->left);
    NLR(pRoot->right);
}

//4. In-order Traversal:
void LNR(NODE* pRoot)
{
    if (pRoot == NULL)
    {
        return;
    }
    NLR(pRoot->left);
    cout << pRoot->key << " ";
    NLR(pRoot->right);
}

//5. Post-order Traversal:
void LRN(NODE* pRoot)
{
    if (pRoot == NULL)
    {
        return;
    }
    NLR(pRoot->left);
    NLR(pRoot->right);
    cout << pRoot->key << " ";
}

//6. Level-order Traversal:

void LevelOrder(NODE* pRoot)
{
    // Base Case
    if (pRoot == NULL)
        return;
 
    // Create an empty queue for level order traversal
    queue<NODE*> q;
 
    // Enqueue Root and initialize height
    q.push(pRoot);
 
    while (q.empty() == false) {
        // Print front of queue and remove it from queue
        NODE* node = q.front();
        cout << node->key << " ";
        q.pop();
 
        /* Enqueue left child */
        if (node->left != NULL)
            q.push(node->left);
 
        /*Enqueue right child */
        if (node->right != NULL)
            q.push(node->right);
    }
}

//7. Calculate the height of a given Binary Tree;
int Height(NODE* pRoot)
{
    queue<NODE*> nodesInLevel;
    int height = 0;
    int nodeCount = 0; // Calculate  number of nodes in a level.
    NODE* currentNode; // Pointer to store the address of a
                       // node in the current level.
    if (pRoot == NULL) {
        return 0;
    }
    nodesInLevel.push(pRoot);
    while (!nodesInLevel.empty()) {
        // This while loop runs for every level and
        // increases the height by 1 in each iteration. If
        // the queue is empty then it implies that the last
        // level of tree has been parsed.
        height++;
        // Create another while loop which will insert all
        // the child nodes of the current level in the
        // queue.
 
        nodeCount = nodesInLevel.size();
        while (nodeCount--) {
            currentNode = nodesInLevel.front();
 
            // Check if the current nodes has left child and
            // insert it in the queue.
 
            if (currentNode->left != NULL) {
                nodesInLevel.push(currentNode->left);
            }
 
            // Check if the current nodes has right child
            // and insert it in the queue.
            if (currentNode->right != NULL) {
                nodesInLevel.push(currentNode->right);
            }
 
            // Once the children of the current node are
            // inserted. Delete the current node.
 
            nodesInLevel.pop();
        }
    }
    return height;
}

//8. Count the number of NODE from a given Binary Tree:
int countNode(NODE* pRoot)
{
    if (pRoot == NULL) 
    {
        return 0;
    }
    return 1 + countNode(pRoot->left) + countNode(pRoot->right);
}

//9. Calculate the total value of all NODEs from a given Binary Tree:
//-----Method 1: recursive-----
/* int sumNode(NODE* pRoot)
{
    if (pRoot == NULL)
    {
        return 0;
    }
    return pRoot->key + sumNode(pRoot->left) + sumNode(pRoot->right);
}
 */
//-----Method 2: level order-----
int sumNode(NODE* pRoot)
{
    int sum = 0;
    queue<NODE*> nodesInLevel;
    nodesInLevel.push(pRoot);
    while (!nodesInLevel.empty()/* nodesInLevel.empty() == false */)
    {
        NODE* temp = nodesInLevel.front();
        nodesInLevel.pop();
        
        sum += temp->key;
        
        if (temp->left != NULL)
        {
            nodesInLevel.push(temp->left);
        }
        if (temp->right != NULL)
        {
            nodesInLevel.push(temp->right);
        }
    }
    return sum;
}


//10. Find and return a NODE with given value from a given Binary Search Tree:
NODE* Search(NODE* pRoot, int x)
{
    if (pRoot == NULL)
    {
        return NULL;
    }
    if (pRoot->key == x) 
    {
        return pRoot;
    }
    if (pRoot->key > x)
    {
        return Search(pRoot->left, x);
    }
    else 
    {
        return Search(pRoot->right, x);
    }
}

//11. Remove a NODE with given value from a given Binary Search Tree:
/* Given a non-empty binary search tree, return the node
with minimum key value found in that tree. Note that the
entire tree does not need to be searched. */
NODE* minValueNode(NODE* node)
{
    NODE* current = node;
    // loop down to find the leftmost leaf
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

/* Given a binary search tree and a key, this function
deletes the key and returns the new root */
void Remove(NODE* &pRoot, int x)
{
    // base case
    if (pRoot == NULL)
    {
        return;
    }

    if (x < pRoot->key)
    {
        Remove(pRoot->left, x);
    }
    else if (x > pRoot->key)
    {
        Remove(pRoot->right, x);
    }
    else 
    {
        if (pRoot->left == NULL && pRoot->right == NULL)
        {
            delete pRoot;
            pRoot = NULL;
            return;
            
        }
        else if (pRoot->left == NULL)
        {
            pRoot->key = pRoot->right->key;
            delete pRoot->right;
            pRoot->right = NULL;
            return;
        }
        else if (pRoot->right == NULL)
        {
            pRoot->key = pRoot->left->key;
            delete pRoot->left;
            pRoot->left = NULL;
            return;
        }

        NODE* temp = minValueNode(pRoot->right);
        pRoot->key = temp->key;
        Remove(pRoot->right, temp->key);
    }
}

//12. Initialize a Binary Search Tree from a given array:
NODE* createTree(int a[], int n)
{
    NODE* root = createNode(a[0]);
    for (int i = 1; i < n; i++)
    {
        Insert(root, a[i]);
    }
    return root;
}

//13. Completely remove a given Binary Search Tree:
void removeTree(NODE* &pRoot)
{
    if (pRoot == NULL)
    {
        return;
    }
    removeTree(pRoot->left);
    removeTree(pRoot->right);
    Remove(pRoot, pRoot->key);
}

//14. Calculate the height of a NODE with given value: (return -1 if value not exist)
int findHeightUtil(NODE* root, int x, int& height)
{
    // Base Case
    if (root == NULL) {
        return -1;
    }
  
    // Store the maximum height of the left and right subtree
    int leftHeight = findHeightUtil(root->left, x, height);
    int rightHeight = findHeightUtil(root->right, x, height);
  
    // Update height of the current node
    int ans = max(leftHeight, rightHeight) + 1;
  
    // If current node is the required node
    if (root->key == x)
        height = ans;
  
    return ans;
}
  
// Function to find the height of a given node in a Binary Tree
int heightNode(NODE* pRoot, int value){
    // Store the height of the given node
    int h = -1;
  
    // Stores height of the Tree
    int maxHeight = findHeightUtil(pRoot, value, h);
  
    // Return the height
    return h;
}

//15. * Calculate the level of a given NODE:
int Level(NODE* pRoot, NODE* p)
{
    if (pRoot == NULL)
    {
        return 0;
    }
    queue<NODE*> q;
    NODE* node; 
    int currLevel = 1;
    q.push(pRoot);
    while (q.empty() == false)
    {
        int size = q.size();
        while (size--)
        {
            node = q.front();
            if (node->key == p->key)
            {
                return currLevel;
            }   
            q.pop();
            if (node->left != NULL)
            {
                q.push(node->left);
            }
            if (node->right != NULL)
            {
                q.push(node->right);
            }
        }
        currLevel++;
    }
    return 0;
}

//16. * Count the number leaves from a given Binary Tree:
int countLeaf(NODE* pRoot)
{
    if (pRoot == NULL)
    {
        return 0;
    }
    if (pRoot->left == NULL && pRoot->right == NULL)
    {
        return 1;
    }
    else 
    {
        return countLeaf(pRoot->left) + countLeaf(pRoot->right);
    }
}

//17. * Count the number of NODE from a given Binary Search Tree which key value is less than a given value:
int countLess(NODE* pRoot, int x)
{
    int count = 0;
    if (pRoot == NULL)
    {
        return 0;
    }
    if (pRoot->key < x)
    {
        count++;
        count += countLess(pRoot->left, x);
        count += countLess(pRoot->right, x);
    }
    else 
    {
        count += countLess(pRoot->left, x);
    }
    return count;
}

//18. * Count the number of NODE from a given Binary Search Tree which key value
// is greater than a given value:
int countGreater(NODE* pRoot, int x)
{
    int count = 0;
    if (pRoot == NULL)
    {
        return 0;
    }
    if (pRoot->key > x)
    {
        count++;
        count += countGreater(pRoot->left, x);
        count += countGreater(pRoot->right, x);
    }
    else 
    {
        count += countGreater(pRoot->right, x);
    }
    return count;
}

//19. * Determine if a given Binary Tree is Binary Search Tree:
bool isBSTUtil(struct NODE* root, int& prev)
{
    // traverse the tree in inorder fashion and
    // keep track of prev node
    if (root) {
        if (!isBSTUtil(root->left, prev))
            return false;
 
        // Allows only distinct valued nodes
        if (root->key <= prev)
            return false;
 
        // Initialize prev to current
        prev = root->key;
 
        return isBSTUtil(root->right, prev);
    }
 
    return true;
}
 
// Function to check if Binary Tree is BST
bool isBST(NODE* root)
{
    int prev = INT_MIN;
    return isBSTUtil(root, prev);
}

// 20. * Determine if a given Binary Tree is a Full Binary Search Tree:
bool isFullBST(NODE* pRoot)
{
    if (!isBST(pRoot))
    {
        return false;
    }

    if (pRoot == NULL)
    {
        return true;
    }

    if (pRoot->left == NULL && pRoot->right == NULL)
    {
        return true;
    }

    if ((pRoot->left) && (pRoot->right))
    {
        return (isFullBST(pRoot->left) && isFullBST(pRoot->right));
    }

    return false;
}

int main()
{
    // NODE* root = NULL;
    // Insert(root, 10);
    // Insert(root, 5);
    // Insert(root, 12);
    // Insert(root, 2);
    // Insert(root, 7);
    // Insert(root, 8);
    // Insert(root, 6);
    // LevelOrder(root);
    // cout << endl;
    // /* int height = Height(root);
    // int numberOfNodes = countNode(root);
    // int sumOfNodes = sumNode(root);
    // NODE* nodeSearch = Search(root, 15); */
    // Remove(root, 10);
    // LevelOrder(root);


    int a[] = {6,3,8,4,2};
    int n = sizeof(a)/sizeof(int);
    NODE* root = createTree(a, n);
    LevelOrder(root);
    int height = heightNode(root, 6);
    //int level = Level(root, root->right->right->right);
    int leaves = countLeaf(root);
    int node_less_than_key = countLess(root, 11);
    int node_greater_than_key = countGreater(root, 2);
    int is_BST = isBST(root);
    int is_Full_BST = isFullBST(root);
    return 0;
}
