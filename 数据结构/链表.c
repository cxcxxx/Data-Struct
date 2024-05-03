#include <stdio.h>
#include <stdlib.h>

#define InitSize 100 // 定义初始大小
typedef int ElemType; // 元素类型，这里假设是 int

typedef struct {
    ElemType *data; // 存储数据的数组
    int length;     // 当前长度
    int MaxSize;    // 最大容量
} SeqList;

// 初始化顺序表
void InitList(SeqList *L) {
    L->data = (ElemType *)malloc(InitSize * sizeof(ElemType));
    if (!L->data) {
        // 内存分配失败
        exit(EXIT_FAILURE);
    }
    L->length = 0;      // 初始长度为 0
    L->MaxSize = InitSize; // 初始最大容量为 InitSize
}

// 增加元素
void Insert(SeqList *L, int i, ElemType e) {
    if (i < 1 || i > L->length + 1) {
        // 插入位置不合法
        printf("插入位置错误\n");
        return;
    }
    if (L->length >= L->MaxSize) {
        // 存储空间已满，需重新分配空间
        ElemType *newBase = (ElemType *)realloc(L->data, (L->MaxSize + 10) * sizeof(ElemType));
        if (!newBase) {
            // 重新分配失败
            exit(EXIT_FAILURE);
        }
        L->data = newBase;
        L->MaxSize += 10; // 增加容量
    }
    ElemType *p, *q;
    q = &(L->data[i - 1]); // 插入位置的地址
    for (p = &(L->data[L->length - 1]); p >= q; --p) {
        *(p + 1) = *p; // 插入位置及之后的元素后移
    }
    *q = e; // 插入元素
    ++L->length; // 长度增加
}

// 删除元素
void Delete(SeqList *L, int i) {
    if (i < 1 || i > L->length) {
        // 删除位置不合法
        printf("删除位置错误\n");
        return;
    }
    ElemType *p, *q;
    p = &(L->data[i - 1]); // 删除位置的地址
    q = L->data + L->length - 1; // 最后一个元素的地址
    for (++p; p <= q; ++p) {
        *(p - 1) = *p; // 删除位置之后的元素前移
    }
    --L->length; // 长度减少
}

// 查找元素
int Locate(SeqList *L, ElemType e) {
    int i;
    for (i = 0; i < L->length; ++i) {
        if (L->data[i] == e) {
            return i + 1; // 返回元素位置
        }
    }
    return 0; // 未找到返回 0
}

// 修改元素
void Modify(SeqList *L, int i, ElemType e) {
    if (i < 1 || i > L->length) {
        // 修改位置不合法
        printf("修改位置错误\n");
        return;
    }
    L->data[i - 1] = e; // 修改元素
}

// 销毁顺序表
void DestroyList(SeqList *L) {
    free(L->data);
    L->length = 0;
    L->MaxSize = 0;
}

int main() {
    SeqList L;
    InitList(&L); // 初始化顺序表

    // 在第一个位置插入元素 10
    Insert(&L, 1, 10);

    // 在第二个位置插入元素 20
    Insert(&L, 2, 20);

    // 删除第一个位置的元素
    Delete(&L, 1);

    // 查找元素 20 的位置
    int pos = Locate(&L, 20);
    if (pos != 0) {
        printf("元素 20 的位置为：%d\n", pos);
    } else {
        printf("未找到元素 20\n");
    }

    // 修改第一个位置的元素为 30
    Modify(&L, 1, 30);

    // 销毁顺序表
    DestroyList(&L);

    return 0;
}
