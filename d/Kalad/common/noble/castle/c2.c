// Sarr,
// Recoded by Fysix, March 1998
#include "default.h"

inherit NOBLE_ROOM;

object *guard = allocate(2);

void reset_room();

void
create_noble_room()
{
    set_short("In a hall of the Castle of the High-Lord");
    INSIDE;
    set_long("You stand in the entrance hall of the Castle of the "+
        "High-Lord. The ground is covered with a red carpet, and the "+
        "north wall has windows letting in light. The grand doors lead "+
        "out north, while the hall contines to the east and west. To "+
        "the south, a large room opens up.\n");

    add_exit(NOBLE + "castle/c1", "west", 0, 0);
    add_exit(NOBLE + "castle/c3", "east", 0, 0);
    add_exit(NOBLE + "castle/c6", "south", 0, 0);

    clone_object(NOBLE + "castle/door2")->move(TO);

    reset_room();
}

void
reset_room()
{
    guard = clone_npcs(guard, NOBLE + "npc/castle_guard");
    guard[0]->team_join(guard[1]);
}
