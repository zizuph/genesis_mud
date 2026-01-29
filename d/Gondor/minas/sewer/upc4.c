inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

object  door;

void
create_room() 
{
    set_short("A narrow staircase");
    set_long(BSN(
        "This is a narrow staircase hewn into the vast pier of rock "
      + "whose huge out-thrust bulk divides into all circles of the "
      + "city save the first. A flight of stairs is leading down "
      + "into the sewers under the city."));

    add_exit(MINAS_DIR + "sewer/stairc4", "down", 0, 0);

    add_item(({"stairs", "steps", "flight of stairs", }), BSN(
        "A narrow flight of stairs is leading down into the sewers. "
      + "The stone steps run alongside the southern wall of the "
      + "staircase."));

    add_item(({"wall","walls"}), BSN(
        "The walls were hewn from the living rock of the huge "
      + "cliff dividing the circles of the city."));

    door = clone_object(MINAS_DIR + "doors/sewer-c4-in");
    door->move(TO);

    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, "@@query_door@@");
}

int
query_door()
{
    if (!objectp(door))
        return -2;

    if (door->query_open())
        return 1;

    return 0;
}
