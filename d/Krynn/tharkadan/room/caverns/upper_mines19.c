#include "/d/Krynn/common/defs.h"
#include "../../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

inherit CAVERNS_BASE;
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs(({"cave",}));
object dwarf1, dwarf2, dwarf3;

void
reset_tharkadan_room()
{
    if(!objectp(dwarf1))
    {
        dwarf1 = clone_object(LIVING + "theiwar_miner");
        dwarf1->move(TO, 1);
    }

    if(!objectp(dwarf2))
    {
        dwarf2 = clone_object(LIVING + "theiwar_axeman");
        dwarf2->move(TO, 1);
    }

    if(!objectp(dwarf3))
    {
        dwarf3 = clone_object(LIVING + "theiwar_axeman");
        dwarf3->move(TO, 1);
    }

    set_searched(0);
}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(CAVERNS + "upper_mines16","south", 0);
    add_exit(CAVERNS + "upper_mines20","north","@@passage_blocked_north");

    add_prop(ROOM_S_DARK_LONG, "A lightless tunnel. Without a light " +
          "source it is too dark to see in here.\n"); 
    add_prop(ROOM_S_DARK_MSG, "It is too dark to"); 
    add_prop(ROOM_I_LIGHT, DARKNESS_PASSIVE);

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
        "the dwarves. The tunnel continues here to your north and " +
        "south.\n";
}

int
passage_blocked_north()
{
     if(objectp(dwarf3) && CAN_SEE(dwarf3, TP))
     {
        dwarf3->command("emote blocks the tunnel, preventing passage " +
            "to your north.");
        dwarf3->command("scowl " + TP->query_real_name());
        return 1;
     }

     if(objectp(dwarf1) && CAN_SEE(dwarf1, TP))
     {
        dwarf1->command("emote blocks the tunnel, preventing passage " +
            "to your north.");
        dwarf1->command("scowl " + TP->query_real_name());
        return 1;
     }

     if(objectp(dwarf2) && CAN_SEE(dwarf2, TP))
     {
        dwarf2->command("emote blocks the tunnel, preventing passage " +
            "to your north.");
        dwarf2->command("growl " + TP->query_real_name());
        return 1;
     }

     return 0;
}
