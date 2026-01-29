#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include <stdproperties.h>
#include <macros.h>

inherit COURRAIN_OUT;

object captain, sailor1, sailor2, sailor3, sailor4, ship;


void
reset_courrain_room()
{
     object boat_in;

     if (!objectp(ship)) 
     {
          ship = clone_object(BOBJ +"ghost_ship");
          ship->move(this_object());
     }

     if(!present(ship, TO))
     {
          ship = clone_object(BOBJ +"ghost_ship");
          ship->move(this_object());
     }

     if (!objectp(boat_in = ship->query_boat_in())) 
     {
         ship->config_boat_inside();
         boat_in = ship->query_boat_in();
     }

     if (!objectp(sailor1)) 
     {
         sailor1 = clone_object(BNPC + "ghost_gdwarf");
         sailor1->move_living("into the ghost ship", boat_in);
         sailor1->arm_me();
     }

     if (!objectp(sailor2)) 
     {
         sailor2 = clone_object(BNPC + "ghost_gdwarf");
         sailor2->move_living("into the ghost ship", boat_in);
         sailor2->arm_me();
     }

     if (!objectp(sailor3)) 
     {
         sailor3 = clone_object(BNPC + "ghost_gdwarf");
         sailor3->move_living("into the ghost ship", boat_in);
         sailor3->arm_me();
     }

     if (!objectp(sailor4)) 
     {
         sailor4 = clone_object(BNPC + "ghost_gdwarf");
         sailor4->move_living("into the ghost ship", boat_in);
         sailor4->arm_me();
     }


     if (!objectp(captain)) 
     {
         captain = clone_object(BNPC + "ghost_capt");
         captain->move_living("into the ghost ship", boat_in);
         captain->arm_me();
         boat_in->set_owner(captain); 
     }
}

create_courrain_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");


    add_item(({"water", "sea", "ocean","courrain ocean"}), 
       "Expanding out before you is the vast Courrain Ocean, a sea " +
       "that borders all of eastern Ansalon. Few have ventured far " +
       "from the sight of land when sailing this body of water, and " +
       "of those who have, none have returned.\n");

    add_row_exit(CROOM + "8u", "west", 0, 1);
    add_row_exit(CROOM + "9v", "north", 0, 1);
    add_row_exit(CROOM + "8w", "east", 0, 1);
    add_row_exit(CROOM + "7v", "south", 0, 1);


    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    reset_courrain_room();

}

int
no_go()
{
    write("You decided not to sail in that direction, as the waters are " +
      "uncharted. Rumour has it that those who do sail too far into the " +
      "Courrain Ocean are never seen of again!\n");
    return 1;
}

int
no_go_saifhum()
{
    write("A great reef surrounds the northern part of the island of Saifhum. " +
          "You will have to find another way to sail to it.\n");
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
    return courrain_short();
}
 
string
long_descr()
{
    return courrain_desc()+ "\n";
}