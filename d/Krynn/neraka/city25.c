/* Tantallon coded by Nick */
/* Additional draconians added by Arman 25 Oct 2015 */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_OUTSIDE;
#include <macros.h>

object draco, baaz1, baaz2;
int key;

#include RND_MEET

reset_tantallon_room()
{
    key = 0;
    if (draco)
    	return;
    draco = RANDOM_MEET(DRACOS);/*clone_object(MON + "draconian");*/
    if (draco->query_prop(OBJ_I_COLORABLE))
	draco->set_color("red");
    draco->set_random_move(30);
    BAAZ_COIN1->move(draco);
    BAAZ_COIN2->move(draco);
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
    set_short("Guards meeting place");
    set_long(BS(
    	"This seems to be a meeting place for the guards of Tantallon. There " +
	"are some chairs and a table here. The ground once was covered with " +
	"grass but now it has turned into mud on most places. You can go " +
	"neither south nor east since the river is blocking the exits.", SL));

    add_item("table", BS(
    	"It's made out of wood and looks quite heavy. It must have been here " +
    	"some time because you can see deep holes in the ground where the " +
    	"legs of the table stands.", SL));
    add_item("holes",
    	"You see nothing special about them.\n");
    add_item(({"chairs", "chair"}), BS(
    	"The chairs are all black and made out of wood. They seem to have " +
    	"been used a lot.", SL));
    add_item("river",
    	"It comes from north and turns west here. The water looks cold.\n");
    add_item(({"ground", "mud", "grass"}), BS(
    	"The mud is covering almost everything, some grass is peeking up " +
    	"under the table but that's all.", SL));

    add_search(({"mud","grass","ground"}), 5, OBJ + "d_city20_key", -1);
    add_cmd_item(({"mud", "grass", "ground", "in"}), "dig", "@@dig");

    add_exit(TDIR + "city23", "north", 0);
    add_exit(TDIR + "city24", "west", 0);

    set_alarm(1.0,0.0,"reset_room");
}


dig()
{
    object ob;

    seteuid(getuid(TO));

    if (key < 1)
    {
	key++;
	ob = clone_object(OBJ + "d_city20_key");
	if (ob->move(TP))
	{
	    write("You find a key in the mud.\n");
	    ob->move(TO);
	} else
	    write("You find a key in the mud and pick it up.\n");
	say(QCTNAME(TP) + " digs in the mud and finds a key.\n");
	return 1;
    }
    write("You find nothing but manage to get mud on your hands.\n");
    say(QCTNAME(TP) + " dig in the mud and get dirty hands.\n");
    return 1;
}

	
