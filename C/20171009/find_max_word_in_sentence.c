/*************************************************************************
	> File Name: find_word.c
	> Author: 
	> Mail: 
	> Created Time: Sun 27 Nov 2016 11:08:48 AM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>

int rule(char ch, const char rules[]);
int find_word(char *str, const char rules[]);

int main(void)
{
    char str[80] = {'\0'};
    char rules[] = ",.!: ";

    gets(str);

    find_word(str, rules);

    return 0;
}

/*
 * 功能：打印句子中的每个单词，并且找出最大的那个单词
 * 逻辑：单词分割符保存在rules数组，依据它来找单词
*/
int find_word(char *str, const char rules[])
{
    int i = 0;
    int j = 0;
    char word[20] = {'\0'};
    char max[20] = {'\0'};
    
    while('\0' != str[i++])
    {
        if(rule(str[i - 1], rules))
        {
            if(0 == strlen(word))
            {
                continue;
            }
            if(strcmp(max, word) < 0)
            {
                memset(max, '\0', sizeof(max));
                strcpy(max, word);
            }
            printf("%s\n", word);
            memset(word, '\0', sizeof(word));
            j = 0;
            continue;
        }
        word[j++] = str[i - 1];
    }
    printf("max = %s\n", max);
}

int rule(char ch, const char rules[])
{
    int i = 0;
    
    while('\0' != rules[i++])
    {
        if(ch == rules[i - 1])
        {
            return 1;   
        }
    }
    return 0;
}
