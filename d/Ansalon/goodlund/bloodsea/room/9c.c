#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include <stdproperties.h>
#include <macros.h>

inherit BLOODSEA_OUT;

object captain, sailor1, sailor2, sailor3, sailor4, ship;
object drac1, drac2, drac3, drac4, drac5;

#define DRAC "/d/Krynn/solamn/splains/living/"


void
reset_bloodsea_room()
{
     object boat_in;

     if (!objectp(ship)) 
     {
          ship = clone_object(BOBJ +"warship");
          ship->move(this_object());
     }

     if(!present(ship, TO))
     {
          ship = clone_object(BOBJ +"warship");
          ship->move(this_object());
     }

     if (!objectp(boat_in = ship->query_boat_in())) 
     {
         ship->config_boat_inside();
         boat_in = ship->query_boat_in();
     }

     if (!objectp(sailor1)) 
     {
         sailor1 = clone_object(BNPC + "sailor");
         sailor1->move_living("into his warship", boat_in);
         sailor1->arm_me();
     }

     if (!objectp(sailor2)) 
     {
         sailor2 = clone_object(BNPC + "sailor");
         sailor2->move_living("into his warship", boat_in);
         sailor2->arm_me();
     }

     if (!objectp(sailor3)) 
     {
         sailor3 = clone_object(BNPC + "sailor");
         sailor3->move_living("in his warship", boat_in);
         sailor3->arm_me();
     }

     if (!objectp(sailor4)) 
     {
         sailor4 = clone_object(BNPC + "sailor");
         sailor4->move_living("in his warship", boat_in);
         sailor4->arm_me();
     }

     if (!objectp(drac1)) 
     {
         drac1 = clone_object(DRAC + "bozak");
         drac1->set_color("black");
         drac1->move_living("in his warship", boat_in);
     }

     if (!objectp(drac2)) 
     {
         drac2 = clone_object(DRAC + "sivak");
         drac2->set_color("black");
         drac2->move_living("in his warship", boat_in);
     }

     if (!objectp(drac3)) 
     {
         drac3 = clone_object(DRAC + "sivak");
         drac3->set_color("black");
         drac3->move_living("in his warship", boat_in);
     }

     if (!objectp(drac4)) 
     {
         drac4 = clone_object(DRAC + "sivak");
         drac4->set_color("black");
         drac4->move_living("in his warship", boat_in);
     }

     if (!objectp(drac5)) 
     {
         drac5 = clone_object(DRAC + "aurak");
         drac5->set_color("black");
         drac5->move_living("in his warship", boat_in);
     }

     if (!objectp(captain)) 
     {
         captain = clone_object(BNPC + "da_captain");
         captain->move_living("into his warship", boat_in);
         boat_in->set_owner(captain); 
     }
}

create_bloodsea_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"karthay","isle of karthay"}), "While not visible to the eye, you " +
               "know the isle of Karthay lies to the north of Mithas.\n");
    add_item(({"water", "sea"}), "The water within the Bloodsea has "+
               "a strange and reddish colour. Rumour has it that the colour "+
               "is the result of the blood of many victims who lost their "+
               "lives during Krynn's most terrible hour, though it "+
               "could be the clay stirred up from the sea bottom by the "+
               "maelstrom.\n");

    add_row_exit(BROOM + "xx", "west", "@@no_go");
    add_row_exit(BROOM + "9d", "north", 0, 1);
    add_row_exit(BROOM + "8c", "east", 0, 1);
    add_row_exit(BROOM + "9b", "south", 0, 1);


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
    return bloodsea_short();
}
 
string
long_descr()
{
    return bloodsea_desc()+ "\n";
}