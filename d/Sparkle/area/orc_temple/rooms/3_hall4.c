/*
 *  /d/Sparkle/area/orc_temple/rooms/3_hall4.c
 *
 *  One of the rooms in the dungeons beneath the orc temple. This room is
 *  on level 3.
 *
 *  Created November 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include "../defs.h"

inherit ROOMS_DIR + "pentagram_room";


/* Prototypes */
public void         create_pentagram_room();


/*
 * Function name:        create_pentagram_room
 * Description  :        constructor for the room
 */
public void
create_pentagram_room()
{
    set_side("northwest");
    set_extraline("A set of manacles hang in the corner.");

    add_item( ({ "manacle", "manacles", "set",
                 "set of manacles" }),
        "The manacles are made of black metal and are fastened to"
      + " the wall by thick chain links.\n");
    add_item( ({ "black metal", "metal" }),
        "Hard stuff. Heavy, too.\n");
    add_item( ({ "link", "links", "chain", "chains",
                 "chain link", "chain links", "thick link",
                 "thick links", "thick chain", "thick chains",
                 "thick chain link", "thick chain links" }),
        "They say a chain is only as strong as its weakest link.\n");
    add_item( ({ "weak link", "weakest link", "weak links", 
                 "weakest links" }),
        "There don't appear to be any. This stuff is solid and"
      + " strong.\n");
    add_item( ({ "northwestern end", "end" }),
        "Here, you stand between two points of a colossal pentagram that"
      + " is constructed of candles.\n");

    add_delay_cmd_item(
        ({ "chain", "manacle", "manacles", "set",
           "set of manacles", "link", "links", "chains",
           "chain link", "chain links", "weak link",
           "weak links", "weakest link", "weakest link",
           "thick chain link", "thick chain links",
           "thick links", "thick chain", "thick chains", }),
        "break",
        "trying to break the chains that hold the manacles to the wall",
        10,
        "You begin struggling to break the chain.\n",
        "Ugh ... it appears that you are ... the ... WEAKEST LINK!\n");

    add_exit("3_hall5", "east");
    add_exit("3_pit", "southeast", check_exit, 1, 0);
    add_exit("3_hall3", "south");

    set_no_exit_msg( ({ "north", "northeast", "southwest",
                        "west", "northwest" }),
        "You boldly stroll directly into a wall. OOOF!\n");
} /* create_pentagram_room */
