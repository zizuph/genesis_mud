#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include <money.h>

inherit FOREST_IN;
inherit "/lib/unique";

object hoopak, boots, money1, money2, scroll;

void
reset_flotsam_room()
{
    if(!P("hoopak", TO))
    {
	hoopak = clone_unique(FOBJ + "weapon/mag_hoopak", 5, "/d/Ansalon/goodlund/kendermore/obj/yew_hoopak");
	hoopak->move(TO);
    }
    if(!P("boots", TO))
    {
	boots = clone_object(FOBJ + "armour/mag_boots");
	boots->move(TO);
    }
    if(!objectp(money1))
    {
	money1 = MONEY_MAKE_CC(200);
	money1->move(TO);
    }

    if(!objectp(money2))
    {
	money2 = MONEY_MAKE_SC(20);
	money2->move(TO);
    }

    // 1% chance of spawning a scroll per reset
    if(!P("scroll", TO) && (random(100) == 1))
    {
	scroll = clone_object("/d/Krynn/common/scrolls/scare_scroll");
	scroll->move(TO);
    }
}

create_flotsam_room()
{
    set_short("In a damp, cold troll cave");
    set_long("@@long_descr");

    add_item("moss",
      "Greyish-green moss grows here sparsely due to the damp " +
      "conditions.\n");

    DARK;
    add_exit(FROOM + "under_bridge","out",0);
}

string
long_descr()
{
    return "You stand in a cold and damp cave that " +
    "has been burrowed into the side of a river bank. " +
    "Moss grows sparsely here, and a fetid smell reminds you " +
    "that you are in a troll's lair.\n";
}


