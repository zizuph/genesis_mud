/* Tantallon coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>
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
    set_short("By the river");
    set_long(BS(
        "You are standing by the river. North a high tent is blocking the " +
	"way. West you can see a rather large opening, it appears to be " +
	"the center of Tantallon and a lot of people are running there. Maybe " +
	"they come here because of the well?", SL));
 
    add_item(({"tent", "north tent", "high tent"}), BS(
    	"It's a grey tent and it's very high. High enough for a giant to " +
    	"enter it. The tent smells of beer.", SL));
    add_item("river",
    	"It runs from north to south.\n");
    add_item(({"opening", "people"}), BS(
        "You can't get a good look. Perhaps your eyes aren't as good as "+
    	"you think they are?", SL));
    add_item("well", "It's the city well.\n");

    add_exit(TDIR + "city16", "west", 0);
    add_exit(TDIR + "city20", "south", 0);

    reset_tantallon_room();
}

init()
{
    ::init();
    ADA("drink");
}


drink(str)
{
    object ob;

    if ((str == "well") || (str == "from well") ||
	(str == "water") || (str == "water from well"))
    {
	if (TP->drink_soft(TP->drink_max() / 16,0))
	  {
	      write("You drink from the well and feel refreshed.\n");
	      say(QCTNAME(TP) + " drinks from the well.\n");
              TP->heal_hp(20);
	      if (ob = present("tour2", TP))
		ob->set_arr("well");
	  }
	else
	  write("Hmm, you are not thirsty at all at the moment.\n");
	return 1;
    }
}

