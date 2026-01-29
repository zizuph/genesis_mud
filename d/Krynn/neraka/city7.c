#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_OUTSIDE;

object draco, baaz1, kapak1;

#include RND_MEET

reset_tantallon_room()
{
    if(!objectp(baaz1))
        {
         baaz1 = clone_object("/d/Krynn/std/baaz");
         baaz1->set_color("red");
         BAAZ_COIN1->move(baaz1);
         BAAZ_COIN2->move(baaz1);
         baaz1->move(TO);
    }

    if(!objectp(kapak1))
        {
         kapak1 = clone_object("/d/Krynn/std/kapak");
         kapak1->set_color("red");
         KAPAK_COIN1->move(kapak1);
         KAPAK_COIN2->move(kapak1);
         kapak1->move(TO);
    }

    if (draco)
    	return;
    draco = RANDOM_MEET(DRACOS);/*clone_object(MON + "draconian");*/
    if (draco->query_prop(OBJ_I_COLORABLE))
	draco->set_color("red");
    draco->set_random_move(30);
    draco->move_living("xxx", TO);

}

create_tantallon_room()
{
    set_short("On path");
    set_long(BS(
    	"You stand on a small but well used path besides a river. The path " +
	"makes a small bend here leaving you the choice to walk south or " +
	"northwest. Far away to the north you see some high mountains. " +
	"West from here you see one of the many tents in Tantallon.", SL));

    add_item(({"mountain", "mountains"}), BS(
    	"The mountains are very high. The look very dark and unfriendly. " +
	"On some of the higher peaks you can see something white, snow " +
	"perhaps?", SL));
    add_item("path",
    	"It seems like a lot of people walk this path normally.\n");
    add_item(({"tent", "west tent"}), BS(
    	"It's a small grey tent. You hear some sounds from it. You can't " +
    	"enter it from this side.", SL));
    add_item("river",
    	"The river runs from northeast to south. It looks wet.\n");

    add_exit(TDIR + "city4", "northwest", 0);
    add_exit(TDIR + "city10", "south", 0);

    reset_tantallon_room();
}
