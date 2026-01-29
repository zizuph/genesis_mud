#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include <stdproperties.h>
#include <macros.h>

inherit BLOODSEA_OUT;

object ship, captain;

void
reset_bloodsea_room()
{
     object boat_in;

     if (!objectp(ship)) 
     {
          ship = clone_object(BOBJ +"ship");
          ship->move(this_object());
     }

     if (!objectp(boat_in = ship->query_boat_in())) 
     {
         ship->config_boat_inside();
         boat_in = ship->query_boat_in();
     }

     if (!objectp(captain)) 
     {
         captain = clone_object(BNPC + "m_pirate");
         captain->move_living("into his ship", boat_in);
         captain->arm_me();
         captain->equip_me();
         boat_in->set_owner(captain); 
     }
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

    add_row_exit(BROOM + "2e", "east", 0, 1);
    add_row_exit(BROOM + "4e", "west", 0, 1);
    add_row_exit(BROOM + "3f", "north", 0, 1);
    add_row_exit(BROOM + "3d", "south", 0, 1);

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