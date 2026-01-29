/* Tantallon coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_OUTSIDE;

object kapak1, kapak2;

reset_tantallon_room()
{

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
    	"You are standing on a twisty little path. You can follow it north " +
	"towards some mountains or west closer the heart of Tantallon. There " +
	"are two tents here, one south and one east.", SL));

    add_item(({"mountain", "mountains"}), BS(
    	"The mountains are very high. The look very dark and unfriendly. On " +
	"some of the higher peaks you can see something white, snow "  +
	"perhaps?", SL));
    add_item("path",
    	"It looks well used.\n");
    add_item("tent",
    	"Which tent do you mean, the south tent or the east tent?\n");
    add_item("east tent", BS(
    	"It's a small grey tent. You can hear some noise from it. There is " +
	"a sign hanging on it.", SL));
    add_item("south tent", BS(
    	"It looks like if this tent is the biggest one in Tantallon. It's " +
    "coloured in deep black and you feel something evil present " +
	"inside it.",SL));
    add_item("sign",
    	"It's a small sign made out of wood with some words painted on it.\n");
    add_item("words",
    	"They look readable.\n");

    add_cmd_item("sign", "read", "You read: Home sweet home.\n");

    add_exit(TDIR + "city3", "north", 0);
    add_exit(TDIR + "city5", "west", 0);
    add_exit(TDIR + "tent7", "east", 0);

    reset_tantallon_room();
}
