/* Tantallon coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_OUTSIDE;

object draco, kapak1, kapak2;

#include RND_MEET

reset_tantallon_room()
{
    if (draco)
    	return;
    draco = RANDOM_MEET(DRACOS);/*clone_object(MON + "draconian");*/
    if (draco->query_prop(OBJ_I_COLORABLE))
	draco->set_color("red");
    draco->set_random_move(30);
    draco->move_living("xxx", TO);

    if(!objectp(kapak1))
        {
         kapak1 = clone_object("/d/Krynn/std/kapak");
         kapak1->set_color("red");
         KAPAK_COIN1->move(kapak1);
         KAPAK_COIN2->move(kapak1);
         kapak1->move(TO);
    }

    if(!objectp(kapak2))
        {
         kapak2 = clone_object("/d/Krynn/std/kapak");
         kapak2->set_color("red");
         KAPAK_COIN1->move(kapak2);
         KAPAK_COIN2->move(kapak2);
         kapak2->move(TO);
    }
}

create_tantallon_room()
{
    set_short("On path");
    set_long(BS(
    	"You are standing on a twisty little path. You can follow it both " +
	"east and south. The evil is rather strong in the air and it seems " +
   "to come from south. There is a tent west from here and another " +
	"one stands to the north.", SL));

    add_item("path",
    	"It looks well used.\n");
    add_item("tent",
    	"Which tent do you mean, the north tent or the west tent?\n");
    add_item("west tent", BS(
    	"It's a small grey tent. You can hear some noise from it. There is " +
	"a sign hanging on it. You see no entrance to it.", SL));
    add_item("north tent", BS(
    	"It's a small grey tent. There isn't a sound to be heard from it. " +
    	"You can't enter it from this side.", SL));
    add_item("sign",
    	"It's a small sign made out of wood with some words painted on it.\n");
    add_item("words",
    	"They look readable.\n");

    add_cmd_item("sign", "read", "You read: My home is my castle.\n");

    add_exit(TDIR + "city8", "south", 0);
    add_exit(TDIR + "city6", "east", 0);

    reset_tantallon_room();
}
