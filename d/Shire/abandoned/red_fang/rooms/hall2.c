inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/red_fang/default.h"

/* Sarr */

void
create_room()
{
    ::create_room();
    set_short("Guild Hall");
    set_long("\n   You are in a stone corridor. The walls are damp and "+
    "cold, and it the air is filled with an earthly smell. The "+
    "torches on the walls cast a dim light around. To the south, "+
    "you see a crack of sunlight.\n\n");
    add_item("torches","The torches burn brightly.\n");
    add_item("walls","The walls are made of smoothened stone.\n");
    INSIDE;
    add_exit(FANG_DIR(rooms/hall3),"south",0,-1);
    add_exit(FANG_DIR(rooms/hall),"north",0,-1);
}

