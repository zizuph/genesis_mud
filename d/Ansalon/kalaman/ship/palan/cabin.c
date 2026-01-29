inherit "/d/Krynn/std/cabin";

#include <stdproperties.h>
#include "local.h"

void
create_cabin()
{
    set_short("A cabin inside the ship");
    set_long("You stand in a small cabin. As " +
	"this boat is built for speed and not luxury, you find it " +
	"hard to imagine more than two people being able to " +
	"comfortably fit down here. A hammock hangs on the back " +
	"wall, and a table has been nailed to the middle of the " +
	"floor. A wooden door leads back up onto the deck.\n");

    add_item("table", "A sturdy wooden table. Some maps are spread upon it.\n");
    add_item(({"map", "maps"}),
	"The maps are nautical maps and " +
	"there seem to be several doublets, some being riddled with " +
	"marked lines and notations while others seem brand new. " +
	"Alas, you find no treasure map.\n");

    add_item("hammock","A hammock hangs on the back wall. " +
      "It seems to you that some experience would be " +
      "needed to be able to use this contraption.\n");

    add_exit(SHIP_D + "deck","up",0);

    add_prop(ROOM_I_INSIDE, 1);

    set_cabin_sound("@@sounds");
}

sounds()
{
    /*    if (file_name(environment(ship)) == TDIR + "sea1" ||
	  file_name(environment(ship)) == TDIR + "lake1")
    return "The ship shakes incredibly hard and you hear a big splash!\n";*/

    if (random(2))
	return "The ship sways with the wind.\n";

    return "The ship slides smoothly through the calm waters.\n";
}

