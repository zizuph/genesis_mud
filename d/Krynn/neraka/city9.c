/* Tantallon by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_OUTSIDE;

object draco;

#include RND_MEET

reset_tantallon_room()
{
    if (draco)
    	return;
    draco = RANDOM_MEET(DRACOS);/*draco = clone_object(MON + "draconian");*/
    if (draco->query_prop(OBJ_I_COLORABLE))
	draco->set_color("red");
    draco->set_random_move(30);
    draco->move_living("xxx", TO);
}

create_tantallon_room()
{
    set_short("Road turn");
    set_long(BS(
    	"This is the turning point of the small road. It has to turn since " +
	"there are tents both north and west blocking the way. South is an " +
   "opening and east there seems to be a big crossing.", SL));

    add_item("tent",
    	"Which tent do you mean? The north or the west one?\n");
    add_item("north tent", BS(
    	"It's a rather small and grey tent. You hear sounds from many people " +
    	"comming from it. You wonder how they could all have entered that " +
	"tent. Well, you cannot find out now - because the entrance isn't " +
	"here.", SL));
    add_item("west tent", BS(
    	"It looks like if this tent is the biggest one in Tantallon. It's " +
	"coloured in deep black and you feel something evil present in it." +
	"", SL));
    add_item("road",
    	"It leads off east and south. It's made out of small stones.\n");
    add_item(({"stone", "stones"}), BS(
    	"The stones are small and round but they stick to the ground so you " +
    	"can't pick them up.", SL));

    add_exit(TDIR + "city10", "east", 0);
    add_exit(TDIR + "city12", "south", 0);

    reset_room();
}

