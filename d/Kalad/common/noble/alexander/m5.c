inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */


void
create_room()
{
    set_short("In a short hall");
    set_long("You are in a short hall. The floor beneath you is "+
    "stained with dark spots. You can smell something good to "+
    "east.\n");
  
    add_item("spots","They are odd dark spots, you are not sure from "+
    "what.\n");
    INSIDE;

    add_exit(NOBLE(alexander/m4),"north",0,-1,0);
    add_exit(NOBLE(alexander/m8),"northeast",0,-1,0);
    add_exit(NOBLE(alexander/m9),"east",0,-1,0);
    add_exit(NOBLE(alexander/m6),"south",0,-1,0);
    add_exit(NOBLE(alexander/m1),"west",0,-1,0);
}
