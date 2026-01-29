/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/caves/dead_end.c
 *
 *  This is a dead end in the tunnels dug by the Elves of Telberin.
 *  Formerly, this room was meant to be one of the possible locations
 *  for the tomb of Formandil, when this quest was still intended for
 *  Gondor. Because of that, it has some fun syntax options for
 *  curious players. I'll leave it intact to remain a big fat red
 *  herring.
 *
 *  Copyright (c) September 1998, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
void           create_del_rimmon();
public void    init();
public int     do_push(string arg);

/*
 * Function name:        create_del_rimmon
 * Description  :        set up the room
 */
void
create_del_rimmon()
{
    set_short("a dead end tunnel deep within the cliffs of the Del"
            + " Rimmon");
    set_long(BSN("The walls of the corridor seem to close in here,"
               + " offering nothing but solid rock in nearly every"
               + " direction. Only to the southeast does the passage"
               + " open, disappearing into darkness. This appears to"
               + " be a full dead end."));

    add_item( ({"wall", "walls"}), BSN(
        "The walls of the corridor close in about you here, where the"
      + " corridor runs into a dead end. The surface of the walls"
      + " bears the marks of the instruments which formed these"
      + " tunnels."));
    add_item( ({"mark", "marks"}), BSN(
        "The marks on these walls are subtle and even, which speaks"
      + " to the skill of the workers who made them."));
    add_item( ({"worker", "workers"}), BSN(
        "They are sure to be long dead."));
    add_item( ({"instrument", "instruments"}), BSN(
        "One can only guess as to the instruments which were used to"
      + " bore these tunnels in the stone."));
    add_item( ({"surface", "surfaces", "surface of the wall",
                "surface of the walls"}), BSN(
        "The surface of the walls is rough, yet even."));
    add_item( ({"corridor", "corridors", "passage", "passages",
                "passageway", "passageways", "tunnel", "tunnels"}), BSN(
        "The corridor comes to a stop directly to the northwest, where"
      + " a blank wall rises as a dead end to the passageway."));
    add_item( ({"blank wall", "dead end", "northwest",
                "northwest wall", "wall to the northwest"}), BSN(
        "The wall which marks the dead end is perfectly flat and"
      + " smooth, unlike the other walls of this corridor."));
    add_item( ({"rock", "solid rock", "rocks", "stone", "stones"}), BSN(
        "The stone of these passageways is rough and dark, obviously"
      + " possessing the hardness required for supporting open tunnels"
      + " for years and years."));
    add_item( ({"southeast"}), BSN(
        "The way to the southeast is open, following a dark corridor"
      + " into darkness."));
    add_item( ({"darkness", "dark"}), BSN(
        "The darkness to the southeast reveals the dim outline of"
      + " the passageway rounding a bend in that direction."));
    add_item( ({"bend", "dim outline", "outline"}), BSN(
        "The passageway appears to round a bend to the southeast,"
      + " where it swiftly is lost from view in the darkness."));
    add_item( ({"roof", "ceiling", "up"}), BSN(
        "The roof of this corridor is rough and level, much in the"
      + " same manner as the walls."));
    add_item( ({"ground", "floor", "down"}), BSN(
        "The floor of this passageway runs right up to the wall"
      + " to the northwest, which brings the corridor to a halt."));
    add_item( ({"sun", "sky", "moon", "stars"}), BSN(
        "The sky is not visible from inside these tunnels."));

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);

    add_exit(DELRIMMON_DIR + "lakeside/caves/n_cave", "southeast");

    set_no_exit_msg( ({ "north", "northeast", "east", "south",
                        "southwest", "west", "northwest" }),
        "The way is blocked by the walls of the corridor.\n");
} /* create_del_rimmon */

/*
 * Function name:        init
 * Description  :        add some actions for the player
 */
public void
init()
{
    ::init();

    add_action(do_push, "push");
    add_action(do_push, "shove");
    add_action(do_push, "press");
} /* init */

/*
 * Function name:        do_push
 * Description  :        let the players try to push the wall
 * Arguments    :        arg -- what the player typed
 * Returns      :        1 - success, 0 - failure
 */
public int
do_push(string arg)
{
    if (!strlen(arg))        /* no arg */
    {
        NFN0(CAP(QVB) + " what?");
    }

    if (parse_command(arg, ({}),
        "[the] [wall] [to] [the] 'north' / 'northeast' / 'northern' /"
      + " 'northeastern' / 'east' / 'eastern' / 'south' /"
      + " 'southern' / 'southwest' / 'southwestern' /"
      + " 'west' / 'western' [wall]"))
    {
        WRITE("You strain mightily against the wall,"
            + " but don't accomplish anything.");
        return 1;
    }

    if (!parse_command(arg, ({}),
        "[the] [dead] [northwest] [northwestern] [smooth] 'end' / 'wall'"
      + " [to] [the] [northwest]"))
    {
        if (arg == "southeast wall" || arg == "wall to the southeast" ||
            arg == "southeastern wall")
        {
            NFN0("There is no wall to the southeast.");
        }
        return 0;
    }

    if (arg == "wall" || arg == "walls")
    {
        NFN0(CAP(QVB) + " which wall?");
    }

    WRITE("You push with as much force as you are able to muster"
        + " against the smooth surface of the dead end. It does not"
        + " budge.");
    return 1;
} /* do_push */
