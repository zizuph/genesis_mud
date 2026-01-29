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
    	"You are standing on a small path. Southeast you can see a large " +
	"opening. South is a dark big wall. You feel much evil in the air. " +
	"There are two tents here, one west from here and a bigger one " +
	"east.", SL));

    add_item("path",
    	"It looks well used.\n");
    add_item("tent",
    	"Which tent do you mean, the west tent or the east tent?\n");
    add_item("west tent", BS(
    	"It's a small grey tent. You can hear some noise from it. There is " +
	"a sign hanging on it.", SL));
    add_item("east tent", BS(
    	"It looks like if this tent is the biggest one in Tantallon. It's " +
	"coloured in deep black and you feel something evil present in it. " +
	"You can't enter it from here.", SL));
    add_item("wall", BS(
    	"It's a black wall made out of stone. The wall is so big that the it " +
    	"seldom lets the sun shine down here. The wall seems to radiate " +
	"evil.",SL));
    add_item("sign",
    	"It's a big sign hanging over the entrance with some words on it.\n");
    add_item("words",
    	"They look readable.\n");

    add_cmd_item("sign", "read", "You read: THE TEMPLAR BAR\n");

    add_exit(TDIR + "city5", "north", 0);
    add_exit(TDIR + "tent9", "west", 0);
    add_exit(TDIR + "city11", "southeast", 0);

    reset_tantallon_room();
}
