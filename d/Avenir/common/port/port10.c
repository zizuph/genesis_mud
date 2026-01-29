// file name:        /d/Avenir/common/port/port10.c
// creator(s):       Ilyian
// revision history: 15 April, when I realized my big screw up
//		     Denis, Sep'96: Changes due to the port inheritance recode.
// purpose:
// note:
// bug(s):
// to-do:

# pragma strict_types
# include "port.h"
inherit PORT_ROOM;

static object worker;

static void
create_port_room()
{
    set_short("Eastern side of port cavern");
    set_long("You are at a place where the ledge turns from west " +
             "to south. To the east is a frightening dropoff down a " +
             "sheer cliff, and from here you have an awe inspiring " +
             "view of an enormous cavern to your east, extending many " +
             "leagues across and spreading out below you hundreds of " +
             "meters down to a black sea. To the southwest is the dark " +
             "stormy lake, with waves that lap at the ledge beneath " +
             "you. To the north seems to be a pub, and from the south " +
             "you hear the roar of a waterfall.\n");

    IN
    LIGHT

    add_exit("pub", "north");
    add_exit("port8", "south");
    add_exit("port11", "west");

    add_view_items();
    add_rift_no_see_item();
    add_no_swim_cmditems();

    add_item(({ "pub", "bar" }),
	     "The entrance lies to the north. A sign " +
	     "overhead reads 'Stormy Haven Pub'.\n");

    reset_room();
}

public void
reset_room()
{
    set_searched(0);

    if (!worker)
    {
        worker = clone_object(PORT + "mon/worker");
        worker->move_living("M", this_object());
    }
}
