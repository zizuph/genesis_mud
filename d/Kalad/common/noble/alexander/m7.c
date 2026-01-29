inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */


void
create_room()
{
    set_short("In a hallway of the House of Alexander");
    set_long("You find yourself at a bend in this small "+
    "hallway. The walls here are bare, but there is a small "+
    "black statue against the wall. You can hear sounds of "+
    "dining to the northeast.\n");

    add_item("statue","A statue made out of black marble. It is "+
    "shaped like a giant snake, emerging out of the ground, "+
    "with its mouth open in a silent hiss.\n");

    INSIDE;

    add_exit(NOBLE(alexander/m3),"northwest",0,-1,0);
    add_exit(NOBLE(alexander/m10),"northeast",0,-1,0);
}
