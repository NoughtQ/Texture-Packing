#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX_N 10010       // Project设置数据量N最大为10000 
typedef struct{          // 用于储存每个纹理 
    int width;           // 宽度 
    int height;          // 高度 
} Item; 
typedef struct{          // 用于储存每个层级level 
    int height;          // 层级高度 
    int rest_w;          // 剩余宽度 
} Level;

Item item[MAX_N], copy[MAX_N];  // item索引值从1到N ,用于维护一个最大堆
Level level[MAX_N];             // level索引值从0到N-1，level用于储存层级
int level_num = 0;              // 层级数量 
int N, W;                       // N为矩形数量，W为最大宽度 
int heap_size = 0;              // 堆内元素数量 

// 交换两个堆中元素 
void swap(int x, int y) {       // 两个元素的索引值x,y    
    Item t;
    t = item[x]; item[x] = item[y]; item[y] = t;
}

// 将一个元素最大堆  按高度从大到小排序 
void heap_push(Item x) {         
    Item t;    
    int i, p;
    heap_size++;                // 堆容量+1 
    item[heap_size] = x;        // 将元素加入至堆末位 
    i = heap_size; 
    while (i > 1) {             // 进行堆平衡维护 
        p = i / 2;                 
        if (item[i].height > item[p].height) {  // 符合上滤条件 
            swap(i, p);         // 上滤 
        } else {
            break;
        }
        i = p;    
    }    
} 

// 在最大堆中弹出并删除最大值  重新调整平衡 
Item heap_pop() {             
    Item target, t;
    target = item[1];         // 储存最大值，用于函数末输出 
    swap(1, heap_size);       // 交换堆首与堆尾，即删除了最大值 
    heap_size--;              // 堆容量-1 
    int p = 1, lc, rc;
    while (p < heap_size) {   // p未至堆边界 
        lc = p * 2;           // lc为p左子树 
        rc = p * 2 + 1;       // rc为p右子树 
        if (lc > heap_size) {  // 左子树溢出，结束循环 
            break;
        }
        if (rc > heap_size) {  // 右子树溢出 
            if (item[p].height < item[lc].height) {  // 判断该节点与左子树是否平衡 
                swap(p, lc);
            }
            break;              // 结束循环 
        }
        if (item[p].height > item[lc].height && item[p].height > item[rc].height) {  // 如果目前已经平衡，结束循环 
            break;
        }
        if (item[lc].height < item[rc].height) {    // 如果该节点p和左子树与右子树不平衡 
            swap(p, rc);         // 下滤至右子树 
            p = rc;                
        } else {
            swap(p, lc);         // 下滤至左子树 
            p = lc;
        }
    }
    return target;              // 返回储存的最大值 
}

// 判断堆是否为空 
int IsEmpty() {
    return heap_size == 0;
}

// 每次重复执行指令时需要的初始化 
void Initialize() {
    for (int j = 1; j <= N; j++) {     // 初始化堆 
        item[j] = copy[j];
    }
    heap_size = N;                      // 初始化堆容量 
    level_num = 0;                      // 初始化层级数量 
} 

// BestFit算法判断是否可塞进一个最合适的层级 (最合适：使塞入后的层级的剩余水平宽度最小) 
int BestFitable(Item x) {        
    int min = 1000000, min_index = -1;    // 初始化 
    if (level_num == 0) {                // 无层级直接返回-1 
        return -1;
    }
    for (int i = 0; i < level_num; i++) {
        if (level[i].height >= x.height && level[i].rest_w >= x.width) {  // 判断能否塞入 
            if (level[i].rest_w - x.width < min) {    // 判断塞入后该层级的剩余水平宽度是否最小 
                min = level[i].rest_w - x.width;      // 更新 
                min_index = i;
            }
        } 
    } 
    if (min_index == -1) {        // 不能塞入 
        return min_index;
    } else {
        level[min_index].rest_w = level[min_index].rest_w - x.width;  // 更新被塞入的层级的宽度 
        return min_index;
    }
}

// FirstFit算法会判断直接塞入第一个可塞入的层级 
int FirstFitable(Item x) {
    if (level_num == 0) {           // 无层级直接返回-1 
        return -1;
    }
    for (int i = 0; i < level_num; i++) {        
        if (level[i].height >= x.height && level[i].rest_w >= x.width) {    // 判断是否能塞入,能塞入直接更新相关数据，退出函数 
            level[i].rest_w = level[i].rest_w - x.width;
            return 1;
        }
    }
    return -1;           // 无法塞入 
} 

