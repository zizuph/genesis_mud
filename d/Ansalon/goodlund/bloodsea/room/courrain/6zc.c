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
    add_item(({"island","saifhum"}),
       "To your south lies the island of Saifhum, the home of the sea " +
       "barbarians. You notice the waters to the south ripple considerably, " +
       "indicating an extensive underwater reef surrounding the northern " +
       "part of the island.\n");
    add_item(({"reef","underwater reef"}),
       "It seems like an underwater reef runs around the northern side " +
       "of the island of Saifhum, effectively blocking ships from sailing " +
       "to that part of the island.\n");

    add_row_exit(CROOM + "6zb", "west", 0, 1);
    add_row_exit(CROOM + "7zc", "north", 0, 1);
    add_row_exit(CROOM + "6zd", "east", 0, 1);
    add_row_exit(CROOM + "6zc", "south", "@@no_go_saifhum");


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
    return courrain_short()+ ", in sight of the island of Saifhum";
}
 
string
long_descr()
{
    return courrain_desc()+ "To your south you can just make " +
      "out the island of Saifhum.\n";
}