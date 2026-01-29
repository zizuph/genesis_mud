inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */


void
create_room()
{
    set_short("In a stairwell in the House of Alexander");
    set_long("You stand in a small stairwell. The stairs here "+
    "are made of black oak, and spiral upwards to the upper "+
    "level of this grand estate. A small window here lets "+
    "in some light.\n");
  
    add_item("window","Through the window, you see the noble district "+
    "streets.\n");
    add_item("stairs","The stairs are sturdy.\n");

    INSIDE;

    add_exit(NOBLE(alexander/m1),"southwest",0,-1,0);
    add_exit(NOBLE(alexander/m8),"east",0,-1,0);
    add_exit(NOBLE(alexander/m5),"south",0,-1,0);
    add_exit(NOBLE(alexander/m14),"up",0,-1,0);
}
