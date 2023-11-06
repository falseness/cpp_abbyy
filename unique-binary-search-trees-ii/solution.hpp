/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
/*
generateTrees рекурсивно генерирут деревья со всеми значениями вершин [minimum, maximum]
выбор root'а однозначно задает набор вершин в левом поддереве и в правом.

Время, память - O(размера результата)
*/
class Solution {
    vector<TreeNode*> generateTrees(int minimum, int maximum) {
        if (minimum > maximum) {
            return {nullptr};
        }
        vector<TreeNode*> result;
        for (int root = minimum; root <= maximum; ++root) {
            auto left_childs = generateTrees(minimum, root - 1);
            auto right_childs = generateTrees(root + 1, maximum);
            for (auto left_child : left_childs) {
                for (auto right_child: right_childs) {
                    result.push_back(new TreeNode(root, left_child, right_child));
                }
            }
        }
        return result;
    }
public:
    vector<TreeNode*> generateTrees(int n) {
        return generateTrees(1, n);
    }
};
