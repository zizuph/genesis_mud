/*
 *  NCAMP_ROOM + "ipath1.c"
 *
 *  A woodland path. Only newbies and wizards should ever see this place.
 *
 *  Last modified by Alto, 27 September 2002
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

public void        create_gondor();
public string      long_desc();

public void
create_gondor()
{
    set_short("a path through a woodland in southern Gondor");
    set_long(&long_desc());

    sky_add_items();
    woods_add_items();
    add_woods_tells();

    add_item(({"room", "area", "surroundings", "place",
        "landscape", "narrow glade", "woodland", "woods"}), long_desc);
        
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(NCAMP_ROOM + "entrance.c", "west");
    add_exit(NCAMP_ROOM + "ipath2.c", "southeast");

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
    return "A pleasant woodland surrounds you. The path you are "
        + "following twists and turns through the sturdy oak trees "
        + "such that it is quickly lost from sight in both directions."
        + sky_desc() 
        + " Various roots and vines snake across the trail, eager "
        + "to snag an unsuspecting foot.\n";
}
