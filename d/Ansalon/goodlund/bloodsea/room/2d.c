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

    add_item(({"mithas","isle","cliffs","great cliffs","cliff", "mainland"}),
               "To the north and south rise great cliffs, enclosing this bay. " +
               "To your east spreads the mainland of Mithas, where you can " +
               "just make out the city of Nethosak.\n"); 
    add_item(({"bay","horned bay","bloodsea","blood sea"}), "The Horned Bay "+
               "stretches further out to the northwest where it meets the Bloodsea.\n");
    add_item(({"water", "waters", "sea"}), "The water within the Bloodsea has "+
               "a strange and reddish colour. Rumour has it that the colour "+
               "is the result of the blood of many victims who lost their "+
               "lives during Krynn's most terrible hour, though it "+
               "could be the clay stirred up from the sea bottom by the "+
               "maelstrom.\n");
    add_item(({"village", "nethosak","city"}), "The great Imperial "+
             "city of Nethosak, home of the minotaurs of Ansalon, can be seen "+
             "to the east.\n");

    add_row_exit(BROOM + "1d", "east", 0, 1);
    add_row_exit(BROOM + "3d", "west", 0, 1);
    add_row_exit(BROOM + "2e", "north", 0, 1);
    add_row_exit(BROOM + "2c", "south", 0, 1);

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    reset_bloodsea_room();

}

void
set_sink_path(string sp)
{
    sink_path = "/d/Ansalon/balifor/flotsam/room/bottom_of_bay";
}

string
short_descr()
{
    return "Sheltered waters of Horned Bay, Mithas";
}
 
string
long_descr()
{
    return "You are surrounded by the waters of Horned Bay. " +
    "To your north and south the bay is mostly sheltered by the " +
    "great cliffs of the isle of Mithas. " +bloodsea_desc()+
    "\n";
}