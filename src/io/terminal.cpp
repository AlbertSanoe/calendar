
#include "../include/terminal.h"

#define STD_WRITE std::ios::out
#define STD_APPEND std::ios::app

const char *output_file_path = "/home/su/Documents/Code/xcalendar/cache/output.txt";

void tofile()
{
    const char *urlf = "hello_SICK_MAN";
    // 创建一个 fstream 类对象
    std::fstream fs;
    // 将 test.txt 文件和 fs 文件流关联
    fs.open("/home/su/Documents/Code/calendar/cache/test.txt", std::ios::out);
    // 向test.txt文件中写入 url 字符串
    fs << urlf << std::endl;
    fs.close();
}

void outputfile_demo(const Date &date)
{
    std::fstream fs;
    fs.open(output_file_path, STD_APPEND);
    fs << date << std::endl;
    fs.close();
}

void write_arrangement_header(const char *path){
    std::fstream fs;
    fs.open(output_file_path, STD_WRITE);
    fs << arrangement_header << "\n";
    fs.close();
}

void write_date(const char *path,const Date &date)
{
    std::fstream fs;
    fs.open(output_file_path, STD_APPEND);
    fs << "Date:\t" <<date << std::endl;
    fs.close();
}

void write_time_place_event(const char *path, const Time &t, const Place &p, const Event &e)
{
    std::fstream fs;
    fs.open(output_file_path, STD_APPEND);
    fs << t << "\t" << p << "\t" << e << std::endl;
    fs.close();
}