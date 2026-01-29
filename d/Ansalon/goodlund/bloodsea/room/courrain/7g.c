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
       "that borders all of northern Ansalon. Few have ventured far " +
       "from the sight of land when sailing this body of water, and " +
       "of those who have, none have returned.\n");
    add_item(({"coastline","estwilde","foothills","rugged foothills","barren coastline"}),
       "To your southeast you can just make out the barren coastline of " +
       "Estwilde. Little of interest can be seen beyond the coastline, " +
       "except rugged foothills that span out into the distance.\n");


    add_row_exit(CROOM + "7f", "west", 0, 1);
    add_row_exit(CROOM + "8g", "north", 0, 1);
    add_row_exit(CROOM + "7h", "east", 0, 1);
    add_row_exit(CROOM + "6g", "south", 0, 1);


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
    return courrain_short()+ ", in sight of the coastline of Estwilde";
}
 
string
long_descr()
{
    return courrain_desc()+ "To your southeast you can just make out " +
      "the coastline of Estwilde.\n";

}