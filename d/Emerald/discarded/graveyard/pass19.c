inherit "/d/Emerald/std/dir_room";
 
#include "/d/Emerald/defs.h"
 
#define DP(LABEL) ("@@dir_phrase|" + LABEL + "@@")
 
#define SOUTHWEST GRAVEYARD_DIR + "pass18"
#define NORTH     GRAVEYARD_DIR + "cave10"
 
 
void
create_room()
{
    set_short("Tunnel");
    set_long( "You have entered a roughly carved passageway that"+
        " continues to the "+DP("dir")+".\n" );
 
    add_dir_phrase("dir", SOUTHWEST, "north");
    add_dir_phrase("dir", NORTH    , "southwest");
    add_dir_phrase("dir", 0        , "north");
 
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
 
    add_exit(GRAVEYARD_DIR + "cave10","north",0,1);
    add_exit(GRAVEYARD_DIR + "pass18","southwest",0,1);
}
