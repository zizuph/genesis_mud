inherit "/d/Krynn/std/cabin";

#include <stdproperties.h>
#include "local.h"

void
create_cabin()
{
    set_short("A cabin inside the ship");
    set_long("You stand in a nice and warm cabin. This is a " +
	"good place to stay when the weather is rough. You see a small " +
	"table with some maps. A thin doorway leads out on the deck.\n");

    add_item("table", "A sturdy wooden table. Some maps are spread upon it.\n");
    add_item(({"map", "maps"}),
	    "The maps are nautical maps and " +
	     "there seem to be several doublets, some being riddled with " +
	     "marked lines and notations while others seem brand new. " +
	     "Alas, you find no treasure map.\n");

    add_exit(SHIP_D + "deck", "out", 0);

    add_prop(ROOM_I_INSIDE, 1);

    set_cabin_sound("@@sounds");
}

sounds()
{
/*    if (file_name(environment(ship)) == TDIR + "sea1" ||
            file_name(environment(ship)) == TDIR + "lake1")
        return "The ship shakes incredibly hard and you hear a big splash!\n";*/

    if (random(2))
        return "The ship sways slightly in the wind.\n";

    return "The ship is rocking gently with the waves.\n";
}

