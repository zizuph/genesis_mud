
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
             "passageway leads to the west, while a narrow " +
             "hallway leave out of the northwest corner of " +
             "this chamber.\n");

    add_swim_exit(MENISCA + "gtem1","north",0,1);
    add_swim_exit(MENISCA + "gtem5","west",0,1);
    add_swim_exit(MENISCA + "gtem4","northwest",0,1);
}
