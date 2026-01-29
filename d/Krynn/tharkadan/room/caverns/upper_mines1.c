#include "/d/Krynn/common/defs.h"
#include "../../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

inherit CAVERNS_BASE;
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs(({"cave",}));

void
reset_tharkadan_room()
{
    set_searched(0);
}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(CAVERNS + "lava_vent6","southwest","@@enter_vent");
    add_exit(CAVERNS + "upper_mines2","northwest",0);
    add_exit(CAVERNS + "upper_mines14","southeast",0);

    add_prop(ROOM_S_DARK_LONG, "A lightless tunnel. Without a light " +
          "source it is too dark to see in here.\n"); 
    add_prop(ROOM_S_DARK_MSG, "It is too dark to"); 
    add_prop(ROOM_I_LIGHT, DARKNESS_PASSIVE);

    add_item(({"vent","lava vent","ancient lava vent"}),
        "To your southwest an ancient lava vent opens, leading up out " +
        "of the mines.\n");
    add_item(({"tunnel","excavated tunnel","mines", "ores","minerals"}),
        "You stand within an excavated tunnel, mined of valuable ores " +
        "and minerals with a skill that can only be associated with " +
        "one of the mountain dwarf clans.\n");
    add_item(({"dormant volcano","volcano"}),
        "You stand within the depths of a dormant volcano, now " +
        "seemingly home to a clan of industrious dwarves who now mine " +
        "the rich veins that run through its walls.\n");

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs), ONE_OF(herbs) }), ({ "vent","ground" }), 3);

    reset_tharkadan_room();
}

string
short_descr()
{
    return "an excavated tunnel, deep within a dormant volcano";
}

string
long_descr()
{
    return "You stand within an excavated tunnel deep within the depths " +
        "of a dormant volcano. Expertly carved out you have little " +
        "doubt this was the work of the master subterranean miners, " +
        "the dwarves. The tunnel continues here to your southeast and " +
        "northwest, while to your southwest an ancient lava vent leads " +
        "upwards out of the mines.\n";
}

int
enter_vent()
{
   write("You step out of the dwarven mines and into an ancient lava " +
       "vent leading up...\n");
   return 0;
}