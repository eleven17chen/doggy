//eigqueprob.h
#include "stdio.h"
#define N 8 // N 表示皇后的个数 用来定义答案的结构体
typedef struct
{
    int line; // 答案的行号  
    int row; // 答案的列号 
}ANSWER_TYPE;// 用来定义某个位置是否被占用 
 
typedef enum
{
    notoccued = 0, // 没被占用  occued = 1 // 被占用 
    occued = 1
}IFOCCUED;// 该列是否已经有其他皇后占用 
 
 
IFOCCUED rowoccu[N];// 左上-右下对角位置已经有其他皇后占用 
IFOCCUED LeftTop_RightDown[2 * N - 1];// 右上-左下对角位置已经有其他皇后占用
IFOCCUED RightTop_LefttDown[2 * N - 1];// 最后的答案记录 
ANSWER_TYPE answer[N];
 
 
/* 寻找下一行占用的位置 */
void nextline(int LineIndex)
{
    static int asnnum = 0; /* 统计答案的个数 */
    int RowIndex = 0; /* 列索引 */
    int PrintIndex = 0;/* 按列开始遍历 */
    for (RowIndex = 0; RowIndex < N; RowIndex++)
    {
        /* 如果列和两个对角线上都没有被占用的话，则占用该位置 */
        if ((notoccued == rowoccu[RowIndex]) && (notoccued == LeftTop_RightDown[LineIndex - RowIndex + N - 1]) && (notoccued == RightTop_LefttDown[LineIndex + RowIndex]))
        {
            /* 标记已占用 */
            rowoccu[RowIndex] = occued;
            LeftTop_RightDown[LineIndex - RowIndex + N - 1] = occued;
            RightTop_LefttDown[LineIndex + RowIndex] = occued;
            /* 标记被占用的行、列号 */
            answer[LineIndex].line = LineIndex; answer[LineIndex].row = RowIndex;
            /* 如果不是最后一行，继续找下一行可以占用的位置 */
            if ((N - 1) > LineIndex) {
                nextline(LineIndex + 1);
            }
            /* 如果已经到了最后一行，输出结果 */
            else
            {
                asnnum++;
                printf("\nThe %dth answer is :", asnnum);
                for (PrintIndex = 0; PrintIndex<N; PrintIndex++)
                {
                    printf("(%d,%d) ", answer[PrintIndex].line + 1, answer[PrintIndex].row + 1);
                }
                /* 每10个答案一组，与其他组隔两行 */
                if ((asnnum % 10) == 0)
                    printf("\n\n");
            }
            /* 清空占用标志，寻找下一组解 */
            rowoccu[RowIndex] = notoccued;
            LeftTop_RightDown[LineIndex - RowIndex + N - 1] = notoccued;
            RightTop_LefttDown[LineIndex + RowIndex] = notoccued;
        }
    }
}
int main()
{
    int i = 0;
    /* 调用求解函数*/
    nextline(i);
    /* 保持屏幕结果*/
    getchar();
    return 1;
}