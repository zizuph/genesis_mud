/* Tantallon coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_OUTSIDE;

object draco, baaz1, baaz2;

#include RND_MEET

reset_tantallon_room()
{
    if (draco)
    	return;
    draco = RANDOM_MEET(DRACOS);/*clone_object(MON + "draconian");*/
    if (draco->query_prop(OBJ_I_COLORABLE))
	draco->set_color("red");
    draco->set_random_move(30);
    draco->move_living("xx", TO);

    if (baaz1)
    	return;
    baaz1 = clone_object("/d/Krynn/std/baaz");
    if (baaz1->query_prop(OBJ_I_COLORABLE))
	baaz1->set_color("red");
    BAAZ_COIN1->move(baaz1);
    BAAZ_COIN2->move(baaz1);
    baaz1->move_living("xx", TO);

    if (baaz2)
    	return;
    baaz2 = clone_object("/d/Krynn/std/baaz");
    if (baaz2->query_prop(OBJ_I_COLORABLE))
	baaz2->set_color("red");
    BAAZ_COIN1->move(baaz2);
    BAAZ_COIN2->move(baaz2);
    baaz2->move_living("xx", TO);
}

create_tantallon_room()
{
    set_short("Alley");
    set_long(BS(
    	"You stand between two tents on a muddy ground. East you can see a " +
	"road and far west lies something that looks like a big wall. It " +
   "seems that the guards of Tantallon frequently pass by this part " +
	"of the city.", SL));

    add_item("tent",
    	"Which tent do you mean? The north or the south one?\n");
    add_item("north tent", BS(
    	"It's a rather small black tent and strangely enough you can't hear " +
    	"a thing from it. Obviously the entrance isn't on this side.", SL));
    add_item("south tent", BS(
    	"This is a small grey tent. It sounds like if someone were singing " +
	"in it. There is a sign on the tent.", SL));
    add_item("sign", BS(
    	"It's a big wodden sign hanging over the entrance. It has some words " +
    	"written on it.", SL));
    add_item("words",
    	"They look readable.\n");
    add_item("wall", BS(
    	"It is a big wall, it looks like if it would go all the way from the " +
	"river and continue far north.", SL));

    add_cmd_item("sign", "read", "You read: GUARDIANS PUB\n");

    add_exit(TDIR + "city22", "east", 0);
    add_exit(TDIR + "tent4", "south", 0);
    add_exit(TDIR + "city18", "northwest", 0);

    set_alarm(1.0,0.0,"reset_room");
}
