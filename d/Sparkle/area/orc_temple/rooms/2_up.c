/*
 *  /d/Sparkle/area/orc_temple/2_up.c
 *
 *  One of the rooms in the dungeons beneath the orc temple. This room is
 *  on level 2.
 *
 *  Created June 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include <time.h>
#include "../defs.h"

inherit ROOMS_DIR + "dungeon_room";

#include <macros.h>

/* Prototypes */
public void         create_dungeon_room();
public void         init();
public object       safely_load_master_file(string filename);
public int          climb_up_stair_hook();


/*
 * Function name:        create_dungeon_room
 * Description  :        constructor for the room
 */
public void
create_dungeon_room()
{
    set_short("at the foot of a crumbled stair");
    set_long("Crumbled stairs extend upward from this dark and cramped"
      + " landing. North, a door of some kind is visible set in the"
      + " wall of an east-west corridor that is lit by many flickering"
      + " torches. The air is thick with a putrid smell.\n\n");

    add_item( ({ "stair", "stairs", "step", "steps",
                 "crumbled step", "crumbled steps", "crumbled stone step",
                 "crumbled stone steps", "stairway", "stone stair",
                 "stone step", "stone stairs", "stone steps" }),
        "Climbing the stairway would take you back up to the"
      + " first level of the dungeons.\n");
    add_item( ({ "first level", "first level of the dungeons" }),
        "Sort of like a first girlfriend, but a lot less kissable.\n");
    add_item( ({ "second level", "second level of the dungeons" }),
        "Your smack dab in the middle of it.\n");
    add_item( ({ "landing", "dark landing", "cramped landing",
                 "dark and cramped landing", "here", "foot",
                 "foot of the stair", "foot of a crumbled stair",
                 "foot of a stair" }),
        "The landing extends north where it enters an east-west corridor"
      + " in the distance.\n");
    add_item( ({ "door", "doorway" }),
        "You can't see much detail from here.\n");
    add_item( ({ "east-west corridor", "corridor" }),
        "It's a bit north of here. Not surprisingly, so are the"
      + " details.\n");
    add_item( ({ "detail", "details" }),
        "Yep. You're gonna have to work for it.\n");
    add_item( ({ "air", "smell", "putrid smell", "smells",
                 "bad smell", "bad smells" }),
        "If awards were given out for bad smells, this would rank right"
      + " beside dead cat in a used toilet.\n");

    add_dungeon_items();

    add_exit("2_hall9", "north");
    add_exit("1_down", "up",
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
    add_action(do_smell, "smell");
    add_action(do_smell, "sniff");

    /* Lets make sure the jailer loads and starts doing his
     * routines now that players are down here.
     */
    safely_load_master_file(ROOMS_DIR + "2_jailer");
} /* init */


/*
 * Function:    safely_load_master_file
 * Description: This safely loads the master file if it hasn't already
 *              been loaded. Otherwise, it just returns the existing
 *              master file. If the file is not loadable, then it
 *              simply returns 0
 * Argument:    filename of the file to load
 */
public object
safely_load_master_file(string filename)
{
    object master_obj;
    if (!objectp(master_obj = find_object(filename)))
    {
        LOAD_ERR(filename);
        master_obj = find_object(filename);
    }
    
    return master_obj;
} /* safely_load_master_file */


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
      + " moved up to LEVEL-1.\n");
#endif

    return ::climb_up_stair_hook();
} /* climb_up_stair_hook */