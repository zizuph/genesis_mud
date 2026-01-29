/*
 *  NCAMP_ROOM + "ipath4.c"
 *
 *  A woodland path. Only newbies and wizards should ever see this place.
 *
 *  Last modified by Alto, 10 October 2002
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include <math.h>
#include "/d/Gondor/defs.h"
#include "../ncamp_defs.h"

inherit NCAMP_LIB + "ncamp_funcs.c";

public void        	create_gondor();
public string      	long_desc();

public void
create_gondor()
{
    set_short("a woodland path near the river Anduin");
    set_long(&long_desc());

    sky_add_items();
    woods_add_items();
    add_woods_tells();

    add_item(({"room", "area", "surroundings", "place", "bend",
        "landscape", "woodland", "woods"}), long_desc);
        
    add_item(({"river", "anduin", "river anduin"}), "Through the trees to "
        + "the east you can make out the great river Anduin, mightiest river "
        + "in Gondor. The trees block your passage that way, however.\n");
    add_item(({"bank", "banks"}), "The western bank of the great Anduin lies "
        + "on the other side of the trees to the east of the path.\n");
                
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(NCAMP_ROOM + "ipath5.c", "north");
    add_exit(NCAMP_ROOM + "ipath6.c", "south");
    add_exit(NCAMP_ROOM + "ipath3.c", "northwest");

    reset_room();
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
    {
        sky_add_items();
        start_room_tells();
    }
}

string
long_desc()
{
    return "The path here is a meeting of three ways. To the north and south, "
        + "the path runs just inside the trees along the west bank of the great "
        + "river Anduin. Another part of the path turns to the northwest and "
        + "plunges deeper into the forest."
        + sky_desc() 
        + " \n";
}
