/*
 *  /d/Sparkle/area/tutorial/review/7.c
 *
 *  This room is the final chamber of the review of basic commands that
 *  players can perform in the library of Greenhollow as part of the
 *  tutorial for new players.
 *
 *  Created August 2004, by Cooper Shery (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/room";
inherit REVIEW_DIR + "skip";

#include <login.h>
#include <stdproperties.h>


/* prototypes */
public void        create_room();
public int         gate_shut();
public void        reset_room();
public void        init();


/*
 * Function name:        create_room
 * Description  :        set up the room
 */
public void
create_room()
{
    set_name("7");
    set_short("a small room with many exits");
    set_long("You stand in a large circular chamber with only a single"
      + " exit, leading south down a long corridor.\n\n");

    add_item( ({ "chamber", "circular chamber", "large chamber",
                 "large circular chamber", "here", "area" }), long);
    add_item( ({ "south", "south wall", "corridor", "long corridor",
                 "hall", "hallway", "long hallway" }),
        "A long corridor travels from the south wall into the"
      + " distance.\n");
    add_item( ({ "north", "north wall", "northern wall" }),
        "The northern wall is featureless.\n");
    add_item( ({ "floor", "ground", "down" }),
        "The floor is hard underfoot.\n");
    add_item( ({ "up", "ceiling", "roof" }),
        "The ceiling of this chamber is high above the floor.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop("_room_i_tutorial", 1);

    add_exit("6", "south", gate_shut, 1, 0);
    add_prop(ROOM_S_MAP_FILE, "tutorial_map.txt");

    reset_room();
} /* create_room */


/*
 * Function name:        gate_shut
 * Description  :        we want to prevent mortals from backtracking from
 *                       this room. this function provides an explanation
 *                       to the player.
 * Returns      :        int 1
 */
public int
gate_shut()
{
    write("You travel down the southern corridor. However, when you"
      + " get to the end, you find a gate that is shut tight. You"
      + " cannot go that way, so you return to the circular"
      + " chamber.\n");

    return 1;
} /* gate_shut */


/*
 * Function name:        reset_room
 * Description  :        add a sign to the room
 */
public void
reset_room()
{
    object   sign;

    if (!present("_tutorial_sign"))
    {
        sign = clone_object(OBJ_DIR + "sign");
        sign->config_sign("sign");
        sign->set_chapter(7);
        sign->add_adj( ({ "familiar", "useful" }) );
        sign->add_name("information");
        sign->move(this_object());
    }

    return;
} /* reset_room */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(skip, "skip");
    add_action(skip, "end");
    add_action(tutorial_quit, "quit");
} /* init */


