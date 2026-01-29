/*
 *  /d/Emerald/common/guild/aod/rooms/tunnel4.c
 *
 *  This is a connecting tunnel in the Army of Darkness guildhall.
 *
 *  Created July 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit AOD_ROOM_DIR + "cave_room";
inherit AOD_LIB_DIR + "add_spike";

/* prototypes */
public void        create_cave_room();
public string      which_room1();
public string      which_room2();


/*
 * Function name:        create_cave_room
 * Description  :        set up the room
 */
public void
create_cave_room()
{
    set_short("at the end of a long tunnel within the mountain");
    set_em_long("Having rounded a bend to the southwest, the massive"
      + " tunnel comes to a halt here. Two corridors lead into"
      + " the rock travelling north and east.\n");

    add_item( ({ "tunnel", "massive tunnel" }),
        "The tunnel is enormous, and could easily allow ten men"
      + " walking abreast to pass by. It travels to the southwest"
      + " where it rounds a bend.\n");
    add_item( ({ "corridor", "corridors" }),
        "There are two corridors. One heads north and the other"
      + " east.\n");
    add_item( ({ "north corridor", "northern corridor" }),
        "Yep. North.\n");
    add_item( ({ "east corridor", "eastern corridor" }),
        "East. There it goes.\n");

    add_cave_items();
    add_spike("tunnel4");

    add_exit("@@which_room1@@", "north");
    add_exit("@@which_room2@@", "east");
    add_exit("tunnel3", "southwest");
} /* create_cave_room */


/*
 * Function name:        which_room1
 * Description  :        The player can only access the completed room
 *                       if enough skulls have been collected to make
 *                       it possible. Otherwise, we send them to a
 *                       room that is under construction.
 * Returns      :        string - the file name of the room
 */
public string
which_room1()
{
    return AOD_ROOM_DIR + 
           ((AOD_MASTER->query_guild_total("human") > 24999) ?
           "aod_shop" : "pre_shop");
} /* which_room1 */


/*
 * Function name:        which_room2
 * Description  :        The player can only access the completed room
 *                       if enough skulls have been collected to make
 *                       it possible. Otherwise, we send them to a
 *                       room that is under construction.
 * Returns      :        string - the file name of the room
 */
public string
which_room2()
{
    return AOD_ROOM_DIR + 
           ((AOD_MASTER->query_guild_total("hobbit") > 24999) ?
           "mess_hall" : "pre_mess_hall");
} /* which_room2 */
