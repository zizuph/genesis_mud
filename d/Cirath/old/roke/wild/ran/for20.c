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
    add_item(THIRDITEM, THIRDDESCR2);
    add_exit("for" + N20, "north");
    add_exit("for" + E20, "east");
    add_exit("for" + S20, "south");
    add_exit("for" + W20, "west");

    OUTSIDE;
}
