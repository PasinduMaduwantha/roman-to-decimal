/*
* DATE       : 13-09-2021
* COURSE     : PROGRAMMING QUEST (CO2210)
* TITLE      : QUEST 02- ROMAN NUMBERS
* AUTHOR     : MADHUWANTHA A.P.
* INDEX NO   : 19/ENG/121
*/
#include <iostream> //to access cout cin 
#include <string>   //to use functions of string header
#include <fstream>  //to file handeling
#include <vector>   //to push each string into the vector
#include <sstream>
using namespace std;
/*
Note : in this programme basically were considered up to 100 roman numbers. therefore beyond 100 did not validate here
       so if there is valide number greater than 100 wil also return as error.
*/
/*
Function    : digitValue
Inputs      : character
Output      : compatible decimal value
*/
int digitValue(char romanCharacter)
{
    switch (romanCharacter)
    {
        //according to correct input then output relevent decimal value
        //other than exit from the programme
        case 'i' :
        case 'I' : return 1;

        case 'v' :
        case 'V' : return 5;

        case 'x' :
        case 'X' : return 10;

        case 'l' :
        case 'L' : return 50;

        case 'c' :
        case 'C' : return 100;
        //consider roman numbers upto 100

        default  : exit(0);
    }
}
/*
Function    : convertToDecimal
Inputs      : valid roman number
Output      : N/A
*/
void convertToDecimal(string roman)
{
    int totValue = 0;
    for (int index = 0; index < roman.length() ; index++)
    {
        int digit1 = digitValue(roman[index]);
        if(index<roman.length()-1)
        {
            int digit2 = digitValue(roman[index+1]);
            if(digit1>=digit2)
                totValue += digit1; 
                //if current value greater than or equal imedeat next value add to the total value
            else
                totValue -= digit1;
                //if current value lesser than imedeat next value substract from the total value
        }
        else
            totValue += digit1; //last digit is alwasy add to the total value
    }
    //print the final value
    cout << roman << " \t= " << totValue << endl;
}
/*
Function    : isValid
Inputs      : string
Output      : return true if valid roman number else return false
*/
bool isValid(string roman)
{
    bool condition = true;
    int index = 0;
    int iCount = 0, vCount = 0, xCount = 0, lCount = 0, cCount = 0;
    //puch characters into a stack
    while (roman[index]!='\0')
    {
        char temp = roman[index];
        // int current= digitValue(temp);
        // int next = digitValue(roman[index + 1]);
        temp=towlower(roman[index]); //convert all charaters into lower cases
        //we should take each character count because, i and c can repeat only 3 times,
        //v and l can't repeat and x can repeat 4 times
        if(temp=='i')   
            iCount++;

        else if(temp=='v')  
            vCount++;

        else if(temp=='x')   
            xCount++;

        else if(temp=='l')   
            lCount++;

        else if(temp=='c')
            cCount++;
        //count each character
        else
            return false;
        //if violte counter rule then return false
        if(iCount>3 || vCount>1 || xCount>4 || lCount>1 || cCount>1)
            return false;

        index++;
    }

    //after 100 or c don't consider beyond that value therefore ci , cii ,cx ... also take as invalid
    if(cCount==1 && index>1 && tolower(roman[0])!='x')
    {
        cout << "Can not validate beyond 100\n";
        return false;
    }
    //now index-1 is equal to no of characters in roman number :--> A special scenario
    if(xCount==4)   //if there shouldn't be 4 x value near to  --> xxxx not valid xxxix valid
    {
        int i=0;
        while(tolower(roman[i])!='x')
        {
            i++;
        }
        if(tolower(roman[i+3])=='x')
            return false;
        else
            condition = true;
    }
    
    //up to 100 roman numbers violate the ascending order of the dgits at 
    //only first character (40s and 90s) and before end(4s and 9s)
    //othrewise all digits in ascending order, therefore here will return false if violate those conditions
    //otherwise can't violate the descending order
    for (int j = 0; j < index-1;j++)
    {   //first digit is already checked therefore check with 2nd digit
        int digit1 = digitValue(roman[j]);
        int digit2 = digitValue(roman[j + 1]);
        if(digit1<digit2)   //violate the descending order
        {
            //violate desecnding order at 40s and 90s, are ok
            if((tolower(roman[1])=='l' || tolower(roman[1])=='c') )
            {    
                if(index>2 && digitValue(tolower(roman[2]))>5)
                    return false;
                else if(tolower(roman[0])=='x')
                    condition = true;
                else
                    return false;
            }
                

            //at the end violate the descending order, only ix and iv
            else if((tolower(roman[index-1])=='x' || tolower(roman[index-1])=='v')   )
            {   //**index of the last element is index-1
                if(digitValue(roman[index-2])<digitValue(roman[index-1]))   
                {
                    //if apear same value the can't apear greater vale as next vale -->iiv, iix, xxl
                    //tolower(roman[index - 3]) != 'i'  && tolower(roman[index - 4]) != 'i' checked that condition
                    if (tolower(roman[index - 2]) == 'i' && tolower(roman[index - 3]) != 'i'  && tolower(roman[index - 4]) != 'i')
                        condition = true;
                    else
                        return false;
                }
                else
                {
                    //
                    if (tolower(roman[index - 2]) == 'i' && tolower(roman[index - 3]) != 'i'  && tolower(roman[index - 4]) != 'i')
                        condition = true;
                    else
                        return false;
                }
            }

            else
                return false;
        }
        else
            condition = true;
    }

    return condition;
}

int main()
{
    fstream inFile;
    inFile.open("numbers.txt");
    if(!inFile.is_open())
    {    
        cout << "Can not find the file!";
        exit(0);
        //check whether the file is opend corrwctly. otherwise, exit from the programme
    }
    cout << "File Opened sucess!\n\n";  //indicate that the file is opened

    vector<string> romanNumbers;
    string dat, num;
    stringstream str;
    while(!inFile.eof())
    {
        inFile >> dat;
        romanNumbers.push_back(dat);    //push roman numbers into the vector
    }

    for (int index = 0; index < romanNumbers.size(); index++)
    {
        if(isValid(romanNumbers[index]))    //check the validity of each roman number
            convertToDecimal(romanNumbers[index]);    //call the convertor
        else
            cout << romanNumbers[index] << " \t= error\n";
    }
    return 0; //end of the programme :-)
}