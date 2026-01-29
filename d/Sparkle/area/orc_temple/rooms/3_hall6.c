/*
 *  /d/Sparkle/area/orc_temple/rooms/3_hall6.c
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
    set_side("northeast");
    set_extraline("A strange puddle on the floor barely reflects any"
      + " light.");


    add_item( ({ "northeastern end", "end" }),
        "Here, you stand between two points of a colossal pentagram that"
      + " is constructed of candles.\n");
    add_item( ({ "puddle", "strange puddle" }),
        "A puddle has begun to seep up through some cracks in the"
      + " floor here. The surface of the liquid is oddly absent of"
      + " the normal reflections you would expect from the surrounding"
      + " lights of the candles.\n");
    add_item( ({ "crack", "cracks", "crack in the floor",
                 "cracks in the floor" }),
        "The floor in this corner is badly cracked near the wall.\n");
    add_item( ({ "surface", "surface of the liquid" }),
        "It is sticky, and doesn't reflect light very well.\n");
    add_item( ({ "liquid" }),
        "This would probably have to qualify as a liquid, but it"
      + " seems fully unnatural.\n");

    add_delay_cmd_item(
        ({ "puddle", "liquid", "strange puddle", }),
        "search",
        "searching the strange puddle",
        10,
        "You begin searching the strange puddle.\n",
        "The puddle is sticky, and smells utterly alien. Other than"
      + " that, you discover nothing.\n");

    add_exit("3_hall7", "south");
    add_exit("3_pit", "southwest", check_exit, 1, 0);
    add_exit("3_hall5", "west");

    set_no_exit_msg( ({ "northwest", "north", "northeast",
                        "east", "southeast" }),
        "You boldly stroll directly into a wall. OOOF!\n");
} /* create_pentagram_room */
