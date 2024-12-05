#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int flag;       // ����flag
    int listN[12] = {10, 50, 100, 200, 400, 500, 1000, 2000, 4000, 6000, 8000, 10000};
    int listW[12] = {10, 30, 100, 120, 200, 300, 600, 1000, 3000, 4000, 7500, 8000};

    // ����flag����
    printf("Enter the flag type (1: Fully random, 2: Slightly random, 3: Extreme cases): ");
    scanf("%d", &flag);

    srand((unsigned int)time(NULL)); // ��ʼ�������������

    for (int index = 0; index < 12; index++) {
        int N = listN[index];
        int W = listW[index];
        char filename[20];
        sprintf(filename, "Texture_%d.txt", index + 1); // �����ļ���
        FILE *file = fopen(filename, "w");

        if (!file) {
            printf("Error: Could not create or open file %s. Skipping...\n", filename);
            continue; // �������ļ�
        }

        fprintf(file, "%d %d\n", N, W); // д��N��W

        if (flag == 1 || flag > 3) { // 1. ��ȫ���
            for (int i = 0; i < N; i++) {
                int Random = rand() % W + 1; // ������
                fprintf(file, "%d ", Random);
                Random = rand() % W + 1; // ����߶�
                fprintf(file, "%d\n", Random);
            }
        } else if (flag == 2) { // 2. ����������
            int Reference = rand() % W + 1; // ���ɻ�׼��
            int Var = Reference / 10;      // ����
            Var = Var==0?1:Var;
            printf("%d\n",Var);
            for (int i = 0; i < N; i++) {
                int Random = rand() % Var + 1;
                fprintf(file, "%d ", Reference - Reference / 10 + Random);
                Random = rand() % Var + 1;
                fprintf(file, "%d\n", Reference - Reference / 10 + Random);
            }
        } else if (flag == 3) { // 3. ��������
            int Reference = W * 8 / 10; // ��׼��
            int Var = W / 50;
            Var = Var==0?1:Var;
            for (int i = 0; i < N / 10; i++) { // ��������
                int Random = rand() % Var + 1;
                fprintf(file, "%d ", Reference + Random);
                Random = rand() % Var + 1;
                fprintf(file, "%d\n", Reference + Random);
            }
            Reference = W / 20;
            for (int i = N / 10; i < N; i++) { // ��С����
                int Random = rand() % Var + 1;
                fprintf(file, "%d ", Reference - Random);
                Random = rand() % Var + 1;
                fprintf(file, "%d\n", Reference - Random);
            }
        }

        fclose(file);
        printf("File %s generated successfully.\n", filename);
    }

    printf("All files processed.\n");
    return 0;
}

