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

    add_item(FIRSTITEM, FIRSTDESCR2);
    add_item(SECONDITEM, SECONDDESCR2);
    add_item(THIRDITEM, THIRDDESCR2);
    add_exit("for" + N14, "north");
    add_exit("for" + E14, "east");
    add_exit("for" + S14, "south");
    add_exit("for" + W14, "west");

    OUTSIDE;
}
