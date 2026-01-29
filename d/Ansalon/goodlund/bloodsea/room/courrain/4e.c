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
       "To the north beyond the mouth of the estuary is the vast Courrain Ocean, a sea " +
       "that borders all of northern Ansalon. Few have ventured far " +
       "from the sight of land when sailing this body of water, and " +
       "of those who have, none have returned.\n");
    add_item(({"coastline","estwilde","foothills","rugged foothills",
       "barren coastline","hills", "riverbanks","solamnia"}),
       "To your southwest is the grassy riverbank of the Vingaard River, while " +
       "to your east you can just make out the barren coastline of Estwilde.\n");
    add_item(({"estuary","river","vingaard river","mouth of estuary","riverbank"}),
       "Opening up before you is the great estuary of the longest " +
       "river in Krynn, the Vingaard River.\n");



    add_row_exit(TURBIDUS + "4zk", "northwest", "@@no_go", 1);
    add_row_exit(CROOM + "5e", "north", 0, 1);
    add_row_exit(CROOM + "3e", "south", 0, 1);
    add_row_exit(CROOM + "4f", "east", 0, 1);


    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    reset_courrain_room();

}

int
no_go()
{
    if(this_player()->query_wiz_level())
      return 0;

    if(TURBIDUS_OPEN)
      return 0;

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
    return "at the mouth of the Vingaard River";
}
 
string
long_descr()
{
    return "You are near the mouth of the Vingaard River, " +
       "close to the green riverbank on the Solamnia side of the " +
       "river. To your east " +
       "you can just make out the barren coastline of Estwilde.\n";

}