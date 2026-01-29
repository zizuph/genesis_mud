/*
 *	/d/Gondor/common/dunedain/rooms/hallw_s2.c
 *
 *	Coded by Olorin, November 1994
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/dunedain/rooms/dun_room.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/dunedain/lib/dunedain_defs.h"

public void
create_gondor()
{
    set_short("Southern Hallway in the House of the Dunedain");
    set_long(BSN("The hallway continues east. High stone arcs are "
	+ "leading into chambers to the west and the south."));

    add_item(({"arcs", "stone arcs", "high arcs", }), BSN(
	"There are two arcs here leading into chambers west and south "
	+ "of here."));

    add_item(({"arc", "stone arc", "high arc", }),
      "Which arc, the south or the west arc?\n");

    add_item(({"west arc", "western arc", }), BSN(
	"One of the high arcs is leading west into a "
	+ "chamber visible beyond. Above the arc letters have been chiselled "
	+ "into the stone:")
      + "\t\tSAMBE E LORALYA\n");

    add_item(({"south arc", "southern arc", }), BSN(
	"One of the high arcs is leading south into a "
	+ "small chamber. Above the arc letters have been chiselled into "
	+ "the stone:")
      + "\t\tSAMBE SINIATH\n");

    ceiling();
    floor(1);
    walls(1);

    add_exit(DUNEDAIN_DIR + "rooms/hallw_s2",   "east",  0, 0);
    add_exit(DUNEDAIN_DIR + "post",             "south", check_exit,  0);
    add_exit(DUNEDAIN_DIR + "rooms/start_room", "west",  check_exit,  0);

    add_prop(ROOM_I_INSIDE, 1);
}
