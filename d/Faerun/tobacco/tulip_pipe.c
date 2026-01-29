/*
 * Faerun pipes
 * Based on the hobbit pipe from the Shire
 * -- Finwe, November 2015
 *
 * Updated by Shanoga, 2020-09-29:
 *  - base_pipe now saves leftover tobacco
 *  - added vbfc call so players can see leftover tobacco
 *
 */

//inherit "/d/Faerun/tobacco/base_pipe.c";
inherit "/w/shanoga/open/Faerun/tobacco/base_pipe.c";

#include "/d/Faerun/defs.h"

void
create_pipe()
{
    set_name("pipe");
    add_adj(({"short", "green"}));
    add_name("_smoking_pipe");
    add_name("tulip pipe");
    set_short("short black pipe");
    set_long("This is a tulip pipe. It is short and slightly bent towards " +
        "the top of the stem. The stem is thin and green, and flares " +
        "slightly at the base. The bowl and its neck are stained red. The " +
        "top of the bowl is carved and resembles an open tulip.\n" + 
        "@@Packed_desc@@Some instructions are etched on the bottom of " +
        "the pipe.\n");
}

string
Packed_desc()
{
    string temp_time;
    if (!Packed)
        return "";
    if (Smoking) {
        Packed_time = ftoi(get_alarm(Smoke_time)[2]) + random(5) - random(5);
    }

    switch (Packed_time) {
        case 0..100:
            temp_time = " a little ";
            break;
        case 101..200:
            temp_time = " some ";
            break;
        case 201..300:
            temp_time = " a lot of ";
            break;
        default:
            temp_time = " an abundance of ";
            break;
    }
    return "You still have" + temp_time + tob_type + " left.\n";
}
