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
    add_item(SECONDITEM, SECONDDESCR3);
    add_item(THIRDITEM, THIRDDESCR3);
    add_exit("for" + N9, "north");
    add_exit("for" + E9, "east");
    add_exit("for" + S9, "south");
    add_exit("for" + W9, "west");

    OUTSIDE;
}
