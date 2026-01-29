
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("Ruined house.");
    set_long("SUPRISE!! WATER KROUG AMBUSH!\n");

    add_swim_exit(MENISCA + "path6","north",0,1);
}
