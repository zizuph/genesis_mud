/* A part of the city of Tantallon by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_OUTSIDE;

object baaz1, baaz2;

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
}

create_tantallon_room()
{
    set_short("Alley");
    set_long(BS(
        "You now stand between a big wall and a tent. Everything is quiet " +
	"here with some stench of evil floating by in the air. If you listen " +
	"very carefully you can hear the river far south. You can't really " +
	"make out what's to the north because of the lack of light in that " +
	"direction.", SL));

    add_item("wall", BS(
        "This wall efficiently blocks your way west. It runs south as long " +
        "as you can see.", SL));
    add_item("tent", BS(
        "This is a rather small black tent. The entrance to it is east but " +
        "you can't hear anything from inside it. There is a sign on the " +
	"tent.", SL));
    add_item("sign",
        "It's just hanging there. You can see some words on it.\n");
    add_item("words",
        "They look readable.\n");

    add_cmd_item("sign", "read", "You read: THE OLD LAZY INN\n");

    add_exit(TDIR + "tent1", "east", 0);
    add_exit(TDIR + "city21", "southeast",0);
    add_exit(TDIR + "city13", "north",0);

    reset_tantallon_room();
}
