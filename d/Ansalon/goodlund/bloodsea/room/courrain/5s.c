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
       "Nordmaar, the home of the horse barbarians. Here once stood the " +
       "port town of Jennison, however it has recently been destroyed " +
       "by red dragons.\n");
    add_item(({"jennison","smoke","fire","blaze","buildings","flame","flames","town"}),
       "Smoke billows up from what remains of the small port of Jennison. " +
       "Most of the buildings have been reduced to ash or charred stone, " +
       "while those that are still standing are being consumed by flame.\n");
    add_item(({"port","small port","docks","ruins","ruined docks","dock"}),
       "The docks of Jennison are ruined to the point where no ship could " +
       "land near them... however a strong swimmer could probably swim to the " +
       "docks and make landfall from there.\n");
    add_item(({"specks","small specks","dragons","red dragons"}),
       "Above the port of Jennison soars red dragons, the cause of the towns demise.\n");

    add_row_exit(CROOM + "6s", "north", 0, 1);
    add_row_exit(CROOM + "4s", "south", 0, 1);
    add_row_exit(CROOM + "6r", "northwest", 0, 1);
    add_row_exit(CROOM + "5t", "east", 0, 1);

    add_cmd_item(({"docks","to docks","to the docks","to the dock","to dock","dock"}),
        "swim","A strong undercurrent pulls you back away from the docks. Try again " +
        "at a later date!\n");

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
    return "ruined docks of Jennison along the coastline of Nordmaar";
}
 
string
long_descr()
{
    return "You find yourself close to the coastline of Nordmaar at the ruined docks " +
       "of the port town of Jennison. Of the buildings you can see, all are either " +
       "little more than charred ruins or are currently in the process of becoming " +
       "charred ruins, being totally engulfed in roaring flames.  Above the town " +
       "you see dragons circling... obviously the cause of the demise of Jennison.\n";
}