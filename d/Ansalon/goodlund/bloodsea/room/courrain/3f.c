#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include <stdproperties.h>
#include <macros.h>

inherit COURRAIN_OUT;

object ship, captain;

void
reset_courrain_room()
{
     object boat_in;

     if (!objectp(ship)) 
     {
          ship = clone_object(BOBJ +"fishing_boat");
          ship->move(this_object());
     }

     if (!objectp(boat_in = ship->query_boat_in())) 
     {
         ship->config_boat_inside();
         boat_in = ship->query_boat_in();
     }

     if (!objectp(captain)) 
     {
         captain = clone_object(BNPC + "fisherman");
         captain->move_living("into his ship", boat_in);
         captain->arm_me();
         captain->equip_me();
         boat_in->set_owner(captain); 
     }
}

create_courrain_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");


    add_item(({"sea", "ocean","courrain ocean"}), 
       "You cannot see the Courrain Ocean from here.\n");
    add_item(({"coastline","estwilde","foothills","rugged foothills",
       "barren coastline","hills", "riverbanks","solamnia"}),
       "To your east is the barren coastline of Estwilde, a land of rugged " +
       "foothills, while to your west you can just make out the riverbanks of " +
       "Solamnia.\n");
    add_item(({"river","vingaard river"}),
       "You find yourself upon the longest " +
       "river in Krynn, the Vingaard River. To your north it appears to widen.\n");
    add_item(({"steep banks","banks","bank"}),
       "The banks of the eastern bank of the Vingaard River are quite steep here.\n");


    add_row_exit(CROOM + "3e", "west", 0, 1);
    add_row_exit(CROOM + "4f", "north", 0, 1);
    add_row_exit(CROOM + "2e", "southwest", 0, 1);



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
    return "the Vingaard River, near the steep banks of Estwilde";
}
 
string
long_descr()
{
    return "You find yourself upon the Vingaard River, " +
       "close to the steep banks that mark the barren lands " +
       "of Estwilde. To your west " +
       "you can just make out the green riverbank of Solamnia.\n";

}