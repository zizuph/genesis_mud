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
    add_item(({"nordmaar","kingdom","kingdom of nordmaar","coastline",
               "jungle","foliage","cape of nordmaar","plants","plant life"}),
       "To your southeast you can make out the verdant coastline of " +
       "the Cape of Nordmaar. Its tropical climate and incredible humidity " +
       "has resulted in all types of strange plants growing here.\n");

    add_row_exit(CROOM + "13k", "north", 0, 1);
    add_row_exit(CROOM + "13l", "northeast", 0, 1);
    add_row_exit(CROOM + "12j", "west", 0, 1);
    add_row_exit(CROOM + "11k", "south", 0, 1);


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
    return "along the northwestern side of the Cape of Nordmaar";
}
 
string
long_descr()
{
    return "You are close to the northwestern coastline of the Cape of Nordmaar. " +
       "Verdant and thick with foliage, this jungle environment claims all " +
       "sorts of peculiar plant life whose stalks are so thick that the " +
       "adventurous traveller may find it next to impossible to set foot " +
       "on the ground. To your northwest stretches the vast Courrain Ocean.\n";
}