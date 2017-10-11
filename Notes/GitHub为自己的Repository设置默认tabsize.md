原文链接：[http://www.cnblogs.com/sfqtsh/p/6650257.html](http://www.cnblogs.com/sfqtsh/p/6650257.html)

GitHub默认显示tab为8个空格的大小，若想要改为4个怎么办呢？

---
1.别人的Repository

解决方法：要么浏览器URL中添加后缀?ts=4，要么安装浏览器扩展或自己配置css。

2.自己的Repository

GitHub是支持EditorConfig的。只需在你的Repository根目录下(注意不是.git文件夹下)新建文件

**`.editorconfig`**

```
# top-most EditorConfig file
root = true

# all files
[*]
indent_style = tab
indent_size = 4
```
注意，该配置文件不仅仅对浏览有效，在线编辑时也是有效的。

**indent_style:** 可以是**tab**或**space**。tab是hard tab，space为soft tab(按下的是Tab键，出来的实际是空格)。

**indent_size:** 缩进的宽度，即列数，整数。如果indent_style为tab，则此属性默认为tab_width。

**tab_width:** 设置tab的列数。默认是indent_size。

[参考链接]：

1. [http://stackoverflow.com/questions/8833953/how-to-change-tab-size-on-github](http://stackoverflow.com/questions/8833953/how-to-change-tab-size-on-github)

2. [http://editorconfig.org/](http://editorconfig.org/)

3. [http://www.cnblogs.com/xiyangbaixue/p/4201490.html](http://www.cnblogs.com/xiyangbaixue/p/4201490.html)
