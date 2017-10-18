#include <string.h>
#include <stdlib.h>
#include <assert.h>

void Trim(char *strIn, char *strOut, size_t strOutSize)
{
	int i, j ;
	assert(strIn || strOut);

    i = 0;
    j = strlen(strIn) - 1;

    while(strIn[i] == ' ')
        ++i;

    while(strIn[j] == ' ')
        --j;
    assert(strOutSize > j - i + 1);
    strncpy(strOut, strIn + i , j - i + 1);
    strOut[j - i + 1] = '\0';
}