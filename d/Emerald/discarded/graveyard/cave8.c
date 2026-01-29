inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
 
void
create_room()
{
    set_short("Lit cave");
    set_long( "This is a small rocky cave, lit by a thin shaft"+
        " of light that comes from a small hole in the roof.\n" );
 
    add_item("light", "A narrow beam of light, let in by a small "+
        "hole in the cave roof.\n" );
    add_item("hole", "It's a small hole that is letting some "+
        "light into the cave.\n" );
 
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,1);
 
    add_exit(GRAVEYARD_DIR + "pass3","northwest",0,1);
    add_exit(GRAVEYARD_DIR + "pass13","southeast",0,1);
    add_exit(GRAVEYARD_DIR + "pass12","northeast",0,1);
}
