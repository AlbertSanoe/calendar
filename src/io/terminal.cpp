#include <fstream>
#include "../include/terminal.h"

void tofile(){
    const char *urlf ="hello worldz";
    //创建一个 fstream 类对象
    std::fstream fs;
    //将 test.txt 文件和 fs 文件流关联
    fs.open("/home/su/Documents/Code/calendar/cache/test.txt", std::ios::out);
    //向test.txt文件中写入 url 字符串
    fs.write(urlf, 12);
    fs.close();
}

void toterminal(){

}