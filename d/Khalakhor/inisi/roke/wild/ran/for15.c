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
    add_item(THIRDITEM, THIRDDESCR3);
    add_exit("for" + N15, "north");
    add_exit("for" + E15, "east");
    add_exit("for" + S15, "south");
    add_exit("for" + W15, "west");

    OUTSIDE;
}
