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

    add_item(FIRSTITEM, FIRSTDESCR3);
    add_item(SECONDITEM, SECONDDESCR3);
    add_item(THIRDITEM, THIRDDESCR1);
    add_exit("for" + N25, "north");
    add_exit("for" + E25, "east");
    add_exit("for" + S25, "south");
    add_exit("for" + W25, "west");

    OUTSIDE;
}
