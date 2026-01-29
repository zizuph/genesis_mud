inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */

void
create_room()
{
    ::create_room();
    set_short("On the road of Farmer's Way");
    set_long("You are still on the Farmer's Way road and "+
    "you cough up dust from all the horses and carts that farmers push "+
    "through here to the market and caravan district. A small, well-"+
    "paved road branches off here to the north into the noble district. "+
    "You are now getting closer "+
    "to End street, the most western street of Kabal that runs the "+
    "full vertical length of the west side of Kabal. "+
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
    add_exit(NOBLE(farmer/s10),"west",0,0,0);
    add_exit(NOBLE(farmer/s8),"east",0,0,0);
    add_exit(NOBLE(road/r8),"north",0,0,-1);
}

