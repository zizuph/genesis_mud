// file name:        port7.c
// creator(s):       Ilyian
// revision history: Denis, Sep'96: Changes due to the port inheritance recode.
// purpose:
// note:
// bug(s):
// to-do:

# pragma strict_types
# include "port.h"
inherit PORT_ROOM_SILENT;

static void
create_port_room()
{
    set_short("Above the floodgate");
    set_long("You are on a wide ledge between the choppy waters " +
             "of the cavern lake to the west and an incredible dropoff " +
             "to the right. Beneath you is a floodgate through which tons " +
             "of water flow through every minute, falling hundreds of " +
             "meters to the sea below. The noise " +
             "in the cavern is deafening, as winds buffet the walls and " +
             "churn the water. The white mist is especially thick here, " +
             "the ground beneath you is very slippery. The ledge " +
             "continues to the north and south.\n");

    IN
    LIGHT

    add_exit("port8", "north");
    add_exit("port1", "south");

    add_view_items();
    add_rift_no_see_item();
    add_no_swim_cmditems();

    add_item("waterfall",
	     "The waterfall rushes through the floodgate " +
             "beneath you at a frightening speed, creating a thundering " +
             "noise. It falls hundreds of meters to the dark sea below "+
             "you, where you see a small cloud of white which must be the " +
             "foam from where it hits.\n");

    add_item("floodgate",
	     "The gate below you prevents the port cavern " +
             "from flooding. It seems to be wide open, letting out as much " +
             "of the water as possible. You wonder if the cavern is ever " +
             "less stormy and violent.\n");
}

