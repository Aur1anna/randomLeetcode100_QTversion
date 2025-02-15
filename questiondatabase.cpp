#include "questiondatabase.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QRandomGenerator>

QuestionDatabase::QuestionDatabase(QObject *parent)
    : QObject(parent)
{}

QVector<Question> QuestionDatabase::loadQuestions(const QString &filePath)
{
    QVector<Question> questions = {
       {"两数之和", "https://leetcode-cn.com/problems/two-sum/", false},
       {"字母异位词分组", "https://leetcode-cn.com/problems/group-anagrams/", false},
       {"最长连续序列", "https://leetcode-cn.com/problems/longest-consecutive-sequence/", false},
       {"移动零", "https://leetcode-cn.com/problems/move-zeroes/", false},
       {"盛最多水的容器", "https://leetcode-cn.com/problems/container-with-most-water/", false},
       {"三数之和", "https://leetcode-cn.com/problems/3sum/", false},
       {"接雨水", "https://leetcode-cn.com/problems/trapping-rain-water/", false},
       {"无重复字符的最长子串", "https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/", false},
       {"找到字符串中所有字母异位词", "https://leetcode.cn/problems/find-all-anagrams-in-a-string/", false},
       {"和为 K 的子数组", "https://leetcode-cn.com/problems/subarray-sum-equals-k/", false},
       {"滑动窗口最大值", "https://leetcode-cn.com/problems/sliding-window-maximum/", false},
       {"最小覆盖子串", "https://leetcode.cn/problems/minimum-window-substring/", false},
       {"最大子数组和", "https://leetcode-cn.com/problems/maximum-subarray/", false},
       {"合并区间", "https://leetcode.cn/problems/merge-intervals/", false},
       {"轮转数组", "https://leetcode.cn/problems/rotate-array/", false},
       {"除自身以外数组的乘积", "https://leetcode-cn.com/problems/product-of-array-except-self/", false},
       {"缺失的第一个正数", "https://leetcode.cn/problems/first-missing-positive/", false},
       {"矩阵置零", "https://leetcode.cn/problems/set-matrix-zeroes/", false},
       {"螺旋矩阵", "https://leetcode.cn/problems/spiral-matrix/", false},
       {"旋转图像", "https://leetcode-cn.com/problems/rotate-image/", false},
       {"搜索二维矩阵 II", "https://leetcode-cn.com/problems/search-a-2d-matrix-ii/", false},
       {"相交链表", "https://leetcode.cn/problems/intersection-of-two-linked-lists/", false},
       {"反转链表", "https://leetcode-cn.com/problems/reverse-linked-list/", false},
       {"回文链表", "https://leetcode-cn.com/problems/palindrome-linked-list/", false},
       {"环形链表", "https://leetcode-cn.com/problems/linked-list-cycle/", false},
       {"环形链表 II", "https://leetcode-cn.com/problems/linked-list-cycle-ii/", false},
       {"合并两个有序链表", "https://leetcode.cn/problems/merge-two-sorted-lists/", false},
       {"两数相加", "https://leetcode-cn.com/problems/add-two-numbers/", false},
       {"删除链表的倒数第 N 个结点", "https://leetcode.cn/problems/remove-nth-node-from-end-of-list/", false},
       {"两两交换链表中的节点", "https://leetcode.cn/problems/swap-nodes-in-pairs/", false},
       {"K个一组翻转链表", "https://leetcode.cn/problems/reverse-nodes-in-k-group/", false},
       {"随机链表的复制", "https://leetcode.cn/problems/copy-list-with-random-pointer/", false},
       {"排序链表", "https://leetcode.cn/problems/sort-list/description/", false},
       {"合并K个升序链表", "https://leetcode-cn.com/problems/merge-k-sorted-lists/", false},
       {"LRU 缓存", "https://leetcode-cn.com/problems/lru-cache/", false},
       {"二叉树的中序遍历", "https://leetcode-cn.com/problems/binary-tree-inorder-traversal/",false},
       {"二叉树的最大深度", "https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/",false},
       {"翻转二叉树", "https://leetcode-cn.com/problems/invert-binary-tree/",false},
       {"对称二叉树", "https://leetcode-cn.com/problems/symmetric-tree/",false},
       {"二叉树的直径", "https://leetcode-cn.com/problems/diameter-of-binary-tree/",false},
       {"二叉树的层序遍历", "https://leetcode-cn.com/problems/binary-tree-level-order-traversal/",false},
       {"将有序数组转换为二叉搜索树", "https://leetcode.cn/problems/convert-sorted-array-to-binary-search-tree/",false},
       {"验证二叉搜索树", "https://leetcode-cn.com/problems/validate-binary-search-tree/",false},
       {"二叉搜索树中第 K 小的元素", "https://leetcode.cn/problems/kth-smallest-element-in-a-bst/",false},
       {"二叉树的右视图", "https://leetcode-cn.com/problems/binary-tree-right-side-view/",false},
       {"二叉树展开为链表", "https://leetcode-cn.com/problems/flatten-binary-tree-to-linked-list/",false},
       {"从前序与中序遍历序列构造二叉树", "https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/",false},
       {"路径总和 III", "https://leetcode-cn.com/problems/path-sum-iii/",false},
       {"二叉树的最近公共祖先", "https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/", false},
       {"二叉树中的最大路径和", "https://leetcode.cn/problems/binary-tree-maximum-path-sum/", false},
       {"岛屿数量", "https://leetcode-cn.com/problems/number-of-islands/",false},
       {"腐烂的橘子", "https://leetcode-cn.com/problems/rotting-oranges/", false},
       {"课程表", "https://leetcode-cn.com/problems/course-schedule/",false},
       {"实现 Trie (前缀树)", "https://leetcode-cn.com/problems/implement-trie-prefix-tree/", false},
       {"全排列", "https://leetcode-cn.com/problems/permutations/",false},
       {"子集", "https://leetcode.cn/problems/subsets/",false},
       {"电话号码的字母组合", "https://leetcode.cn/problems/letter-combinations-of-a-phone-number/",false},
       {"组合总和", "https://leetcode-cn.com/problems/combination-sum/",false},
       {"括号生成", "https://leetcode-cn.com/problems/generate-parentheses/", false},
       {"单词搜索", "https://leetcode.cn/problems/word-search/", false},
       {"分割回文串", "https://leetcode.cn/problems/palindrome-partitioning/",false},
       {"N皇后", "https://leetcode.cn/problems/n-queens/description/",false},
       {"搜索插入位置", "https://leetcode.cn/problems/search-insert-position/",false},
       {"搜索二维矩阵", "https://leetcode.cn/problems/search-a-2d-matrix/", false},
       {"在排序数组中查找元素的第一个和最后一个位置", "https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/",false},
       {"搜索旋转排序数组", "https://leetcode-cn.com/problems/search-in-rotated-sorted-array/",false},
       {"寻找旋转排序数组中的最小值", "https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array/",false},
       {"寻找两个正序数组的中位数", "https://leetcode-cn.com/problems/median-of-two-sorted-arrays/",false},
       {"有效的括号", "https://leetcode.cn/problems/valid-parentheses/description/", false},
       {"最小栈", "https://leetcode.cn/problems/min-stack/", false},
       {"字符串解码", "https://leetcode-cn.com/problems/decode-string/", false},
       {"每日温度", "https://leetcode-cn.com/problems/daily-temperatures/", false},
       {"柱状图中最大的矩形", "https://leetcode.cn/problems/largest-rectangle-in-histogram/", false},
       {"数组中的第K个最大元素", "https://leetcode.cn/problems/kth-largest-element-in-an-array/", false},
       {"前 K 个高频元素", "https://leetcode-cn.com/problems/top-k-frequent-elements/", false},
       {"数据流的中位数", "https://leetcode.cn/problems/find-median-from-data-stream/", false},
       {"买卖股票的最佳时机", "https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/", false},
       {"跳跃游戏", "https://leetcode-cn.com/problems/jump-game/", false},
       {"跳跃游戏 II", "https://leetcode-cn.com/problems/jump-game-ii/",false},
       {"划分字母区间", "https://leetcode.cn/problems/partition-labels/",false},
       {"爬楼梯", "https://leetcode-cn.com/problems/climbing-stairs/", false},
       {"杨辉三角", "https://leetcode.cn/problems/pascals-triangle/", false},
       {"打家劫舍", "https://leetcode-cn.com/problems/house-robber/", false},
       {"完全平方数", "https://leetcode-cn.com/problems/perfect-squares/", false},
       {"零钱兑换", "https://leetcode-cn.com/problems/coin-change/", false},
       {"单词拆分", "https://leetcode-cn.com/problems/word-break/", false},
       {"最长递增子序列", "https://leetcode-cn.com/problems/longest-increasing-subsequence/", false},
       {"乘积最大子数组", "https://leetcode-cn.com/problems/maximum-product-subarray/", false},
       {"分割等和子集", "https://leetcode-cn.com/problems/partition-equal-subset-sum/", false},
       {"最长有效括号", "https://leetcode.cn/problems/longest-valid-parentheses/", false},
       {"不同路径", "https://leetcode-cn.com/problems/unique-paths/", false},
       {"最小路径和", "https://leetcode-cn.com/problems/minimum-path-sum/", false},
       {"最长回文子串", "https://leetcode-cn.com/problems/longest-palindromic-substring/", false},
       {"最长公共子序列", "https://leetcode.cn/problems/longest-common-subsequence/", false},
       {"编辑距离", "https://leetcode-cn.com/problems/edit-distance/", false},
       {"只出现一次的数字", "https://leetcode.cn/problems/single-number/",false},
       {"多数元素", "https://leetcode-cn.com/problems/majority-element/",false},
       {"颜色分类", "https://leetcode-cn.com/problems/sort-colors/", false},
       {"下一个排列", "https://leetcode-cn.com/problems/next-permutation/",false},
       {"寻找重复数", "https://leetcode-cn.com/problems/find-the-duplicate-number/", false}
    };

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        QJsonObject rootObj = doc.object();
        QJsonArray jsonArray = rootObj["questions"].toArray();
        for (int i = 0; i < jsonArray.size() && i < questions.size(); ++i) {
            QJsonObject obj = jsonArray[i].toObject();
            questions[i].isSolved = obj["isSolved"].toBool();
        }
        file.close();
    } else {
        saveQuestions(questions, filePath);
    }
    return questions;
}

void QuestionDatabase::saveQuestions(const QVector<Question> &questions, const QString &filePath)
{
    QJsonArray jsonArray;
    for (const auto &q : questions) {
        QJsonObject obj;
        obj["title"] = q.title;
        obj["url"] = q.url;
        obj["isSolved"] = q.isSolved;
        jsonArray.append(obj);
    }
    QJsonObject rootObj;
    rootObj["questions"] = jsonArray;
    QJsonDocument doc(rootObj);
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
}

int QuestionDatabase::getRandomUnsolvedIndex(const QVector<Question> &questions)
{
    QVector<int> unsolvedIndices;
    for (int i = 0; i < questions.size(); ++i) {
        if (!questions[i].isSolved)
            unsolvedIndices.append(i);
    }
    if (unsolvedIndices.isEmpty())
        return -1;
    int randIndex = QRandomGenerator::global()->bounded(unsolvedIndices.size());
    return unsolvedIndices[randIndex];
}
