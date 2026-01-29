/* Tantallon coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_OUTSIDE;

object baaz1, kapak1;

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
}

create_tantallon_room()
{
    set_short("Big crossing");
    set_long(BS(
	"You are at a big crossing. Not big in number of exits but still you " +
    	"sense that something big is related with it. There is a bridge east " +
    	"from here crossing a river and south you see a high tent. There is " +
	"a small path going north beside the river too as well as a small " +
	"road leading west into the heart of Tantallon." +
	"", SL));

    add_item(({"tent", "south tent","high tent"}), BS(
    	"It's a grey tent and it's very high. High enough for a giant to " +
    	"enter it. The tent smells of beer. There is a sign on it.",SL));
    add_item("path",
    	"It leads off north besides the river. It looks well used.\n");
    add_item("road",
    	"It leads off west. It's made out of small stones.\n");
    add_item(({"stone","stones"}), BS(
    	"The stones are small and round but they stick to the ground so you " +
    	"can't pick them up.", SL));
    add_item("bridge",
    	"It's an old fashioned stone bridge, it looks quite safe.\n");
    add_item("river", BS(
    	"The river runs from north to south. The only way to cross it is " +
    	"walking that bridge.", SL));
    add_item(({"city","village","Tantallon","tantallon"}), BS(
    	"There is not much to see from here, why not enter it and get a " +
    	"closer look.", SL));
    add_item("sign",
        "It's a big wooden sign with some words painted on it.\n");
    add_item("words",
        "They look readable.\n");

    add_cmd_item("sign", "read", "You read: Giants only\n");

    add_exit(TDIR + "city7", "north", 0);
    add_exit(TDIR + "city9", "west", 0);
    add_exit(TDIR + "bridgee", "east", 0);
    add_exit(TDIR + "tent5", "south", 0);

    reset_tantallon_room();
}
