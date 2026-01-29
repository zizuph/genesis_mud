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
    add_item(SECONDITEM, SECONDDESCR1);
    add_item(THIRDITEM, THIRDDESCR2);
    add_exit("for" + N11, "north");
    add_exit("for" + E11, "east");
    add_exit("for" + S11, "south");
    add_exit("for" + W11, "west");

    OUTSIDE;
}
