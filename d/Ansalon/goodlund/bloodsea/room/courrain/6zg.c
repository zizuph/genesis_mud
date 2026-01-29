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

    add_item(({"karthay","coastline", "isle of karthay","isle","island"}),
               "Just visible to the eye, you " +
               "can make out the coastline of the isle of Karthay to your east.\n");

    add_row_exit(CROOM + "6zf", "west", 0, 1);
    add_row_exit(CROOM + "7zg", "north", 0, 1);
    add_row_exit(BROOM + "9s", "east", 0, 1);
    add_row_exit(CROOM + "5zg", "south", 0, 1);


    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    reset_courrain_room();

}

int
no_go()
{
    write("You try and sail in that direction, however the current and wind created by a " +
       "mighty storm agressively drives you back!\n");
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
    return courrain_short()+ ", near the isle of Karthay";
}
 
string
long_descr()
{
    return courrain_desc()+ "\n";
}