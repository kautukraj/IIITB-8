#include <iostream>
#include<sstream>
#include<vector>
#include <fstream>
#include "Task4.h"
using namespace std;

void Task4::read(){// this will form all the paragraphs 
    ifstream fin;
    try{//using avoid file opening errors
        fin.open(filename);//opening the file
    }
    catch(const ifstream::failure& e){
        cout<<"Error reading the file"<<endl;
        fin.close();
        return;
    }
    string text = "";
    string line;
    while(getline(fin,line)){//scanning contents of file linewise
        text = "";
        for(int i=0;i<line.length();i++){
            if(line[i] == '\n'){//if it is end of line it means paragraph ended so make a paragraph of that much text and store it in the paragraphs vector
                break;
            }
            text += line[i];
        }
        text += "\n";//adding the line character add the end of each paragraph 
        Paragraph P(text);//making paragraph

        paragraphs.push_back(P);//storing it
    }
    fin.close();//closing the file after use

}


void Task4::operate(){//this will calculate the all the stats of all the paragraphs and of overall document
    for(auto &P : paragraphs){//loop over all the paragraphs and calculate stats of each para
        calculateStats(P);
    }
    for(auto &P : paragraphs){
        Total = Total + P.getStats();//add up the stats of each paragraph using the overloaded operator 
    }
    if(Total.getBytes() > 0){
        Stats S(0,-1,0,0,-1);//to overcome the last extra the char
        Total = Total +  S;//adding this to remove the excess character by but also avoiding negative values
    }
} 



void Task4::write(){//writing with calculated stats in a new output file.
    ofstream fout;
    fout.open("output.txt");//opening output file
    fout<<Total;//using overloaded operator to write in file add the header on the file
    for(auto &P : paragraphs){//Add up the normal text as it is
        fout<<P.getText();//add the text
    }

    fout.close();//close it after use
}

void Task4 :: calculateStats(Paragraph &P){//Take a para by reference as we have to set the stats of this para taking by value and copy won't help
    string text = P.getText();
    int char_with_spaces = text.length();//length of the paragraph

    int spaces = 0,lines = 0,words = 0;
    for(int i=0;i<text.length();i++){
        if(isspace(text[i])){//this will also take care of tabs and spaces
            spaces++;
        }
        if(text[i] == '\n'){
            lines++;
        }
        if(i < text.length()-1 && isalnum(text[i]) && !isalnum(text[i+1])){// in gedit words are considered different if they are separated 
            //using special characters so we check if some char is special and char next to it is not special that means we have a word 
            words++;
        }
    }   
    int char_without_spaces = char_with_spaces - spaces;
    int bytes = char_with_spaces;//As per ASCII format each character takes up a byte to store so total bytes will be equal to total chars in text file
    Stats S(words,char_with_spaces,char_without_spaces,lines,bytes);//Make a stat 
    P.setStats(S);// assign this stat to para
}
