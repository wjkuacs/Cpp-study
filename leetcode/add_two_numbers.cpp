#include <iostream>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummyHead = new ListNode(0); // 创建一个哑节点，方便操作
        ListNode* current = dummyHead; // 指向当前处理的节点
        int carry = 0; // 用于保存进位值

        // 遍历两个链表，直到两个链表的节点都为空且没有进位
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            int sum = carry; // 初始化当前位的和为进位值

            if (l1 != nullptr) {
                sum += l1->val; // 加上链表 l1 当前节点的值
                l1 = l1->next; // 移动到下一个节点
            }

            if (l2 != nullptr) {
                sum += l2->val; // 加上链表 l2 当前节点的值
                l2 = l2->next; // 移动到下一个节点
            }

            carry = sum / 10; // 计算新的进位值
            current->next = new ListNode(sum % 10); // 创建新节点保存当前位的和，并连接到结果链表中
            current = current->next; // 移动到下一个处理节点
        }

        return dummyHead->next; // 返回结果链表的头节点
    }
}; // 别忘了在这里添加闭括号

// 测试函数
int main() {
    // 创建第一个链表 2 -> 4 -> 3
    ListNode* l1 = new ListNode(2);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(3);

    // 创建第二个链表 5 -> 6 -> 4
    ListNode* l2 = new ListNode(5);
    l2->next = new ListNode(6);
    l2->next->next = new ListNode(4);

    Solution solution;
    ListNode* result = solution.addTwoNumbers(l1, l2);

    // 输出结果链表
    while (result != nullptr) {
        std::cout << result->val;
        if (result->next != nullptr) {
            std::cout << " -> ";
        }
        result = result->next;
    }

    system("pause");
    return 0;
}
