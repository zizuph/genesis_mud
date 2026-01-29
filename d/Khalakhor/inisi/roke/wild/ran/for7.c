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
    add_item(THIRDITEM, THIRDDESCR1);
    add_exit("for" + N7, "north");
    add_exit("for" + E7, "east");
    add_exit("for" + S7, "south");
    add_exit("for" + W7, "west");

    OUTSIDE;
}
