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
       "Nordmaar, the home of the horse barbarians. Further south " +
       "along the coastline you can make out a small port.\n");
    add_item(({"port","small port","jennison","smoke","fire","blaze"}),
       "Along the coastline to your south you can just make out the small " +
       "Nordmaarian port of Jennison. Disturbingly, smoke billows up from " +
       "the port, and you notice small specks in the sky above it that look " +
       "suspiciously like dragons!\n");
    add_item(({"specks","small specks","dragons","red dragons"}),
       "From this distance it is hard to make out what flies above the port " +
       "of Jennison... they look suspiciously like red dragons!\n");

    add_row_exit(CROOM + "7r", "north", 0, 1);
    add_row_exit(CROOM + "5s", "southeast", 0, 1);
    add_row_exit(CROOM + "6s", "east", 0, 1);


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
       "beach referred to as the 'Last Coast'. "+
       "While this land is largely a barren wasteland, you do notice " +
       "to your south a small port that seems to be ablaze! To your " +
       "north and east open up to the vast Courrain Ocean.\n";
}