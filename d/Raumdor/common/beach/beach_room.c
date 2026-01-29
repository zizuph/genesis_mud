#include "defs.h"
inherit STD_ROOM;
inherit COMMON_LIB_DIR + "carvings";

mapping yGrid = ([
    "beach2": 1,
    "beach1": 0,
    "beach3": -1,
]);

void
create_room()
{
    add_prop(ROOM_I_TYPE, ROOM_BEACH);
    ::create_room();
    add_item(
      ({"sea","water"}), "The sea is calm. The wind gently rolls the waves.\n");
    add_item("waves", "The waves lap in slowly.\n");
    add_item("carvings", "@@carvings_description@@"); 
    add_item(({"blocks", "stone blocks"}),
      "The stone blocks are in good condition for being seaside. Although " +
      "easy to miss on first glance, they are covered in carvings.\n");
}

int *
query_coordinates()
{
    string room = extract(MASTER_OB(TO), strlen(BEACH_DIR));
    return ({0, yGrid[room], 0});
}
