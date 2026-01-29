inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
 
void
create_room()
{
    set_short("Small cave");
    set_long( "This is a small, rough walled cave. Scattered on the "+
        "floor are bones, most seem to be elven or human, and all are "+
        "stripped of flesh. A rough tunnel leads north into the darkness"+
        ", but you feel uneasy about going that way.\n" );
 
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
 
    add_item("bones", "The bones seemed to have had all their "+
       "flesh removed by someone, or something. Studying them closely, you also"+
       " notice that some have been partially crushed.\n" );
 
    add_exit(GRAVEYARD_DIR + "junction","south",0,1);
    add_exit(GRAVEYARD_DIR + "pass18","north",0,1);
}
