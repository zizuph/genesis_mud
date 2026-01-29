inherit "/d/Genesis/ship/cabin";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "defs.h"


void
create_cabin()
{
    set_short("Captain's cabin");
    set_long(break_string("This is where the captain calls home. "+
	"There is a small ship stove made from bronze and "+
	"set upon a swivel device that allows it to move "+
	"with the action of the boat. A bunk is set against "+
	"one side, shaped to the curve of the ship's hull. "+
	"A small table is bolted down in the center "+
	"and seems to serve the purpose of desk as well, "+
	"covered with maps and papers. An astrolabe of "+
	"polished bronze is set in the center of it.\n", 70));
    add_item((({"stove", "ship's stove", "device"})),
      "The ship's stove contains some sort of swivel "+
      "device that allows the stove to move with the "+
      "ship and not spill the captain's dinner.\n");
    add_item((({"maps", "papers"})),
      "Apparently the captain uses these to navigate "+
      "the course of the ship.\n");
    add_item("bunk",
      "The bunk is where the captain sleeps.\n");
    add_item("astrolabe",
      "The astrolabe is a device the captain uses "+
      "to determine his position at sea by sun or "+
      "stars.\n");

    set_cabin_sound("The ship rocks on the waves.\n");

    add_exit(CALIA_LINE + "deck", "up");

}
