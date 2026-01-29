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
    set_short("Inside a warehouse");
    set_long(long_descr);

    add_exit("s03", "north");
    reset_kalaman_room();
}

string
long_descr()
{
   return "You stand inside a warehouse in the poor districts of the city, " +
    "this warehouse seems to hold a various type of wares for the merchants " +
    "of the city. You see everything from grain to clothes on the many " +
    "shelves that cover the walls of the warehouse.\n"; 
}
