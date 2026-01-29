/*
 * /d/Genesis/guilds/merc/room/boardroom
 *
 */

inherit "/std/room";

#include "../merc.h"
#include "room.h"

public string
read_rules()
{
    return "NOTICE:\n\n"+
	"I have had the carpenters build this room\n"+
	"against my better judgement. I will have\n"+
	"Dalizen monitor the board, and if he tells\n"+
	"me that it has become a forum for whining\n"+
	"it will be removed.\n\n"+
	"Maligant\n";
}

int enter_hall()
{
    write(GREAT_HALL_ENTER);
}

public void
create_room()
{
    set_short("A quiet room off the Great Hall");
    set_long(BUILDING_DESC+
 	" On one wall of this room is nailed a bulletin board, "+
	"which is covered with notes and announcements of all sorts. "+
	"To the southwest is the Great Hall, and the noise of talk and "+
	"movement leaks into this quieter area. There is a poster on "+
	"the wall next to the board.\n");

    add_item(({"poster", "sign"}), &read_rules());
    add_cmd_item(({"poster", "sign"}), "read", 
        &read_rules());

    add_prop(ROOM_I_INSIDE, 1);
    add_exit(MROOM + "great_hall", "southwest", "@@enter_hall", 1, 0);
    clone_object(MOBJ + "board")->move(this_object());
}
