#include "../include/terminal.h"

#define STD_WRITE std::ios::out
#define STD_APPEND std::ios::app

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
    fs.open("/home/su/Documents/Code/xcalendar/cache/output.txt", STD_APPEND);
    fs << date << std::endl;
    fs.close();
}

void write_arrangement_header(const char *path)
{
    std::fstream fs;
    fs.open(path, STD_WRITE);
    fs << arrangement_header << "\n";
    fs.close();
}

void write_date(const char *path, const Date &date)
{
    std::fstream fs;
    fs.open(path, STD_APPEND);
    fs << "Date:\t" << date << std::endl;
    fs.close();
}

void write_time_place_event(const char *path, const Time &t, const Place &p, const Event &e)
{
    std::fstream fs;
    fs.open(path, STD_APPEND);
    fs << t << "\t" << p << "\t" << e << std::endl;
    fs.close();
}

void write_file_output(const char *file, Output_table *tbl)
{
    write_arrangement_header(file);
    tbl->iter_init();
    Date date = Date(0, 0, 0, 0);
    Time time;
    Place place;
    Event event;
    Date old_date(1, 1, 1, 1);
    bool res;
    do
    {
#ifdef TRY_DEBUG
        std::cout << "###############the date is " << date << std::endl;
#endif
        res = tbl->iter_traverse(date, time, place, event);
        if (res)
        {
            if (old_date != date)
            {
                write_date(file, date);
                old_date = date;
            }

            write_time_place_event(file, time, place, event);
        }

    } while (res);
}

static int __parse_option(const std::string &str, int &number)
{
    if (str.length() < 2)
    {
        return -1; // 字符串太短，无法解析
    }

    char letter = str[0];
    if (!(letter == 'A' || letter == 'a' || letter == 'B' || letter == 'b'))
    {
        return -1; // 首字符不是A、a、B或b，无法解析
    }

    bool is_digit = true;
    for (size_t i = 1; i < str.length(); ++i)
    {
        if (!isdigit(str[i]))
        {
            is_digit = false;
            break;
        }
    }

    if (!is_digit)
    {
        return -1; // 字符串中有非数字字符，无法解析
    }

    number = std::stoi(str.substr(1)); // 解析数字部分并转换为整数

    if (letter == 'A' || letter == 'a')
    {
        return 0;
    }
    else if (letter == 'B' || letter == 'b')
    {
        return 1;
    }

    return -1; // 未知错误
}

