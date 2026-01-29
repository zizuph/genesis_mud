/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/pathway2.c
 *
 *  The path which leads into the valley of Del Rimmon passes
 *  between two ledges here, which were originally manned
 *  at all times with a post of guards. Now, things are
 *  very overgrown, and the western overlook is hardly
 *  recognizable as anything other than a mass of vines.
 *
 *  Copyright (c) February 2001, by Cooper Sherry (Gorboth)
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
    set_short("on a pathway leading between two cliff ledges");
    set_long(del_rimmon_long);
    Extraline =
             "The pathway travels along a narrow corridor here, set"
           + " between two sheer walls of rock which rise high"
           + " above both to the east and west. To the north and south,"
           + " the rock walls fall away to reveal open air, and a"
           + " swift descent. It appears as if this place marks the"
           + " pass over these hills.";

    add_item( ({ "base", "base of the stair", "base of the stairs",
                 "base of the stairway", "base of the stairways" }),
        "Just to the east and west of the path, the base of a stairway"
      + " is visible, cut slightly into the rock wall.\n");
    add_item( ({ "path", "pathway", "corridor",
                 "narrow corridor" }),
        "The pathway travels to the north and south, apparently"
      + " rising over a pass of sorts here. It is hemmed in on"
      + " both sides by sheer walls of rock. This would most"
      + " certainly be a perfect location for an ambush.\n");
    add_item( ({ "pass" }),
        "The pathway descends to both the north and south, and"
      + " it would seem that this is indeed a pass over the"
      + " hills where the pathway crests to its highest point.\n");
    add_item( ({ "open air", "air", "descent", "swift descent" }),
        "To the north and south, it appears as if the pathway"
      + " makes its way down from this pass.\n");
    add_item( ({ "rock", "wall", "walls", "wall of rock", 
                 "walls of rock", "sheer wall", "sheer walls",
                 "sheer wall of rock", "sheer walls of rock" }),
        "To both the east and west, sheer rock walls rise"
      + " forbodingly to fence the pathway in. You notice that"
      + " on both sides, a stairway leads up to what appears to"
      + " be a landing of some kind, overlooking the narrow"
      + " corridor from above.\n");
    add_item( ({ "east", "west" }),
        "You notice a stairway leading up to what appears to"
      + " be a landing of some kind in that direction.\n");
    add_item( ({ "landing", "landings", "overlook", "overlooks",
                 "outlook", "outlooks" }),
        "Above to the east and west, you notice what appears"
      + " to be some kind of overlook at the top of a row of"
      + " stairs. A wall with what appear to be arrow slots"
      + " crown the landing on each side.\n");
    add_item( ({ "stair", "stairs", "stairway", "stairways",
                 "east stairway", "eastern stairway",
                 "east stair", "eastern stair",
                 "east stairs", "eastern stairs",
                 "west stairway", "western stairway",
                 "west stair", "western stair",
                 "west stairway", "western stairway",
               }),
        "The stairways to the east and west both begin level with"
      + " the path, and then run up northwards parallel to the sheer"
      + " rock walls before reaching an opening in the walls which"
      + " crown the landings above on each side.\n");
    add_item( ({ "landing wall", "landing walls", "wall on the landing",
                 "walls on the landing", "overlook wall", "overlook walls",
                 "wall above the stairs" }),
        "The walls which frame the overlooks to this corridor"
      + " appear to be the method by which this pass was once"
      + " guarded and controlled. Arrow slots are visible in" 
      + " their surfaces.\n");
    add_item( ({ "slot", "slots", "arrow slot", "arrow slots" }),
        "The arrow slots above would seem to have the perfect"
      + " positioning to control any access on this pathway.\n");
    add_item( ({ "opening", "opening in the wall" }),
        "At the top of each stairway, an opening in the wall"
      + " appears to allow access to the landings.\n");
    add_item( ({ "mountain", "mountains", "blackwall mountains" }),
        "Though the sheer walls of rock on both sides of the path"
      + " prevent any real view of the Blackwall Mountains, you remain"
      + " well aware that they are all around you. A dim glimpse of"
      + " them can be had to the north, where they appear far off,"
      + " rising through the tops of the trees.\n");
    add_item( ({ "hill", "hills" }),
        "You stand on a pass through the hills which border the"
      + " lake to the north. Just to the east, Melan Rath rises"
      + " high into the sky. You know this, though from this"
      + " point all you can see are its feet in the form of the"
      + " sheer rock wall to the east.\n");
    add_item( ({ "melan rath" }),
        "Melan Rath rises high above to the east, though you are"
      + " only able to glimpse its feet - the"
      + " sheer walls of rock which rise east of the pathway.\n");
    add_item( ({ "south" }),
        "To the south, the path drops away, and all that is visible"
      + " is the sky.\n");
    add_item( ({ "north" }), 
        "North of here, the tops of the trees are visible, where wooded"
      + " slopes descend from this pass down to the shores of a lake.\n");
    add_item( ({ "tree", "trees", "top of the trees", "tops of the trees",
                 "tree top", "tree tops" }),
        "To the north, trees are visible, rising up to block the view"
      + " in that direction.\n");
    add_item( ({ "lake", "del rimmon", "lake of del rimmon",
                 "shore", "shores", "lakeshore", "lakeshores",
                 "shore of the lake", "shores of the lake",
                 "shores of del rimmon" }),
        "Though it is not visible from here, the Lake of Del Rimmon"
      + " lies down the path to the north.\n");

    add_exit(DELRIMMON_DIR + "lakeside/w_stairway", "west",
             0, 1, 1); /* non-obvious */
    add_exit(DELRIMMON_DIR + "lakeside/e_stairway", "east",
             0, 1, 1); /* non-obvious */
    add_exit(DELRIMMON_DIR + "lakeside/pathway1", "south");
    add_exit(DELRIMMON_DIR + "lakeside/pathway3", "north");

    set_no_exit_msg( ({ "northwest", "northeast", "southwest",
                        "southeast" }),
        "The pathway is fenced in by sheer walls of rock in that"
      + " direction.\n");

    add_view();
} /* create_del_rimmon */


/*
 * Function name:        do_climb
 * Description  :        allow the player to try to climb the stairways
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
        "[up] [the] [west] [western] [east] [eastern]"
      + " 'stair' / 'stairs' / 'steps' / 'stairway'"))
    {
        if (!parse_command(arg, ({}),
            "[up] [the] 'rock' / 'rock wall' / 'rock walls'"
          + " 'walls of rock' / 'wall of rock' / 'cliff' / 'cliffs'"))
        {
            return 0; /* bad syntax */
        }

        write("The walls of rock are far too steep to climb here.\n");
        return 1;
    }

    write("The stairs are not accessable from the pathway. You would"
        + " need to walk to the base of the stairs first, which are"
        + " located just to the east and west of the path.\n");
    return 1;
} /* do_climb */


/*
 * Function name:        init
 * Description  :        add some actions to the players
 */
public void
init()
{
    ::init();

    add_action(do_climb, "climb");
} /* init */
