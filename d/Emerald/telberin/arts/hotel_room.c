/*
 *  /d/Emerald/telberin/arts/hotel_room.c
 *
 *  This is the hotel room which can be purchased by players in
 *  the Silver Swan Inn in Telberin. It was copied from the
 *  hotel room in Minas Morgul created by Olorin in 1993.
 *
 *  Copyright (c) March 2003, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/std/room";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"


/*
 * Function name:        create_emerald_room
 * Description  :        set up the room
 */
public void
create_emerald_room()
{
    set_short("upstairs in the Silver Swan Inn in Telberin");
    set_em_long("A flight of stairs leads down to the main floor from"
      + " here. If you have purchased a key from the innkeeper"
      + " downstairs, you can spend the night here by typing"
      + " <start here>.\n");

    add_exit("/d/Emerald/telberin/arts/inn", "down");
    add_prop(ROOM_I_INSIDE,1);  /* This room is indoors */

    add_item( ({ "stair", "step", "steps", "stairs", "flight",
                 "flight of stairs" }),
        "The stairs are clean and well-built. They lead down"
      + " to the main floor of the Inn.\n");
    add_item( ({ "main floor", "down", "downstairs", "below" }),
        "The main floor is visible down below the stairs. It is"
      + " there that one might purchase a key for this room, if"
      + " one does not already possess one.\n");
    add_item( ({ "wall", "walls", "floor", "ceiling", "room",
                 "here", "area" }),
        "The walls and floor are all immaculately kept here."
      + " It looks as if this would be a very comfortable place"
      + " to spend the night.\n");
} /* create_emerald_room */


/*
 * Function name:        start
 * Description  :        allows the player to start here, if they have
 *                       the key
 * Returns      :        int 1 - player did something we understand,
 *                           0 - player did something else
 */
public int
start(string arg)
{
    object ob;

    if (!strlen(arg))
    {
        notify_fail("Start where?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[in] [this] 'room' / 'here'"))
    {
        return 0;
    }


    if (this_player()->query_temp_start_location() ==
        "/d/Emerald/telberin/arts/hotel_room")
    {
        write("You have already checked in!\n");
        return 1;
    }

    if (!(ob=present("_the_key_to_the_silver_swan_inn_",
          this_player())))
    {
        write("You need to purchase a key downstairs first.\n");
        return 1;
    }

    ob->remove_object();

    TP->set_temp_start_location(
        "/d/Emerald/telberin/arts/hotel_room");
    write("You notice that the slender alabaster key crumbles to dust in your "
        + "hand. Suddenly you are confident that you will start here the next "
        + "time you enter the game.\n");
    return 1;
} /* start */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();
    add_action(start, "start");
} /* init */
