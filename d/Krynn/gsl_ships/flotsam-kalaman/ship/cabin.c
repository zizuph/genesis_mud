inherit "/d/Krynn/std/cabin";

#include <stdproperties.h>
#include "/d/Ansalon/balifor/flotsam/ship2/local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>

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

    add_item("cabin","Other than the hammock, the table and the " +
      "door, there is nothing else of note in this cabin.\n");
    add_item("door","This solid wooden door leads up to the " +
      "deck above.\n");
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

    add_cmd_item(({"hammock","in hammock"}),
      ({"use","sleep","rest"}),"@@use_hammock");
    set_cabin_sound("@@sounds");
}

sounds()
{
    /*    if (file_name(environment(ship)) == TDIR + "sea1" ||
	  file_name(environment(ship)) == TDIR + "lake1")
    return "The ship shakes incredibly hard and you hear a big splash!\n";*/

    if (random(2))
	return "The ship sways with the wind.\n";

    return "The ship rocks violently to the tune of the turbulent waters.\n";
}

string
use_hammock()
{
    write("Since you are not a sailor by trade, as soon "+
      "as you are in the hammock, you fall out again.\n"); 
    say(QCTNAME(TP) + " attempts to climb into the "+
      "hammock, but falls out almost at once, looking "+
      "quite the fool.\n");
    return "";
}

