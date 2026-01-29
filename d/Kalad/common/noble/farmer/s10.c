inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */

void
create_room()
{
    ::create_room();
    set_short("On the road of Farmer's Way");
    set_long("You are on Farmer's way in Kabal. All around you, "+
    "farmers and their carts move "+
    "through here to the market and caravan district. You are just "+
    "east of the End and Farmer's Way intersection, and the great "+
    "western gate. "+
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
    add_exit(NOBLE(farmer-end),"west",0,0,0);
    add_exit(NOBLE(farmer/s9),"east",0,0,0);
}

