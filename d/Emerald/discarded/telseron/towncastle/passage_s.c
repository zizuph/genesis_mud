inherit "/std/room";
 
#include "default.h"
 
void
create_room()
{
    set_short("Secret passage");
    set_long( "The passage leads northwards from here. A ladder "+
	     "is leading up to something that looks like a landing of sorts. "+
	     "There are no indication of anyone passing this way for a long "+
	     "time.\n" );
 
    add_item("ladder", "It is made of wood and bolted to the wall.\n");
    add_item("landing", "It is almost impossible to make out from here.\n");
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_exit(TCASTLE_DIR + "passage_w", "north", 0);
    add_exit(TCASTLE_DIR + "landing", "up", 0);
}
