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
    static vector<TreeNode*> kEmptyTree;
    vector<TreeNode*>& generateTrees(int minimum, int maximum) {
        if (minimum > maximum) {
            return kEmptyTree;
        }
        auto& result = found_tree_[minimum - 1][maximum - 1]; 
        if (!result.empty()) {
            return result;
        }
        for (int root = minimum; root <= maximum; ++root) {
            auto& left_childs = generateTrees(minimum, root - 1);
            auto& right_childs = generateTrees(root + 1, maximum);

            for (auto left_child : left_childs) {
                for (auto right_child: right_childs) {
                    result.push_back(new TreeNode(root, left_child, right_child));
                }
            }
        }
        return result;
    }
    vector<vector<vector<TreeNode*>>> found_tree_;
public:
    vector<TreeNode*> generateTrees(int n) {
        found_tree_.resize(n, vector<vector<TreeNode*>>(n));
        auto result = generateTrees(1, n); 
        found_tree_.clear();
        return result;
    }
};

vector<TreeNode*> Solution::kEmptyTree = {nullptr};

