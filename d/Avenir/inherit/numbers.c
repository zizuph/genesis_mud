#include "/d/Avenir/common/common.h"

string *ones = ({ "", ".", "..", ":.", "::" });
string *fives = ({ "-" });
string *tens = ({ "=" });
string *fiftys = ({ "|" });

string
number_to_string(int num)
{
    int div, left, i;
    string str = "";

    left = num;

    div = left/50;

    if(div)
    {
        left = num%50;

        for(i=0;i<div;i++)
            str += fiftys[0];
    }

    div = left/10;

    if(div)
    {
        left = num%10;

        for(i=0;i<div;i++)
            str += tens[0];
    }

    div = left/5;

    if(div)
    {
        left = num%5;

        for(i=0;i<div;i++)
            str += fives[0];
    }

    str += ones[left];

    return str;
}


int
string_to_number(string str)
{


}

