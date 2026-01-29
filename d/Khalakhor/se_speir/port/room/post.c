/*
 * post.c
 *
 * Post Office of Port MacDunn
 *
 * Khail - March 30/97
 */
#pragma save_binary

inherit "/d/Khalakhor/std/room";
inherit "/d/Genesis/lib/post";
#include <stdproperties.h>
#include <macros.h>
#include "room.h"
#include "/d/Khalakhor/sys/defs.h"

public int *
query_local_coords()
{
    return ({9,2});
}

public int *
query_global_coords()
{
    return VILLAGE_COORDS;
}

/*
 * Function name: create_khalakhor_room
 * Description  : Turns this object into a post office.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_khalakhor_room()
{
    set_short("post office of Port MacDunn");
    set_long("   You've entered the post office of Port MacDunn. " +
        "The building is small, just big enough to house a " +
        "few small desks for writing letters, which are " +
        "collected every now and then and sent out to the " +
        "addressee. You should <examine mailreader> for more "+
        "information.\n");

    add_item(({"desks", "desk"}),
        "A handful of desks stand around the room, " +
        "covered with paper, quills, and inkpots for " +
        "writing mail.\n");
    add_item(({"paper"}),
        "Small piles of incredibly cheaply made paper " +
        "lie on the desks. So cheap, in fact, there's still " +
        "chunks of wood visible in some of them.\n");
    add_item(({"quills", "quill"}),
        "One or two quills for writing lie on each desk.\n");
    add_item(({"inkpots", "pots", "inkpot", "pot", "ink"}),
        "One or two small pots full of dark blue ink " +
        "stand on every table.\n");
   add_item(({"floor", "ground"}),
        "The floor of the post office is just hard-packed " +
        "dirt.\n");
    add_item(({"walls", "wall"}),
        "The walls of the building are made from various sized " +
        "pieces of hard grey stone, carefully placed together " +
        "and packed with clay.\n");
    add_item(({"roof", "ceiling"}),
        "The ceiling of the building is a simple thatch and wooden " +
        "rafter construction.\n");
    add_item(({"thatch", "seaweed", "seagrass"}),
        "The thatch looks to be tightly-bundled mats of " +
        "some sort of seagrass or seaweed.\n");
    add_item(({"rafters"}),
        "The thatch of the roof is supported by a handful of " +
        "very thin wooden rafters.\n");

    INSIDE;

    add_exit(ROOM + "road_9_1", "north");
}

/*
 * Function name:   leave_inv
 * Description:     remove mailreader from players exiting the room
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    post_leave_inv(ob, to);
}

public void
mail_message(string new)
{
    write("\nThere is"+ new +" mail for you in the Port MacDunn "+
      "post office.\n");
}

/*
 * Function name:   init
 * Description:     add a mailreader to players who enter the room
 */
public void
init()
{
    ::init();
    post_init();

}
