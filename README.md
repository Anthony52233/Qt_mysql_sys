# Qt_mysql_sys  

大三开学数据库设计作业  
先说一下的我配置环境：  

1、电脑系统：系统Ubuntu16.04 
2、语言：C++、Qt  
3、编译器：Qt Creator
4、Qt版本：最好是5,如果是4的话，把connect函数给修改下。有的connect函数用Qt4的写法写的，有的是用Qt5的写法写的。Qt5向下兼容Qt5  

5、数据库：Mysql，Server version: 5.7.27-0ubuntu0.16.04.1 (Ubuntu)。【注意】Qt Creator默认没有mysql驱动器，需要自己编译。Ubuntu系统如果下载了Qt Creator源码，可以自己编译驱动，Windows系统需要把下载的驱动的动态链接库给放到Qt Creator文件夹里。具体如何配置，自己上网搜索吧。  

使用该系统需要配套的数据库设置  

数据库设置如下：  
建表有：admins、cameras、customs、indents、browse、manage、update_user。  
表中属性名以及属性值见项目中mysql_table目录下的图片。  

  
【软件文档】文件夹下的  

1、 8.27_mysql.sql是我建数据库用的sql语句，算是测试数据，用处不太大。  
2、 2019数据库原理课程设计报告.docx和2019数据库原理课程设计报告_陈振山_9月6号.pdf，这两个文件的内容一致。pdf文件用于打印，排版不会乱。
3、 ER图.eddx是edrawmax软件能识别的类型。我用来画ER图，ER图.png是ER图的图片。  
4、 大三数据库设计.docx是我在软件开发过程中的随笔记录。
