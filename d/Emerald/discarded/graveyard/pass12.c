inherit "/d/Emerald/std/dir_room";
 
#include "/d/Emerald/defs.h"
#define DP(LABEL) ("@@dir_phrase|" + LABEL + "@@")
 
#define SOUTHWEST GRAVEYARD_DIR + "cave8"
#define EAST GRAVEYARD_DIR + "pass15"
 
void
create_room()
{
    set_short("Dark passage");
    set_long( "You have entered a dark passage which continues"+
        " to the "+DP("dir")+" you there is a shaft of light, "+
        "illuminating a small cave.\n" );
 
    add_dir_phrase("dir", SOUTHWEST,"east. Behind");
    add_dir_phrase("dir", EAST,"southwest. Ahead of");
    add_dir_phrase("dir", 0,"east. Behind");
 
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
 
    add_exit(GRAVEYARD_DIR + "cave8","southwest",0,1);
    add_exit(GRAVEYARD_DIR + "pass15","east",0,1);
}
