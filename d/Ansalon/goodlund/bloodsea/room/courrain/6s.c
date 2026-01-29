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
    add_item(({"nordmaar","kingdom","kingdom of nordmaar","coastline"}),
       "To your southwest you can make out the rugged coastline of " +
       "Nordmaar, the home of the horse barbarians. Examing the coastline " +
       "closely, you can also make out a small port.\n");
    add_item(({"port","small port","jennison","smoke","fire","blaze"}),
       "Along the coastline to your south you can just make out the small " +
       "Nordmaarian port of Jennison. Disturbingly, smoke billows up from " +
       "the port, and you notice small specks in the sky above it that look " +
       "suspiciously like dragons!\n");
    add_item(({"specks","small specks","dragons","red dragons"}),
       "From this distance it is hard to make out what flies above the port " +
       "of Jennison... they look suspiciously like red dragons!\n");


    add_row_exit(CROOM + "6r", "west", 0, 1);
    add_row_exit(CROOM + "7s", "north", 0, 1);
    add_row_exit(CROOM + "6t", "east", 0, 1);
    add_row_exit(CROOM + "5s", "south", 0, 1);


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
    return courrain_short()+ ", near the coastline of Nordmaar";
}
 
string
long_descr()
{
    return courrain_desc()+ "To your west you can just make out " +
      "the coastline of Nordmaar.\n";
}