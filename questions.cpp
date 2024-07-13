// QUESTION 1 : Write a function to reverse a singly linked list.The function should take the head of the list and return the new head of the reversed list.

#include <bits/stdc++.h>
using namespace std;
class TreeNode {
    public:
    TreeNode *left;
    TreeNode *right;
    int data;

    TreeNode(int data) {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

class Node
{
public:
    Node *next;
    int data;
    Node()
    {
        this->next = NULL;
    }
    Node(int data)
    {
        this->data = data;
        this->next = NULL;
    }
};

void preorder(TreeNode *root) {
    if(root == NULL) return;
    cout << root->data << " -> ";
    preorder(root->left);
    preorder(root->right);
}

Node *reverseList(Node *head)
{
    if (head == NULL)
    {
        cout << "head is NULL";
        return head;
    }
    Node *prev = NULL, *curr = head, *fwd = NULL;
    while (curr != NULL)
    {
        fwd = curr->next;
        curr->next = prev;
        prev = curr;
        curr = fwd;
    }
    return prev;
}
/*
int main()
{
    Node *head = new Node(10);
    Node *num1 = new Node(20);
    Node *num2 = new Node(30);
    Node *num3 = new Node(40);
    Node *num4 = new Node(50);
    head->next = num1;
    num1->next = num2;
    num2->next = num3;
    num3->next = num4;
    // num4->next = NULL;
    Node *curr = head;
    cout << "Before Reverse : " << endl;
    while (head != NULL)
    {
        cout << head->data << " -> ";
        head = head->next;
    }
    cout << "NULL" << endl;

    head = curr;
    Node *newhead = reverseList(head);
    cout << "After Reverse : " << endl;
    while (newhead != NULL)
    {
        cout << newhead->data << " -> ";
        newhead = newhead->next;
    }
    cout << "NULL";
}
*/

// QUESTION 2 : Given a string, find the length of the longest substring without repeating characters.The function should return an integer representing the length of the longest substring without repeating characters.
int findLongestSubstring(string s) {
    int ans = 0;
    unordered_map<char,int> mp;
    int length = 0;
    int left = 0, right = 0;
    while(right < s.size()) {
        if(mp[s[right]] and mp[s[right]] >= left) {
            left = mp[s[right]]+1;
            length = 0;
        }
        else {
            length++;
            ans = max(ans, length);
        }
        mp[s[right]] = right;
        right++;
    }
    return ans;
}

// QUESTION 3 : Given a non-empty binary tree, find the maximum path sum. A path is defined as any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The path must contain at least one node and does not need to go through the root.The function should return an integer representing the maximum path sum.
int maxPathSum(TreeNode* root) {
    int maxi = INT_MIN;
    solve(root, maxi);
    return maxi;
}
int solve(TreeNode *node, int &maxi) {
    if(node == NULL) return 0;
    int leftSum = max(0, solve(node->left, maxi));
    int rightSum = max(0, solve(node->right, maxi));

    maxi = max(maxi, leftSum + rightSum + node->data);
    return max(leftSum, rightSum) + node->data;
}
// QUESTION 4 :  Design an algorithm to serialize and deserialize a binary tree. Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment. Implement the serialize and deserialize methods.
string serializeBST(TreeNode *root) {
    if(!root) return "";
    queue<TreeNode *> q;
    q.push(root);
    string result = "";
    while(!q.empty()) {
        TreeNode *temp = q.front();
        q.pop();
        if(temp != NULL) {
            result.append(to_string(temp->data));
            result.append(", ");
            q.push(temp->left);
            q.push(temp->right);
        }
        else {
            result.append("#, ");
        }
    }
    // result.pop_back();
    return result;

}

TreeNode *deserializeBST(string str) {
    if(str.size() == 0) return NULL;
    stringstream s(str);
    string st;
    getline(s, st, ',');
    TreeNode *root = new TreeNode(stoi(str));
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        TreeNode *node = q.front();
        q.pop();

        // for left node
        getline(s,st,',');
        if(st == "#") node->left = NULL;
        else {
            TreeNode *leftNode = new TreeNode(stoi(st));
            node->left = leftNode;
            q.push(leftNode);
        }

        // for right node
        getline(s,st,',');
        if(st == "#") node->right = NULL;
        else {
            TreeNode *rightNode = new TreeNode(stoi(st));
            node->right = rightNode;
            q.push(rightNode);
        }
    }
    return root;
}
int main() {
    // string s = "cadbzabcd";
    // cout << findLongestSubstring(s);
    TreeNode *root = new TreeNode(10);
    TreeNode *node1 = new TreeNode(20);
    TreeNode *node2 = new TreeNode(30);
    TreeNode *node3 = new TreeNode(40);
    TreeNode *node4 = new TreeNode(50);
    root->left = node1;
    root->right = node2;
    node2->left = node3;
    node2->right = node4;
    preorder(root);
    cout << endl;
    string deserializeString = serializeBST(root);
    cout << deserializeString << endl;
    TreeNode *newNode = deserializeBST(deserializeString);
    preorder(newNode);
}
//  QUESTION 5 : Write a function to rotate an array to the right by k steps.The function should modify the array in place to achieve the rotation.
vector<int> solve(vector<int> &a, int n, int k, int b[])
{
    for (int i = 0; i < n; i++)
    {
        a[(i + k) % n] = b[(i % n) % n];
    }
    return a;
}

void rotate2(std::vector<int>& nums, int k) {
    k = k % nums.size();
    std::reverse(nums.begin(), nums.end());
    std::reverse(nums.begin(), nums.begin() + k);
    std::reverse(nums.begin() + k, nums.end());
}

void rotate(vector<int>& nums, int k) {
int b[nums.size()];
for(int i = 0; i<nums.size(); i++) {
    b[i] = nums[i];
}
solve(nums, nums.size(), k, b);
}

//  QUESTION 6 : Write a function to find the factorial of a given number.The function should return the factorial of the number.
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

//  QUESTION 7 : Write a function to compute the sum of the digits of a given number.The function should return the sum of the digits of the number.

int sumOfDigits(int num) {
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

//  QUESTION 8 : Write a function to find the greatest common divisor (GCD) of two numbers. The function should return the GCD of a and b.
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

//  QUESTION 9 : Write a function to find the maximum difference between any two elements in an array.The function should return the maximum difference between any two elements in the array.
int maxDifference(std::vector<int>& nums) {
    if (nums.size() < 2) return 0;
    int minElement = nums[0];
    int maxDiff = 0;
    for (int i = 1; i < nums.size(); ++i) {
        maxDiff = std::max(maxDiff, nums[i] - minElement);
        minElement = std::min(minElement, nums[i]);
    }
    return maxDiff;
}
//  QUESTION 10 : Write a function to check if a given string contains only alphabetic characters.The function should return true if the string contains only alphabetic characters, and false otherwise.

bool isAlphabetic(const std::string& s) {
    for (char c : s) {
        if (!isalpha(c)) return false;
    }
    return true;
}
