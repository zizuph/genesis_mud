/*
 *  NCAMP_ROOM + "camp8.c"
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

object puddle;

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
        + "to the west grow very close together.\n");
    add_item(({"woods", "woodland", "stand"}), "A dense stand "
        + "of trees grows to the west of the settlement.\n");
    add_item(({"hut", "small hut"}), "There is a large hut here. "
        + "It is reasonbly well-kept, and probably serves as the "
        + "dwelling for a small family of farmers.\n");

    add_prop(ROOM_I_INSIDE, 0);
    
    add_exit(NCAMP_ROOM + "camp3.c", "north");
    add_exit(NCAMP_ROOM + "camp7.c", "northeast");
    add_exit(NCAMP_ROOM + "camp9.c", "east");
    add_exit(NCAMP_ROOM + "camp10.c", "southeast");
    add_exit(NCAMP_ROOM + "camp23.c", "southwest");
    add_exit(NCAMP_ROOM + "hut8.c", "enter", 0, 0, 1);

    puddle = clone_object(NCAMP_OBJ + "puddle8.c");
    puddle->move(TO);

    reset_room();
}

void
reset_room()
{
    puddle->remove_object();

    puddle = clone_object(NCAMP_OBJ + "puddle8.c");
    puddle->move(TO);
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
    return "The muck is especially wet and clinging in "
        + "this part of the settlement. Most of the huts lie to the "
        + "east and northeast, but there is one small hut nearby "
        + "that could be entered. To the west, you spot a large "
        + "stand of trees."
        + sky_desc() 
        + " There is a very wide puddle in the middle of "
        + "the muddy path.\n";
}
