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
    add_item(({"coastline","estwilde","foothills","rugged foothills",
       "barren coastline","bay","mainland","unsheltered bay","hills"}),
       "You find yourself in a bay on the edge of the barren coastline " +
       "of Estwilde. The rugged foothills that you can just make out " +
       "on the horizon do little to calm the winds that blow towards " +
       "you from the mainland.\n");



    add_row_exit(CROOM + "7h", "west", 0, 1);
    add_row_exit(CROOM + "8i", "north", 0, 1);
    add_row_exit(CROOM + "7j", "east", 0, 1);
    add_row_exit(CROOM + "6i", "south", 0, 1);


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
    return courrain_short()+ ", near the coastline of Estwilde";
}
 
string
long_descr()
{
    return courrain_desc()+ " You find yourself in a bay just off the coastline " +
       "of Estwilde. You notice that the distant hills do little to " +
       "block the strong winds that blow off the mainland.\n";

}