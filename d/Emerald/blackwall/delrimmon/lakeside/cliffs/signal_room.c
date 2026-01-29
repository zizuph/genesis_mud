/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/cliffs/signal_room.c
 *
 *  This is the high ledge upon which Maeltar set the signal
 *  for the outposts of Del Rimmon. From this point, the troops
 *  within the valley could be alerted to any danger or invasion
 *  based on the sequence of notes blown on the horn.
 *
 *  Copyright (c) January 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types


inherit "/d/Emerald/blackwall/delrimmon/lakeside/cliffs/ledge_master";
inherit "/d/Emerald/blackwall/delrimmon/del_rimmon";
inherit "/d/Emerald/blackwall/delrimmon/legacy/tell_funcs";

#include <macros.h>      /* for VBFC, etc */
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void        create_ledge();
public int        check_exit();
public int        climb_ladder(string arg);
public void       init();
public void        entry_msg(object pl);


/*
 * Function name:        create_ledge
 * Descriptionn :        set up the room with area presets
 */
public void
create_ledge()
{
    set_cliff_base(DELRIMMON_DIR + "lakeside/nw_cliff5");

    add_name("del_rimmon_cliffs");
    set_short("atop a high cliff ledge");
    set_long(del_rimmon_long);
    set_show_area_desc();
    set_extraline("You stand on an isolated ledge which juts out from"
      + " a long plateau to the south. To the north and east, a sheer"
      + " precipice looms. To the west, the tall slopes of a peak"
      + " rise to form a rock wall. The rocky ground is interrupted"
      + " here by a large hole leading downward.");

    add_item( ({ "ledge", "isolated ledge", "here", "area" }),
        "This ledge forms a sheer precipice which overlooks the"
      + " lake far below to the east.\n");
    add_item( ({ "plateau", "long plateau" }),
        "A long plateau extends to the south, high above the"
      + " lakeshore far below. A large pile of boulders separates"
      + " this ledge from the rest of the precipice directly"
      + " south from here.\n");
    add_item( ({ "pile", "large pile", "pile of boulders",
                 "large pile of boulders", "boulder", "boulders",
                 "boulder pile", "south" }),
        "A large pile of boulders is heaped just to the south of"
      + " this ledge, cutting you off from any travel in that"
      + " direction. It may be that at one time, this ledge was"
      + " connected to the plateau which extends beyond the pile.\n");
    add_item( ({ "precipice", "sheer precipice", "drop", "sheer drop",
                 "dropoff", "sheer dropoff", "north", "east"}),
        "The ledge forms a sheer dropoff to the north and east, where"
      + " the rock upon which you stand extends out over the lake,"
      + " many hundreds of feet in the air.\n");
    add_item( ({ "peak", "west", "slopes of a peak", "tall peak" }),
        "A tall peak rises to the west, its rock walls framing this"
      + " ledges western side.\n");
    add_item( ({ "rock wall" }),
        "The wall to the west rises directly overhead to form the"
      + " base of a tall peak which rises in that direction.\n");
    add_item( ({ "ground", "down", "rocky ground", "floor" }),
        "The ground here is mostly flat, if a little uneven. It is"
      + " clear that nature has formed this surface, though perhaps"
      + " not the large hole which leads down into the rock here.\n");
    add_item( ({ "hole", "large hole" }),
        "A large hole leads down into the rock here. The top of a"
      + " ladder is visible extending slightly out of its depths.\n");
    add_item( ({ "ladder" }),
        "A ladder leads down into a hole in the ground here.\n");


    add_cmd_item( ({ "pile", "pile of boulders", "boulder", "boulders" }),
                  ({ "climb", "jump" }),
        "You attempt to scramble over the pile of boulders, but soon"
      + " give up. Risking your life so close to a dropoff is simply"
      + " not wise.\n");

    add_prop("_signal_room", 1);
    add_prop(ROOM_S_EXIT_FROM_DESC,
        "from above, climbing down the ladder.");

    add_exit(DELRIMMON_DIR + "lakeside/cliffs/outpost1b", "down",
             check_exit, 5, 1);

    set_no_exit_msg( ({ "northwest", "north", "northeast", "east",
                        "southeast" }),
        "You take a few steps toward the dropoff, and stop. Peering"
      + " over the long drop, your head swims slightly, and you"
      + " step back from the precipice.\n");
    set_no_exit_msg( ({ "west", "southwest" }),
        "The rock wall of a tall peak blocks your movement in that"
      + " direction.\n");
    set_no_exit_msg( ({ "south" }),
        "A tall pile of boulders rises to block the way.\n");

    add_lakeview();
    add_view();

    reset_room();
} /* create_ledge */


/*
 * Function name:        reset_room
 * Description  :        clone the signal horn into the room
 */
public void
reset_room()
{
    object signal;

    if (!present("del_rimmon_signal"))
    {
        signal =
            clone_object(DELRIMMON_DIR + "obj/signal")->move(this_object());
    }

} /* reset_room */


/*
 * Function name:        check_exit
 * Description  :        Describe the player going down the
 *                       ladder.
 * Returns      :        int 0 - ok to leave,
 */
public int
check_exit()
{
    write("You grasp the rungs of the ladder, and make your way"
        + " down through the hole in the ground.\n");
    tell_room(this_object(), QCTNAME(this_player()) + " climbs"
        + " down the ladder and disappears through the hole"
        + " in the ground.\n", this_player());

    return 0;
} /* check_exit */


/*
 * Function name:        climb_ladder
 * Description  :        allow the player to climb down the ladder
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
climb_ladder(string arg)
{
    if (!strlen(arg))
    {
        NFN0("Climb what?");
    }

    if (!parse_command(arg, ({}),
        "[down] [the] [dusty] [wooden] 'ladder' / 'hole'"))
    {
        NFN0("What?"); /* the player used bad syntax */
    }

    if (this_player()->query_wiz_level())
    {
        write("Normally, we would move the player 'down' here, using"
            + " command. Since you are a wiz, that won't work.\n");
    }

    this_player()->command("down");
    return 1;
} /* climb_ladder */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(climb_ladder, "climb");
} /* init */


/*
 * Function name:        entry_msg
 * Description  :        give the room a message about the player
 *                       who is climbing the ladder
 * Arguments    :        object pl - the player doing the climbing
 */
public void
entry_msg(object pl)
{
    tell_room(this_object(), QCTNAME(pl) + " climbs out of the"
      + " hole in the ground to stand on the ledge.\n");

    return;
} /* entry_msg */
