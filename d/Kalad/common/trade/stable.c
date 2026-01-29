inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

void
create_room()
{
    set_short("Stable of Kabal");
    set_long("You are now in foul smelling room. This appears to be "+
    "a stable of some sort. There are many stalls lining the room, "+
    "and the ground is covered in hay. Buckets of water and oats "+
    "are placed on the ground, and on a rack against the wall "+
    "is some riding equipment.\n");
    add_item("stalls","When you look in them, you find them empty.\n");
    add_item("hay","Old straw hay, its very dirty and smelly.\n");
    add_item("buckets","A couple buckets filled with water and oats.\n");
    add_item("riding equipment","Saddles and the like.\n");
    INSIDE;
    add_exit(TRADE(ts2),"east",0,0,1);
    clone_object(TRADE(horse))->move(TO);
}

