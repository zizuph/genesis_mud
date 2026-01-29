/*
 *  NCAMP_ROOM + "ipath3.c"
 *
 *  A woodland path. Only newbies and wizards should ever see this place.
 *
 *  Last modified by Alto, 28 September 2002
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
public string		b_message();

public void
create_gondor()
{
    set_short("a sloping woodland path");
    set_long(&long_desc());

    sky_add_items();
    woods_add_items();
    add_woods_tells();

    add_item(({"room", "area", "surroundings", "place", "bend",
        "landscape", "woodland", "woods"}), long_desc);
        
    add_item(({"slope", "natural slope"}), "The path beneath your feet runs uphill "
        + "to the west and downhill to the east. This is because you are in the "
        + "drainage basin of the mighty Anduin river. All lands in this part of the "
        + "world run downhill toward it.\n");
    add_item(({"tree", "oak tree", "large oak tree"}), "Rising from the middle of "
        + "the path stands a particularly old and especially tall oak tree. Its "
        + "trunk is extremely broad and its branches gnarled with age.\n");
    add_item(({"trunk"}), "The trunk of the oak tree is very broad. Five grown "
        + "men of Gondor would not be able to encircle it with arms outstretched.\n");
    add_item(({"branch", "branches"}), "Some of the branches on the oak tree seem "
        + "low enough to climb. Perhaps you could try going up?\n");
        
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(NCAMP_ROOM + "ipath2.c", "northwest");
    add_exit(NCAMP_ROOM + "ipath4.c", "southeast");
    add_exit(NCAMP_ROOM + "ipath_tree.c", "up", b_message, 2, 1);
    add_exit(NCAMP_ROOM + "ipath_tree.c", "climb", b_message, 2, 1);

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

public string
b_message()
{
    object actor;
    actor = this_player();
    
    write("You jump to the lowest branch and pull yourself up into the oak "
        + "tree.\n");
    tell_room(environment(actor), QCTNAME(actor) + " climbs up into the "
        + "oak tree.\n", 
        ({actor}));
}

string
long_desc()
{
    return "The path moves along a natural slope in the landscape. If you are "
        + "travelling to the west, it is an uphill climb. Eastward the way is easier "
        + "and the path meanders along a downhill grade."
        + sky_desc() 
        + " Growing in the middle of the path is an exceptionally large oak tree.\n";
}
