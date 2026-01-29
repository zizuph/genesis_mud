inherit "/d/Emerald/common/dir_room";
 
#include "/d/Emerald/defs.h"
#define DP(LABEL) ("@@dir_phrase|" + LABEL + "@@")
#define EAST GRAVEYARD_DIR + "pass3"
#define NW "/d/Emerlad/room/graveyard/pass1"
#define SOUTH GRAVEYARD_DIR + "cave2"
 
 
 
void
create_room()
{
    set_short("Tunnel");
    set_long( "You are standing in a rocky tunnel under the grave"+
        "yard. The main tunnel "+DP("dir")+" and a small passage"+
        " leads off to the south.\n" );
 
    add_dir_phrase("dir", EAST, "continues to the northwest");
    add_dir_phrase("dir", NW, "continues to the east");
    add_dir_phrase("dir", SOUTH, "runs northwest and east,");
    add_dir_phrase("dir", 0, "continues to the east");
 
    add_prop(ROOM_I_LIGHT,1);
    add_prop(ROOM_I_INSIDE,1);
 
    add_exit(GRAVEYARD_DIR + "pass1","northwest",0,1);
    add_exit(GRAVEYARD_DIR + "pass3","east",0,1);
    add_exit(GRAVEYARD_DIR + "pass4","south",0,1);
}
