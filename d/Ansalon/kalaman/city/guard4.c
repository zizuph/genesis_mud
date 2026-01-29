#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit KALAMAN_IN;

void
reset_kalaman_room()
{
    return;
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("Guard room for the western gates of Kalaman");

    add_item(({"guard room","barracks"}),"@@long_descr");
    add_item(({"stone stairway","stairway"}),
      "A stone stairway leads up to the wall's battlements.\n");
    add_item(({"gate","western gate"}),
      "Out the exit you can see the western gates.\n");

    add_exit(WALL + "g4","up",0);
    add_exit(CITY + "gate1","northeast",0);

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand within one of the guard rooms that act " +
    "as barracks for those soldiers charged to guard the " +
    "western gate of Kalaman. Here a stone stairway rises up to " +
    "the wall's battlements, and " +
    "an open exit leads out to the city gates.\n";
}
