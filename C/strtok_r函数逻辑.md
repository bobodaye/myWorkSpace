# strtok函数源码：

```c
//在NetBSD中strtok的实现:
char* strtok_r(char* string_org, const char* demial, char** last)
{
	const char* spanp; //span表示分隔，p表示指针
	char c, sc; //c表示char字符，sc表示 span char
	char* tok;  //token表示分隔的段
 
	//当开始结尾都为NULL的时候，说明没有字符被查找，所以返回NULL
	if (string_org == NULL  && (string_org = *last) == NULL)
	{
	    return (NULL);
	}
 
	//由goto组成的循环是在扫描字符串的时候，当遇到所需要匹配的字符时，略过这个字符。        
cout:
	c = *string_org++;
    
	for (spanp = demial; (sc = *spanp++) != 0; )
    {
    	if (c == sc)
        {
        	goto cout;
        }
    }
 
	//下一个字符为0，则表示到达了搜索结果，把last置为NULL，并返回NULL            
	if (c == 0)
	{
	    *last = NULL;
	    return (NULL);
	}
 
	//把原始的字符串指针回退。            
	tok = string_org - 1;
	
	//开始扫描字符串中是否含有要匹配的字符，之后把这个匹配字符之前的部分返回。
	//这看似是个无限循环，但当源字符串和匹配字符串都走到结尾时，也就是string_org和sc都为NULL时，最外层循环最后会走到return(tok)结束循环。
	for (;;)
    {
	    c = *string_org++;
	    spanp = demial;
	    
	    do 
        {
	        if ((sc = *spanp++) == c) 
            {
	            if (c == 0)
                {
	                string_org = NULL;
                }
	            else
                {
	                string_org[-1] = 0;
                }
	            *last = string_org;
	            return (tok);
            }
        } while (sc != 0);
    }	    
}

//把last设置为一个静态局部变量来保存余下内容的地址。
char *
strtok(char *s, const char *delim)
{
    static char *lasts; 
    return strtok_r(s, delim, &lasts);
}
```
---

## strtok_r函数逻辑：

第一步：开始扫描字符串str，如果遇到所要匹配的字符，则忽略。否则，结束goto组成的循环，继续往下判断。

第二步：有两种情况：

1. str字符串到达结尾（扫描完成），返回NULL。

2. str字符串未到达结尾，下面继续扫描字符串是否含有要匹配的字符c，之后把这个匹配字符c之前的部分返回。

**具体步骤**：

tok指向待返回部分的首地址，继续扫描字符串str，如果遇到所要匹配的字符c，有两种情况：

1. 字符串str扫描完成（因为字符串结尾都是'\0'，肯定匹配）

2. 要返回它之前的部分，将原字符串中的c替换为'\0'，再用内部的静态指针变量保存下一次开始扫描的位置，最后返回字符c之前的部分。