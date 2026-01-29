/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/cliffs/tunnel2.c
 *
 *  A tunnel connects the ledge which runs along the western
 *  cliff faces to the single path which leads into the
 *  valley. The tunnel runs straight for a bit here.
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
    set_short("in a tunnel which travels to the east and west");
    set_long(del_rimmon_long);

    set_extraline("The tunnel travels both to the east and west here,"
                + " extending in both directions for a good distance."
                + " To the east, it appears as if the tunnel comes to"
                + " an end.");

    add_item( ({ "west" }),
        "To the west, the tunnel travels straight as far as your eyes can"
      + " see.\n");
    add_item( ({ "east", "end" }),
        "Though you cannot see much detail from here, you get the sense"
      + " that the tunnel comes to an end as one travels east.\n");

    tunnel_items();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(DELRIMMON_DIR + "lakeside/cliffs/tunnel3", "west");
    add_exit(DELRIMMON_DIR + "lakeside/cliffs/tunnel1", "east");

    set_no_exit_msg( ({ "northwest", "north", "northeast",
                        "southwest", "south", "southeast" }),
        "You are halted by the tunnel walls in that direction.\n");
} /* create_del_rimmon */
