inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */


void
create_room()
{
    set_short("In the hall");
    set_long("You are in a stairwell in the house of Alexander. The "+
        "stairs lead down into the main floor. The walls around you " +
        "gleam from the black wood that dominates this house. The main "+
        "hub is to the south.\n");
    add_item("walls","They are polished very well.\n");
    
    INSIDE;
    
    add_exit(NOBLE(alexander/m17),"south",0,-1,0);
    add_exit(NOBLE(alexander/m4),"down",0,-1,0);
}
