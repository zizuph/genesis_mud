/*
 *  /d/Emerald/blackwall/delrimmon/trail/forest_path.c
 *
 *  This path leads from the northern shores of Lake Telberin
 *  toward the base of the Blackwall Mountains, where switchbacks
 *  lead up to Del Rimmon and the Valley high above.
 *
 *  Copyright (c) March 2002, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";

#include "/d/Emerald/blackwall/delrimmon/defs.h"


/* prototypes */
public void        create_del_rimmon();
public int         do_climb(string arg);
public void        init();


/*
 * Function name:        create_del_rimmon
 * Description  :        set up the room
 */
public void
create_del_rimmon()
{
    set_short("an overgrown path through the woods");
    set_long("A thick carpet of pine needles covers what looks to"
           + " have once been a very well used path through the"
           + " woods here. A ways to the north, the trees fall"
           + " away before tall cliffs which rise in that direction."
           + " To the south, the glimmer of light on water can"
           + " be seen between the tall trunks.\n");

    add_item( ({ "carpet", "thick carpet", "pine needles",
                 "pine needle", "needles", "needle",
                 "carpet of pine needles",
                 "thick carpet of pine needles",
                 "floor", "forest floor", "down", "ground" }),
        "Pine needles cover the forest floor here. They mound"
      + " up here and there in shades of green and brown, soon"
      + " to be integrated into the soil that feeds the tree"
      + " roots.\n");
    add_item( ({ "path", "trail" }),
        "A depression with slight banks on either sides runs north"
      + " to south through the forest here, evidence to the fact"
      + " that at one time this was once a well-used path.\n");
    add_item( ({ "depression" }),
        "The depression leads towards the cliffs to the north, and"
      + " to the lake heading south. Slight banks couch it in on"
      + " either side.\n");
    add_item( ({ "bank", "banks", "slight bank", "slight banks" }),
        "The banks on either side of the depression suggest that"
      + " this path was once very well defined and probably used"
      + " quite often.\n");
    add_item( ({ "forest", "woods", "wood", "tree", "trees",
                 "pine", "pines", "pine tree", "pine trees",
                 "trunk", "trunks", "tree trunk",
                 "tree trunks" }),
        "Tall pine trees rise on all sides of the path, growing"
      + " dense and impenetrable to the east and west. To the north"
      + " and south they open up somewhat where the forest gives"
      + " way.\n");
    add_item( ({ "cliff", "tall cliff", "cliffs", "tall cliffs",
                 "mountain", "mountains", "blackwall mountains",
                 "feet", "feet of the mountains",
                 "feet of the blackwall mountains",
                 "north" }),
        "The cliffs which peer through the trees to the north are"
      + " none other than the feet of the Blackwall Mountains.\n");
    add_item( ({ "water", "glimmer", "light", "light on water",
                 "glimmer of light", "lake", "lake telberin",
                 "telberin lake" }),
        "To the south, light glimmers from the waters of Lake"
      + " Telberin which extends for many miles in that direction.\n");
    add_item( ({ "sky", "up" }),
        "Peering upwards, you are able to catch a glint of the sky"
      + " through the trees above.\n");
    add_item( ({ "trunk", "tree trunk", "trunks", "tree trunks",
                 "trunks of the trees", "trunk of the tree" }),
        "The trunks of the trees are buried beneath a thick layer"
      + " of needles which have fallen from above.\n");

    add_exit(DELRIMMON_DIR + "trail/switchback_base", "north");
    add_exit("/d/Emerald/north_shore/dock", "south", 0, 1, 1);

    set_no_exit_msg( ({ "northeast", "east", "southeast",
                        "southwest", "west", "northwest" }),
        "The trees crowd densely in that direction, barring your"
      + " movement.\n");
} /* create_del_rimmon */


/*
 * Function name:        do_climb
 * Description  :        allow players to try to climb to trees
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - sucess, 0 - failure
 */
public int
do_climb(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("Climb what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[up] [the] [tall] [pine] 'trunk' / 'tree'"
      + " / 'trees' / 'trunks'"))
    {
        return 0; /* odd syntax ... failed */
    }

    write("You grasp the trunk of a nearby tree and do your best to"
        + " climb it. However, there are no limbs which reach anywhere"
        + " near to the ground, making it impossible to make your"
        + " way up the tree. After a bit, you stop trying.\n");
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













