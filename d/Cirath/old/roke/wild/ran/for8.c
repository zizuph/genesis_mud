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
    add_item(THIRDITEM, THIRDDESCR2);
    add_exit("for" + N8, "north");
    add_exit("for" + E8, "east");
    add_exit("for" + S8, "south");
    add_exit("for" + W8, "west");

    OUTSIDE;
}