// 存在问题： 当An Bn时,可能会超出界限
void xcal_process(int argc, const std::vector<std::string> &argv)
{
#ifdef TRY_DEBUG
    DEBUG("argc %d\n", argc);
#endif
    if (argc == 1)
    {
        if (argv[0] == "today")
        {
            auto today = Date::get_today(nullptr);
            std::cout << today << std::endl;
        }
        else if (argv[0] == "now")
        {
            Time tt;
            auto today = Date::get_today(&tt);
            std::cout << today << "\t" << tt << std::endl;
        }
        else if (std::isdigit(argv[0][0]))
        {
            // ask for the current month
            if (argv[0].size() == 1 || argv[0].size() == 2 && std::isdigit(argv[0][1]))
            {
                int current_month = std::stoi(argv[0]);
                if (current_month >= 1 && current_month <= 12)
                {
                    Month month = current_month;
                    Year year = Date::get_currentyear();
                    int after = 0;
                    int before = 0;
                    Calendar *new_cal = Calendar::get_cal(&month, &year, &after, &before);
                    new_cal->generate();
                    std::cout << new_cal->content << std::endl;
                }
                else
                {
                    std::cerr << "Not supported input" << std::endl;
                }
            }
            else if (argv[0].size() == 4 && std::isdigit(argv[0][1]) && std::isdigit(argv[0][2]) && std::isdigit(argv[0][3]))
            {
                int current_year = std::stoi(argv[0]);
                if (current_year >= 1912 && current_year <= 9999)
                {
                    Month month = 1;
                    Year year = current_year;
                    int after = 11;
                    int before = 0;
                    Calendar *new_cal = Calendar::get_cal(&month, &year, &after, &before);
                    new_cal->generate();
                    std::cout << new_cal->content << std::endl;
                }
                else
                {
                    std::cerr << "Not supported input" << std::endl;
                }
            }
            else if (argv[0].size() == 6 && std::isdigit(argv[0][1]) && std::isdigit(argv[0][2]) && std::isdigit(argv[0][3]) && std::isdigit(argv[0][5]) && (argv[0][4] == '.' || argv[0][4] == '-'))
            {
                int current_year = (argv[0][0] - '0') * 1000 + (argv[0][1] - '0') * 100 + (argv[0][2] - '0') * 10 + (argv[0][3] - '0');
                int current_month = argv[0][5] - '0';
                if (current_year >= 1912 && current_year <= 9999 && current_month != 0)
                {
                    Month month = current_month;
                    Year year = current_year;
                    int after = 0;
                    int before = 0;
                    Calendar *new_cal = Calendar::get_cal(&month, &year, &after, &before);
                    new_cal->generate();
                    std::cout << new_cal->content << std::endl;
                }
                else
                {
                    std::cerr << "Not supported input" << std::endl;
                }
            }
            else if (argv[0].size() == 7 && std::isdigit(argv[0][1]) && std::isdigit(argv[0][2]) && std::isdigit(argv[0][3]) && std::isdigit(argv[0][5]) && std::isdigit(argv[0][6]) && (argv[0][4] == '.' || argv[0][4] == '-'))
            {
                int current_year = (argv[0][0] - '0') * 1000 + (argv[0][1] - '0') * 100 + (argv[0][2] - '0') * 10 + (argv[0][3] - '0');
                int current_month = (argv[0][5] - '0') * 10 + argv[0][6] - '0';
                if (current_year >= 1912 && current_year <= 9999 && current_month >= 1 && current_month <= 12)
                {
                    Month month = current_month;
                    Year year = current_year;
                    int after = 0;
                    int before = 0;
                    Calendar *new_cal = Calendar::get_cal(&month, &year, &after, &before);
                    new_cal->generate();
                    std::cout << new_cal->content << std::endl;
                }
                else
                {
                    std::cerr << "Not supported input" << std::endl;
                }
            }
            else
            {
                std::cerr << "Not supported input" << std::endl;
            }
        }
    }
    else if (argc == 2)
    {
        int result;
        int number;
        int after = 0;
        int before = 0;
        result = __parse_option(argv[0], number);
#ifdef TRY_DEBUG
        DEBUG("the result is %d\n", result);
#endif
        if (result == 0)
        {
            after = number;
        }
        else if (result == 1)
        {
            before = number;
        }
        else
        {
            std::cerr << "Not supported input" << std::endl;
            return;
        }
#ifdef TRY_DEBUG
        DEBUG("a b %d %d\n", after, before);
#endif
        int current_month;
        int current_year;
        if (std::isdigit(argv[1][0]))
        {
            if (argv[1].size() == 1 || argv[1].size() == 2 && std::isdigit(argv[1][1]))
            {
                current_month = std::stoi(argv[1]);
                current_year = Date::get_currentyear();
                if (current_month >= 1 && current_month <= 12)
                {
                    Month month = current_month;
                    Year year = current_year;
                    Calendar *new_cal = Calendar::get_cal(&month, &year, &after, &before);
                    new_cal->generate();
                    std::cout << new_cal->content << std::endl;
                }
                else
                {
                    std::cerr << "Not supported input" << std::endl;
                }
            }
            else if (argv[1].size() == 6 && std::isdigit(argv[1][1]) && std::isdigit(argv[1][2]) && std::isdigit(argv[1][3]) && std::isdigit(argv[1][5]) && (argv[1][4] == '.' || argv[1][4] == '-'))
            {
#ifdef TRY_DEBUG
                DEBUG("the size is 6\n");
#endif
                current_year = (argv[1][0] - '0') * 1000 + (argv[1][1] - '0') * 100 + (argv[1][2] - '0') * 10 + (argv[1][3] - '0');
                current_month = argv[1][5] - '0';
#ifdef TRY_DEBUG
                DEBUG("year month %d %d\n", current_year, current_month);
#endif
                if (current_year >= 1912 && current_year <= 9999 && current_month != 0)
                {
                    Month month = current_month;
                    Year year = current_year;
                    Calendar *new_cal = Calendar::get_cal(&month, &year, &after, &before);
                    new_cal->generate();
                    std::cout << new_cal->content << std::endl;
                }
                else
                {
                    std::cerr << "Not supported input" << std::endl;
                }
            }
            else if (argv[1].size() == 7 && std::isdigit(argv[1][1]) && std::isdigit(argv[1][2]) && std::isdigit(argv[1][3]) && std::isdigit(argv[1][5]) && std::isdigit(argv[1][6]) && (argv[1][4] == '.' || argv[1][4] == '-'))
            {
                current_year = (argv[1][0] - '0') * 1000 + (argv[1][1] - '0') * 100 + (argv[1][2] - '0') * 10 + (argv[1][3] - '0');
                current_month = (argv[1][5] - '0') * 10 + (argv[1][6] - '0');
                if (current_year >= 1912 && current_year <= 9999 && current_month >= 1 && current_month <= 12)
                {
                    Month month = current_month;
                    Year year = current_year;
                    Calendar *new_cal = Calendar::get_cal(&month, &year, &after, &before);
                    new_cal->generate();
                    std::cout << new_cal->content << std::endl;
                }
                else
                {
                    std::cerr << "Not supported input" << std::endl;
                }
            }
            else
            {
                std::cerr << "Not supported input" << std::endl;
            }
        }
        else
        {
            std::cerr << "Not supported input" << std::endl;
        }
    }
    else if (argc == 3)
    {
        int result;
        int number;
        int after = 0;
        int before = 0;
        result = __parse_option(argv[0], number);
#ifdef TRY_DEBUG
        DEBUG("the result is %d\n", result);
#endif
        if (result == 0)
        {
            after = number;
        }
        else if (result == 1)
        {
            before = number;
        }
        else
        {
            std::cerr << "Not supported input" << std::endl;
            return;
        }

        result = __parse_option(argv[1], number);
#ifdef TRY_DEBUG
        DEBUG("the result is %d\n", result);
#endif
        if (result == 0)
        {
            after = number;
        }
        else if (result == 1)
        {
            before = number;
        }
        else
        {
            std::cerr << "Not supported input" << std::endl;
            return;
        }

#ifdef TRY_DEBUG
        DEBUG("a b %d %d\n", after, before);
#endif

        int current_month;
        int current_year;
        if (std::isdigit(argv[2][0]))
        {
            if (argv[2].size() == 1 || argv[2].size() == 2 && std::isdigit(argv[2][1]))
            {
                current_month = std::stoi(argv[2]);
                current_year = Date::get_currentyear();
                if (current_month >= 1 && current_month <= 12)
                {
                    Month month = current_month;
                    Year year = current_year;
                    Calendar *new_cal = Calendar::get_cal(&month, &year, &after, &before);
                    new_cal->generate();
                    std::cout << new_cal->content << std::endl;
                }
                else
                {
                    std::cerr << "Not supported input" << std::endl;
                }
            }
            else if (argv[2].size() == 6 && std::isdigit(argv[2][1]) && std::isdigit(argv[2][2]) && std::isdigit(argv[2][3]) && std::isdigit(argv[2][5]) && (argv[2][4] == '.' || argv[2][4] == '-'))
            {
#ifdef TRY_DEBUG
                DEBUG("the size is 6\n");
#endif
                current_year = (argv[2][0] - '0') * 1000 + (argv[2][1] - '0') * 100 + (argv[2][2] - '0') * 10 + (argv[2][3] - '0');
                current_month = argv[2][5] - '0';
#ifdef TRY_DEBUG
                DEBUG("year month %d %d\n", current_year, current_month);
#endif
                if (current_year >= 1912 && current_year <= 9999 && current_month != 0)
                {
                    Month month = current_month;
                    Year year = current_year;
                    Calendar *new_cal = Calendar::get_cal(&month, &year, &after, &before);
                    new_cal->generate();
                    std::cout << new_cal->content << std::endl;
                }
                else
                {
                    std::cerr << "Not supported input" << std::endl;
                }
            }
            else if (argv[2].size() == 7 && std::isdigit(argv[2][1]) && std::isdigit(argv[2][2]) && std::isdigit(argv[2][3]) && std::isdigit(argv[2][5]) && std::isdigit(argv[2][6]) && (argv[2][4] == '.' || argv[2][4] == '-'))
            {
                current_year = (argv[2][0] - '0') * 1000 + (argv[2][1] - '0') * 100 + (argv[2][2] - '0') * 10 + (argv[2][3] - '0');
                current_month = (argv[2][5] - '0') * 10 + (argv[2][6] - '0');
                if (current_year >= 1912 && current_year <= 9999 && current_month >= 1 && current_month <= 12)
                {
                    Month month = current_month;
                    Year year = current_year;
                    Calendar *new_cal = Calendar::get_cal(&month, &year, &after, &before);
                    new_cal->generate();
                    std::cout << new_cal->content << std::endl;
                }
                else
                {
                    std::cerr << "Not supported input" << std::endl;
                }
            }
            else
            {
                std::cerr << "Not supported input" << std::endl;
            }
        }
        else
        {
            std::cerr << "Not supported input" << std::endl;
        }
    }
    else
    {
        std::cerr << "Not supported input" << std::endl;
    }
}

