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

    add_item(({"bay","horned bay","bloodsea","blood sea"}), "The Horned Bay "+
               "opens out to the southeast, while to the west is the Bloodsea " +
               "of Istar.\n");
    add_item(({"water", "sea"}), "The water within the Bloodsea has "+
               "a strange and reddish colour. Rumour has it that the colour "+
               "is the result of the blood of many victims who lost their "+
               "lives during Krynn's most terrible hour, though it "+
               "could be the clay stirred up from the sea bottom by the "+
               "maelstrom.\n");

    add_row_exit(BROOM + "7i", "west", 0, 1);
    add_row_exit(BROOM + "6j", "north", 0, 1);
    add_row_exit(BROOM + "6h", "south", 0, 1);
    add_row_exit(BROOM + "5i", "east", 0, 1);

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
    return "near the entrance to Horned Bay of the isle of Mithas";
}
 
string
long_descr()
{
    return "You are at the entry of Horned Bay, where the Bloodsea meets " +
    "with the isle of Mithas. " +bloodsea_desc()+
    "\n";
}