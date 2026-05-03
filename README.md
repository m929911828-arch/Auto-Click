# Auto-Click
基于www.humanbenchmark.com网站的自动点击程序
Click when the screen turns from color A to color B.  
先分别获取目标色的RGB以及屏幕检测的位置坐标并且在宏定义处修改  
编译时链接上-luser32 -lgdi32:  
`gcc AutoClick.c -o AutoClick.exe -luser32 -lgdi32 `
