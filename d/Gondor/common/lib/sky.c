/* Standardfile to make the looks of the sky for Rohan*/
/* By Hamurabbi (e90jp1@garfield.hh.se) Feb 1992 */

#pragma save_binary

inherit "/d/Gondor/common/room";

#include "/d/Gondor/defs.h"

string long_descf,time,extraline;
object clock;

void
make_the_room()
{
    set_long("@@describe");
}

string
describe(string str)
{
    clock = find_object(CLOCK);
    time=clock->query_time_of_day();
    long_descf = CAP(short())+". ";
    switch (time)
    {
        case "night":
            long_descf += "The dark sky above you is full of stars.";
            break;
        case "early morning":
            long_descf +="The sun has barely made it over the eastern horizon.";
            break;
        case "morning":
            long_descf +="The sun has worked its way a bit up the sky.";
            break;
        case "noon":
            long_descf +="The sun shines down from right above your head.";
            break;
        case "afternoon":
            long_descf +="The sun is moving towards the west.";
            break;
        case "evening":
            long_descf +="The sun is setting in the west.";
            break;
        default:
            break;
    }
    long_descf += " It is "+time+" in Rohan.";
    if (extraline)
       long_descf += (" " + extraline);

    return BSN(long_descf);
}

void
reset_room()
{
    set_searched(0);
}
