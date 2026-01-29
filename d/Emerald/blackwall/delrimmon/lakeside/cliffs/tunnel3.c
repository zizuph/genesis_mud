/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/cliffs/tunnel3.c
 *
 *  A tunnel connects the ledge which runs along the western
 *  cliff faces to the single path which leads into the
 *  valley. The tunnel rounds a bend here.
 *
 *  Copyright (c) January 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/lakeside/cliffs/tunnel1";
inherit "/d/Emerald/blackwall/delrimmon/del_rimmon";

#include <macros.h>      /* for VBFC, etc */
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void        create_del_rimmon();


/*
 * Function name:        create_del_rimmon
 * Descriptionn :        set up the room with area presets
 */
public void
create_del_rimmon()
{
    set_short("in a dark tunnel. The tunnel rounds a bend here");
    set_long(del_rimmon_long);

    set_extraline("This appears to be the southern portion of a turn"
                + " in the tunnel, which travels to the northwest and"
                + " east here. The rock walls crowd in all around you"
                + " here.");

    add_item( ({ "turn", "bend" }),
        "The tunnel rounds a bend here, making its way to the east"
      + " and northwest.\n");
    add_item( ({ "east" }),
        "The tunnel extends to the east, running as far as the eye can"
      + " see in the dim light.\n");
    add_item( ({ "light", "dim light" }),
        "Though there is light within this tunnel, it is very dim, and"
      + " does not allow one to see far.\n");
    add_item( ({ "northwest" }),
        "To the northwest, the tunnel rounds a bend, making its way"
      + " northward.\n");

    tunnel_items();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(DELRIMMON_DIR + "lakeside/cliffs/tunnel4", "northwest");
    add_exit(DELRIMMON_DIR + "lakeside/cliffs/tunnel2", "east");

    set_no_exit_msg( ({ "north", "northeast", "southeast", "south",
                        "southwest", "west" }),
        "The rock walls of the tunnel prevent any movement in that"
      + " direction.\n");
} /* create_del_rimmon */
