/*
 *  NCAMP_ROOM + "hut11.c"
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

object shelf;

public void
create_gondor()
{
    set_short("a small hut in the southern parts of the settlement");
    set_long(&long_desc());

    hut_add_items();

    add_item(({"room", "area", "surroundings", "place",
        "cottage", "house", "hut", "cabin", "building"}), long_desc);
        
    add_item(({"shed"}), "On closer inspection, you see that nobody "
        + "lives here. It is a shed.\n");
    add_item(({"box", "boxes", "crate", "crates"}), "The boxes and "
        + "crates are mostly smashed open and looted. It looks like "
        + "the orcs have already been here. If you look around, "
        + "however, it is possibly you will find something they "
        + "missed.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(NCAMP_ROOM + "camp11.c", "out");

    shelf = clone_object(NCAMP_OBJ + "shelf11.c");
    shelf->move(TO);

    reset_room();
}

void
reset_room()
{
    shelf->remove_object();

    shelf = clone_object(NCAMP_OBJ + "shelf11.c");
    shelf->move(TO);
}    

string
long_desc()
{
    return "This hut looks like something of a storage shed. Various "
        + "boxes and crates can be seen stacked in the corners. There "
        + "is an especially large shelf next to the doorway.\n";
}
