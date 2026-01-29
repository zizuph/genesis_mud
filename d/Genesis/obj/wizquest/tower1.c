
inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>

#define CONNECT_ROOM "/d/Genesis/start/human/wild/c_trail"

string *signatories;

create_room()
{
    set_short("Ground Floor, Tower of the Wizards");
    set_long(
"Ordinary stone walls seem to shimmer with delight in the raw magical\n" +
"energy that permeates this place.  A small table is set against one wall.\n");

    add_item("table", "This table is made of the finest oak.\n");

    CONNECT_ROOM->add_my_desc("As the mist shifts and dances you can make " +
        "out the outlines of a tower\n" +
        "built just north of here.  It appears the trail ends at the door " +
        "of the tower.\n");
    CONNECT_ROOM->add_exit(MASTER, "north", 0);
    CONNECT_ROOM->change_prop(ROOM_I_NO_CLEANUP, 1);
    change_prop(ROOM_I_NO_CLEANUP, 1);
    add_exit(CONNECT_ROOM, "south", 0);
}