void xcc_process(int argc, const std::vector<std::string> &argv){
    if(argc==2){
        read_write(argv[0].c_str(),argv[1].c_str());
    }
    else{
        std::cerr << "Not supported input" << std::endl;
    }
}

void read_write(const char *file, const char *ofile)
{
    std::string fileName = file;
    std::ifstream inFile(fileName);
    if (!inFile.is_open())
    {
        std::cerr << "Error: Unable to open the file." << std::endl;
    }

    Analyzer scanner;
    Output_table ot;
    CmdParser cp(&ot, &scanner);
    Preprocessor_table pt;
    PreParser pp(&pt, &scanner);
    kw_punctuation kwp;
    int offset;
    ERROR_CODE status;
    int boolean_res_logic = 0;
    bool command_context = false;
    while (!inFile.eof())
    {
        if (!scanner.scan_whitespace(inFile, offset))
        {
            inFile.seekg(-offset, std::ios::cur);
        }
        else
        {
            break;
        }

        status = scanner.scan_punctuation(inFile, kwp, offset);

#ifdef TRY_DEBUG
        DEBUG("status, offset %d, %d\n", (int)status, offset);
#endif

        if (status != A_FINE || offset != 1)
        {
            std::cerr << error_handler(status) << std::endl;
            return;
        }

        inFile.seekg(-offset, std::ios::cur);
        offset = 0;

        // use switch later
        if (kwp == kwa_not)
        {
            if (command_context == false)
            {
                bool ig_res = scanner.ignore(inFile, offset, '}');
#ifdef TRY_DEBUG
                DEBUG("ig_res, offset %d, %d\n", (int)ig_res, offset);
#endif
                if (!ig_res)
                {
                    std::cerr << error_handler(P_SCANNING_MISMATCHED) << std::endl;
                    return;
                }
                inFile.seekg(-offset, std::ios::cur);
                continue;
            }
            status = read_command(inFile, &scanner, &cp);

#ifdef TRY_DEBUG
            DEBUG("status, offset %d, %d\n", (int)status, offset);
#endif
            if (status != P_FINE)
            {
                std::cerr << error_handler(status) << std::endl;
                return;
            }
        }
        else if (kwp == kwd_dol)
        {
            status = read_logic(inFile, &scanner, &pp, boolean_res_logic);

#ifdef TRY_DEBUG
            DEBUG("status, offset %d, %d\n", (int)status, offset);
#endif
            if (status != P_FINE)
            {
                std::cerr << error_handler(status) << std::endl;
                return;
            }
        }
        else if (kwp == kwd_lcb && boolean_res_logic == 1)
        {
            boolean_res_logic = 0;
            command_context = true;
        }
        else if (kwp == kwd_rcb)
        {
            command_context = false;
        }
    }
    write_file_output(ofile, &ot);
}

