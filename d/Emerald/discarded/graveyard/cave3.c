inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
 
void
create_room()
{
    set_short("Cave");
    set_long( "You are in a small cave. To the north the cave "+
        "looks to open up, passages lead northwest and east.\n" );
 
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
 
    add_exit(GRAVEYARD_DIR + "pass5","northwest",0,1);
    add_exit(GRAVEYARD_DIR + "cave4","north",0,1);
    add_exit(GRAVEYARD_DIR + "pass6","east",0,1);
}
