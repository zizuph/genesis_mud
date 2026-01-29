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
       "To your northwest opens up the vast Courrain Ocean, a sea " +
       "that borders all of eastern Ansalon. Few have ventured " +
       "from the sight of land when sailing this body of water, and " +
       "of those who have, none have returned.\n");
    add_item(({"nordmaar","coastline","estwilde","barren coastline",
       "border"}),
       "To your southeast runs a barren coastline that marks the " +
       "border between Estwilde and Nordmaar, the kingdom of the " +
       "horse barbarians.\n");
    add_item(({"tors","tor","skeletal tors","dragon's graveyard",
       "graveyard","dragons graveyard","hills"}),
       "Looking far out onto the hilly mainland, you see skeletal tors " +
       "rise. They resemble the bones of a great beast, and is probably " +
       "why sailors call this area Dragon's Graveyard... probably, that is! " +
       "Many believe this is the final resting place of a number of great " +
       "wyrms who died in a mighty battle, and that great riches are buried " +
       "with them.\n");

    add_row_exit(CROOM + "8j", "north", 0, 1);
    add_row_exit(CROOM + "6i", "southwest", 0, 1);
    add_row_exit(CROOM + "7i", "west", 0, 1);


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
    return "along the barren coastline bordering Nordmaar and Estwilde";
}
 
string
long_descr()
{
    return "You are close to the barren coastline that borders the lands of " +
       "Estwilde and Nordmaar.  In the distance, skeletal tors rise from the ground, " +
       "like the ribs of a giant creature once buried here... hence why these hills " +
       "are referred to as the Dragon's Graveyard. To your " +
       "northwest stretches the vast Courrain Ocean.\n";
}