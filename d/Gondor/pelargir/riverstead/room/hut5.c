/*
 *  NCAMP_ROOM + "hut5.c"
 *
 *  A hut. Only newbies and wizards should ever see this place.
 *
 *  Last modified by Alto, 16 November 2002
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

object hole;

public void
create_gondor()
{    
    set_short("a small hut in the northern parts of the settlement");
    set_long(&long_desc());

    hut_add_items();

    add_item(({"room", "area", "surroundings", "place",
        "cottage", "house", "hut", "cabin", "building"}), long_desc);

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(NCAMP_ROOM + "camp5.c", "out");

    setuid();
    seteuid(getuid());

    hole = clone_object(NCAMP_OBJ + "hole5.c");
    hole->move(TO);

    reset_room();
}

void
reset_room()
{
    hole->remove_object();

    hole = clone_object(NCAMP_OBJ + "hole5.c");
    hole->move(TO);
}    


string
long_desc()
{
    return "This hut looks to be recently abandoned. All the "
        + "furniture has been removed. In one corner, it appears "
        + "that a large object had covered a hole in the floor.\n";
}
