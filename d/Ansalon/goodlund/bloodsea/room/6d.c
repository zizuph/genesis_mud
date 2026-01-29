#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include <stdproperties.h>
#include <macros.h>

inherit BLOODSEA_OUT;

void
reset_bloodsea_room()
{
    return;
}

create_bloodsea_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"isle","island","mithas","isle of mithas","coastline"}), 
               "To your east is the coastline of the isle of Mithas, " +
               "an island ruled by the Bloodsea minotaurs.\n");
    add_item(({"volcano","volcanoes","four volcanoes","four great volcanoes"}),
               "Dominating the island of Mithas are four great volcanoes. " +
               "While continuously smoking, they are dormant... like a sleeping " +
               "dragon. The inhabitants of this isle treat them with cautious " +
               "respect.\n");
    add_item(({"rocks","dangerous rocks"}), "To your south you notice rocks just " +
               "below the surface of the water. You realise that sailing south would " +
               "be suicidal!\n");
    add_item(({"water", "sea"}), "The water within the Bloodsea has "+
               "a strange and reddish colour. Rumour has it that the colour "+
               "is the result of the blood of many victims who lost their "+
               "lives during Krynn's most terrible hour, though it "+
               "could be the clay stirred up from the sea bottom by the "+
               "maelstrom.\n");

    add_row_exit(BROOM + "7d", "west", 0, 1);
    add_row_exit(BROOM + "6e", "north", 0, 1);
    add_row_exit(BROOM + "7c", "southwest", 0, 1);
    add_row_exit(BROOM + "xx", "south", "@@no_go");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    reset_bloodsea_room();

}

int
no_go()
{
    write("As you begin sailing south, you notice dangerous rocks just below " +
      "the surface of the water in front of you. You decide it would be better " +
      "to sail in a different direction.\n");
    say(QCTNAME(TP)+ " starts sailing south, however notices dangerous rocks " +
      "just below the surface of the water and changes course at the last " +
      "minute.\n");
    return 1;
}


void
set_sink_path(string sp)
{
    sink_path = "/d/Ansalon/balifor/flotsam/room/bottom_of_bay";
}

string
short_descr()
{
    return "Along the coastline of the isle of Mithas";
}
 
string
long_descr()
{
    return "To your east is the coastline of the isle of Mithas, a fiery " +
    "island whose scrub plains lie in the shadow of four great volcanoes. " +
    bloodsea_desc()+ "\n";
}