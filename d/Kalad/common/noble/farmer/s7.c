inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */

void
create_room()
{
    ::create_room();
    set_short("On the road of Farmer's Way");
    set_long("You are now on the dusty road known as Farmer's way. "+
    "All around you, many farmers push their carts back and forth "+
    "through here to the market and caravan district. The noise "+
    "from all the comotion is very great, and you feel like a lost "+
    "child in all this chaos. You are now just west to the "+
    "intersection of Farmer and Market, and you notice much of the "+
    "noise comes from the market district to the south. "+
    "The eternal, blazing Kaladian sun "+
    "beams down on you, making you sweat a little.\n");
    hear_bell = 2;
    add_item("road","Many branch off at the intersection to your west.\n");
    add_item("intersection","It is just off to your west, and you see "+
    "four other roads coming off of it.\n");
    add_item("farmers","They move about you pushing their carts "+
    "along the road.\n");
    add_item("carts","They are wooden carts filled with fruits and "+
    "vegtables off all types.\n");
    add_item("sun","It is making you hot.\n");
    add_item("road","The road is make of stone and dirt and looks "+
    "worn down.\n");
    add_exit(NOBLE(farmer-market),"east",0,0,0);
    add_exit(NOBLE(farmer/s8),"west",0,0,0);
}

