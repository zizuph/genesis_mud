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
       "Expanding out before you is the vast Courrain Ocean, a sea " +
       "that borders all of eastern Ansalon. Few have ventured far " +
       "from the sight of land when sailing this body of water, and " +
       "of those who have, none have returned.\n");
    add_item(({"currents","bloodsea"}),
       "Here the Bloodsea meets with the Courrain Ocean, making this " +
       "area particularly trecherous for seafarers.\n");
    add_item(({"karthay","coastline", "isle of karthay","isle","island", 
               "karthay peninsula", "peninsula"}),
               "You are at the western-most point of the isle of Karthay, " +
               "where rocky cliffs are punished by the waters of the " +
               "Courrain Ocean and the Bloodsea of Istar.\n");
    add_item(({"cliffs","steep cliffs"}), "Here the coastline of Karthay is nothing " +
               "but steep cliffs, an impossible location for ships to land without " +
               "risk of being battered against their unforgiving rocky face.\n");

    add_row_exit(CROOM + "7zf", "west", 0, 1);
    add_row_exit(CROOM + "xx", "north", "@@no_go");
    add_row_exit(CROOM + "xx", "northeast", "@@no_go");
    add_row_exit(BROOM + "9s", "southeast", 0, 1);
    add_row_exit(CROOM + "6zg", "south", 0, 1);


    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    reset_courrain_room();

}

int
no_go()
{
    write("A great storm blows from around the other side of the isle of Karthay. " +
          "Your ship will not be able to sail in that direction without sinking!\n");
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
    return courrain_short()+ ", west of Karthay peninsula";
}
 
string
long_descr()
{
    return "You are at the western edge of Karthay peninsula. " +
           "Here the currents of the Bloodsea meet the " +
           "Northern Courrain Ocean, making the waters here " +
           "particularly rough. " +courrain_desc()+ "\n";
}