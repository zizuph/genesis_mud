/* Navarre July 3rd, fixed typo in NOON description */

/* The base for looking out on the street from inside. */

#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include DL_CLOCK

string
street_descr()
{
    string str;
    switch (GET_TIME_STRING)
    {
        case MIDNIGHT:
        str = "The streets are fairly empty in the middle of the night.";
        break;
        case NIGHT:
        str = "The kender on the streets seem to be heading home, or " + 
            "are heading out for adventures.";
        break;
        case EVENING:
        str = "Kender still crowd the streets as the sun's rays fade " + 
            "from view.";
        break;
        case EARLY_MORNING:
        str = "A few early risers dot the streets.";
        break;
        case MORNING:
        str = "Kender fill the streets as the day begins."; 
        break;
        case NOON:
        str = "Kender crowd the streets as the day reaches its peak."; 
        break;
        case AFTERNOON:
        str = "Kender crowd the streets as afternoon sets in.";
        break;
    }
    return str;
}

