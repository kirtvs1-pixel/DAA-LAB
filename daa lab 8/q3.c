#include<stdio.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
int main()
{
    int m,n;
    printf("Enter length of first sequence");
    scanf("%d",&m);
    char seq1[m];
    printf("enter first sequence");
    scanf("%s",seq1);
    printf("Enter length of second sequence");
    scanf("%d",&n);
    char seq2[n];
    printf("enter the second sequence");
    scanf("%s",seq2);
    int dp[m+1][n+1];
    for(int i = 0;i<n+1;i++)
    {
        dp[i][0] = 0;
    }
    for(int j = 0;j<m+1;j++)
    {
        dp[0][j] = 0;
    }
    for(int i = 1;i<m+1;i++)
    {
        for(int j = 1;j<n+1;j++)
        {
            if(seq1[i-1] == seq2[j-1])
            {
                dp[i][j] = dp[i-1][j-1] + 1;
            }
            else
            {
                dp[i][j] = MAX(dp[i-1][j],dp[i][j-1]);
            }
        }
    }
    printf("length of LCS: %d",dp[m][n]);
    int i = m;
    int j = n;
    char temp[dp[m][n]];
    int count = dp[m][n]-1;
    while (i >0 &&j > 0)
    {
        if(seq1[i-1]==seq2[j-1])
        {
            printf("%c",seq1[i-1]);
            temp[count] = seq1[i-1];
            count--;
            i--;
            j--;
        }
        else
        {
            if(dp[i][j-1]>dp[i-1][j])
            {
                j--;
            }
            else
            {
                i--;
            }
        }
    }
    printf("proper version = %s",temp);
    return 0;
}