// invoked by !
ERROR_CODE read_command(std::ifstream &inFile, Analyzer *a, CmdParser *cp)
{
    kw_command kw;
    int offset;
    ERROR_CODE status;
    Place p;
    Event e;
    bool res;
    status = a->scan_command(inFile, kw, offset);

#ifdef TRY_DEBUG
    DEBUG("status, offset %d, %d\n", (int)status, offset);
#endif

    if (status != A_FINE || offset != 1)
    {
        std::cerr << error_handler(status) << std::endl;
        return P_SCANNING_MISMATCHED;
    }

    inFile.seekg(-offset, std::ios::cur);

    switch (kw)
    {
    case kwc_set:
    {
        status = cp->cmd_set(inFile, offset);
        break;
    }
    case kwc_findset:
    {
        status = cp->cmd_findset(inFile, offset);
        break;
    }
    case kwc_get:
    {
        status = cp->cmd_get(inFile, offset, &p, &e);
        break;
    }
    case kwc_clear:
    {
        status = cp->cmd_clear(inFile, offset);
        break;
    }
    case kwc_check:
    {
        status = cp->cmd_check(inFile, offset, res);
        break;
    }
    default:
        status = P_SCANNING_MISMATCHED;
        break;
    }
    if (status != A_FINE || offset != 0)
    {
        std::cerr << error_handler(status) << std::endl;
        return P_SCANNING_MISMATCHED;
    }
#ifdef TRY_DEBUG
    DEBUG("END OF READ COMMAND\n");
#endif
    return status;
}

