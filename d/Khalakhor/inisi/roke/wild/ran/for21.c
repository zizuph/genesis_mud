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
    add_item(SECONDITEM, SECONDDESCR1);
    add_item(THIRDITEM, THIRDDESCR3);
    add_exit("for" + N21, "north");
    add_exit("for" + E21, "east");
    add_exit("for" + S21, "south");
    add_exit("for" + W21, "west");

    OUTSIDE;
}
