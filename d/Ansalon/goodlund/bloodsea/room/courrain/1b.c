#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include <stdproperties.h>
#include <macros.h>

inherit COURRAIN_OUT;

void
reset_courrain_room()
{
    return;
}

create_courrain_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");


    add_item(({"sea", "ocean","courrain ocean"}), 
       "You cannot see the Courrain Ocean from here.\n");
    add_item(({"coastline","estwilde","foothills","rugged foothills",
       "barren coastline","hills", "riverbanks","solamnia"}),
       "To your south is the barren coastline of Estwilde, a land of rugged " +
       "foothills, while to your north you can just make out the riverbanks of " +
       "Solamnia. To your southwest is the port city of " +
       "Kalaman.\n");
    add_item(({"river","vingaard river"}),
       "You find yourself upon the longest river in Krynn, the Vingaard River. " +
       "To your southwest is the port city of Kalaman.\n");
    add_item(({"steep banks","banks","bank"}),
       "The banks of the southern side of the Vingaard River are quite steep here.\n");
    add_item(({"port","port city","kalaman","lights","breakwalls","southern banks","harbour"}),
       "The port city of Kalaman rises in the distance. You can make out the " +
       "protective breakwalls of the harbour along the southern banks.\n");

    add_row_exit(CROOM + "1a", "west", "@@no_go");
    add_row_exit("/d/Ansalon/kalaman/room/dock3", "southwest", "@@sail_into_kalaman");
    add_row_exit(CROOM + "2b", "north", 0, 1);
    add_row_exit(CROOM + "1c", "east", 0, 1);




    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    reset_courrain_room();

}

int
no_go()
{
    write("Great chains have been strung up between the breakwalls of Kalaman and the " +
      "northern bank of Solamnia, blocking any passage down the Vingaard River.\n");
    return 1;
}

int
sail_into_kalaman()
{
    write("\n\nYou sail southwest towards the harbour at Kalaman...\n\n\n");
    return 0;
}

void
set_sink_path(string sp)
{
    sink_path = "/d/Ansalon/balifor/flotsam/room/bottom_of_bay";
}

string
short_descr()
{
    return "the Vingaard River, in sight of the port city of Kalaman";
}
 
string
long_descr()
{
    return "You find yourself upon the Vingaard River, close to the banks of " +
           "Estwilde. This river is the lifeblood of Solamnia, allowing merchants " +
           "to travel from the port city of Kalaman to the far off Vingaard Keep. " +
           "At the moment it is calm, allowing for easy sailing. To your southwest " +
           "you can make out the lights of the port city of Kalaman.\n";

}