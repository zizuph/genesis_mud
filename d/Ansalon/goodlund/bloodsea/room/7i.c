#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include <stdproperties.h>
#include <macros.h>

inherit BLOODSEA_OUT;

object captain, sailor1, sailor2, sailor3, sailor4, ship;

void
reset_bloodsea_room()
{
     object boat_in;

     if (!objectp(ship)) 
     {
          ship = clone_object(BOBJ +"pirate_ship1");
          ship->move(this_object());
     }

     if(!present(ship, TO))
     {
          ship = clone_object(BOBJ +"pirate_ship1");
          ship->move(this_object());
     }

     if (!objectp(boat_in = ship->query_boat_in())) 
     {
         ship->config_boat_inside();
         boat_in = ship->query_boat_in();
     }

     if (!objectp(captain)) 
     {
         captain = clone_object(BNPC + "drenaol");
         captain->move_living("into his cutter", boat_in);
         captain->arm_me();
         boat_in->set_owner(captain); 
     }

     if (!objectp(sailor1)) 
     {
         sailor1 = clone_object(BNPC + "pirate");
         sailor1->move_living("into his cutter", boat_in);
         sailor1->arm_me();
     }

     if (!objectp(sailor2)) 
     {
         sailor2 = clone_object(BNPC + "pirate");
         sailor2->move_living("into his cutter", boat_in);
         sailor2->arm_me();
     }

     if (!objectp(sailor3)) 
     {
         sailor3 = clone_object(BNPC + "pirate");
         sailor3->move_living("in his schooner", boat_in);
         sailor3->arm_me();
     }

     if (!objectp(sailor4)) 
     {
         sailor4 = clone_object(BNPC + "minotaur");
         sailor4->move_living("in his schooner", boat_in);
         sailor4->arm_me();
     }
}

create_bloodsea_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"water", "sea"}), "The water within the Bloodsea has "+
               "a strange and reddish colour. Rumour has it that the colour "+
               "is the result of the blood of many victims who lost their "+
               "lives during Krynn's most terrible hour, though it "+
               "could be the clay stirred up from the sea bottom by the "+
               "maelstrom.\n");

    add_row_exit(BROOM + "8i", "west", 0, 1);
    add_row_exit(BROOM + "7j", "north", 0, 1);
    add_row_exit(BROOM + "6i", "east", 0, 1);
    add_row_exit(BROOM + "7h", "south", 0, 1);


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
    return bloodsea_short();
}
 
string
long_descr()
{
    return bloodsea_desc()+ "\n";
}