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


    add_item(({"water", "sea", "ocean","courrain ocean"}), 
       "To your north and east opens up the vast Courrain Ocean, a sea " +
       "that borders all of eastern Ansalon. Few have ventured " +
       "from the sight of land when sailing this body of water, and " +
       "of those who have, none have returned.\n");
    add_item(({"nordmaar","kingdom","kingdom of nordmaar","coastline",
               "beach","last coast"}),
       "To your west you can make out the rugged coastline of " +
       "Nordmaar, the home of the horse barbarians.\n");

    add_row_exit(CROOM + "8r", "north", 0, 1);
    add_row_exit(CROOM + "6r", "south", 0, 1);
    add_row_exit(CROOM + "7s", "east", 0, 1);


    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    reset_courrain_room();

}

int
no_go()
{
    write("The Miremier Straights get dangerously shallow in that direction. " +
          "You cannot sail any further for risk of running aground.\n");
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
    return "along the rugged coastline of Nordmaar";
}
 
string
long_descr()
{
    return "You are close to the rugged coastline of Nordmaar, along a stretch of " +
       "beach referred to as the 'Last Coast'. To your " +
       "north and east stretches the vast Courrain Ocean.\n";
}