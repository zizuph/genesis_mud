#pragma strict_types
#include "defs.h"

inherit "/std/room";

#include <stdproperties.h>


public object sconce;

public string
sconce_desc(void)
{
    if (!sconce)
        return "";

     return sconce->external_desc();
}

public void
reset_room(void)
{
    sconce = present("sconce");
    sconce->reset_container();
}

public void
create_room()
{
    set_short("passageway");
    set_long("This is a long, wide passage way. The floor is "+
	"made from wide blocks of dark slate, and the walls "+
	"are soft off-white limestone.@@sconce_desc@@ The "+
	"passage leads east through an ashwood lintel into a "+
	"large chamber, and climbs up to the west into darkness.\n");

    add_item(({"floor","ground","slate","blocks"}),
	"The floor is made from wide, irregular blocks of "+
	"gleaming dark slate.\n");
    add_item(({"wall","walls"}), "The walls are constructed from "+
	"pale, off-white limestone.\n");
    add_item("lintel", "It frames to entry to the east.\n");

    add_exit("false_tomb", "east");
    add_exit("entry_passage1", "west");

    remove_prop(ROOM_I_LIGHT);
    add_object(TOBJ + "sconce");
    set_alarm(0.0, 0.0, reset_room);
}
