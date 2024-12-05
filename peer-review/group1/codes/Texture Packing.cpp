#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX_N 10010       // Project����������N���Ϊ10000 
typedef struct{          // ���ڴ���ÿ������ 
    int width;           // ��� 
    int height;          // �߶� 
} Item; 
typedef struct{          // ���ڴ���ÿ���㼶level 
    int height;          // �㼶�߶� 
    int rest_w;          // ʣ���� 
} Level;

Item item[MAX_N], copy[MAX_N];  // item����ֵ��1��N ,����ά��һ������
Level level[MAX_N];             // level����ֵ��0��N-1��level���ڴ���㼶
int level_num = 0;              // �㼶���� 
int N, W;                       // NΪ����������WΪ����� 
int heap_size = 0;              // ����Ԫ������ 

// ������������Ԫ�� 
void swap(int x, int y) {       // ����Ԫ�ص�����ֵx,y    
    Item t;
    t = item[x]; item[x] = item[y]; item[y] = t;
}

// ��һ��Ԫ������  ���߶ȴӴ�С���� 
void heap_push(Item x) {         
    Item t;    
    int i, p;
    heap_size++;                // ������+1 
    item[heap_size] = x;        // ��Ԫ�ؼ�������ĩλ 
    i = heap_size; 
    while (i > 1) {             // ���ж�ƽ��ά�� 
        p = i / 2;                 
        if (item[i].height > item[p].height) {  // ������������ 
            swap(i, p);         // ���� 
        } else {
            break;
        }
        i = p;    
    }    
} 

// �������е�����ɾ�����ֵ  ���µ���ƽ�� 
Item heap_pop() {             
    Item target, t;
    target = item[1];         // �������ֵ�����ں���ĩ��� 
    swap(1, heap_size);       // �����������β����ɾ�������ֵ 
    heap_size--;              // ������-1 
    int p = 1, lc, rc;
    while (p < heap_size) {   // pδ���ѱ߽� 
        lc = p * 2;           // lcΪp������ 
        rc = p * 2 + 1;       // rcΪp������ 
        if (lc > heap_size) {  // ���������������ѭ�� 
            break;
        }
        if (rc > heap_size) {  // ��������� 
            if (item[p].height < item[lc].height) {  // �жϸýڵ����������Ƿ�ƽ�� 
                swap(p, lc);
            }
            break;              // ����ѭ�� 
        }
        if (item[p].height > item[lc].height && item[p].height > item[rc].height) {  // ���Ŀǰ�Ѿ�ƽ�⣬����ѭ�� 
            break;
        }
        if (item[lc].height < item[rc].height) {    // ����ýڵ�p������������������ƽ�� 
            swap(p, rc);         // ������������ 
            p = rc;                
        } else {
            swap(p, lc);         // ������������ 
            p = lc;
        }
    }
    return target;              // ���ش�������ֵ 
}

// �ж϶��Ƿ�Ϊ�� 
int IsEmpty() {
    return heap_size == 0;
}

// ÿ���ظ�ִ��ָ��ʱ��Ҫ�ĳ�ʼ�� 
void Initialize() {
    for (int j = 1; j <= N; j++) {     // ��ʼ���� 
        item[j] = copy[j];
    }
    heap_size = N;                      // ��ʼ�������� 
    level_num = 0;                      // ��ʼ���㼶���� 
} 

// BestFit�㷨�ж��Ƿ������һ������ʵĲ㼶 (����ʣ�ʹ�����Ĳ㼶��ʣ��ˮƽ�����С) 
int BestFitable(Item x) {        
    int min = 1000000, min_index = -1;    // ��ʼ�� 
    if (level_num == 0) {                // �޲㼶ֱ�ӷ���-1 
        return -1;
    }
    for (int i = 0; i < level_num; i++) {
        if (level[i].height >= x.height && level[i].rest_w >= x.width) {  // �ж��ܷ����� 
            if (level[i].rest_w - x.width < min) {    // �ж������ò㼶��ʣ��ˮƽ����Ƿ���С 
                min = level[i].rest_w - x.width;      // ���� 
                min_index = i;
            }
        } 
    } 
    if (min_index == -1) {        // �������� 
        return min_index;
    } else {
        level[min_index].rest_w = level[min_index].rest_w - x.width;  // ���±�����Ĳ㼶�Ŀ�� 
        return min_index;
    }
}

// FirstFit�㷨���ж�ֱ�������һ��������Ĳ㼶 
int FirstFitable(Item x) {
    if (level_num == 0) {           // �޲㼶ֱ�ӷ���-1 
        return -1;
    }
    for (int i = 0; i < level_num; i++) {        
        if (level[i].height >= x.height && level[i].rest_w >= x.width) {    // �ж��Ƿ�������,������ֱ�Ӹ���������ݣ��˳����� 
            level[i].rest_w = level[i].rest_w - x.width;
            return 1;
        }
    }
    return -1;           // �޷����� 
} 

