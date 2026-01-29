#pragma strict_types

inherit "/std/room";
#include "defs.h"

public void
create_room(void)
{
    set_short("passageway");
    set_long("This is a long, wide passage way. The floor is "+
	"made from wide blocks of dark slate, and the walls "+
	"are soft off-white limestone. The passageway continues "+
	"down to the east, and ascends to the west, from where "+
	"you can hear the gentle lapping of water.\n");

    add_item(({"floor","ground","slate","blocks"}),
	"The floor is made from wide, irregular blocks of "+
	"gleaming dark slate.\n");
    add_item(({"wall","walls"}), "The walls are constructed from "+
	"pale, off-white limestone.\n");

    add_exit("tomb_landing", "west");
    add_exit("entry_passage2", "east");
}
