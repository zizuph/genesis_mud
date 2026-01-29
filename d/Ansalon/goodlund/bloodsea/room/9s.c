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

    add_item(({"karthay","coastline", "isle of karthay","isle","island"}), 
               "You are near the rocky coastline of the isle of Karthay. " +
               "You notice atop the cliffs that rise up here is the ruins " +
               "of a great light tower.\n");
    add_item(({"tower","ruins","light tower","great light tower","winston's tower"}),
               "This is the ruins of Winston's tower, a 130-foot-tall monolith " +
               "that once served as a beacon for travelers across Istar. It is " +
               "now abandoned and rumoured to be cursed.\n");
    add_item(({"cliffs","steep cliffs"}), "Here the coastline of Karthay is nothing " +
               "but steep cliffs, an impossible location for ships to land without " +
               "risk of being battered against their unforgiving rocky face.\n");
    add_item(({"water", "sea"}), "The water within the Bloodsea has "+
               "a strange and reddish colour. Rumour has it that the colour "+
               "is the result of the blood of many victims who lost their "+
               "lives during Krynn's most terrible hour, though it "+
               "could be the clay stirred up from the sea bottom by the "+
               "maelstrom.\n");

    add_row_exit(CROOM + "6zg", "west", 0, 1);
    add_row_exit(CROOM + "7zg", "northwest", 0, 1);
    add_row_exit(BROOM + "8r", "southeast", 0, 1);
    add_row_exit(BROOM + "9r", "south", 0, 1);


    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    reset_bloodsea_room();

}

int
no_go()
{
    write("You try and sail in that direction, however the current and wind created by a " +
       "mighty storm agressively drives you back!\n");
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
    return bloodsea_short() + ", near the rocky coastline of Karthay";
}
 
string
long_descr()
{
    return "You are near the rocky coastline of the isle of Karthay. " +
        "The waters of the Bloodsea batter against steep cliffs that " +
        "rise here out of the water. Atop the cliff you notice the " +
        "ruins of a great light tower. "+ bloodsea_desc()+ "\n";
}