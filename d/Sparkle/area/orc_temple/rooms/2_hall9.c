/*
 *  /d/Sparkle/area/orc_temple/2_hall9.c
 *
 *  One of the rooms in the dungeons beneath the orc temple. This room is
 *  on level 2.
 *
 *  Created September 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include "../defs.h"

inherit ROOMS_DIR + "dungeon_room";


/* Prototypes */
public void         create_dungeon_room();


/*
 * Function name:        create_dungeon_room
 * Description  :        constructor for the room
 */
public void
create_dungeon_room()
{
    set_short("at an intersection of an east-west corridor");
    set_long("An east-west corridor connects here to a passage"
      + " leading south toward some stairs. Just before you is a"
      + " door-like opening in the north wall which looks into a"
      + " large chamber of some kind. The smell here is just awful.\n\n");

    try_item( ({ "intersection", "here", "east-west corridor",
                 "corridor" }),
        "This corridor runs a short distance both west and east.\n");
    try_item( ({ "passage", "south" }),
        "Just south of here some stairs lead up and out of sight.\n");
    try_item( ({ "stair", "stairs", "stairway" }),
        "The stairs are to the south. It's the usual deal. Go there,"
      + " then look at them, get information, everyone's happy.\n");
    try_item( ({ "opening", "opening in the north wall" }),
        "It's rather door-like.\n");
    try_item( ({ "north wall" }),
        "It looks like all the other walls except it has a door-like"
      + " opening in it.\n");
    try_item( ({ "door-like opening" }),
        "If it had a door in it, you'd probably just call it a doorway."
      + " But ... it doesn't.\n");
    try_item( ({ "door", "doorway" }),
        "Nope, it's a door-like opening.\n");
    try_item( ({ "chamber", "chamber of some kind", "large chamber",
                 "large chamber of some kind" }),
        "Go north and see for yourself, perhaps?\n");
    try_item( ({ "smell", "smells" }),
        "Smells like ... like ... like somebody cut a cow into"
      + " fifty pieces, soaked each one in urine and let them"
      + " decompose in the swamp!\n");

    add_dungeon_items();
    add_jail_npcs(2);

    add_exit("2_hall4", "west");
    add_exit("2_jailer", "north", check_exit, 1, 0);
    add_exit("2_hall5", "east");
    add_exit("2_up", "south");

    set_no_exit_msg( ({ "northeast", "southeast",
                        "southwest", "northwest" }),
        "You boldly stroll directly into a wall. OOOF!\n");
} /* create_dungeon_room */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_smell, "smell");
    add_action(do_smell, "sniff");
} /* init */


/*
 * Function name:        exit_blocked_hook
 * Description  :        provide a message that can be customized
 *                       when an npc blocks the path moving in a given
 *                       direction in the dungeons.
 * Arguments    :        object guard - the npc blocking the path
 * Returns      :        string - the message
 */
public string
exit_blocked_hook(object guard)
{
    return "The " + guard->short() + " slaps you in the face and says:"
      + " You's stay outta dere!\n";
} /* exit_blocked_hook */