ERROR_CODE read_logic(std::ifstream &inFile, Analyzer *a, PreParser *pp, int &_res)
{
    kw_logic kw;
    int offset;
    ERROR_CODE status;
    Place p;
    Event e;
    bool res;
    status = a->scan_logic(inFile, kw, offset);

#ifdef TRY_DEBUG
    DEBUG("status, offset %d, %d\n", (int)status, offset);
#endif

    if (status != A_FINE || offset != 1)
    {
        std::cerr << error_handler(status) << std::endl;
        return P_SCANNING_MISMATCHED;
    }

    inFile.seekg(-offset, std::ios::cur);

    switch (kw)
    {
    case kwl_if:
    {
        status = pp->pre_if(inFile, offset, res); // offset =0
        break;
    }
    case kwl_ifdef:
    {
        status = pp->pre_ifdef(inFile, offset, res); // offset =0
        break;
    }
    case kwl_ifeq:
    {
        status = pp->pre_ifeq(inFile, offset, res); // offset =0
        break;
    }
    case kwl_ifndef:
    {
        status = pp->pre_ifndef(inFile, offset, res); // offset =0
        break;
    }
    case kwl_ifneq:
    {
        status = pp->pre_ifne(inFile, offset, res); // offset =0
        break;
    }
    case kwl_else:
    {
        status = pp->pre_else(inFile, offset); // offset =0
        break;
    }
    case kwl_define:
    {
        status = pp->pre_define(inFile, offset); // offset =0
        break;
    }
    default:
    {
        status = P_SCANNING_MISMATCHED;
        break;
    }
    }
#ifdef TRY_DEBUG
    DEBUG("status, offset %d, %d\n", (int)status, offset);
#endif

    if (status != A_FINE || offset != 0)
    {
        std::cerr << error_handler(status) << std::endl;
        return P_SCANNING_MISMATCHED;
    }

    if (kw == kwl_define)
    {
        _res = -1;
    }
    else
    {
        _res = (int)res;
    }
#ifdef TRY_DEBUG
    DEBUG("status, offset %d, %d\n", (int)status, offset);
#endif
    return status;
}