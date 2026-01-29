inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/red_fang/default.h"
#pragma save_binary
#pragma strict_types
/* Sarr */

void
create_room()
{
    ::create_room();
    set_short("Guild Hall");
    set_long("\n   You are in a stone corridor. The walls have torches on "+
    "them, casting light in this otherwise dark and dismal place.\n"+
    "   To the west, you see the Red Fang's message sending service. "+
    "And to the east, is the sleeping quarters. The hall continues "+
    "to the south.\n\n");
    add_item("torches","The torches are well tended and burn brightly.\n");
    add_item("walls","The walls are made of smoothened stone.\n");
    INSIDE;
    add_exit(FANG_DIR(rooms/hall2),"south",0,-1);
    add_exit(FANG_DIR(rooms/po),"west",0,-1);
    add_exit(FANG_DIR(rooms/start),"east",0,-1);
    add_exit(FANG_DIR(rooms/joinroom),"north",0,-1);
}

