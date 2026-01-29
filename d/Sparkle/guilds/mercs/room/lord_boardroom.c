/*
 * /d/Genesis/guilds/merc/room/lord_boardroom
 *
 */

inherit "/std/room";

#include "../merc.h"
#include "room.h"

public string
read_rules()
{
    return "NOTICE:\n\n"+
	"This board is for the use of the Mercenary Lords to communicate "+
	"with their followers.\n";
}

public void
create_room()
{
    set_short("A quiet room off the Great Hall");
    set_long(BUILDING_DESC+
 	" On one wall of this room is nailed a bulletin board, "+
	"which is covered with notes and announcements of all sorts. "+
	"To the south you will enter the hallway which leads back to "+
	"the common area of the halls. There is a poster on "+
	"the wall next to the board.\n");

    add_item(({"poster", "sign"}), &read_rules());
    add_cmd_item(({"poster", "sign"}), "read", 
        &read_rules());

    add_prop(ROOM_I_INSIDE, 1);
    add_exit(MROOM + "lord_entrance", "south", 0, 1, 0);
    clone_object(MOBJ + "lord_board")->move(this_object());
}
