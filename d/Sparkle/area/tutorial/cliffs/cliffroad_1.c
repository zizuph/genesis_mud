/*
 *  /d/Sparkle/area/tutorial/cliffs/cliffroad_1.c
 *
 *  A road in the cliffs leading toward Krolock's castle.
 *
 *  Created November 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

#include <macros.h>    /* for QCTNAME */
#include <ss_types.h>  /* for SS_CLIMB */

/* prototypes */
public void        create_silverdell();
public int         check_exit();
public void        init();
public int         do_climb(string arg);


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("on a path leading up into the cliffs");
    set_long("The road has become little more than a narrow path"
      + " leading up into the cliffs here. To the east, rope dangles"
      + " down beside a sheer ledge which obscures the view in that"
      + " direction.\n");

    add_outdoor_items();
    add_cliffs_items();

    add_item( ({ "here", "area" }), long);
    add_item( ({ "mudslide", "ledge", "slide", "east", "sheer ledge" }),
        "To the east a ledge perhaps 15 feet tall rises where a mudslide"
      + " washed away the formerly gradual slope of the path. A rope"
      + " dangles down from above, hanging perhaps four feet above the"
      + " ground.\n");
    add_item( ({ "rope" }),
        "The rope is just where you left it. You can <climb> up it to"
      + " travel to the east.\n");

    add_exit(FARM_DIR + "crossroad_4", "east", check_exit, 1, 0);
    add_exit("cliffroad_2", "northwest");

    add_npc(NPC_DIR + "lion", 1, &->arm_me());
    
    //This room is instanced.
    instance_entrance = 0;
} /* create_silverdell */


/*
 * Function name:        check_exit
 * Description  :        see if the player is allowed to travel this
 *                       direction
 * Returns      :        1 - don't allow, 0 - allow
 */
public int
check_exit()
{
    write("The ledge to the east blocks the road. You can probably"
      + " <climb> back up the rope, however.\n");
    return 1;
} /* check_exit */


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


/*
 * Function name:        do_climb
 * Description  :        allow the player to try to climb over the rocks
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_climb(string arg)
{
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " where?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[up] [the] 'rope' / 'mudslide' / 'east'"))
    {
        if (arg != "up")
        {
            return 0; /* bad or unexpected syntax */
        }
    }

    write("You climb up the rope and work your way to the top of"
      + " the ledge.\n");

    write("Reality trembles slightly.\n");

    this_player()->move_living("M", FARM_DIR + "crossroad_4", 1, 0);
    tell_room(this_object(), QCTNAME(this_player())
      + " clambers up the rope and disappears.\n");
    tell_room(environment(this_player()), QCTNAME(this_player())
      + " climbs over the edge, arriving from below.\n", this_player());

    this_player()->add_fatigue(-10);

    return 1;
} /* do_climb */

