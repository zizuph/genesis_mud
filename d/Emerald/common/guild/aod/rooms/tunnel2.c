/*
 *  /d/Emerald/common/guild/aod/rooms/tunnel2.c
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
public string      which_room();


/*
 * Function name:        create_cave_room
 * Description  :        set up the room
 */
public void
create_cave_room()
{
    set_short("at the midpoint a long tunnel");
    set_em_long("You stand at the midpoint to a massive tunnel"
      + " which travels northwest and southeast into the rock. The"
      + " northern wall opens on two separate corridors, one heading"
      + " northeast and another east.\n");

    add_item( ({ "midpoint", "middle" }),
        "Yep. Middle. This is it. You've arrived. Party on.\n");
    add_item( ({ "ground" }),
        "It is vibrating slightly with all the ridiculous snoring"
      + " coming from the north.\n");
    add_item( ({ "tunnel", "massive tunnel" }),
        "The tunnel is enormous, and could easily allow ten men"
      + " walking abreast to pass by. It travels to the northwest and"
      + " southeast.\n");
    add_item( ({ "northern wall", "north wall" }),
        "Two corridors open from the northern wall.\n");
    add_item( ({ "corridor", "corridors" }),
        "There are two of them. One goes east and the other northeast.\n");
    add_item( ({ "east corridor", "eastern corridor" }),
        "Yep. There it goes. East.\n");
    add_item( ({ "northeast corridor", "northeastern corridor" }),
        "It goes, well ... northeast.\n");

    add_cave_items();
    add_spike("tunnel2");

    add_exit("tunnel1", "northwest");
    add_exit("post", "northeast");
    add_exit("@@which_room@@", "east");
    add_exit("tunnel3", "southeast");
} /* create_cave_room */


/*
 * Function name:        which_room
 * Description  :        The player can only access the completed room
 *                       if enough skulls have been collected to make
 *                       it possible. Otherwise, we send them to a
 *                       room that is under construction.
 * Returns      :        string - the file name of the room
 */
public string
which_room()
{
    return AOD_ROOM_DIR + 
           ((AOD_MASTER->query_guild_total("gnome") > 24999) ?
           "bank" : "pre_bank");
} /* which_room */