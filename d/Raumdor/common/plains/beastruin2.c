#include "defs.h"
inherit STD_ROOM;

void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    ::create_room();
    set_short("An old ruin");
    set_long("As you clamber down into the darkness, you are overcome "+
    "with a feeling of great despair. The air seems to get colder, and "+
    "your pulse quickens. There is a set of old stairs here leading "+
    "down into darkness. The hole in the ceiling here is where you "+
    "came in through.\n");
    add_item("hole","Through the hole you can see daylight.\n");
    add_item(({"stairs"}),"They lead down into darkness.\n");
    add_exit(DUNGEON_DIR + "dungeon10","down",0);
    add_exit(PLAINS_DIR + "beastruin1","up",0,1);
}

int *
query_coordinates()
{
    return ({52, -1, -1});
}

