#include <stdio.h>
#include <stdlib.h>

#define InitSize 100 // �����ʼ��С
typedef int ElemType; // Ԫ�����ͣ���������� int

typedef struct {
    ElemType *data; // �洢���ݵ�����
    int length;     // ��ǰ����
    int MaxSize;    // �������
} SeqList;

// ��ʼ��˳���
void InitList(SeqList *L) {
    L->data = (ElemType *)malloc(InitSize * sizeof(ElemType));
    if (!L->data) {
        // �ڴ����ʧ��
        exit(EXIT_FAILURE);
    }
    L->length = 0;      // ��ʼ����Ϊ 0
    L->MaxSize = InitSize; // ��ʼ�������Ϊ InitSize
}

// ����Ԫ��
void Insert(SeqList *L, int i, ElemType e) {
    if (i < 1 || i > L->length + 1) {
        // ����λ�ò��Ϸ�
        printf("����λ�ô���\n");
        return;
    }
    if (L->length >= L->MaxSize) {
        // �洢�ռ������������·���ռ�
        ElemType *newBase = (ElemType *)realloc(L->data, (L->MaxSize + 10) * sizeof(ElemType));
        if (!newBase) {
            // ���·���ʧ��
            exit(EXIT_FAILURE);
        }
        L->data = newBase;
        L->MaxSize += 10; // ��������
    }
    ElemType *p, *q;
    q = &(L->data[i - 1]); // ����λ�õĵ�ַ
    for (p = &(L->data[L->length - 1]); p >= q; --p) {
        *(p + 1) = *p; // ����λ�ü�֮���Ԫ�غ���
    }
    *q = e; // ����Ԫ��
    ++L->length; // ��������
}

// ɾ��Ԫ��
void Delete(SeqList *L, int i) {
    if (i < 1 || i > L->length) {
        // ɾ��λ�ò��Ϸ�
        printf("ɾ��λ�ô���\n");
        return;
    }
    ElemType *p, *q;
    p = &(L->data[i - 1]); // ɾ��λ�õĵ�ַ
    q = L->data + L->length - 1; // ���һ��Ԫ�صĵ�ַ
    for (++p; p <= q; ++p) {
        *(p - 1) = *p; // ɾ��λ��֮���Ԫ��ǰ��
    }
    --L->length; // ���ȼ���
}

// ����Ԫ��
int Locate(SeqList *L, ElemType e) {
    int i;
    for (i = 0; i < L->length; ++i) {
        if (L->data[i] == e) {
            return i + 1; // ����Ԫ��λ��
        }
    }
    return 0; // δ�ҵ����� 0
}

// �޸�Ԫ��
void Modify(SeqList *L, int i, ElemType e) {
    if (i < 1 || i > L->length) {
        // �޸�λ�ò��Ϸ�
        printf("�޸�λ�ô���\n");
        return;
    }
    L->data[i - 1] = e; // �޸�Ԫ��
}

// ����˳���
void DestroyList(SeqList *L) {
    free(L->data);
    L->length = 0;
    L->MaxSize = 0;
}

int main() {
    SeqList L;
    InitList(&L); // ��ʼ��˳���

    // �ڵ�һ��λ�ò���Ԫ�� 10
    Insert(&L, 1, 10);

    // �ڵڶ���λ�ò���Ԫ�� 20
    Insert(&L, 2, 20);

    // ɾ����һ��λ�õ�Ԫ��
    Delete(&L, 1);

    // ����Ԫ�� 20 ��λ��
    int pos = Locate(&L, 20);
    if (pos != 0) {
        printf("Ԫ�� 20 ��λ��Ϊ��%d\n", pos);
    } else {
        printf("δ�ҵ�Ԫ�� 20\n");
    }

    // �޸ĵ�һ��λ�õ�Ԫ��Ϊ 30
    Modify(&L, 1, 30);

    // ����˳���
    DestroyList(&L);

    return 0;
}
