#include <bits/stdc++.h>

typedef short Status;
namespace initial {
    const int MAX_SIZE = 1e3;
    const Status ERROR = 0, NOT_FOUND = 0, SUCCEEDED = 1, WARNING = 2;
}; // namespace initial
namespace natural {
    bool InRange(size_t i, size_t leftBorder, size_t rightBorder,
                 bool leftOpen = false, bool rightOpen = false) {
        return i >= leftBorder + leftOpen && i <= rightBorder - rightOpen;
    }
}; // namespace natural
namespace container {
    namespace list {
        const size_t MAX_LIST_SIZE = initial::MAX_SIZE + 10;
        namespace sequential_list {
            typedef int DataType;
            struct basic_seq_list {
                DataType *ListData; // ListData[0] is free
                size_t length;
            };

            bool ListEmpty(basic_seq_list *L) { return !L->length; }
            Status InitList(basic_seq_list *L) {
                L->ListData =
                    (DataType *)malloc(MAX_LIST_SIZE * sizeof(DataType));
                L->length = 0;
                return initial::SUCCEEDED;
            }
            Status GetElem(basic_seq_list *L, size_t i, DataType *e) {
                if (ListEmpty(L)) return initial::ERROR;
                if (!natural::InRange(i, 1, L->length)) return initial::ERROR;
                *e = L->ListData[i];
                return initial::SUCCEEDED;
            }
            Status DeleteElem(basic_seq_list *L, size_t i, DataType *e) {
                if (ListEmpty(L)) return initial::ERROR;
                if (!natural::InRange(i, 1, L->length)) return initial::ERROR;
                if (e) *e = L->ListData[i];
                for (size_t j = L->length; j >= i; j--)
                    L->ListData[j] = L->ListData[j + 1];
                L->length--;
                return initial::SUCCEEDED;
            }
            Status InsertElem(basic_seq_list *L, size_t i, DataType e) {
                if (!natural::InRange(i, 1, L->length + 1))
                    return initial::ERROR;
                for (size_t j = L->length; j >= i; j--)
                    L->ListData[j + 1] = L->ListData[j];
                L->length++;
                L->ListData[i] = e;
                return initial::SUCCEEDED;
            }
            size_t LocateElem(basic_seq_list *L, DataType *e) {
                for (size_t i = 1; i <= L->length; i++)
                    if (*e == L->ListData[i]) return i;
                return initial::NOT_FOUND;
            }
            Status ClearList(basic_seq_list *L) {
                if (ListEmpty(L)) return initial::WARNING;
                L->length = 0;
                return initial::SUCCEEDED;
            }
            Status DestroyList(basic_seq_list *L) {
                free(L->ListData);
                L->ListData = NULL;
                L->length = 0;
                return initial::SUCCEEDED;
            }
            size_t ListLength(basic_seq_list *L) { return L->length; }
            struct SeqList {
                basic_seq_list self;
                SeqList() { InitList(&self); }
                Status clear() { return ClearList(&self); }
                size_t length() { return ListLength(&self); }
                size_t size() { return this->length(); }
                Status insert(size_t beginPos, DataType destElem) {
                    return InsertElem(&self, beginPos, destElem);
                }
                Status erase(size_t beginPos, DataType *destElem = NULL) {
                    return DeleteElem(&self, beginPos, destElem);
                }
                size_t find(DataType e) { return LocateElem(&self, &e); }
                Status destroy() { return DestroyList(&self); }
                DataType *operator[](const size_t x) {
                    return &(this->self.ListData[x]);
                }
            };
        }; // namespace sequential_list
        namespace single_linked_list {
            typedef int DataType;
            struct ListNode {
                DataType NodeData;
                ListNode *next;
            };
            typedef ListNode *LinkList;
            Status InitList(LinkList L) {
                L = (LinkList)malloc(sizeof(LinkList));
                if (!L) return OVERFLOW;
                L->next = NULL;
                return initial::SUCCEEDED;
            }
            Status GetElem(LinkList L, size_t i, DataType *e) {
                size_t cnt = 1;
                ListNode *p = L->next;
                while (cnt < i && p) p = p->next, cnt++;
                if (cnt > i || !p) return initial::ERROR;
                *e = p->NodeData;
                return initial::SUCCEEDED;
            }
        }; // namespace single_linked_list
    };     // namespace list
};         // namespace container
typedef container::list::sequential_list::SeqList seq_list;