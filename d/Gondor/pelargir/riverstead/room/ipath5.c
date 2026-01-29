/*
 *  NCAMP_ROOM + "ipath5.c"
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
public string		b_message();

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
        + "in Gondor. The trees might be sparse enough to squeeze through.\n");
    add_item(({"bank", "banks"}), "The western bank of the great Anduin lies "
        + "on the other side of the trees to the east of the path.\n");
    add_item(({"tree", "trees"}), "Most of the trees here seem to be oak. "
        + "You notice a few places in between them where you might squeeze "
        + "through.\n");
                
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(NCAMP_ROOM + "ipath4.c", "south");
    add_exit(NCAMP_ROOM + "camp1.c", "squeeze", b_message, 2, 1);

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
    
    write("You find a place in the trees just wide enough to squeeze through.\n");
    tell_room(environment(actor), QCTNAME(actor) + " squeezes through the "
        + "trees lining the great Anduin.\n", 
        ({actor}));
}

string
long_desc()
{
    return "You have reached the end of the path. The only obvious way to leave "
        + "this place lies to the south."
        + sky_desc() 
        + " You notice that the trees along the bank of the Anduin seem to have "
        + "thinned out somewhat.\n";
}
