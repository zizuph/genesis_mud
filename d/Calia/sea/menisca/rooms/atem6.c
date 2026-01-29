
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("Temple room");
    set_long("This is a small antechamber. There is a doorway " +
             "to the north that leads to the main foyer. A " +
             "passageway leads to the east, while a narrow " +
             "hallway leave out of the northeast corner of " +
             "this chamber.\n");

    add_swim_exit(MENISCA + "atem1","north",0,1);
    add_swim_exit(MENISCA + "atem5","east",0,1);
    add_swim_exit(MENISCA + "atem4","northeast",0,1);
}
