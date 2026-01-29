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
       "Far to your north opens up the vast Courrain Ocean, a sea " +
       "that borders all of eastern Ansalon. Few have ventured " +
       "from the sight of land when sailing this body of water, and " +
       "of those who have, none have returned.\n");
    add_item(({"green sea","deep green sea","straights","miremier",
       "miremier straights","marsh","tidal marsh"}),
       "You float within the tidal marsh of the Miremier " +
       "Straights, a deep green sea that stretches along Kern peninsula " +
       "and across to Nordmaar.\n");
    add_item(({"peninsula","kern","pines","kern peninsula", "trees",
               "ferns","endscape woods","woods","forest"}),
       "You cannot see the peninsula of Kern from here.\n");
    add_item(({"nordmaar","kingdom","kingdom of nordmaar","coastline"}),
       "To your west you can make out the rugged coastline of " +
       "Nordmaar, the home of the horse barbarians. Further north " +
       "along the coastline you can make out a small port.\n");
    add_item(({"port","small port","jennison","smoke","fire","blaze"}),
       "Along the coastline to your north you can just make out the small " +
       "Nordmaarian port of Jennison. Disturbingly, smoke billows up from " +
       "the port, and you notice small specks in the sky above it that look " +
       "suspiciously like dragons!\n");
    add_item(({"specks","small specks","dragons","red dragons"}),
       "From this distance it is hard to make out what flies above the port " +
       "of Jennison... they look suspiciously like red dragons!\n");

    add_row_exit(CROOM + "5s", "north", 0, 1);
    add_row_exit(CROOM + "3r", "southwest", 0, 1);
    add_row_exit(CROOM + "4t", "east", 0, 1);
    add_row_exit(CROOM + "3s", "south", 0, 1);


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
    return "Miremier Straights, along the coastline of Nordmaar";
}
 
string
long_descr()
{
    return "You are in the deep green tidal marshes " +
       "of the Miremier Straights, close to the rugged coastline of Nordmaar. "+
       "While largely a barren wasteland, you do notice further along the coastline " +
       "to your north a small port that seems to be ablaze! Far to your " +
       "northeast the straights open up to the vast Courrain Ocean.\n";
}