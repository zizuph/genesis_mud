#include "defs.h"
#include <stdproperties.h>

create_rivendell_room()
{
    set_short("Passage in the House of Elrond");

    set_long(
	"You are walking in the passage in the House of Elrond. "+
	"The passage continues west towards the opening and east towards "+
	"the Bell Tower. There is an open door in the north leading to the "+
	"Healers' Guildhall, and in the south there is the "+
	"traininghall of the Sula a Imladris.");

    add_exit(IML_DIR+"passage1",  "west");

/*    add_exit(STAND_DIR+"belltower", "east"); */

    add_exit(IML_DIR+"guild_hall", "north");
    add_exit(IML_DIR+"training_hall", "south");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
}
