/*
 *  NCAMP_ROOM + "camp1.c"
 *
 *  A dirt path. Only newbies and wizards should ever see this place.
 *
 *  Coded by Alto, 17 November 2002
 *
 * Modification Log:
 * Date     Name    Modification
 * 6-3-17   Alto    Added exit to squeeze back to ipath5
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";  /* create_gondor */

/* Definitions used by this file */
#include <macros.h>
#include <stdproperties.h>
#include <math.h>
#include "/d/Gondor/defs.h"
#include "../ncamp_defs.h"

inherit NCAMP_LIB + "ncamp_funcs.c";

public void         create_gondor();

/* Prototypes */
public string       long_desc();
public string	    b_message();

public void
create_gondor()
{
    set_short("in the northwestern part of a settlement");
    set_long(&long_desc());

    sky_add_items();
    camp_add_items();
    add_camp_tells();

    add_item(({"room", "area", "surroundings", "place",
        "landscape", "settlement", "village", "camp"}), long_desc);
        
    add_item(({"tree", "trees"}), "Most of the trees here seem to be oak. "
        + "You notice a few places in between them where you might squeeze "
        + "through.\n");
    add_item(({"woods", "woodland", "stand"}), "A dense stand "
        + "of trees grows to the west of the settlement.\n");
        
    add_prop(ROOM_I_INSIDE, 0);
    
    add_exit(NCAMP_ROOM + "camp2.c", "southeast");
    add_exit(NCAMP_ROOM + "ipath5.c", "squeeze", b_message, 2, 1);

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
        + "dense stand of trees to the west.\n", 
        ({actor}));
}


string
long_desc()
{
    return "You are standing in the northwestern parts of what "
        + "appears to be a farming settlement. The ground is bare "
        + "and muddy between the numerous wooden huts."
        + sky_desc() 
        + " Trees grow in a dense stand to the west, but "
        + "within the village itself there is little growth of any "
        + "kind, probably because the settlers cleared away the "
        + "trees to make space and building materials. The settlement "
        + "proper lies to the southeast.\n";
}
