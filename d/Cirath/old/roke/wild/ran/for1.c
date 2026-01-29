/* A maze-forest north of Cadu  */

#pragma save_binary
#pragma strict_types

#include "randefs.h"

inherit WILDDIR + "ran/forroom";

void
create_forroom()
{
    set_short(SHORTDESCR);
    set_long(LONGDESCR);

    add_item(FIRSTITEM, FIRSTDESCR1);
    add_item(SECONDITEM, SECONDDESCR1);
    add_item(THIRDITEM, THIRDDESCR1);
    add_exit("for" + N1, "north");
    add_exit("for" + E1, "east");
    add_exit(SOUTHROOM, "south");
    add_exit("for" + W1, "west");

    OUTSIDE;
}

