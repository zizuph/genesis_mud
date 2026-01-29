#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit KALAMAN_IN;

string long_descr();

void
reset_kalaman_room()
{
    return;
}

create_kalaman_room()
{
    set_short("District guard office");
    set_long(long_descr);

    add_exit("s01", "west");
    reset_kalaman_room();
}

string
long_descr()
{
   return "You stand inside the office of the city guard that is in charge " +
    "of the poor district. The room has two desks at the east and north wall " +
    "and also a weapons rack on the south wall but other then that there is " +
    "wery little in this room.\n";
}
