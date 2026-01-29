#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_OUTSIDE;

object kapak1, baaz1, baaz2;

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

    if(!objectp(baaz2))
        {
         baaz2 = clone_object("/d/Krynn/std/baaz");
         baaz2->set_color("red");
         BAAZ_COIN1->move(baaz2);
         BAAZ_COIN2->move(baaz2);
         baaz2->move(TO);
    }

    if(!objectp(kapak1))
        {
         kapak1 = clone_object("/d/Krynn/std/kapak");
         kapak1->set_color("red");
         KAPAK_COIN1->move(kapak1);
         KAPAK_COIN2->move(kapak1);
         kapak1->move(TO);
    }

}
create_tantallon_room()
{
    set_short("On path crossing");
    set_long(BS(
           "Here the little path splits in two. There is one way leading off " +
	"northeast closer to the big mountains you can see north from " +
	"here. You can also follow the path west or southeast. The way " +
	"south is blocked by one of the many tents in Tantallon.", SL));

    add_item(({"mountain", "mountains"}),BS(
    	"The mountains are very high. The look very dark and unfriendly. In " +
    	"fact most people avoid getting any closer than this to them.",SL));
    add_item("path",
    	"It seems like a lot of people walk this path normally.\n");
    add_item(({"tent", "south tent"}),BS(
    	"It's a small grey tent. You hear some sounds from it. You can't " +
    	"enter it from this side.",SL));

    add_exit(TDIR + "city1", "northeast",0);
    add_exit(TDIR + "city7", "southeast",0);
    add_exit(TDIR + "city3", "west",0);

    reset_tantallon_room();
}
