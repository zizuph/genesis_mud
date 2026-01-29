#pragma save_binary

inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "guild.h"

void
create_room()
{
    set_short("Antechamber");
    set_long("You stand in a small dimly lit antechamber. A mouldy " +
	"dampness prevails in the air and makes breathing rather more " +
	"difficult.\n" +
	"Embeded in the walls are large, roughly cut stone slabs. They " +
	"circle the entire chamber and form a crude rock staircase.\n");

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    add_item(({ "stone slabs", "slabs", "stones", "stairs", "staircase",
	"stair" }), "These rocks have been crudely cut into steplike " +
	"shapes and inserted into the side of the chamber. Why don't " +
	"you climb them?\n");

    add_exit(THIS_DIR+"c3", "west");
    add_exit(THIS_DIR+"ac2", "up");
}