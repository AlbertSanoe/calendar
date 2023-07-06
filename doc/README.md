# DRAFT

## KEYWORD

/* begin with '!' */

SET
FIND_SET
FIND
CLEAR
CHECK
GET

CAL

/* begin with '$' */
let 
if	ifdef	ifndef	ifeq	ifneq	
else
endif

WEATHER
TIME
PLACE
PERSON
ARRANGEMENT


## VARIABLE
digit_one_to_nine :=
    "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9";
 
digit := 
    "0" | digit_one_to_nine;

second :=
    digit
    | ( "1" | "2" | "3" | "4" | "5"), digit
    | "60";

minute :=
    digit
    | ( "1" | "2" | "3" | "4" | "5"), digit
    | "60";

hour :=
    digit_one_to_nine
    | "1", digit
    | "2", ("0" | "1" | "2" | "3");

year_digit := digit_one_to_nine, [digit], [digit], [digit];

day_digit :=
    digit_one_to_nine
    | "1", digit
    | "2", ("0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9")
    | "3", ("0" | "1");

month_digit :=
    digit_one_to_nine
    | "1", ("0" | "1" | "2");

month_string :=
    "January"   |
    "February"  |
    "March"     |
    "April"     |
    "May"       |
    "June"      |
    "July"      |
    "August"    |
    "September" |
    "October"   |
    "November"  |
    "Decemeber"; 

month_string_abbr3 :=
    "Jan" | "Feb" | "Mar" | "Apr" | "May" | "Jun" |
    "Jul" | "Aug" | "Sep" | "Oct" | "Nov" | "Dec";

weekday_digit :=
    "0" | "1" | "2" | "3" | "4" | "5" | "6";

weekday_string :=
    "Sunday"    |
    "Monday"    |
    "Tuesday"   |
    "Wednesday" |
    "Thursday"  |
    "Friday"    |
    "Saturday";  

weekday_string_abbr3 :=
    "Sun" | "Mon" | "Tue" | "Wed" | "Thu" | "Fri" | "Sat";

cal_time := 
    [year_digit] , "-" , ( month_digit | month_string | month_string_abbr3 ), "-" , 
    day_digit ,  [ "-" , ( weekday_digit | weekday_string | weekday_string_abbr3 ) ];

exact_time := hour , ":" , minute , ":" , second;

space := " ";

time := [cal_time, space], exact_time;

letter := 
    "A" | "B" | "C" | "D" | "E" | "F" | "G" | "H" | "I" | "J" | "K" | "L" | "M" |
    "N" | "O" | "P" | "Q" | "R" | "S" | "T" | "U" | "V" | "W" | "X" | "Y" | "Z" | 
    "a" | "b" | "c" | "d" | "e" | "f" | "g" | "h" | "i" | "j" | "k" | "l" | "m" | 
    "n" | "o" | "p" | "q" | "r" | "s" | "t" | "u" | "v" | "w" | "x" | "y" | "z";

allowed_char := letter | digit | space;

allowed_string := "\"", allowed_char {allowed_char}, "\"";

place := "PLACE", allowed_string;

arrangement :=  "ARRANGE" , allowed_string;

person := "PERSON", allowed_string;

## COMMAND
command_prefix := "!";
end_of_command := "!";

<set_command> :=
    command_prefix , "SET" , space , time ,[ space , place ],space, arrangment,
    end_of_command;
/// !SET  TIME [PLACE] ARRANGEMENT!

<findset_command> :=
    command_prefix , "FIND_SET",space , time, [space, place], [space, arrangement]
    end_of_command; 
/// !FIND_SET TIME [PLACE] [ARRANGEMENT]!

<clear_command> :=
    command_prefix ,  "CLEAR" , [space, time], [space, place], [space arrangement]
    end_of_command; 
/// !CLEAR [TIME] [PLACE] [ARRANGEMENT]!

<check_command> :=
    command_prefix , "CHECK", space, time, [space, place], [space arrangement]
    end_of_command;
/// ！CHECK TIME [PLACE] [ARRANGEMENT]!

<get_command> :=
    command_prefix , "GET", space, time
    end_of_comand;
// !GET TIME!

<cal_command> :=
CAL {CALTIME}

## CONTROL STATEMENT
/* begin with '$' */

cntl_stat_pre = "$";

condition :=

let

if_kw = "if";
endif_kw = "endif";
ifdef_kw =  "ifdef";
ifndef_kw = "ifndef";
ifeq_kw =   "ifeq";
ifneq_kw = "ifneq";
else_kw =   "else";


<if_statement> :=
    cntl_stat_pre , if_kw <condition>

if	ifdef	ifndef	ifeq	ifneq	
else
endif

1999-12-31 "Internatinal Conference Center" "Meeting"

