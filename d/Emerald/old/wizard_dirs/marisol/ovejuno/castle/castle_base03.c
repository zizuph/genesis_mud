/* Castle_base_room
 * To be used as a base for the castle third floor in Ovejuno, Emerald.
 * Contain general information
 * Coded by Marisol (12/01/98)
 * Copyright (c) Marisol Ramos 1998
 */

#pragma strict_types;

inherit "/d/Emerald/std/room";
#include "/d/Emerald/sys/macros.h"
#include "defs.h"
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>


void
create_castle_room()
{
}

nomask void
create_emerald_room()
{


    set_short("The Lord's residence third floor.");

    add_item(({"residence", "castle", "third floor"}),
        "The third floor of this residence seemed abandoned.  "+
        "The rooms and corridors here are dusty and spiderwebs "+
        "are everywhere. The room smells musty and dusty.\n");


    add_item(({"lamps", "lamp"}),
        "The lamp is hanging on the wall. The lamp is of elvish "+
        "making. Its globular head is all covered with dust and "+
        "grime. It really needs a good rub. There are several "+
        "other lamps along the walls.\n");

    add_item("walls",
        "The walls are all dirty. Ragged wallpaper hang "+
        "loosely along the walls.\n");

    add_item(({"ragged wallpaper", "wallpaper"}),
        "The wallpaper seem quite old. The design of the paper "+
        "have faded. The only predominantely colors are brown and "+
        "black from the dust and mold.\n");

    add_item("floor",
        "The floor is made of wooden boards. The floor is covered "+
        "with a thick layer of dust. It seems that the dust has "+
        "been undisturbed for many months or even years. "+
        "Not even the tracks of mice's feet can be found on the "+
        "floor.\n");

    reset_room();

create_castle_room();

}                                                                  
