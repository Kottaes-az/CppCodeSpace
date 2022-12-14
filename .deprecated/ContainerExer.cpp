#include <bits/stdc++.h>

typedef int status_t;
namespace initial {
    const size_t MAX_SIZE = 1e3;
    const status_t ERROR = 0, NOT_FOUND = 0, SUCCEEDED = 1, WARNING = 2;
}; // namespace initial
namespace natural {
    bool InRange(size_t dest, size_t leftBorder, size_t rightBorder,
                 bool leftOpen = false, bool rightOpen = false) {
        return dest >= leftBorder + leftOpen && dest <= rightBorder - rightOpen;
    }
    size_t MaxOf(size_t totNum, ...) {
        size_t cnt = 0, iter = 0, maxVal = -SIZE_MAX - 1;
        va_list varList;
        va_start(varList, totNum);
        while (cnt <= totNum)
            maxVal = maxVal > iter ? maxVal : iter, cnt++,
            iter = va_arg(varList, size_t);
        va_end(varList);
        return maxVal;
    }
}; // namespace natural
namespace container {
    namespace list {
        const size_t max_type_list_size = initial::MAX_SIZE + 10;
        namespace sequential_list {
            typedef int DataType;
            struct basic_seq_list {
                DataType *ListData; // ListData[0] is free
                size_t length;
            };

            bool ListEmpty(basic_seq_list *L) { return !L->length; }
            status_t InitList(basic_seq_list *L) {
                L->ListData =
                    (DataType *)malloc(max_type_list_size * sizeof(DataType));
                L->length = 0;
                return initial::SUCCEEDED;
            }
            status_t GetElem(basic_seq_list *L, size_t i, DataType *e) {
                if (ListEmpty(L)) return initial::ERROR;
                if (!natural::InRange(i, 1, L->length)) return initial::ERROR;
                *e = L->ListData[i];
                return initial::SUCCEEDED;
            }
            status_t DeleteElem(basic_seq_list *L, size_t i, DataType *e) {
                if (ListEmpty(L)) return initial::ERROR;
                if (!natural::InRange(i, 1, L->length)) return initial::ERROR;
                if (e) *e = L->ListData[i];
                for (size_t j = L->length; j >= i; j--)
                    L->ListData[j] = L->ListData[j + 1];
                L->length--;
                return initial::SUCCEEDED;
            }
            status_t InsertElem(basic_seq_list *L, size_t i, DataType e) {
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
            status_t ClearList(basic_seq_list *L) {
                if (ListEmpty(L)) return initial::WARNING;
                L->length = 0;
                return initial::SUCCEEDED;
            }
            status_t DestroyList(basic_seq_list *L) {
                free(L->ListData);
                L->ListData = NULL;
                L->length = 0;
                return initial::SUCCEEDED;
            }
            size_t ListLength(basic_seq_list *L) { return L->length; }
            struct SeqList {
                basic_seq_list self;
                SeqList() { InitList(&self); }
                status_t clear() { return ClearList(&self); }
                size_t length() { return ListLength(&self); }
                size_t size() { return this->length(); }
                status_t insert(size_t beginPos, DataType destElem) {
                    return InsertElem(&self, beginPos, destElem);
                }
                status_t erase(size_t beginPos, DataType *destElem = NULL) {
                    return DeleteElem(&self, beginPos, destElem);
                }
                size_t find(DataType e) { return LocateElem(&self, &e); }
                status_t destroy() { return DestroyList(&self); }
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
            status_t InitList(LinkList L) {
                L = (ListNode *)malloc(sizeof(ListNode));
                if (!L) return OVERFLOW;
                L->next = NULL;
                return initial::SUCCEEDED;
            }
            status_t GetElem(LinkList L, size_t i, DataType *e) {
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