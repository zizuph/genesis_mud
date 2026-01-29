/*
 *  /d/Sparkle/area/orc_temple/1_up.c
 *
 *  One of the rooms in the dungeons beneath the orc temple. This room is
 *  on level 1.
 *
 *  Created June 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include <time.h>
#include "../defs.h"

inherit ROOMS_DIR + "dungeon_room";


/* Prototypes */
public void         create_dungeon_room();
public void         init();
public int          climb_up_stair_hook();


/*
 * Function name:        create_dungeon_room
 * Description  :        constructor for the room
 */
public void
create_dungeon_room()
{
    set_short("at the foot of a stone stair");
    set_long("Uneven stone steps empty on to a rough and dirty floor"
      + " here. A dark corridor leads south, lit by many flickering"
      + " torches which are bracketed to the walls.\n\n");

    add_item( ({ "stair", "stairs", "step", "steps",
                 "uneven step", "uneven steps", "uneven stone step",
                 "uneven stone steps", "stairway", "stone stair",
                 "stone step", "stone stairs", "stone steps" }),
        "Climbing the stairway would take you back up to the"
      + " temple.\n");
    add_item( ({ "rough floor" }),
        "You've seen pinecones that are smoother than this floor.\n");
    add_item( ({ "dirty floor" }),
        "Clearly, the maid is out.\n");
    add_item( ({ "rough and dirty floor" }),
        "This place is enough to make you want to wipe your feet before"
      + " going OUTSIDE.\n");

    add_dungeon_items();

    add_exit("1_hall4", "south");
    add_exit("/d/Genesis/start/human/wild2/orcfort/stair", "up",
        climb_up_stair_hook, 1, 0);

    setuid();
    seteuid(getuid());
} /* create_dungeon_room */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(climb_stairs, "climb");
} /* init */


/*
 * Function name:        climb_up_stair_hook
 * Description  :        message to print to the player when they
 *                       climb up some stairs
 * Returns      :        string - the message
 *
 * Masked to allow for some logging.
 */
public int
climb_up_stair_hook()
{
#if LOG_MOVES
    write_file(LOG_DIR + "moves", 
        TIME2FORMAT(time(), "mm/dd/yyyy")
      + " (" + ctime(time())[11..18] + ") "
      + capitalize(this_player()->query_name())
      + " moved up and OUTSIDE.\n");
#endif

    return ::climb_up_stair_hook();
} /* climb_up_stair_hook */