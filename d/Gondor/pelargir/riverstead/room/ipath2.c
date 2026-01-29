/*
 *  NCAMP_ROOM + "ipath2.c"
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
    set_short("a bend in the path");
    set_long(&long_desc());

    sky_add_items();
    woods_add_items();
    add_woods_tells();

    add_item(({"room", "area", "surroundings", "place", "bend",
        "landscape", "narrow glade", "woodland", "woods"}), long_desc);
    add_item(({"burrow", "small burrow"}), "Beneath the large rock "
        + "is a small burrow. It looks to have been made by some animal. "
        + "It seems big enough for you to enter.\n");
    add_item(({"rock", "large rock"}), "A great knife of rock has "
        + "thrust its way up through the woodland floor. It towers "
        + "above you, pointing into the sky of southern Gondor.\n");
    add_item(({"shadow", "shadow of the rock"}), "The rock leaves a "
        + "long shadow on the ground. There is a small burrow concealed "
        + "therein.\n");
        
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(NCAMP_ROOM + "ipath1.c", "northwest");
    add_exit(NCAMP_ROOM + "ipath3.c", "southeast");
    add_exit(NCAMP_ROOM + "ipath_burrow.c", "enter", b_message, 2, 1);

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
    
    write("You get down on all fours and scramble down into the "
        + "small burrow.\n");
    tell_room(environment(actor), QCTNAME(actor) + " gets down on "
        + "all fours and scrambles down into the small burrow.\n", 
        ({actor}));
}

string
long_desc()
{
    return "The path here forms a tight oxbow shape as it veers around "
        + "a large rock jutting from the ground."
        + sky_desc() 
        + " In the shadow of the rock you can make out a small burrow "
        + "nestled among the fallen leaves.\n";
}
