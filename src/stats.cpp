#include "stats.h"
#include<ostream>
#include<fstream>
using namespace std;
Stats :: Stats(int words,int char_with_spaces,int char_without_spaces,int lines,int bytes):
    words(words),
    char_with_spaces(char_with_spaces),
    char_without_spaces(char_without_spaces),
    lines(lines),
    bytes(bytes)
    {}
Stats :: Stats(const Stats &S){
    words = S.words;
    char_with_spaces = S.char_with_spaces;
    char_without_spaces = S.char_without_spaces;
    lines = S.lines;
    bytes = S.bytes;
}
Stats Stats :: operator + (const Stats &s){
    int total_words = words + s.words;
    int total_lines = lines + s.lines;
    int total_chars = char_with_spaces + s.char_with_spaces;
    int total_chars_without_spaces = char_without_spaces + s.char_without_spaces;
    int total_bytes = bytes + s.bytes;

    if(total_bytes < 0 )total_bytes = 0;//just in case 
    if(total_chars < 0 )total_bytes = 0;
    if(total_lines < 0 )total_bytes = 0;
    if(char_with_spaces < 0 )total_bytes = 0;
    if(char_without_spaces < 0 )total_bytes = 0;

    Stats total(total_words,total_chars,total_chars_without_spaces,total_lines,total_bytes);
    return total;
}
ofstream & operator<<(ofstream &fout,Stats &S){
    //printing in the format it is shown in gedit
    fout<<"Lines                    "<<S.lines<<"\n";
    fout<<"Words                    "<<S.words<<"\n";
    fout<<"Characters(with spaces)  "<<S.char_with_spaces<<"\n";
    fout<<"Characters(no spaces)    "<<S.char_without_spaces<<"\n";
    fout<<"Bytes                    "<<S.bytes<<"\n\n";
    return fout;
    
}