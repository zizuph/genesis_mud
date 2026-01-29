/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/cliffs/tunnel4.c
 *
 *  A tunnel connects the ledge which runs along the western
 *  cliff faces to the single path which leads into the
 *  valley. Here, it leads to the ledge.
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
    set_short("within the entrance to a tunnel");
    set_long(del_rimmon_long);

    set_extraline("The ground below your feet is framed by the rock"
                + " walls of a tunnel which travels southeast into the"
                + " cliffs. Just to the north, the tunnel opens out"
                + " onto a ledge.");

    add_item( ({ "north", "ledge" }),
        "Just to the north, the tunnel falls away, running out on to"
      + " a ledge along the cliffs.\n");
    add_item( ({ "southeast", "bend", "turn" }),
        "To the southeast, the tunnel rounds a bend, travelling deeper"
      + " into the cliffs.\n");

    tunnel_items();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(DELRIMMON_DIR + "lakeside/cliffs/ledge1", "north");
    add_exit(DELRIMMON_DIR + "lakeside/cliffs/tunnel3", "southeast");

    set_no_exit_msg( ({ "northeast", "east", "south", "southwest",
                        "west", "northwest" }),
        "You bump up against the tunnel walls.\n");
} /* create_del_rimmon */
