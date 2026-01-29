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
       "To your north is the grassy riverbank of the Vingaard River, while " +
       "to your south you can just make out the barren coastline of Estwilde.\n");
    add_item(({"estuary","river","vingaard river","mouth of estuary","riverbank"}),
       "You are upon the longest river in Krynn, the Vingaard River. To your " +
       "southwest you can make out the port city of Kalaman.\n");
    add_item(({"port","port city","kalaman","lights","breakwalls","southern banks",
       "harbour"}),
       "The port city of Kalaman rises in the distance. You can make out the " +
       "protective breakwalls of the harbour along the southern banks.\n");


    add_row_exit(CROOM + "1b", "south", 0, 1);
    add_row_exit(CROOM + "2c", "east", 0, 1);
    add_row_exit(CROOM + "2a", "west", "@@sail_into_kalaman");


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
sail_into_kalaman()
{
    write("Great chains have been strung up between the breakwalls of Kalaman and the northern bank " +
      "of Solamnia, blocking any passage down the Vingaard River.\n");
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
    return "the Vingaard River, in sight of the port city of Kalaman";
}
 
string
long_descr()
{
    return "You find yourself upon the Vingaard River, close to the banks of " +
           "Solamnia. This river is the lifeblood of Solamnia, allowing merchants " +
           "to travel from the port city of Kalaman to the far off Vingaard Keep. " +
           "At the moment it is calm, allowing for easy sailing. To your southwest " +
           "you can make out the lights of the port city of Kalaman.\n";

}