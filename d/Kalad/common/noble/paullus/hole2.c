inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

void
create_room()
{
    set_short("In a secret passageway in the House of Paullus");
    set_long("You are in a tight passageway. The latter continues "+
    "down into darkness, while you can climb back up to fresh air.\n");
    add_item("latter","An iron, rusty latter leading down and up.\n");
    
    INSIDE;
    add_prop(ROOM_I_LIGHT,0);
    
    add_exit(NOBLE(paullus/hole1),"up",0,-1,-1);
    add_exit(NOBLE(paullus/hole3),"down",0,-1,-1);
}

