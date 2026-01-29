/* File         : /d/Khalakhor/se_speir/rannoch/village/room/post.c
 * Creator      : Darragh@Genesis
 * Date         : 03-07-27      
 * Purpose      : Map room file of the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: 
 */
#pragma save_binary

inherit "/d/Khalakhor/std/room";

#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include "room.h"
#include "/d/Khalakhor/sys/defs.h"

#define MAILREADER	"/secure/mail_reader"

string messages;
int new_mail;

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
 * Function name: leave_inv (MASK)
 * Description  : Called when an object leaves our inventory.
 *                Used here to remove mailreaders when a player
 *                leaves the PO.
 * Arguments    : ob - Object pointer to the leaving object.
 *                to - 'ob's next environment.
 */
public nomask void
leave_inv(object ob, object to)
{
    object reader;
    ::leave_inv(ob, to);

    reader = present("mailread", ob);
    if (reader)
        reader->remove_object();
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
    set_short("post office of Abhainn Ruith");
    set_long("You've entered the post office of Abhainn Ruith. " +
        "The building is small, just big enough to house a " +
        "few small desks for writing letters, which are " +
        "collected every now and then and sent out to the " +
        "addressee.\n");

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

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(ROOM + "road_15_7.c", "out");
}

void
init()
{
    object reader;
    ::init();

    reset_euid();
    reader = clone_object(MAILREADER);
    if (!reader)
    {
	write("No mailreader is available at this time.\n");
	return;
    }
    reader->move(TP);
}

