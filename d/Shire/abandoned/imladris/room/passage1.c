#include <stdproperties.h>
#include "defs.h"

create_rivendell_room()
{
    set_short("Passage in the House of Elrond");

    set_long(
	"You are standing in a magnificient passage in the House of Elrond. "+
	"Standing by the front door west of you, this 30 meter long passage "+
	"leads all the way to the center of the House, under the Bell Tower. "+
	"More interesting though are the two opposite exits in the north and "+
	"south. Elrond's Hall, where all the feasts are held is due south, "+
	"and The Hall of Fire in the north, where the burdens of the soul "+
	"is lightened by a cosy fire.");

    add_exit(IML_DIR+"fireroom", "north");
    add_exit(IML_DIR+"elrond_hall", "south");
    add_exit(IML_DIR+"passage2", "east");
    add_exit(IML_DIR+"w_porch", "west");

    add_item( ({ "door", "front door" }),
	"The front door leads west out to the front porch.");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
}
