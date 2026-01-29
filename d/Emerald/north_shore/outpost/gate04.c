/*
 *  /d/Emerald/north_shore/outpost/gate04.c
 *
 *  This area was originally created by Mhyrkhaan in November of
 *  1998 and then put on hold. That wizard has since left the
 *  Emerald domain, and so I have decided to put his work to some
 *  use as a small killing area to give some small satisfaction
 *  to players who value that sort of thing. The descriptions
 *  and items have been updated by Gorboth.
 *
 *  Update August 2003 (Gorboth)
 */
#pragma strict_types

#include "/d/Emerald/common/guild/aod/defs.h"
#include "defs.h"
inherit OUTPOST_OUTSIDE_ROOM;


/* prototypes */
public void        create_outpost_outside_room();
public int         enter_outpost(string arg);
public void        init();       


/*
 * Function name:    create_outpost_outside_room
 * Description  :    set up the room with annoying noises
 */
public void
create_outpost_outside_room()
{
    set_short("outside the northern gates of the outpost");
    set_em_long("Here, before the northern gates of the"
      + " outpost, the forest has been clear cut for perhaps"
      + " two dozen meters to the north. Beyond that point,"
      + " the forest dominates the view. The"
      + " tall dark peaks of the Blackwall Mountains rise"
      + " just above the tops of the closest trees, frowning"
      + " down over the entire region.\n");

    add_item( ({ "mountain", "mountains", "blackwall mountains" }),
        "The Blackwall Mountains rise beyond the forest,"
      + " dominating the landscape for miles to the north.\n");
    add_item( ({ "forest", "tree", "trees", "woods" }),
        "The woods spread out in all northern directions,"
      + " forming a perimeter beyond the walls of the outpost.\n");
    add_item( ({ "lake", "lake telberin", "water", "waters",
                 "waters of the lake" }),
        "The waters of the lake are not visible from here.\n");
    add_item( ({ "clear cut", "clear-cut" }),
        "A clear-cut has been made in the forest here. It is"
      + " likely that these trees were removed as much for"
      + " timber to build the outpost as they were to provide"
      + " space to build upon.\n");

    add_npc(OUTPOST1_NPC + "woodcutter", 1);
    add_outpost_items();

    add_exit("gate03", "south");
    add_exit("path1", "north");

    set_no_exit_msg( ({ "northwest", "north", "northeast" }),
        "You walk to the edge of the clear-cut. Finding no path"
      + " to follow into the woods, you return to where you were.\n");
    set_no_exit_msg( ({ "west", "southwest", "east", "southeast" }),
        "You walk along the outside of the wall for a bit and then"
      + " return to the gate.\n");
} /* create_outpost_outside_room */


/* 
 * Function name:        enter_outpost
 * Description  :        allow players to use the 'enter' command
 *                       to enter the outpsot
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - otherwise
 */
public int
enter_outpost(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("Enter what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [large] [elven] [elvish] 'outpost' / 'fortress'"
      + " / 'gate' / 'gates' [of] [the] [outpost]"))
    {
        return 0; /* can't parse the player syntax */
    }

    if (this_player()->query_wiz_level())
    {
        write("Normally, we would move the player 'south' here using"
          + " command(). Since you are a wizard, that will not work."
          + " Simply go 'south' yourself.\n");
        return 1;
    }

    this_player()->command("south");
    return 1;
} /* enter_outpost */


/* 
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(enter_outpost, "enter");
} /* init */
