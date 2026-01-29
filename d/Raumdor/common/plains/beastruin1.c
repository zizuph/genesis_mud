#include "defs.h"
inherit STD_ROOM;

void
create_room()
{
    ::create_room();
    set_short("A small ruin");
    set_long("You are at a small ruin just off the main road in "+
    "the bleak plains of Raumdor. Around you, broken shards of blocks "+
    "of stone are scattered. Hills stretch further everywhere, and "+
    "you can see a city to the northeast far away.\n");
    add_item(({"stones","blocks"}),"The blocks of stones are large and old "+
    "looking. Due to the circle shape, it must have been an old "+
    "tower of some sort. In the very center, partialy obscured "+
    "by the falling blocks, you see a dark opening.\n");
    add_item("opening","It looks big enough for you to go down.\n");
    add_item("road","It is old and worn, made of dirt and stone.\n");
    add_item("plains","They stretch all around you, save to the "+
    "northwest, where it meets the Kolpharian and Worldsrim mountains. "+
    "You can see a city to the south and east of you.\n");
    add_item("hills","They roll on for as far as you can see.\n");
    add_item("city","It is a large walled city.\n");
    add_exit(ROAD_DIR + "road11","southeast");
    add_exit(MAZE_DIR + "cave_entrance","north");
    add_exit(PLAINS_DIR + "beastruin2","down");
}

int *
query_coordinates()
{
    return ({52, -1, 0});
}
