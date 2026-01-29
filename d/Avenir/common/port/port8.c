// file name:        port8.c
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
    set_short("Eastern side of port cavern");
    set_long("You are on a wide ledge to the east of a stormy " +
             "lake within the cavern. The noise " +
             "in the cavern is deafening, as winds buffet the walls and " +
             "churn the water. The whole area is lit by an unearthly white " +
             "glow that seems to come from the rocks above, but the grey " +
             "mist that hangs in the air prevents you from seeing very far " +
             "in any direction. To the east is a sheer dropoff and " +
             "to the south " +
             "you can hear the roar of a waterfall.\n");

    IN
    LIGHT

    add_exit("port10", "north");
    add_exit("port7", "south");

    add_view_items();
    add_rift_no_see_item();
    add_no_swim_cmditems();
}
