/*
 *  NCAMP_ROOM + "camp24.c"
 *
 *  A dirt path. Only newbies and wizards should ever see this place.
 *
 *  Last modified by Alto, 17 November 2002
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
public string	   b_message();

public void
create_gondor()
{
    set_short("in the southwestern part of a settlement");
    set_long(&long_desc());

    sky_add_items();
    camp_add_items();
    add_camp_tells();

    add_item(({"room", "area", "surroundings", "place",
        "landscape", "settlement", "village", "camp"}), long_desc);
        
    add_item(({"tree", "trees"}), "The trees of the woodland "
        + "to the west grow very close together. You might be able "
        + "to slip through them, however.\n");
    add_item(({"woods", "woodland", "stand"}), "A dense stand "
        + "of trees grows to the west of the settlement.\n");
        
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(NCAMP_ROOM + "camp23.c", "northeast");
    add_exit(NCAMP_ROOM + "ipath6.c", "slip", b_message, 2, 1);
    
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
    return "The path from the settlement ends here at the woodland "
        + "stand."
        + sky_desc() 
        + " Although the trees grow very close together, you spy a spot "
        + "through which you might slip.\n";
}

public string
b_message()
{
    object actor;
    actor = this_player();
    
    write("You slip between the trees and enter the woods.\n");
    tell_room(environment(actor), QCTNAME(actor) + " slips between "
        + "the trees and disappears into the woods.\n", 
        ({actor}));
}

