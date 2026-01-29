// file name:        port3.c
// creator(s):       Ilyian
// revision history: Denis, Sep'96: Changes due to the port inheritance recode.
// purpose:
// note:
// bug(s):
// to-do:


# pragma strict_types
# include "port.h"
inherit PORT_ROOM;

static void
create_port_room()
{
    set_short("South-eastern side of port cavern");
    set_long("The ledge runs north and west here. To the " +
             "west the ledge leads " +
             "away from the terrible cliff along the cavern wall, " +
             "and to the north you can vaguely hear a waterfall over " +
             "the rest of the noise in the cavern. The area is " +
             "lit by an unearthly white " +
             "glow that seems to come from the rocks above, but the grey " +
             "mist that hangs in the air prevents you from seeing very far " +
             "in any direction.\n");

    IN
    LIGHT

    add_exit("port6", "west");
    add_exit("port2", "north");

    add_view_items();
    add_rift_no_see_item();
    add_wall_item();
    add_no_swim_cmditems();
}
