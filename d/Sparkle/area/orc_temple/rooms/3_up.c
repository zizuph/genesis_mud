/*
 *  /d/Sparkle/area/orc_temple/3_up.c
 *
 *  One of the rooms in the dungeons beneath the orc temple. This room is
 *  on level 3.
 *
 *  Created November 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include "../defs.h"
#include <time.h>

inherit ROOMS_DIR + "dungeon_room";


/* Prototypes */
public void         create_dungeon_room();
public int          climb_up_stair_hook();


/*
 * Function name:        create_dungeon_room
 * Description  :        constructor for the room
 */
public void
create_dungeon_room()
{
    set_short("at the foot of a dark stairway");
    set_long("Dark stairs lead upward here, where a short passage"
      + " leads north toward what appears to be a large, vast open"
      + " chamber of some kind. A terrifying awareness touches at"
      + " the edges of your mind.\n\n");

    add_item( ({ "stair", "stairs", "step", "steps",
                 "dark step", "dark steps", "dark stone step",
                 "dark stone steps", "stairway", "stone stair",
                 "stone step", "stone stairs", "stone steps",
                 "dark stairs", "dark stair",
                 "dark stairway" }),
        "Climbing the stairway would take you back up to the"
      + " second level of the dungeons.\n");
    add_item( ({ "short hallway" }),
        "It is more of a short passage, actually.\n");
    add_item( ({ "second level", "second level of the dungeons" }),
        "You remember the place. Lots of cell doors and bad"
      + " smells.\n");
    add_item( ({ "cell", "cell door", "door", "doors", "cell doors" }),
        "Missing them already? Just climb the stairs.\n");
    add_item( ({ "smell", "smells", "bad smell", "bad smells" }),
        "Down here, the smell isn't even remotely as bad as on the"
      + " second level.\n");
    add_item( ({ "third level", "third level of the dungeons" }),
        "Yup. This is it.\n");
    add_item( ({ "passage", "short passage", "here", "area",
                 "corridor", "hall", "hallway" }),
        "This short hallway leads between the large chamber to the"
      + " north and the stairs.\n");
    add_item( ({ "chamber", "large chamber", "vast chamber", "open chamber",
                 "large open chamber", "vast open chamber",
                 "large vast open chamber", "large, vast open chamber" }),
        "You can't see much from here. There is some odd flickering"
      + " light that you see in the distance.\n");
    add_item( ({ "distance" }),
        "Away over yonder.\n");
    add_item( ({ "yonder", "over yonder" }),
        "Get along, little doggie.\n");
    add_item( ({ "doggie", "little doggie" }),
        "Aww ... shucks.\n");
    add_item( ({ "light", "flickering", "flickering light",
                 "odd flickering", "odd light",
                 "odd flickering light" }),
        "Hard to make out what it might be from here.\n");
    add_item( ({ "terror", "awareness", "terrifying awareness" }),
        "The feeling grips you, and you cannot help but feel that"
      + " something ... terrible ... knows you are here.\n");
    add_item( ({ "something", "something terrible" }),
        "Thinking about it causes you to break out in a cold sweat.\n");

    add_dungeon_items();

    add_exit("3_hall1", "north");
    add_exit("2_down", "up",
        climb_up_stair_hook, 1, 0);

    setuid();
    seteuid(getuid());
} /* create_dungeon_room */


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
      + " moved up to LEVEL-2.\n");
#endif

    return ::climb_up_stair_hook();
} /* climb_up_stair_hook */