// NextFit�㷨�ж��Ƿ��ܷ��뵱ǰ�㼶
int NextFitable(Item x) {
    if (level_num == 0 || level[level_num - 1].rest_w < x.width) {
        return -1;  // �����ǰ�㼶ʣ���Ȳ�������������ͼ������-1
    } else {
        level[level_num - 1].rest_w -= x.width;  // ���뵱ǰ�㼶
        return 1;
    }
}

// NextFit�㷨
int Next_Fit_Find() {
    Item x;
    int flag;
    while (IsEmpty() != 1) {           // �ѷǿ������ִ�� 
        x = heap_pop();                 // ���߶ȴӴ�С��ʼ 
        flag = NextFitable(x);          // �ж��Ƿ������� 
        if (flag == -1) {               // ����޷����룬�򴴽��²㼶 
            level_num++;                // �����µĲ㼶 
            level[level_num - 1].height = x.height;
            level[level_num - 1].rest_w = W - x.width;
        }
    }
    int sum_height = 0;
    for (int i = 0; i < level_num; i++) {
        sum_height += level[i].height;
    }
    return sum_height;  // �����ܵĸ߶�
}

// BestFit�㷨 
int Best_Fit_Find() {
    Item x;
    int flag;
    while (IsEmpty() != 1) {           // �ѷǿ������ִ�� 
        x = heap_pop();                 // ���߶ȴӴ�С��ʼ 
        flag = BestFitable(x);          // �ж��Ƿ������� 
        if (flag == -1) {               // �޷����� 
            level_num++;                // �����µĲ㼶 
            level[level_num - 1].height = x.height;
            level[level_num - 1].rest_w = W - x.width;
        }
    }
    int sum_height = 0;
    for (int i = 0; i < level_num; i++) {
        sum_height += level[i].height;
    }
    return sum_height;  // �����ܵĸ߶� 
}

// FirstFit�㷨 
int First_Fit_Find() {
    Item x;
    int flag;
    while (IsEmpty() != 1) {           // �ѷǿ������ִ�� 
        x = heap_pop();                 // ���߶ȴӴ�С��ʼ 
        flag = FirstFitable(x);         // �ж��Ƿ������� 
        if (flag == -1) {               // �޷����� 
            level_num++;                // �����µĲ㼶 
            level[level_num - 1].height = x.height;
            level[level_num - 1].rest_w = W - x.width;
            
        }
    }
    int sum_height = 0;
    for (int i = 0; i < level_num; i++) {
        sum_height += level[i].height;
    }
    return sum_height;  // �����ܵĸ߶�
}

int main(void) {
    // ������ر��������ļ���ȡ��д�� 
    clock_t start, stop;
    double total_time;
    freopen("Texture_in.txt", "r", stdin);
    freopen("Texture_out.txt", "w", stdout);
    scanf("%d %d", &N, &W);    // ��ȡ��������N��ָ�����W 
    Item temp;                 
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &temp.width, &temp.height);
        heap_push(temp);        // ���������ݵ�����У����ж����� 
    }
    for (int i = 1; i <= N; i++) {
        copy[i] = item[i];      // �����ѽ��б��ݣ�������ѭ�� 
    }
    
    int k = 1000;    // ѭ������,�ɸ�;���ڳ���ִ�нϿ죬ʱ��仯�����ԣ�����1000��ѭ��ִ��Ϊһ�飻 
    start = clock();        // ��ʼ��ʱ 
    int Best_Fit_Minimum_Height;
    for (int i = 1; i <= k; i++) {
        Initialize();        // ��ʼ�� 
        Best_Fit_Minimum_Height = Best_Fit_Find();
    }
    stop = clock();         // ֹͣ��ʱ 
    total_time = ((double)(stop - start)) / 1.0 / CLK_TCK;
    // ���BestFit����͸߶�������ʱ�� 
    printf("Best_Fit_Minimum_Height: %d\n", Best_Fit_Minimum_Height);
    printf("Best_Fit_Find_Time: %lfs\n", total_time);
    
    start = clock();        // ��ʼ��ʱ 
    int First_Fit_Minimum_Height;
    for (int i = 1; i <= k; i++) {
        Initialize();
        First_Fit_Minimum_Height = First_Fit_Find();
    }
    stop = clock();         // ֹͣ��ʱ
    total_time = ((double)(stop - start)) / 1.0 / CLK_TCK;
    // ���FirstFit����͸߶�������ʱ�� 
    printf("First_Fit_Minimum_Height: %d\n", First_Fit_Minimum_Height);
    printf("First_Fit_Find_Time: %lfs\n", total_time);
    
    // NextFit�㷨
    start = clock();        // ��ʼ��ʱ 
    int Next_Fit_Minimum_Height;
    for (int i = 1; i <= k; i++) {
        Initialize();
        Next_Fit_Minimum_Height = Next_Fit_Find();
    }
    stop = clock();         // ֹͣ��ʱ
    total_time = ((double)(stop - start)) / 1.0 / CLK_TCK;
    // ���NextFit����͸߶�������ʱ�� 
    printf("Next_Fit_Minimum_Height: %d\n", Next_Fit_Minimum_Height);
    printf("Next_Fit_Find_Time: %lfs\n", total_time);
}

