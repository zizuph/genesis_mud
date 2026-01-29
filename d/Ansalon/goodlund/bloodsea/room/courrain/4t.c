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
       "To your north opens up the vast Courrain Ocean, a sea " +
       "that borders all of eastern Ansalon. Few have ventured far " +
       "from the sight of land when sailing this body of water, and " +
       "of those who have, none have returned.\n");
    add_item(({"green sea","deep green sea","straights","miremier",
       "miremier straights","marsh","tidal marsh"}),
       "You float within the tidal marsh of the Miremier " +
       "Straights, a deep green sea that stretches along Kern peninsula " +
       "and across to Nordmaar.\n");
    add_item(({"peninsula","kern","pines","kern peninsula", "trees",
               "ferns","endscape woods","woods","forest"}),
       "To the southeast is a peninsula covered with hardy pines and " +
       "exotic ferns, making up what is known as the Endscape " +
       "Woods. This forest makes up the most northeastern " +
       "part of the ogre empire of Kern.\n");
    add_item(({"nordmaar","kingdom","kingdom of nordmaar","coastline"}),
       "To your west you can make out the rugged coastline of " +
       "Nordmaar, the home of the horse barbarians.\n");

    add_row_exit(CROOM + "5t", "north", 0, 1);
    add_row_exit(CROOM + "4s", "west", 0, 1);
    add_row_exit(CROOM + "4u", "east", 0, 1);
    add_row_exit(CROOM + "3t", "south", 0, 1);



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
    return "Miremier Straights, running between the peninsula of Kern and Nordmaar";
}
 
string
long_descr()
{
    return "You are in the deep green tidal marshes " +
       "of the Miremier Straights. To the southeast rises the peninsula of " +
       "Kern, where hardy pines and exotic ferns grow in abundance. To your " +
       "west you can also make out land, the kingdom of Nordmaar. Far to your " +
       "north the straights open up to the vast Courrain Ocean.\n";
}