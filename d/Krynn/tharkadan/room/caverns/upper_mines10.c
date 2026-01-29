#include "/d/Krynn/common/defs.h"
#include "../../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

inherit CAVERNS_BASE;
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs(({"cave",}));
object dwarf1, dwarf2;

void
reset_tharkadan_room()
{

    if(!objectp(dwarf1))
    {
        dwarf1 = clone_object(LIVING + "theiwar_savant");
        dwarf1->move(TO, 1);
    }

    if(!objectp(dwarf2))
    {
        dwarf2 = clone_object(LIVING + "theiwar_savant");
        dwarf2->move(TO, 1);
    }

    set_searched(0);
}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(CAVERNS + "upper_mines11","north","@@passage_blocked");
    add_exit(CAVERNS + "upper_mines8","southeast",0);

    add_prop(ROOM_S_DARK_LONG, "A lightless tunnel. Without a light " +
          "source it is too dark to see in here.\n"); 
    add_prop(ROOM_S_DARK_MSG, "It is too dark to"); 
    add_prop(ROOM_I_LIGHT, DARKNESS_PASSIVE);

    add_item(({"tunnel","excavated tunnel","mines", "ores","minerals"}),
        "You stand within an excavated tunnel, mined of valuable ores " +
        "and minerals with a skill that can only be associated with " +
        "one of the mountain dwarf clans.\n");
    add_item(({"walls","wall","carvings","procession of dwarves",
        "dwarf carvings","disturbing carving","carving of devouring " +
        "darkness","devouring darkness"}), "The walls of the tunnel " +
        "here have clearly been worked for a purpose other than mining, " +
        "with carvings adorning both sides of the walls. The carvings " +
        "show a procession of dark dwarves walking with heads bowed " +
        "and bearing sacrificial gifts, moving in a line towards the " +
        "entrance of a shadowy portal to your north. Around the portal " +
        "entrance is carved a disturbing image that can only be " +
        "described as a devouring darkness.\n");
    add_item(({"portal","shadowy portal","entrance","portal entrance"}),
        "To your north the tunnel continues through a portal with " +
        "disturbing carvings around it. You notice it is unnaturally " +
        "dark in that direction.\n");
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
    return "an excavated tunnel leading to a shadowy portal";
}

string
long_descr()
{
    return "You stand within an excavated tunnel deep within the depths " +
        "of a dormant volcano. The walls of the tunnel here are more " +
        "refined, with carvings of a procession of dwarves - heads " +
        "bowed - walking towards a disturbing carving of a devouring " +
        "darkness that surrounds the entrance of a shadowy portal to " +
        "your north.\n";
}

int
passage_blocked()
{

     if(objectp(dwarf1) && CAN_SEE(dwarf1, TP))
     {
         dwarf1->command("emote blocks access to the shadowy portal, " +
             "preventing passage to your north.");
         dwarf1->command("scowl " + TP->query_real_name());
         return 1;
     }

     if(objectp(dwarf2) && CAN_SEE(dwarf2, TP))
     {
         dwarf1->command("emote blocks access to the shadowy portal, " +
             "preventing passage to your north.");
         dwarf1->command("scowl " + TP->query_real_name());
         return 1;
     }

     return 0;
}
