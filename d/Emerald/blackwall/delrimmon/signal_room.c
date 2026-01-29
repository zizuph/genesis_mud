/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/cliffs/signal_room.c
 *
 *  This is the high ledge upon which Formandil set the signal
 *  for the outposts of Del Rimmon. From this point, the troops
 *  within the valley could be alerted to any danger or invasion
 *  based on the sequence of notes blown on the horn.
 *
 *  Copyright (c) January 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";
inherit "/d/Emerald/blackwall/delrimmon/del_rimmon";
inherit "/d/Emerald/blackwall/delrimmon/legacy/tell_funcs";

#include <macros.h>      /* for VBFC, etc */
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void        create_del_rimmon();
public void        light_beacon();


/*
 * Function name:        create_del_rimmon
 * Descriptionn :        set up the room with area presets
 */
public void
create_del_rimmon()
{
    add_name("del_rimmon_cliffs");
    set_short("atop a high cliff ledge");
    set_long(del_rimmon_long);
    set_extraline("Placeholder desc for the signal room.");

    add_prop("_signal_room", 1);
    add_prop(ROOM_S_EXIT_FROM_DESC,
        "from above, climbing down the ladder.");
    add_exit(DELRIMMON_DIR + "lakeside/cliffs/outpost1b", "down");

    add_lakeview();
    add_view();

    reset_room();
} /* create_del_rimmon */


/*
 * Function name:        light_beacon
 * Description  :        we light up the beacon on Melan Earl, and
 *                       tell everyone in the area about the event
 */
public void
light_beacon()
{
    tell_players_in_dir(DELRIMMON_DIR, "Melan Earl lights up!\n");
    return;
} /* light_beacon */


/*
 * Function name:        reset_room
 * Description  :        clone the corpse of signal into the room
 */
public void
reset_room()
{
    object signal;

    if (!present("del_rimmon_signal"))
    {
        signal =
            clone_object(DELRIMMON_DIR + "obj/signal")->move(this_object());
    }

} /* reset_room */
