/*
 * /d/Emerald/blackwall/delrimmon/lakeside/w_stairway.c
 *
 * On either side of the pass which crosses over the hills and allows
 * entrance to the lake of Del Rimmon, one of these stairwells allows
 * access to a ledge whose purpose it was to control pasage to and
 * from the area.
 *
 * Copyright (c) February 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";
inherit "/d/Emerald/blackwall/delrimmon/del_rimmon";

#include <macros.h>      /* for QCTNAME, etc */
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* global variables */

/* prototypes */
public void        create_del_rimmon();
public int         do_climb(string arg);
public void        init();


/*
 * Function name:       create_del_rimmon
 * Description :        set up the room with area presets
 */
public void
create_del_rimmon()
{
    set_short("on a stairway leading to a landing high above");
    set_long(del_rimmon_long);

    Extraline = "A stairway leads up to a landing in the rock wall"
              + " high above, running north along the sheer wall"
              + " of rock. Just to the east, a pathway runs through"
              + " a narrow corridor, leading north and south.";

    add_item( ({ "mountains", "blackwall mountains" }),
        "Though the walls of rock block any view you might hope to"
      + " have of them, you are well aware that the Blackwall Mountains"
      + " spread out to the north, running for many miles in"
      + " all directions.\n");
    add_item( ({ "stair", "stairs", "stairway", "step", "steps",
                 "stone step", "stone steps" }),
        "Stone steps rise to the north, running along the walls of"
      + " rock as they lead up towards a landing high above.\n");
    add_item( ({ "landing", "overlook", "outlook", "above" }),
        "High above, a landing of some kind overlooks the pathway."
      + " A stone wall runs its length, perhaps serving as an arrow"
      + " blind should the pass need to be defended.\n");
    add_item( ({ "wall", "wall of stone", "stone wall", "arrow blind" }),
        "A stone wall runs the length of the landing above. At even"
      + " intervals along its length, narrow slots are cut in the"
      + " stone, and at the northern end an opening is visible where"
      + " the stairs provide access to the overlook.\n");
    add_item( ({ "opening", "opening in the wall" }),
        "The opening in the wall connects with the top of the"
      + " stairway, which runs from here up to the landing.\n");
    add_item( ({ "top of the stair", "top of the stairs",
                 "top of the stairway" }),
        "At the top of the stairway, an opening in the wall allows"
      + " for access to the landing.\n");
    add_item( ({ "slot", "slots", "arrow slot", "arrow slots",
                 "narrow slot", "narrow slots" }),
        "These are almost certainly arrow slots. Their narrow lengths"
      + " run horizontal, allowing for aiming up and down.\n");
    add_item( ({ "rock", "rock wall", "wall of rock", "rock walls",
                 "walls", "walls of rock", "sheer rock wall",
                 "sheer rock walls" }),
        "A great rock wall rises up to the west, towering over"
      + " this stairway and the pathway to the east. Along its"
      + " side, high above, a landing of some kind is visible,"
      + " overlooking the pass.\n");
    add_item( ({ "pass", "mountain pass" }),
        "The pathway to the east is the only way in or out of the"
      + " area to the north.\n");
    add_item( ({ "path", "pathway", "east", "corridor",
                 "narrow corridor" }),
        "The pathway runs north and south, descending in either"
      + " direction.\n");
    add_item( ({ "melan rath" }),
        "Though Melan Rath rises directly to the east, the perspective"
      + " is too drastic here to get any real view of it.\n");

    add_exit(DELRIMMON_DIR + "lakeside/pathway2", "east");
    add_exit(DELRIMMON_DIR + "lakeside/west_overlook", "up", 0, 1, 1);

    set_no_exit_msg( ({ "northwest", "west", "southwest" }),
        "Sheer walls of rock rise to block movement in that direction.\n");
    set_no_exit_msg( ({ "south", "southeast" }),
        "A wall of rock rises to the south, blocking your movement.\n");
    set_no_exit_msg( ({ "northeast" }),
        "You pause at the edge of the stairs, and decide not to take"
      + " what would be a very nasty fall.\n");
    set_no_exit_msg( ({ "north" }),
        "The way to the north is blocked by a stairway which rises"
      + " to a landing high above.\n");


    add_view();
} /* create_del_rimmon */


/*
 * Function name:        do_climb
 * Description  :        let the players climb the stairs
 * Arguments    :        string arg - what the player typed
 * Returns      :        int
 */
public int
do_climb(string arg)
{
    if (!strlen(arg))
    {
        NFN0("Climb what?");
    }

    if (!parse_command(arg, ({}),
        "[up] [the] [stone] 'stair' / 'stairs' / 'stairway' / 'steps'"))
    {
        return 0; /* unacceptable syntax */
    }

    write("You climb up the stone steps, and make your way to the"
        + " landing above.\n");

    if (this_player()->query_wiz_level())
    {
        write("Normally, we move the player 'up' here using 'command'."
          + " Since you are a wizard, that won't work, so you'll need"
          + " to move 'up' manually.\n");

        return 1;
    }

    this_player()->command("$up");
    return 1;
} /* do_climb */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_climb, "climb");
} /* init */
