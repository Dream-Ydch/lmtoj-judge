struct Node { Node* next; };
int main() {
    Node a, b;
    a.next = &b;
    b.next = &a;  // 环
    Node* p = &a;
    while(p) p = p->next;  // 永远不结束
}