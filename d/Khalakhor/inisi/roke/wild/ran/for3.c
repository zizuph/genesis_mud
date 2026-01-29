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
    add_item(THIRDITEM, THIRDDESCR3);
    add_exit("for" + N3, "north");
    add_exit(EASTROOM, "east");
    add_exit("for" + S3, "south");
    add_exit("for" + W3, "west");

    OUTSIDE;
}