// NextFit算法判断是否能放入当前层级
int NextFitable(Item x) {
    if (level_num == 0 || level[level_num - 1].rest_w < x.width) {
        return -1;  // 如果当前层级剩余宽度不足以容纳条形图，返回-1
    } else {
        level[level_num - 1].rest_w -= x.width;  // 放入当前层级
        return 1;
    }
}

// NextFit算法
int Next_Fit_Find() {
    Item x;
    int flag;
    while (IsEmpty() != 1) {           // 堆非空则继续执行 
        x = heap_pop();                 // 按高度从大到小开始 
        flag = NextFitable(x);          // 判断是否能塞入 
        if (flag == -1) {               // 如果无法放入，则创建新层级 
            level_num++;                // 创建新的层级 
            level[level_num - 1].height = x.height;
            level[level_num - 1].rest_w = W - x.width;
        }
    }
    int sum_height = 0;
    for (int i = 0; i < level_num; i++) {
        sum_height += level[i].height;
    }
    return sum_height;  // 返回总的高度
}

// BestFit算法 
int Best_Fit_Find() {
    Item x;
    int flag;
    while (IsEmpty() != 1) {           // 堆非空则继续执行 
        x = heap_pop();                 // 按高度从大到小开始 
        flag = BestFitable(x);          // 判断是否能塞入 
        if (flag == -1) {               // 无法放入 
            level_num++;                // 创建新的层级 
            level[level_num - 1].height = x.height;
            level[level_num - 1].rest_w = W - x.width;
        }
    }
    int sum_height = 0;
    for (int i = 0; i < level_num; i++) {
        sum_height += level[i].height;
    }
    return sum_height;  // 返回总的高度 
}

// FirstFit算法 
int First_Fit_Find() {
    Item x;
    int flag;
    while (IsEmpty() != 1) {           // 堆非空则继续执行 
        x = heap_pop();                 // 按高度从大到小开始 
        flag = FirstFitable(x);         // 判断是否能塞入 
        if (flag == -1) {               // 无法放入 
            level_num++;                // 创建新的层级 
            level[level_num - 1].height = x.height;
            level[level_num - 1].rest_w = W - x.width;
            
        }
    }
    int sum_height = 0;
    for (int i = 0; i < level_num; i++) {
        sum_height += level[i].height;
    }
    return sum_height;  // 返回总的高度
}

int main(void) {
    // 声明相关变量，打开文件读取和写入 
    clock_t start, stop;
    double total_time;
    freopen("Texture_in.txt", "r", stdin);
    freopen("Texture_out.txt", "w", stdout);
    scanf("%d %d", &N, &W);    // 读取样本数量N和指定宽度W 
    Item temp;                 
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &temp.width, &temp.height);
        heap_push(temp);        // 将样本数据弹入堆中，进行堆排序 
    }
    for (int i = 1; i <= N; i++) {
        copy[i] = item[i];      // 对最大堆进行备份，方便多次循环 
    }
    
    int k = 1000;    // 循环次数,可改;由于程序执行较快，时间变化不明显，设置1000次循环执行为一组； 
    start = clock();        // 开始计时 
    int Best_Fit_Minimum_Height;
    for (int i = 1; i <= k; i++) {
        Initialize();        // 初始化 
        Best_Fit_Minimum_Height = Best_Fit_Find();
    }
    stop = clock();         // 停止计时 
    total_time = ((double)(stop - start)) / 1.0 / CLK_TCK;
    // 输出BestFit的最低高度与运行时间 
    printf("Best_Fit_Minimum_Height: %d\n", Best_Fit_Minimum_Height);
    printf("Best_Fit_Find_Time: %lfs\n", total_time);
    
    start = clock();        // 开始计时 
    int First_Fit_Minimum_Height;
    for (int i = 1; i <= k; i++) {
        Initialize();
        First_Fit_Minimum_Height = First_Fit_Find();
    }
    stop = clock();         // 停止计时
    total_time = ((double)(stop - start)) / 1.0 / CLK_TCK;
    // 输出FirstFit的最低高度与运行时间 
    printf("First_Fit_Minimum_Height: %d\n", First_Fit_Minimum_Height);
    printf("First_Fit_Find_Time: %lfs\n", total_time);
    
    // NextFit算法
    start = clock();        // 开始计时 
    int Next_Fit_Minimum_Height;
    for (int i = 1; i <= k; i++) {
        Initialize();
        Next_Fit_Minimum_Height = Next_Fit_Find();
    }
    stop = clock();         // 停止计时
    total_time = ((double)(stop - start)) / 1.0 / CLK_TCK;
    // 输出NextFit的最低高度与运行时间 
    printf("Next_Fit_Minimum_Height: %d\n", Next_Fit_Minimum_Height);
    printf("Next_Fit_Find_Time: %lfs\n", total_time);
}

