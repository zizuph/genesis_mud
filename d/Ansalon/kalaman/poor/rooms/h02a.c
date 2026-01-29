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
    set_short("Inside a house");
    set_long(long_descr);

    add_exit("s05", "west");
    reset_kalaman_room();
}

string
long_descr()
{
   return "You stand in one of the houses in the poor districts of Kalaman. " +
     "Nothing in this house could hint that you are in one of the riches " +
     "and busies ports of Ansalon. The furniture is sparse and what does " +
     "exist is of inferior quality and most of them are homemade. There is " +
     "a staircase that leads upstairs to the upper levels and a simple wooden " +
     "door that leads to the kitchen. Next to the kitchen door stands a wooden " +
     "cupboard. A giant homemade dirty rug covers the simple wooden plank that " +
     "make up the floor of this type of house. On the wall that faces the " +
     "street a large bookcare stands and beside it is a small window that gives " +
     "a clear view of the street.\n";
}
