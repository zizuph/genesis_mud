/*
 *  NCAMP_ROOM + "ipath6.c"
 *
 *  A woodland path. Only newbies and wizards should ever see this place.
 *
 *  Coded by Alto, 10 October 2002
 *
 * Modification Log:
 * Date     Name    Modification
 * 6-6-17   Alto    Added exit to slip through trees to camp24
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";     /* create_gondor */

/* Definitions used by this file */
#include <macros.h>
#include <stdproperties.h>
#include <math.h>
#include "/d/Gondor/defs.h"
#include "../ncamp_defs.h"

inherit NCAMP_LIB + "ncamp_funcs.c";

public void        	create_gondor();

/* Prototypes */
public string       long_desc();
public string       b_message();

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
        + "in Gondor.\n");
    add_item(({"bank", "banks"}), "The western bank of the great Anduin lies "
        + "on the other side of the trees to the east of the path.\n");
    add_item(({"tree", "trees"}), "The trees of the woodland "
        + "to the east grow very close together. You might be able "
        + "to slip through them, however.\n");
                
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(NCAMP_ROOM + "ipath4.c", "north");
    add_exit(NCAMP_ROOM + "camp24.c", "slip", b_message, 2, 1);


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
    
    write("You slip between the trees to the east.\n");
    tell_room(environment(actor), QCTNAME(actor) + " slips between "
        + "the trees and disappears from view.\n", 
        ({actor}));
}

string
long_desc()
{
    return "There seems to be no way to move further to the south. The path "
        + "leads only back to the north."
        + sky_desc() 
        + " \n";
}
